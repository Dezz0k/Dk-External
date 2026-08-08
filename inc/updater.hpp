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

// Change these to match your GitHub repo. Releases must use tags like v1.1.1
// and attach an asset named exactly UPDATE_ASSET_NAME.
namespace UpdaterConfig
{
	constexpr const char* APP_VERSION = "1.1.11";
	constexpr const char* GITHUB_OWNER = "Dezz0k";
	constexpr const char* GITHUB_REPO = "Dk-External";
	constexpr const char* UPDATE_ASSET_NAME = "DkExternal.exe";
}

namespace Updater
{
	enum class Result
	{
		Continue,      // already on latest — safe to run
		ExitForUpdate, // update applied; process should exit and restart
		ExitBlocked    // could not verify/update — do not allow old build to run
	};

	inline void FailPause(const std::string& message)
	{
		std::cout << message << "\n";
		system("pause");
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

		const char* headers = "Accept: application/vnd.github+json\r\nX-GitHub-Api-Version: 2022-11-28\r\n";

		HINTERNET hUrl = InternetOpenUrlA(
			hInternet,
			url.c_str(),
			headers,
			static_cast<DWORD>(strlen(headers)),
			INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE | INTERNET_FLAG_NO_CACHE_WRITE,
			0);

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

		const char* headers = "Accept: application/octet-stream\r\n";

		HINTERNET hUrl = InternetOpenUrlA(
			hInternet,
			url.c_str(),
			headers,
			static_cast<DWORD>(strlen(headers)),
			INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE | INTERNET_FLAG_NO_CACHE_WRITE,
			0);

		if (!hUrl)
		{
			InternetCloseHandle(hInternet);
			return false;
		}

		std::ofstream out(outPath, std::ios::binary);
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

		if (!ok || !std::filesystem::exists(outPath) || std::filesystem::file_size(outPath) == 0)
		{
			std::error_code ec;
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
			try
			{
				parts.push_back(std::stoi(item));
			}
			catch (...)
			{
				parts.push_back(0);
			}
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

	inline bool ApplyUpdate(const std::filesystem::path& downloadedExe)
	{
		const auto exePath = GetExePath();
		const auto batPath = exePath.parent_path() / "dk_update.bat";

		std::ofstream bat(batPath);
		if (!bat.is_open())
			return false;

		bat
			<< "@echo off\r\n"
			<< "setlocal\r\n"
			<< "set \"TARGET=" << exePath.string() << "\"\r\n"
			<< "set \"NEWFILE=" << downloadedExe.string() << "\"\r\n"
			<< ":wait\r\n"
			<< "timeout /t 1 /nobreak >nul\r\n"
			<< "del \"%TARGET%\" >nul 2>&1\r\n"
			<< "if exist \"%TARGET%\" goto wait\r\n"
			<< "move /y \"%NEWFILE%\" \"%TARGET%\" >nul\r\n"
			<< "start \"\" \"%TARGET%\"\r\n"
			<< "del \"%~f0\" >nul 2>&1\r\n";

		bat.close();

		ShellExecuteA(
			nullptr,
			"open",
			batPath.string().c_str(),
			nullptr,
			exePath.parent_path().string().c_str(),
			SW_HIDE);

		return true;
	}

	// Must run before anything else.
	// Old builds are blocked unless they successfully update to the latest GitHub release.
	inline Result CheckAndUpdate()
	{
		std::cout << "Checking for updates (local v" << UpdaterConfig::APP_VERSION << ")...\n";

		const std::string apiUrl =
			std::string("https://api.github.com/repos/") +
			UpdaterConfig::GITHUB_OWNER + "/" +
			UpdaterConfig::GITHUB_REPO + "/releases/latest";

		const std::string body = HttpGet(apiUrl);
		if (body.empty())
		{
			FailPause("Updater: could not reach GitHub. Internet is required — blocked.");
			return Result::ExitBlocked;
		}

		json release;
		try
		{
			release = json::parse(body);
		}
		catch (...)
		{
			FailPause("Updater: invalid release response — blocked.");
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

		if (!release.contains("tag_name") || !release["tag_name"].is_string())
		{
			FailPause("Updater: no GitHub releases found — blocked.");
			return Result::ExitBlocked;
		}

		const std::string remoteTag = release["tag_name"].get<std::string>();

		if (IsSameVersion(remoteTag, UpdaterConfig::APP_VERSION))
		{
			std::cout << "Updater: up to date (" << remoteTag << ").\n";
			return Result::Continue;
		}

		if (!IsRemoteNewer(remoteTag, UpdaterConfig::APP_VERSION))
		{
			// Local is ahead of published release (dev build) — allow.
			std::cout << "Updater: local v" << UpdaterConfig::APP_VERSION
				<< " is newer than release " << remoteTag << ". Continuing.\n";
			return Result::Continue;
		}

		std::string downloadUrl;
		if (release.contains("assets") && release["assets"].is_array())
		{
			for (const auto& asset : release["assets"])
			{
				if (!asset.contains("name") || !asset.contains("browser_download_url"))
					continue;

				if (asset["name"].get<std::string>() == UpdaterConfig::UPDATE_ASSET_NAME)
				{
					downloadUrl = asset["browser_download_url"].get<std::string>();
					break;
				}
			}
		}

		if (downloadUrl.empty())
		{
			FailPause(
				std::string("Updater: release ") + remoteTag +
				" has no asset named \"" + UpdaterConfig::UPDATE_ASSET_NAME + "\" — blocked.");
			return Result::ExitBlocked;
		}

		std::cout << "Updater: outdated build. Downloading " << remoteTag << "...\n";

		const auto exePath = GetExePath();
		const auto tempPath = exePath.parent_path() / (exePath.filename().string() + ".new");

		if (!HttpDownloadFile(downloadUrl, tempPath))
		{
			FailPause("Updater: download failed — blocked. Retry when online.");
			return Result::ExitBlocked;
		}

		std::cout << "Updater: installing update and restarting...\n";

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
