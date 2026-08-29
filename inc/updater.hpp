#pragma once

#include <Windows.h>
#include <wininet.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include "dependencies/json.hpp"

#pragma comment(lib, "wininet.lib")

using json = nlohmann::json;

// Releases must use tags like v1.1.1 and attach an asset named UPDATE_ASSET_NAME.
namespace UpdaterConfig
{
	constexpr const char* APP_VERSION = "1.2.11";
	constexpr const char* GITHUB_OWNER = "Dezz0k";
	constexpr const char* GITHUB_REPO = "Dk-External";
	constexpr const char* UPDATE_ASSET_NAME = "DkExternal.exe";
}

namespace Updater
{
	enum class Result
	{
		Continue,
		ExitForUpdate,
		ExitBlocked
	};

	inline void FailPause(const std::string& message)
	{
		std::cout << message << "\n";
		system("pause");
	}

	inline DWORD HttpStatus(HINTERNET hUrl)
	{
		DWORD status = 0;
		DWORD statusSize = sizeof(status);
		HttpQueryInfoA(hUrl, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &status, &statusSize, nullptr);
		return status;
	}

	inline std::string HttpQueryHeader(HINTERNET hUrl, DWORD query)
	{
		char buf[2048]{};
		DWORD size = sizeof(buf);
		if (!HttpQueryInfoA(hUrl, query, buf, &size, nullptr))
			return {};
		return std::string(buf, size);
	}

	inline HINTERNET OpenUrl(HINTERNET hInternet, const std::string& url, const char* headers, DWORD extraFlags = 0)
	{
		return InternetOpenUrlA(
			hInternet,
			url.c_str(),
			headers,
			headers ? static_cast<DWORD>(strlen(headers)) : 0,
			INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE | INTERNET_FLAG_NO_CACHE_WRITE |
			INTERNET_FLAG_NO_UI | INTERNET_FLAG_KEEP_CONNECTION | extraFlags,
			0);
	}

	inline std::string HttpGet(const std::string& url)
	{
		std::string result;

		HINTERNET hInternet = InternetOpenA(
			"DkExternalUpdater/1.0",
			INTERNET_OPEN_TYPE_PRECONFIG,
			nullptr,
			nullptr,
			0);
		if (!hInternet)
			return result;

		const char* headers =
			"User-Agent: DkExternalUpdater/1.0\r\n"
			"Accept: application/vnd.github+json\r\n"
			"X-GitHub-Api-Version: 2022-11-28\r\n";

		HINTERNET hUrl = OpenUrl(hInternet, url, headers);
		if (!hUrl)
		{
			InternetCloseHandle(hInternet);
			return result;
		}

		char buffer[4096];
		DWORD bytesRead = 0;
		while (InternetReadFile(hUrl, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0)
		{
			result.append(buffer, bytesRead);
			bytesRead = 0;
		}

		InternetCloseHandle(hUrl);
		InternetCloseHandle(hInternet);
		return result;
	}

	inline bool IsValidPeFile(const std::filesystem::path& path)
	{
		std::ifstream in(path, std::ios::binary);
		if (!in.is_open())
			return false;
		char magic[2]{};
		in.read(magic, 2);
		return in.gcount() == 2 && magic[0] == 'M' && magic[1] == 'Z';
	}

	inline bool HttpDownloadFile(const std::string& url, const std::filesystem::path& outPath)
	{
		HINTERNET hInternet = InternetOpenA(
			"DkExternalUpdater/1.0",
			INTERNET_OPEN_TYPE_PRECONFIG,
			nullptr,
			nullptr,
			0);
		if (!hInternet)
			return false;

		std::string current = url;
		HINTERNET hUrl = nullptr;
		for (int hop = 0; hop < 8; ++hop)
		{
			const char* headers =
				"User-Agent: DkExternalUpdater/1.0\r\n"
				"Accept: application/octet-stream\r\n";

			hUrl = OpenUrl(hInternet, current, headers, INTERNET_FLAG_NO_AUTO_REDIRECT);
			if (!hUrl)
				break;

			const DWORD status = HttpStatus(hUrl);
			if (status == 301 || status == 302 || status == 303 || status == 307 || status == 308)
			{
				std::string loc = HttpQueryHeader(hUrl, HTTP_QUERY_LOCATION);
				InternetCloseHandle(hUrl);
				hUrl = nullptr;
				if (loc.empty())
					break;
				current = loc;
				continue;
			}

			if (status != 0 && status != 200)
			{
				InternetCloseHandle(hUrl);
				hUrl = nullptr;
				break;
			}

			break;
		}

		if (!hUrl)
		{
			InternetCloseHandle(hInternet);
			return false;
		}

		std::error_code ec;
		std::filesystem::remove(outPath, ec);

		std::ofstream out(outPath, std::ios::binary | std::ios::trunc);
		if (!out.is_open())
		{
			InternetCloseHandle(hUrl);
			InternetCloseHandle(hInternet);
			return false;
		}

		char buffer[8192];
		DWORD bytesRead = 0;
		bool ok = false;
		while (InternetReadFile(hUrl, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0)
		{
			out.write(buffer, static_cast<std::streamsize>(bytesRead));
			ok = true;
			bytesRead = 0;
		}

		out.close();
		InternetCloseHandle(hUrl);
		InternetCloseHandle(hInternet);

		if (!ok || !std::filesystem::exists(outPath) || std::filesystem::file_size(outPath) < 64 || !IsValidPeFile(outPath))
		{
			std::filesystem::remove(outPath, ec);
			return false;
		}
		return true;
	}

	inline std::vector<int> ParseVersion(std::string version)
	{
		if (!version.empty() && (version[0] == 'v' || version[0] == 'V'))
			version.erase(version.begin());

		std::vector<int> parts;
		std::stringstream ss(version);
		std::string item;
		while (std::getline(ss, item, '.'))
		{
			try { parts.push_back(std::stoi(item)); }
			catch (...) { parts.push_back(0); }
		}
		while (parts.size() < 3)
			parts.push_back(0);
		return parts;
	}

	inline bool IsRemoteNewer(const std::string& remoteVersion, const std::string& localVersion)
	{
		auto remote = ParseVersion(remoteVersion);
		auto local = ParseVersion(localVersion);
		for (size_t i = 0; i < 3; ++i)
		{
			if (remote[i] > local[i])
				return true;
			if (remote[i] < local[i])
				return false;
		}
		return false;
	}

	inline bool IsSameVersion(const std::string& remoteVersion, const std::string& localVersion)
	{
		return ParseVersion(remoteVersion) == ParseVersion(localVersion);
	}

	inline std::filesystem::path GetExePath()
	{
		char path[MAX_PATH]{};
		GetModuleFileNameA(nullptr, path, MAX_PATH);
		return std::filesystem::path(path);
	}

	inline std::filesystem::path GetTempPayloadPath()
	{
		char tmp[MAX_PATH]{};
		GetTempPathA(MAX_PATH, tmp);
		return std::filesystem::path(tmp) / "dk_update_payload.exe";
	}

	inline bool ApplyUpdate(const std::filesystem::path& downloadedExe)
	{
		const auto exePath = GetExePath();
		const auto dir = exePath.parent_path();
		char tmp[MAX_PATH]{};
		GetTempPathA(MAX_PATH, tmp);
		const auto batPath = std::filesystem::path(tmp) / "dk_update.bat";
		const DWORD pid = GetCurrentProcessId();

		std::ofstream bat(batPath);
		if (!bat.is_open())
			return false;

		// Never delete DkExternal.exe after copying — that was wiping GitHub downloads.
		bat
			<< "@echo off\r\n"
			<< "setlocal EnableExtensions\r\n"
			<< "set \"DIR=" << dir.string() << "\"\r\n"
			<< "set \"TARGET=" << exePath.string() << "\"\r\n"
			<< "set \"NEWFILE=" << downloadedExe.string() << "\"\r\n"
			<< "set \"PID=" << pid << "\"\r\n"
			<< "cd /d \"%DIR%\"\r\n"
			<< "set N=0\r\n"
			<< ":wait\r\n"
			<< "timeout /t 1 /nobreak >nul\r\n"
			<< "tasklist /FI \"PID eq %PID%\" 2>nul | find \"%PID%\" >nul\r\n"
			<< "if not errorlevel 1 (\r\n"
			<< "  set /a N+=1\r\n"
			<< "  if %N% LSS 30 goto wait\r\n"
			<< ")\r\n"
			<< "set N=0\r\n"
			<< ":retry\r\n"
			<< "copy /Y \"%NEWFILE%\" \"%TARGET%\" >nul 2>&1\r\n"
			<< "if exist \"%TARGET%\" goto launch\r\n"
			<< "set /a N+=1\r\n"
			<< "timeout /t 1 /nobreak >nul\r\n"
			<< "if %N% LSS 20 goto retry\r\n"
			<< "echo Updater failed to replace exe.\r\n"
			<< "pause\r\n"
			<< "exit /b 1\r\n"
			<< ":launch\r\n"
			<< "del /f /q \"%NEWFILE%\" >nul 2>&1\r\n"
			<< "start \"\" /D \"%DIR%\" \"%TARGET%\"\r\n"
			<< "del /f /q \"%~f0\" >nul 2>&1\r\n";

		bat.close();

		STARTUPINFOA si{};
		si.cb = sizeof(si);
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_HIDE;
		PROCESS_INFORMATION pi{};

		std::string cmd = "cmd.exe /C call \"" + batPath.string() + "\"";
		std::vector<char> cmdBuf(cmd.begin(), cmd.end());
		cmdBuf.push_back('\0');

		const BOOL created = CreateProcessA(
			nullptr,
			cmdBuf.data(),
			nullptr,
			nullptr,
			FALSE,
			CREATE_NO_WINDOW | DETACHED_PROCESS | CREATE_NEW_PROCESS_GROUP | CREATE_BREAKAWAY_FROM_JOB,
			nullptr,
			dir.string().c_str(),
			&si,
			&pi);

		if (!created)
		{
			std::string cmd2 = "cmd.exe /C call \"" + batPath.string() + "\"";
			std::vector<char> cmdBuf2(cmd2.begin(), cmd2.end());
			cmdBuf2.push_back('\0');
			if (!CreateProcessA(
				nullptr, cmdBuf2.data(), nullptr, nullptr, FALSE,
				CREATE_NO_WINDOW | DETACHED_PROCESS | CREATE_NEW_PROCESS_GROUP,
				nullptr, dir.string().c_str(), &si, &pi))
			{
				return false;
			}
		}

		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		return true;
	}

	inline bool DownloadLatestAsset(const json& release, const std::filesystem::path& tempPath)
	{
		std::vector<std::string> urls;
		if (release.contains("assets") && release["assets"].is_array())
		{
			for (const auto& asset : release["assets"])
			{
				if (!asset.contains("name"))
					continue;
				const std::string name = asset["name"].get<std::string>();
				if (name != UpdaterConfig::UPDATE_ASSET_NAME && name.find(".exe") == std::string::npos)
					continue;

				if (asset.contains("url") && asset["url"].is_string())
					urls.push_back(asset["url"].get<std::string>());
				if (asset.contains("browser_download_url") && asset["browser_download_url"].is_string())
					urls.push_back(asset["browser_download_url"].get<std::string>());

				if (name == UpdaterConfig::UPDATE_ASSET_NAME)
					break;
			}
		}

		urls.push_back(
			std::string("https://github.com/") + UpdaterConfig::GITHUB_OWNER + "/" +
			UpdaterConfig::GITHUB_REPO + "/releases/latest/download/" + UpdaterConfig::UPDATE_ASSET_NAME);

		for (const auto& url : urls)
		{
			if (url.empty())
				continue;
			if (HttpDownloadFile(url, tempPath))
				return true;
		}
		return false;
	}

	inline Result CheckAndUpdate()
	{
		std::cout << "Checking for updates (local v" << UpdaterConfig::APP_VERSION << ")...\n";

		const std::string apiUrl =
			std::string("https://api.github.com/repos/") +
			UpdaterConfig::GITHUB_OWNER + "/" +
			UpdaterConfig::GITHUB_REPO + "/releases/latest";

		std::string body = HttpGet(apiUrl);
		json release;
		bool parsed = false;
		if (!body.empty())
		{
			try
			{
				release = json::parse(body);
				parsed = release.contains("tag_name") && release["tag_name"].is_string();
			}
			catch (...)
			{
				parsed = false;
			}
		}

		if (!parsed)
		{
			FailPause("Updater: could not reach GitHub. Internet is required — blocked.");
			return Result::ExitBlocked;
		}

		if (release.contains("message") && release["message"].is_string())
		{
			const std::string msg = release["message"].get<std::string>();
			if (msg.find("Not Found") != std::string::npos || msg.find("rate limit") != std::string::npos)
			{
				FailPause("Updater: " + msg + " — blocked.");
				return Result::ExitBlocked;
			}
		}

		const std::string remoteTag = release["tag_name"].get<std::string>();

		if (IsSameVersion(remoteTag, UpdaterConfig::APP_VERSION))
		{
			std::cout << "Updater: up to date (" << remoteTag << ").\n";
			return Result::Continue;
		}

		if (!IsRemoteNewer(remoteTag, UpdaterConfig::APP_VERSION))
		{
			std::cout << "Updater: local v" << UpdaterConfig::APP_VERSION
				<< " is newer than release " << remoteTag << ". Continuing.\n";
			return Result::Continue;
		}

		std::cout << "Updater: outdated build. Downloading " << remoteTag << "...\n";

		const auto tempPath = GetTempPayloadPath();
		if (!DownloadLatestAsset(release, tempPath))
		{
			FailPause("Updater: download failed — blocked. Retry when online.");
			return Result::ExitBlocked;
		}

		std::cout << "Updater: replacing old build and restarting...\n";

		if (!ApplyUpdate(tempPath))
		{
			std::error_code ec;
			std::filesystem::remove(tempPath, ec);
			FailPause("Updater: failed to apply update — blocked.");
			return Result::ExitBlocked;
		}

		return Result::ExitForUpdate;
	}
}
