#pragma once

#include <Windows.h>
#include <shellapi.h>
#include <wininet.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <filesystem>
#include <cctype>
#include <ctime>
#include <atomic>
#include <thread>
#include <chrono>
#include <vector>
#include "dependencies/json.hpp"

#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "shell32.lib")

using json = nlohmann::json;

// KeyAuth app credentials (API 1.3 — client does not use the app secret)
namespace KeyAuthConfig
{
	constexpr const char* NAME = "Dkex";
	constexpr const char* OWNER_ID = "dvcf1EcOCE";
	constexpr const char* VERSION = "1.0";
	constexpr const char* API_URL = "https://keyauth.win/api/1.3/";
	constexpr const char* LICENSE_FILE = "license.json";
}

namespace KeyAuth
{
	inline std::string sessionId;
	inline std::string lastMessage;
	inline bool authenticated = false;
	inline long long expiryUnix = 0;
	inline std::string username;
	inline std::string role = "default"; // Owner / CoOwner / Staff / default
	inline int roleLevel = 1;
	inline std::vector<std::string> subscriptions;
	inline std::atomic<bool> countdownRunning{ false };
	inline std::thread countdownThread;

	inline std::string NormalizeRole(std::string s)
	{
		for (char& c : s)
			c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
		// strip spaces/hyphens
		std::string out;
		out.reserve(s.size());
		for (char c : s)
		{
			if (c != ' ' && c != '-' && c != '_')
				out.push_back(c);
		}
		return out;
	}

	// Matches KeyAuth levels: Owner=5, CoOwner=4, Staff=3, default=1
	inline int RankRole(const std::string& s)
	{
		const std::string l = NormalizeRole(s);
		if (l.empty() || l == "default" || l == "user" || l == "member")
			return 1;
		// CoOwner before Owner (substring overlap)
		if (l.find("coowner") != std::string::npos || l == "coown" || l == "co")
			return 4;
		if (l.find("owner") != std::string::npos || l.find("admin") != std::string::npos || l == "5")
			return 5;
		if (l.find("staff") != std::string::npos || l.find("mod") != std::string::npos || l == "3")
			return 3;
		if (l.find("vip") != std::string::npos || l.find("premium") != std::string::npos || l == "2")
			return 2;
		// Exact legacy names
		if (l == "owner" || l == "admin") return 5;
		if (l == "coowner") return 4;
		if (l == "staff" || l == "moderator") return 3;
		return 1;
	}

	inline bool IsOwner() { return roleLevel >= 5; }
	inline bool IsCoOwner() { return roleLevel >= 4; }
	inline bool IsStaff() { return roleLevel >= 3; }

	inline std::string SubNameFromJson(const json& sub)
	{
		// KeyAuth uses "subscription"; some panels use "name"
		if (sub.contains("subscription") && sub["subscription"].is_string())
			return sub["subscription"].get<std::string>();
		if (sub.contains("name") && sub["name"].is_string())
			return sub["name"].get<std::string>();
		if (sub.is_string())
			return sub.get<std::string>();
		return {};
	}

	inline void ApplyBestRole()
	{
		int best = 0;
		std::string bestName = "default";
		for (const auto& sub : subscriptions)
		{
			const int r = RankRole(sub);
			if (r > best)
			{
				best = r;
				bestName = sub;
			}
		}
		role = bestName;
		roleLevel = best > 0 ? best : 1;
	}

	inline void ParseUserInfo(const json& j)
	{
		username.clear();
		subscriptions.clear();
		role = "default";
		roleLevel = 1;
		expiryUnix = 0;

		if (!j.contains("info") || !j["info"].is_object())
			return;

		const json& info = j["info"];
		username = info.value("username", "");

		if (info.contains("subscriptions") && info["subscriptions"].is_array())
		{
			for (const auto& sub : info["subscriptions"])
			{
				const std::string name = SubNameFromJson(sub);
				if (!name.empty())
					subscriptions.push_back(name);

				long long exp = 0;
				try
				{
					if (sub.is_object() && sub.contains("expiry"))
					{
						if (sub["expiry"].is_string())
							exp = std::stoll(sub["expiry"].get<std::string>());
						else if (sub["expiry"].is_number_integer())
							exp = sub["expiry"].get<long long>();
						else if (sub["expiry"].is_number_unsigned())
							exp = static_cast<long long>(sub["expiry"].get<unsigned long long>());
					}
				}
				catch (...) {}

				if (exp > expiryUnix)
					expiryUnix = exp;
			}
		}

		// Some KeyAuth setups put role on the user / license itself
		if (info.contains("subscriptions") == false || subscriptions.empty())
		{
			if (info.contains("subscription") && info["subscription"].is_string())
				subscriptions.push_back(info["subscription"].get<std::string>());
		}

		ApplyBestRole();
	}

	inline std::string UrlEncode(const std::string& value)
	{
		std::ostringstream escaped;
		escaped.fill('0');
		escaped << std::hex;

		for (unsigned char c : value)
		{
			if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
			{
				escaped << c;
			}
			else
			{
				escaped << '%' << std::uppercase << std::setw(2) << int(c) << std::nouppercase;
			}
		}

		return escaped.str();
	}

	inline std::string GetHwid()
	{
		// KeyAuth app settings require HWID length >= 20.
		DWORD serial = 0;
		GetVolumeInformationA("C:\\", nullptr, 0, &serial, nullptr, nullptr, nullptr, 0);

		char computerName[MAX_COMPUTERNAME_LENGTH + 1]{};
		DWORD computerSize = MAX_COMPUTERNAME_LENGTH + 1;
		GetComputerNameA(computerName, &computerSize);

		char userName[256]{};
		DWORD userSize = 256;
		GetUserNameA(userName, &userSize);

		const std::string raw =
			std::string(computerName) + "|" +
			std::string(userName) + "|" +
			std::to_string(serial) + "|Dkex";

		unsigned long long hash1 = 14695981039346656037ull;
		for (unsigned char c : raw)
		{
			hash1 ^= c;
			hash1 *= 1099511628211ull;
		}

		unsigned long long hash2 = 0xcbf29ce484222325ull ^ serial;
		for (unsigned char c : raw)
			hash2 = (hash2 * 131ull) + c;

		std::ostringstream oss;
		oss << std::hex << std::nouppercase << std::setfill('0')
			<< std::setw(16) << hash1
			<< std::setw(16) << hash2
			<< std::setw(8) << serial;
		return oss.str(); // always 40 hex chars
	}

	inline std::string HttpPost(const std::string& body)
	{
		std::string result;

		HINTERNET hInternet = InternetOpenA(
			"DkExternal/1.0",
			INTERNET_OPEN_TYPE_PRECONFIG,
			nullptr,
			nullptr,
			0);

		if (!hInternet)
			return result;

		URL_COMPONENTSA comps{};
		comps.dwStructSize = sizeof(comps);
		char host[256]{};
		char path[1024]{};
		comps.lpszHostName = host;
		comps.dwHostNameLength = sizeof(host);
		comps.lpszUrlPath = path;
		comps.dwUrlPathLength = sizeof(path);

		if (!InternetCrackUrlA(KeyAuthConfig::API_URL, 0, 0, &comps))
		{
			InternetCloseHandle(hInternet);
			return result;
		}

		HINTERNET hConnect = InternetConnectA(
			hInternet,
			comps.lpszHostName,
			comps.nPort ? comps.nPort : INTERNET_DEFAULT_HTTPS_PORT,
			nullptr,
			nullptr,
			INTERNET_SERVICE_HTTP,
			0,
			0);

		if (!hConnect)
		{
			InternetCloseHandle(hInternet);
			return result;
		}

		const char* acceptTypes[] = { "*/*", nullptr };
		HINTERNET hRequest = HttpOpenRequestA(
			hConnect,
			"POST",
			comps.lpszUrlPath,
			nullptr,
			nullptr,
			acceptTypes,
			INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE | INTERNET_FLAG_NO_CACHE_WRITE,
			0);

		if (!hRequest)
		{
			InternetCloseHandle(hConnect);
			InternetCloseHandle(hInternet);
			return result;
		}

		const char* headers = "Content-Type: application/x-www-form-urlencoded\r\n";
		BOOL sent = HttpSendRequestA(
			hRequest,
			headers,
			static_cast<DWORD>(strlen(headers)),
			(LPVOID)body.data(),
			static_cast<DWORD>(body.size()));

		if (sent)
		{
			char buffer[4096];
			DWORD bytesRead = 0;
			while (InternetReadFile(hRequest, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0)
			{
				result.append(buffer, bytesRead);
				bytesRead = 0;
			}
		}

		InternetCloseHandle(hRequest);
		InternetCloseHandle(hConnect);
		InternetCloseHandle(hInternet);
		return result;
	}

	inline bool Init()
	{
		authenticated = false;
		sessionId.clear();
		lastMessage.clear();

		std::ostringstream body;
		body << "type=init"
			<< "&ver=" << UrlEncode(KeyAuthConfig::VERSION)
			<< "&name=" << UrlEncode(KeyAuthConfig::NAME)
			<< "&ownerid=" << UrlEncode(KeyAuthConfig::OWNER_ID);

		const std::string response = HttpPost(body.str());
		if (response.empty())
		{
			lastMessage = "No response from KeyAuth (check internet).";
			return false;
		}

		if (response == "KeyAuth_Invalid")
		{
			lastMessage = "Invalid application credentials.";
			return false;
		}

		try
		{
			json j = json::parse(response);
			const bool success = j.value("success", false);
			lastMessage = j.value("message", "Unknown error");
			if (!success)
				return false;

			sessionId = j.value("sessionid", "");
			return !sessionId.empty();
		}
		catch (...)
		{
			lastMessage = "Failed to parse KeyAuth init response.";
			return false;
		}
	}

	inline std::string FormatRemaining(long long totalSeconds)
	{
		if (totalSeconds <= 0)
			return "EXPIRED";

		const long long days = totalSeconds / 86400;
		totalSeconds %= 86400;
		const long long hours = totalSeconds / 3600;
		totalSeconds %= 3600;
		const long long minutes = totalSeconds / 60;
		const long long seconds = totalSeconds % 60;

		std::ostringstream oss;
		if (days > 0)
			oss << days << "d ";
		oss << std::setfill('0')
			<< std::setw(2) << hours << "h "
			<< std::setw(2) << minutes << "m "
			<< std::setw(2) << seconds << "s";
		return oss.str();
	}

	inline long long SecondsLeft()
	{
		if (expiryUnix <= 0)
			return -1;
		return expiryUnix - static_cast<long long>(std::time(nullptr));
	}

	inline void WriteCountdownLine(const std::string& text)
	{
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (!hOut || hOut == INVALID_HANDLE_VALUE)
			return;

		CONSOLE_SCREEN_BUFFER_INFO csbi{};
		if (!GetConsoleScreenBufferInfo(hOut, &csbi))
			return;

		const COORD saved = csbi.dwCursorPosition;
		COORD home{ 0, 0 };
		SetConsoleCursorPosition(hOut, home);

		std::string line = text;
		if (line.size() < 79)
			line.append(79 - line.size(), ' ');
		else if (line.size() > 79)
			line.resize(79);

		DWORD written = 0;
		WriteConsoleA(hOut, line.c_str(), static_cast<DWORD>(line.size()), &written, nullptr);
		SetConsoleCursorPosition(hOut, saved);
	}

	inline void StopLiveCountdown()
	{
		countdownRunning = false;
		if (countdownThread.joinable())
			countdownThread.join();
	}

	inline void StartLiveCountdown()
	{
		StopLiveCountdown();

		if (expiryUnix <= 0)
		{
			std::cout << "Time left: unknown (no expiry on key)\n";
			return;
		}

		// Reserve top line for the live counter
		std::cout << "\n";
		WriteCountdownLine("Time left: " + FormatRemaining(SecondsLeft()));

		countdownRunning = true;
		countdownThread = std::thread([]()
		{
			while (countdownRunning)
			{
				const long long left = SecondsLeft();
				const std::string remaining = FormatRemaining(left);
				const std::string line = "Time left: " + remaining;

				WriteCountdownLine(line);
				SetConsoleTitleA(("Dk External | Time left: " + remaining).c_str());

				if (left <= 0)
				{
					WriteCountdownLine("Time left: EXPIRED");
					std::cout << "\n\nLicense expired. Exiting...\n";
					Sleep(2000);
					ExitProcess(1);
				}

				for (int i = 0; i < 10 && countdownRunning; ++i)
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		});
	}

	inline bool License(const std::string& key)
	{
		if (sessionId.empty())
		{
			lastMessage = "Not initialized.";
			return false;
		}

		std::ostringstream body;
		body << "type=license"
			<< "&key=" << UrlEncode(key)
			<< "&hwid=" << UrlEncode(GetHwid())
			<< "&sessionid=" << UrlEncode(sessionId)
			<< "&name=" << UrlEncode(KeyAuthConfig::NAME)
			<< "&ownerid=" << UrlEncode(KeyAuthConfig::OWNER_ID);

		const std::string response = HttpPost(body.str());
		if (response.empty())
		{
			lastMessage = "No response from KeyAuth (check internet).";
			return false;
		}

		try
		{
			json j = json::parse(response);
			authenticated = j.value("success", false);
			lastMessage = j.value("message", "Unknown error");
			if (authenticated)
				ParseUserInfo(j);
			return authenticated;
		}
		catch (...)
		{
			lastMessage = "Failed to parse KeyAuth license response.";
			authenticated = false;
			return false;
		}
	}

	inline std::string LoadSavedKey()
	{
		try
		{
			if (!std::filesystem::exists(KeyAuthConfig::LICENSE_FILE))
				return {};

			std::ifstream in(KeyAuthConfig::LICENSE_FILE);
			json j;
			in >> j;
			return j.value("key", "");
		}
		catch (...)
		{
			return {};
		}
	}

	inline void SaveKey(const std::string& key)
	{
		try
		{
			json j;
			j["key"] = key;
			std::ofstream out(KeyAuthConfig::LICENSE_FILE);
			out << j.dump(2);
		}
		catch (...)
		{
		}
	}

	inline void ClearSavedKey()
	{
		std::error_code ec;
		std::filesystem::remove(KeyAuthConfig::LICENSE_FILE, ec);
	}

	// Clears saved key, closes, and relaunches so the license prompt returns.
	inline void LogoutAndRestart()
	{
		ClearSavedKey();
		StopLiveCountdown();

		char path[MAX_PATH]{};
		GetModuleFileNameA(nullptr, path, MAX_PATH);

		ShellExecuteA(nullptr, "open", path, nullptr, nullptr, SW_SHOWNORMAL);
		ExitProcess(0);
	}

	// Returns true if authenticated. Blocks until success or user quits.
	inline bool PromptAndAuthenticate()
	{
		std::cout << "\nConnecting to KeyAuth...\n";

		if (!Init())
		{
			std::cout << "KeyAuth init failed: " << lastMessage << "\n";
			system("pause");
			return false;
		}

		const std::string savedKey = LoadSavedKey();
		if (!savedKey.empty())
		{
			std::cout << "Trying saved license...\n";
			if (License(savedKey))
			{
				std::cout << "License OK: " << lastMessage << "\n";
				StartLiveCountdown();
				return true;
			}

			std::cout << "Saved license failed: " << lastMessage << "\n";
			ClearSavedKey();

			// Session may be consumed; re-init before manual entry
			if (!Init())
			{
				std::cout << "KeyAuth re-init failed: " << lastMessage << "\n";
				system("pause");
				return false;
			}
		}

		for (int attempt = 0; attempt < 5; ++attempt)
		{
			std::cout << "\nEnter license key: ";
			std::string key;
			std::getline(std::cin, key);

			// trim
			while (!key.empty() && (key.back() == ' ' || key.back() == '\r' || key.back() == '\t'))
				key.pop_back();
			size_t start = 0;
			while (start < key.size() && (key[start] == ' ' || key[start] == '\t'))
				++start;
			key = key.substr(start);

			if (key.empty())
			{
				std::cout << "Key cannot be empty.\n";
				continue;
			}

			if (License(key))
			{
				std::cout << "License OK: " << lastMessage << "\n";
				SaveKey(key);
				StartLiveCountdown();
				return true;
			}

			std::cout << "License failed: " << lastMessage << "\n";

			if (!Init())
			{
				std::cout << "KeyAuth re-init failed: " << lastMessage << "\n";
				system("pause");
				return false;
			}
		}

		std::cout << "Too many failed attempts.\n";
		system("pause");
		return false;
	}
}
