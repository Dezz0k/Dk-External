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
	constexpr const char* APP_VERSION = "1.1.5";
	constexpr const char* GITHUB_OWNER = "Dezz0k";
	constexpr const char* GITHUB_REPO = "Dk-External";
	constexpr const char* UPDATE_ASSET_NAME = "DkExternal.exe";
}

namespace Updater
{
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

	// Returns true if the process should exit because an update was applied.
	inline bool CheckAndUpdate()
	{
		if (std::string(UpdaterConfig::GITHUB_OWNER) == "REPLACE_ME")
		{
			std::cout << "Updater: GitHub owner not set. Skipping update check.\n";
			return false;
		}

		std::cout << "Checking for updates (v" << UpdaterConfig::APP_VERSION << ")...\n";

		const std::string apiUrl =
			std::string("https://api.github.com/repos/") +
			UpdaterConfig::GITHUB_OWNER + "/" +
			UpdaterConfig::GITHUB_REPO + "/releases/latest";

		const std::string body = HttpGet(apiUrl);
		if (body.empty())
		{
			std::cout << "Updater: could not reach GitHub. Continuing.\n";
			return false;
		}

		json release;
		try
		{
			release = json::parse(body);
		}
		catch (...)
		{
			std::cout << "Updater: invalid release response. Continuing.\n";
			return false;
		}

		if (!release.contains("tag_name") || !release["tag_name"].is_string())
		{
			std::cout << "Updater: no releases found. Continuing.\n";
			return false;
		}

		const std::string remoteTag = release["tag_name"].get<std::string>();
		if (!IsRemoteNewer(remoteTag, UpdaterConfig::APP_VERSION))
		{
			std::cout << "Updater: up to date (" << remoteTag << ").\n";
			return false;
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
			std::cout << "Updater: release " << remoteTag
				<< " has no asset named \"" << UpdaterConfig::UPDATE_ASSET_NAME << "\". Continuing.\n";
			return false;
		}

		std::cout << "Updater: downloading " << remoteTag << "...\n";

		const auto exePath = GetExePath();
		const auto tempPath = exePath.parent_path() / (exePath.filename().string() + ".new");

		if (!HttpDownloadFile(downloadUrl, tempPath))
		{
			std::cout << "Updater: download failed. Continuing.\n";
			return false;
		}

		std::cout << "Updater: installing update and restarting...\n";

		if (!ApplyUpdate(tempPath))
		{
			std::cout << "Updater: failed to apply update. Continuing.\n";
			std::error_code ec;
			std::filesystem::remove(tempPath, ec);
			return false;
		}

		return true;
	}
}
