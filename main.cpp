#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <random>
#include <cfloat>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <mutex>
#include <cstdint>
#include <vector>
#include <cctype>
#include <sstream>
#include <ctime>
#include <cstdio>
#include <wininet.h>

#pragma comment(lib, "winmm.lib")

#include "resource.h"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

#include "inc/dependencies/json.hpp"

#include "inc/snowflake/Snowflake.hpp"

#include "inc/Renderer.hpp"
#include "inc/rbx.hpp"
#include "inc/utils.hpp"
#include "inc/updater.hpp"
#include "inc/keyauth.hpp"

#include "inc/offsets.hpp"
#include "inc/SkechGui.hpp"

using json = nlohmann::json;

#define SNOW_LIMIT 80

std::vector<RBX::Instance> playersList;
std::vector<std::string> playersListNames;
std::unordered_set<std::string> friendNames;
std::unordered_set<std::string> enemyNames;
std::vector<std::string> aimbotLockPartsR6{ "Head", "Torso", "Left Arm", "Right Arm", "Left Leg", "Right Leg" };
std::vector<std::string> aimbotLockPartsR15{ "Head", "UpperTorso", "LeftUpperArm", "RightUpperArm", "LeftUpperLeg", "RightUpperLeg" };
std::vector<std::string> aimbotLockPartsUI{ "Closest", "Head", "Torso", "Left Arm", "Right Arm", "Left Leg", "Right Leg" };
std::vector<std::string> tracerTypes{ "Mouse", "Corner", "Top", "Bottom" };
std::vector<std::string> espTypes{ "Square", "Skeleton", "Corners" };

std::vector<Snowflake::Snowflake> snow;
ImColor featureBGColor{ 0, 0, 0, 230 };
ImColor glowColor{ 1.0f, 0.0f, 0.0f, 0.8f };

namespace Settings
{
	bool imguiVisible{ true };
	bool mainMenuVisible{ true };
	bool explorerWinVisible{ false };
	bool keybindListVisible{ false };
	bool themeWinVisible{ false };
	bool friendsListVisible{ false };
	bool adminWinVisible{ false };
	int toggleGuiKey{ 45 };
	std::string currentTab{ "Aiming" };

	bool aimbotEnabled{ false };
	bool aimbotFOVEnabled{ false };
	bool aimbotPredictionEnabled{ false };
	bool aimbotToggleLock{ false };
	bool aimbotLockToggled{ false };
	float aimbotFOVRadius{ 100.0f };
	float aimbotStrenght{ 0.35f };
	float aimbotPredictionX{ 5.0f };
	float aimbotPredictionY{ 5.0f };
	std::string aimbotLockPart{ "Closest" };
	int aimbotKey{ 2 };
	ImVec4 aimbotFovColor{ 1.0f, 0.0f, 0.0f, 1.0f };

	bool silentAimEnabled{ false };
	float silentAimFOVRadius{ 500.0f };
	std::string silentAimLockPart{ "Closest" };

	bool triggerbotEnabled{ false };
	bool triggerbotIndicateClicking{ false };
	float triggerbotDetectionRadius{ 20.0f };
	std::string triggerbotTriggerPart{ "Torso" };
	int triggerbotKey{ 0 };

	bool espEnabled{ false };
	bool espFilled{ false };
	bool espShowDistance{ false };
	bool espShowName{ false };
	bool espShowHealth{ false };
	bool espIgnoreDeadPlrs{ true };
	int espDistance{ 0 };
	std::string espType{ "Square" };
	ImVec4 espColor{ 1.0f, 0.0f, 0.0f, 1.0f };
	bool tracersEnabled{ false };
	std::string tracerType{ "Mouse" };
	ImVec4 tracerColor{ 1.0f, 1.0f, 1.0f, 1.0f };

	char configFileName[30]{};
	char themeFileName[30]{};
	bool autoSaveEnabled{ false };
	bool streamproofEnabled{ false };
	bool rbxWindowNeedsToBeSelected{ true };
	int mainLoopDelay{ 0 };
	bool highEndVisuals{ true };
	bool sessionBoost{ false };
	bool hideSmiteLogo{ false };

	bool noclipEnabled{ false };
	bool flyEnabled{ false };
	int flyKey{ 0 };
	bool flyKeyToggled{ false };
	float flySpeed{ 16.0f };
	// Default / CFrame / Position / Velocity / Hybrid / PlatformStand / Anchored
	std::string flyMode{ "Default" };
	bool orbitEnabled{ false };
	float orbitDistanceMultiplier{ 1.0f };
	float orbitSpeedMultiplier{ 1.0f };
	bool behindPlayerEnabled{ true };
	int behindPlayerKey{ 0 };
	float behindPlayerDistance{ 4.0f };
	float behindPlayerFOV{ 250.0f };
	bool walkSpeedEnabled{ false };
	int walkSpeedSet{ 16 };
	int walkSpeedKey{ 0 };
	bool jumpPowerEnabled{ false };
	int jumpPowerSet{ 50 };
	int jumpPowerKey{ 0 };
	char othersRobloxPlr[64]{};
	RBX::Vector3 othersTeleportPos{};

	// Owner-role troll tools (KeyAuth subscription "owner")
	bool ownerBringEnabled{ false };
	bool ownerSpinEnabled{ false };
	bool ownerFreezeEnabled{ false };
	bool ownerFlingEnabled{ false };
	bool ownerFollowEnabled{ false };
	bool ownerJumpOnlyEnabled{ false };

	int gamblingSlotsNumber1{ 0 };
	int gamblingSlotsNumber2{ 0 };
	int gamblingSlotsNumber3{ 0 };
	int gamblingBalance{ 500 };
	int gamblingLastYmd{ 0 };

	bool espPreviewOpened{ false };
}

static bool IsFriend(const std::string& name)
{
	return !name.empty() && friendNames.find(name) != friendNames.end();
}

static std::string GetPlayersListName(size_t idx, RBX::Instance& modelFallback)
{
	if (idx < playersListNames.size())
		return playersListNames[idx];
	return modelFallback.name();
}

static bool PlayerIsSmiteUser(RBX::Instance player);
static int64_t ReadPlayerUserId(RBX::Instance player);
static void RequestAvatar(int64_t userId);
static ID3D11ShaderResourceView* GetAvatarSrv(int64_t userId, ImVec2* sizeOut = nullptr);

static void ToggleFriend(const std::string& name)
{
	if (name.empty())
		return;

	if (IsFriend(name))
		friendNames.erase(name);
	else
		friendNames.insert(name);
}

static void PopulateGuiPlayers(SkechStyle::DemoState& st, RBX::Instance& players, RBX::Instance& localPlayer)
{
	st.livePlayerCount = 0;
	st.adminPlayerCount = 1;
	st.adminPlayerNames[0] = "Select player";

	const std::string localName{ localPlayer.name() };
	for (RBX::Instance plr : players.getChildren())
	{
		if (plr.className() != "Player")
			continue;

		const std::string name{ plr.name() };
		if (name.empty())
			continue;

		if (st.livePlayerCount >= SkechStyle::DemoState::MaxLivePlayers)
			break;

		auto& entry = st.livePlayers[st.livePlayerCount++];
		strncpy_s(entry.name, name.c_str(), _TRUNCATE);
		entry.userId = ReadPlayerUserId(plr);
		entry.isLocal = (name == localName);
		entry.isFriend = IsFriend(name);
		entry.isSmite = PlayerIsSmiteUser(plr);

		if (!entry.isLocal && entry.isSmite && st.adminPlayerCount < SkechStyle::DemoState::MaxLivePlayers + 1)
			st.adminPlayerNames[st.adminPlayerCount++] = entry.name;
	}

	if (st.selectedLivePlayer >= st.livePlayerCount)
		st.selectedLivePlayer = -1;

	st.selectedAvatarTex = nullptr;
	st.selectedAvatarSize = ImVec2(0, 0);
	if (st.selectedLivePlayer >= 0 && st.selectedLivePlayer < st.livePlayerCount)
	{
		const int64_t uid = st.livePlayers[st.selectedLivePlayer].userId;
		RequestAvatar(uid);
		ImVec2 sz{};
		if (ID3D11ShaderResourceView* srv{ GetAvatarSrv(uid, &sz) })
		{
			st.selectedAvatarTex = srv;
			st.selectedAvatarSize = sz;
		}
	}
}

static RBX::Matrix3 YawLookMatrix(float angle);

static bool TeleportBehindPlayer(RBX::Instance targetPlr, RBX::Instance& hrp, RBX::Instance& camera)
{
	if (!targetPlr.address || !hrp.address)
		return false;
	RBX::Instance mi{ targetPlr.getModelInstance() };
	RBX::Instance targetHrp{ mi.address ? mi.findFirstChild("HumanoidRootPart") : RBX::Instance(nullptr) };
	void* targetPrim{ targetHrp.address ? targetHrp.getPrimitive() : nullptr };
	void* localPrim{ hrp.getPrimitive() };
	if (!targetPrim || !localPrim)
		return false;

	const RBX::Vector3 targetPos{ RBX::Memory::read<RBX::Vector3>((void*)((uintptr_t)targetPrim + Offsets::Position)) };
	const RBX::Matrix3 targetRot{ RBX::Memory::read<RBX::Matrix3>((void*)((uintptr_t)targetPrim + Offsets::Rotation)) };
	RBX::Vector3 look{ -targetRot.data[2], 0.0f, -targetRot.data[8] };
	const float lookLen{ sqrtf(look.x * look.x + look.z * look.z) };
	if (lookLen > 0.0001f)
	{
		look.x /= lookLen;
		look.z /= lookLen;
	}
	else
	{
		look = { 0.0f, 0.0f, 1.0f };
	}

	const RBX::Vector3 behindPos{
		targetPos.x - look.x * Settings::behindPlayerDistance,
		targetPos.y,
		targetPos.z - look.z * Settings::behindPlayerDistance
	};
	const RBX::Matrix3 faceSame{ YawLookMatrix(atan2f(look.x, look.z)) };

	for (int i = 0; i < 3; ++i)
	{
		RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)localPrim + Offsets::Position), behindPos);
		RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)localPrim + Offsets::Velocity), { 0.0f, 0.0f, 0.0f });
		RBX::Memory::write<RBX::Matrix3>((void*)((uintptr_t)localPrim + Offsets::Rotation), faceSame);
	}
	if (camera.address)
		RBX::Memory::write<RBX::Matrix3>((void*)((uintptr_t)camera.address + Offsets::CameraRotation), faceSame);
	return true;
}

static void ProcessGuiPlayerActions(SkechStyle::DemoState& st, RBX::Instance& players, RBX::Instance& camera, RBX::Instance& humanoid, RBX::Instance& hrp)
{
	using Action = SkechStyle::DemoState::PlayerListAction;
	if (st.playerAction == Action::None)
		return;

	const char* target = st.playerActionTarget;
	switch (st.playerAction)
	{
	case Action::Spectate:
		if (target[0])
		{
			strncpy_s(Settings::othersRobloxPlr, target, _TRUNCATE);
			RBX::Instance targetPlr{ players.findFirstChild(Settings::othersRobloxPlr) };
			RBX::Instance targetMi{ targetPlr.getModelInstance() };
			RBX::Instance targetHum{ targetMi.findFirstChild("Humanoid") };
			if (targetHum.address)
				RBX::Memory::write<void*>((void*)((uintptr_t)camera.address + Offsets::CameraSubject), targetHum.address);
		}
		break;
	case Action::StopSpectate:
		if (humanoid.address)
			RBX::Memory::write<void*>((void*)((uintptr_t)camera.address + Offsets::CameraSubject), humanoid.address);
		break;
	case Action::Teleport:
		if (target[0])
		{
			strncpy_s(Settings::othersRobloxPlr, target, _TRUNCATE);
			RBX::Instance plr{ players.findFirstChild(Settings::othersRobloxPlr) };
			RBX::Instance plrMi{ plr.getModelInstance() };
			RBX::Instance plrHrp{ plrMi.findFirstChild("HumanoidRootPart") };
			if (plrHrp.address && hrp.address)
				RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)hrp.getPrimitive() + Offsets::Position), plrHrp.getPosition());
		}
		break;
	case Action::Behind:
		if (target[0])
		{
			strncpy_s(Settings::othersRobloxPlr, target, _TRUNCATE);
			TeleportBehindPlayer(players.findFirstChild(target), hrp, camera);
		}
		break;
	case Action::Orbit:
		if (target[0])
		{
			strncpy_s(Settings::othersRobloxPlr, target, _TRUNCATE);
			Settings::orbitEnabled = true;
		}
		break;
	case Action::StopOrbit:
		Settings::orbitEnabled = false;
		break;
	case Action::ToggleFriend:
		if (target[0])
			ToggleFriend(target);
		break;
	case Action::ToggleEnemy:
		if (target[0])
		{
			if (enemyNames.find(target) != enemyNames.end())
				enemyNames.erase(target);
			else
				enemyNames.insert(target);
		}
		break;
	default:
		break;
	}

	st.playerAction = Action::None;
	st.playerActionTarget[0] = '\0';
}

static void ProcessGuiTpActions(SkechStyle::DemoState& st, RBX::Instance& hrp)
{
	using TpAction = SkechStyle::DemoState::TpAction;
	if (st.tpAction == TpAction::None)
		return;

	switch (st.tpAction)
	{
	case TpAction::SetFromLocal:
		if (hrp.address)
		{
			const RBX::Vector3 pos{ hrp.getPosition() };
			st.tpX = pos.x;
			st.tpY = pos.y;
			st.tpZ = pos.z;
			Settings::othersTeleportPos = pos;
		}
		break;
	case TpAction::Clear:
		st.tpX = st.tpY = st.tpZ = 0.0f;
		Settings::othersTeleportPos = { 0.0f, 0.0f, 0.0f };
		break;
	case TpAction::Teleport:
		if (hrp.address)
		{
			Settings::othersTeleportPos = { st.tpX, st.tpY, st.tpZ };
			RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)hrp.getPrimitive() + Offsets::Position), Settings::othersTeleportPos);
		}
		break;
	default:
		break;
	}

	st.tpAction = TpAction::None;
}

static RBX::Instance resolveLockPart(RBX::Instance& plr, const std::string& partName, POINT mousePos, RBX::VisualEngine& visualEngine)
{
	const bool isR6{ plr.findFirstChild("Torso").address != nullptr };

	if (partName == "Closest")
	{
		float bestDist{ FLT_MAX };
		RBX::Instance bestPart{ nullptr };

		for (size_t i{ 0 }; i < aimbotLockPartsR6.size(); ++i)
		{
			RBX::Instance part{ plr.findFirstChild(isR6 ? aimbotLockPartsR6[i] : aimbotLockPartsR15[i]) };
			if (!part.address)
				continue;

			RBX::Vector2 screenPos{ visualEngine.worldToScreen(part.getPosition()) };
			float dx{ screenPos.x - mousePos.x };
			float dy{ screenPos.y - mousePos.y };
			float dist{ sqrtf(dx * dx + dy * dy) };

			if (dist < bestDist)
			{
				bestDist = dist;
				bestPart = part;
			}
		}

		return bestPart;
	}

	if (isR6)
		return plr.findFirstChild(partName);

	auto it{ std::find(aimbotLockPartsR6.begin(), aimbotLockPartsR6.end(), partName) };
	if (it == aimbotLockPartsR6.end())
		return RBX::Instance(nullptr);

	size_t index{ static_cast<size_t>(std::distance(aimbotLockPartsR6.begin(), it)) };
	return plr.findFirstChild(aimbotLockPartsR15[index]);
}

static void DrawKeybindProp(const char* label, const char* mode, int key, bool active)
{
	const ImVec4 color{ active ? ImVec4(0.2f, 1.0f, 0.3f, 1.0f) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f) };
	if (strcmp(mode, "FEATURE") == 0)
	{
		ImGui::TextColored(color, "[%s] %s", mode, label);
		return;
	}

	ImGui::TextColored(color, "[%s] %s - %s", mode, label, GetBindName(key));
}

static void DrawOutlinedText(ImDrawList* drawList, ImVec2 pos, const char* text, ImU32 fill, ImU32 outline, float fontSize = 0.0f)
{
	ImFont* font{ ImGui::GetFont() };
	const float size{ fontSize > 0.0f ? fontSize : ImGui::GetFontSize() };
	for (int x{ -2 }; x <= 2; ++x)
	{
		for (int y{ -2 }; y <= 2; ++y)
		{
			if (x == 0 && y == 0)
				continue;
			drawList->AddText(font, size, { pos.x + static_cast<float>(x), pos.y + static_cast<float>(y) }, outline, text);
		}
	}
	drawList->AddText(font, size, pos, fill, text);
}

static constexpr float kSmiteTagSlope = 89.137f;
static constexpr const char* kDkPresenceUrl = "https://ntfy.sh/dk-external-users-dvcf1EcOCE";
static constexpr const char* kDkCmdUrl = "https://ntfy.sh/dk-external-cmds-dvcf1EcOCE";
static constexpr ULONGLONG kDkPresenceTtlMs = 70000ULL;
static constexpr ULONGLONG kDkCmdTtlMs = 2500ULL;

struct TrollNetCmd
{
	int64_t targetUid{ 0 };
	bool bring{ false };
	bool follow{ false };
	bool freeze{ false };
	bool spin{ false };
	bool fling{ false };
	bool jumpOnly{ false };
	RBX::Vector3 pos{};
	ULONGLONG recvMs{ 0 };

	bool Any() const
	{
		return bring || follow || freeze || spin || fling || jumpOnly;
	}
};

static std::mutex gTrollNetMu;
static TrollNetCmd gOutgoingTroll{};
static TrollNetCmd gIncomingTroll{};

static RBX::Matrix3 YawLookMatrix(float angle)
{
	const float s{ sinf(angle) };
	const float c{ cosf(angle) };
	RBX::Vector3 fwd{ s, 0.0f, c };
	RBX::Vector3 right{ fwd.z, 0.0f, -fwd.x };
	RBX::Matrix3 m{};
	m.data[0] = right.x;
	m.data[3] = right.y;
	m.data[6] = right.z;
	m.data[1] = 0.0f;
	m.data[4] = 1.0f;
	m.data[7] = 0.0f;
	m.data[2] = -fwd.x;
	m.data[5] = 0.0f;
	m.data[8] = -fwd.z;
	return m;
}

static std::string PackTrollCmd(const TrollNetCmd& c)
{
	std::ostringstream oss;
	oss << "CMD|" << c.targetUid << "|"
		<< (c.bring ? 1 : 0) << "|"
		<< (c.follow ? 1 : 0) << "|"
		<< (c.freeze ? 1 : 0) << "|"
		<< (c.spin ? 1 : 0) << "|"
		<< (c.fling ? 1 : 0) << "|"
		<< (c.jumpOnly ? 1 : 0) << "|"
		<< c.pos.x << "|" << c.pos.y << "|" << c.pos.z;
	return oss.str();
}

static bool ParseTrollCmd(const std::string& msg, TrollNetCmd& out)
{
	if (msg.rfind("CMD|", 0) != 0)
		return false;
	int parts[6]{};
	float xyz[3]{};
	int64_t uid = 0;
	if (sscanf_s(msg.c_str(), "CMD|%lld|%d|%d|%d|%d|%d|%d|%f|%f|%f",
		&uid, &parts[0], &parts[1], &parts[2], &parts[3], &parts[4], &parts[5],
		&xyz[0], &xyz[1], &xyz[2]) < 10)
		return false;
	out.targetUid = uid;
	out.bring = parts[0] != 0;
	out.follow = parts[1] != 0;
	out.freeze = parts[2] != 0;
	out.spin = parts[3] != 0;
	out.fling = parts[4] != 0;
	out.jumpOnly = parts[5] != 0;
	out.pos = { xyz[0], xyz[1], xyz[2] };
	out.recvMs = GetTickCount64();
	return true;
}

static std::mutex gDkMu;
static std::unordered_map<int64_t, ULONGLONG> gDkIds;
static std::unordered_map<std::string, ULONGLONG> gDkNames;

static std::string LowerCopy(std::string s)
{
	for (char& ch : s)
		ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
	return s;
}

static void DkNoteUser(int64_t userId, const std::string& name)
{
	const ULONGLONG t{ GetTickCount64() };
	std::lock_guard<std::mutex> lock(gDkMu);
	if (userId > 0)
		gDkIds[userId] = t;
	if (!name.empty())
		gDkNames[LowerCopy(name)] = t;
}

static void DkForgetUser(int64_t userId, const std::string& name)
{
	std::lock_guard<std::mutex> lock(gDkMu);
	if (userId > 0)
		gDkIds.erase(userId);
	if (!name.empty())
		gDkNames.erase(LowerCopy(name));
}

static bool CanHideSmiteLogo()
{
	return KeyAuth::IsStaff();
}

static bool SmiteLogoHidden()
{
	return Settings::hideSmiteLogo && CanHideSmiteLogo();
}

static bool DkIsPresent(int64_t userId, const std::string& name)
{
	const ULONGLONG now{ GetTickCount64() };
	std::lock_guard<std::mutex> lock(gDkMu);
	if (userId > 0)
	{
		const auto it{ gDkIds.find(userId) };
		if (it != gDkIds.end() && now - it->second < kDkPresenceTtlMs)
			return true;
	}
	if (!name.empty())
	{
		const auto it{ gDkNames.find(LowerCopy(name)) };
		if (it != gDkNames.end() && now - it->second < kDkPresenceTtlMs)
			return true;
	}
	return false;
}

static bool HttpPostText(const char* url, const std::string& body)
{
	HINTERNET net{ InternetOpenA("DkExternalPresence/1.0", INTERNET_OPEN_TYPE_PRECONFIG, nullptr, nullptr, 0) };
	if (!net)
		return false;

	URL_COMPONENTSA comps{};
	comps.dwStructSize = sizeof(comps);
	char host[256]{};
	char path[1024]{};
	comps.lpszHostName = host;
	comps.dwHostNameLength = sizeof(host);
	comps.lpszUrlPath = path;
	comps.dwUrlPathLength = sizeof(path);
	if (!InternetCrackUrlA(url, 0, 0, &comps))
	{
		InternetCloseHandle(net);
		return false;
	}

	HINTERNET conn{ InternetConnectA(net, host, comps.nPort ? comps.nPort : INTERNET_DEFAULT_HTTPS_PORT, nullptr, nullptr, INTERNET_SERVICE_HTTP, 0, 0) };
	if (!conn)
	{
		InternetCloseHandle(net);
		return false;
	}

	const char* acceptTypes[]{ "*/*", nullptr };
	HINTERNET req{ HttpOpenRequestA(conn, "POST", path, nullptr, nullptr, acceptTypes,
		INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE | INTERNET_FLAG_NO_CACHE_WRITE, 0) };
	if (!req)
	{
		InternetCloseHandle(conn);
		InternetCloseHandle(net);
		return false;
	}

	const char* headers{ "Content-Type: text/plain\r\n" };
	const BOOL ok{ HttpSendRequestA(req, headers, static_cast<DWORD>(strlen(headers)),
		(LPVOID)body.data(), static_cast<DWORD>(body.size())) };
	InternetCloseHandle(req);
	InternetCloseHandle(conn);
	InternetCloseHandle(net);
	return ok == TRUE;
}

static constexpr float kDefaultMaxSlopeAngle = 89.0f;

static void TagSmiteUser(RBX::Instance humanoid)
{
	if (!humanoid.address)
		return;
	const float slope{ SmiteLogoHidden() ? kDefaultMaxSlopeAngle : kSmiteTagSlope };
	RBX::Memory::write((void*)((uintptr_t)humanoid.address + Offsets::MaxSlopeAngle), slope);
}

static bool FlyVecOk(const RBX::Vector3& v)
{
	return std::isfinite(v.x) && std::isfinite(v.y) && std::isfinite(v.z)
		&& fabsf(v.x) < 1000000.0f && fabsf(v.y) < 1000000.0f && fabsf(v.z) < 1000000.0f;
}

static bool FlyMatOk(const RBX::Matrix3& m)
{
	for (int i = 0; i < 9; ++i)
	{
		if (!std::isfinite(m.data[i]) || fabsf(m.data[i]) > 100.0f)
			return false;
	}
	return true;
}

static bool PrimOk(void* primitive)
{
	return reinterpret_cast<uintptr_t>(primitive) > 0x10000ULL;
}

static uint8_t ReadPrimFlags(void* primitive)
{
	return RBX::Memory::read<uint8_t>((void*)((uintptr_t)primitive + Offsets::CanCollide));
}

static void WritePrimFlags(void* primitive, uint8_t flags)
{
	RBX::Memory::write<uint8_t>((void*)((uintptr_t)primitive + Offsets::CanCollide), flags);
}

static uint8_t kCollideBits()
{
	return static_cast<uint8_t>(Offsets::CanCollideMask | Offsets::CanTouchMask);
}

static void ClearCollideBits(void* primitive)
{
	if (!PrimOk(primitive))
		return;
	WritePrimFlags(primitive, static_cast<uint8_t>(ReadPrimFlags(primitive) & ~kCollideBits()));
}

static void RestoreFlyPhysics(RBX::Instance humanoid, void* primitive, bool usedAnchored, bool usedPlatformStand, float savedWalk)
{
	if (humanoid.address)
	{
		RBX::Memory::write<bool>((void*)((uintptr_t)humanoid.address + Offsets::PlatformStand), false);
		if (usedPlatformStand)
		{
			RBX::Memory::write<bool>((void*)((uintptr_t)humanoid.address + Offsets::AutoRotate), true);
			const float ws{ RBX::Memory::read<float>((void*)((uintptr_t)humanoid.address + Offsets::WalkSpeed)) };
			if (ws <= 0.05f && savedWalk > 0.05f)
				RBX::setWalkSpeed(humanoid, savedWalk);
		}
	}
	if (!PrimOk(primitive))
		return;

	uint8_t flags{ ReadPrimFlags(primitive) };
	if (usedAnchored)
		flags = static_cast<uint8_t>(flags & ~static_cast<uint8_t>(Offsets::AnchoredMask));
	if (Settings::noclipEnabled)
		flags = static_cast<uint8_t>(flags & ~kCollideBits());
	WritePrimFlags(primitive, flags);

	const RBX::Vector3 zero{ 0.0f, 0.0f, 0.0f };
	RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)primitive + Offsets::Velocity), zero);
	RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)primitive + offsets::Primitive::RotationVelocity), zero);
}

static bool InstanceIsPart(RBX::Instance inst)
{
	if (!inst.address)
		return false;
	const std::string c{ inst.className() };
	if (c.empty())
		return false;
	if (c.size() >= 4 && c.compare(c.size() - 4, 4, "Part") == 0)
		return true;
	return c == "UnionOperation" || c == "Seat" || c == "VehicleSeat" || c == "SpawnLocation" || c == "Platform";
}

static void CollectCharacterParts(RBX::Instance model, std::vector<void*>& partAddrs)
{
	if (!model.address)
		return;
	for (RBX::Instance ch : model.getChildren())
	{
		if (!ch.address)
			continue;
		const std::string cn{ ch.className() };
		if (cn == "Tool")
			continue;
		if (InstanceIsPart(ch))
			partAddrs.push_back(ch.address);
		if (cn == "Accessory" || cn == "Hat" || cn == "Model")
		{
			for (RBX::Instance nested : ch.getChildren())
			{
				if (InstanceIsPart(nested))
					partAddrs.push_back(nested.address);
			}
		}
	}
}

static void ApplyForceReset(RBX::Instance humanoid, RBX::Instance hrp, RBX::Instance model)
{
	if (humanoid.address)
	{
		RBX::Memory::write<bool>((void*)((uintptr_t)humanoid.address + Offsets::PlatformStand), false);
		RBX::Memory::write<bool>((void*)((uintptr_t)humanoid.address + Offsets::AutoRotate), true);
		if (!Settings::walkSpeedEnabled)
		{
			const float ws{ RBX::Memory::read<float>((void*)((uintptr_t)humanoid.address + Offsets::WalkSpeed)) };
			if (ws <= 0.05f)
				RBX::setWalkSpeed(humanoid, 16.0f);
		}
		if (!Settings::jumpPowerEnabled)
		{
			const float jp{ RBX::Memory::read<float>((void*)((uintptr_t)humanoid.address + Offsets::JumpPower)) };
			if (jp <= 0.05f)
				RBX::setJumpPower(humanoid, 50.0f);
		}
	}

	std::vector<void*> parts;
	CollectCharacterParts(model, parts);
	if (hrp.address && std::find(parts.begin(), parts.end(), hrp.address) == parts.end())
		parts.push_back(hrp.address);

	const RBX::Vector3 zero{ 0.0f, 0.0f, 0.0f };
	for (void* partAddr : parts)
	{
		if (!partAddr)
			continue;
		RBX::Instance part{ partAddr };
		void* prim{ part.getPrimitive() };
		if (!PrimOk(prim))
			continue;

		uint8_t flags{ ReadPrimFlags(prim) };
		flags = static_cast<uint8_t>(flags & ~static_cast<uint8_t>(Offsets::AnchoredMask));
		if (hrp.address && partAddr == hrp.address)
			flags = static_cast<uint8_t>(flags & ~kCollideBits());
		else
			flags = static_cast<uint8_t>(flags | kCollideBits());
		WritePrimFlags(prim, flags);
		RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)prim + Offsets::Velocity), zero);
		RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)prim + offsets::Primitive::RotationVelocity), zero);
	}
}

static int gForceResetLeft = 0;

static bool IsSmiteUser(RBX::Instance humanoid)
{
	if (!humanoid.address)
		return false;
	const float v{ RBX::Memory::read<float>((void*)((uintptr_t)humanoid.address + Offsets::MaxSlopeAngle)) };
	return fabsf(v - kSmiteTagSlope) < 0.003f;
}

static bool PlayerIsSmiteUser(RBX::Instance player)
{
	if (!player.address)
		return false;
	const std::string name{ player.name() };
	if (DkIsPresent(ReadPlayerUserId(player), name))
		return true;
	RBX::Instance mi{ player.getModelInstance() };
	return IsSmiteUser(mi.findFirstChild("Humanoid"));
}

static int64_t ReadPlayerUserId(RBX::Instance player)
{
	if (!player.address)
		return 0;
	return RBX::Memory::read<int64_t>((void*)((uintptr_t)player.address + Offsets::UserId));
}

static std::mutex gAvatarMu;
struct AvatarPendingBytes { int64_t userId; std::vector<unsigned char> bytes; };
static std::vector<AvatarPendingBytes> gAvatarReady;
static std::unordered_map<int64_t, ID3D11ShaderResourceView*> gAvatarSrv;
static std::unordered_map<int64_t, ImVec2> gAvatarSize;
static std::unordered_set<int64_t> gAvatarPending;

static bool HttpGetBytes(const char* url, std::string& out)
{
	HINTERNET net{ InternetOpenA("Mozilla/5.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0) };
	if (!net) return false;
	HINTERNET req{ InternetOpenUrlA(net, url, NULL, 0,
		INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE | INTERNET_FLAG_NO_CACHE_WRITE, 0) };
	if (!req)
	{
		InternetCloseHandle(net);
		return false;
	}
	char buf[4096];
	DWORD read = 0;
	out.clear();
	while (InternetReadFile(req, buf, sizeof(buf), &read) && read)
		out.append(buf, read);
	InternetCloseHandle(req);
	InternetCloseHandle(net);
	return !out.empty();
}

static void RequestAvatar(int64_t userId)
{
	if (userId <= 0)
		return;
	{
		std::lock_guard<std::mutex> lock(gAvatarMu);
		if (gAvatarSrv.count(userId) || gAvatarPending.count(userId))
			return;
		gAvatarPending.insert(userId);
	}
	std::thread([userId]()
	{
		char metaUrl[256];
		sprintf_s(metaUrl, "https://thumbnails.roblox.com/v1/users/avatar-headshot?userIds=%lld&size=150x150&format=Png&isCircular=false", (long long)userId);
		std::string jsonBody;
		std::string imageUrl;
		if (HttpGetBytes(metaUrl, jsonBody))
		{
			const auto pos = jsonBody.find("\"imageUrl\":\"");
			if (pos != std::string::npos)
			{
				const auto start = pos + 12;
				const auto end = jsonBody.find('"', start);
				if (end != std::string::npos)
				{
					imageUrl = jsonBody.substr(start, end - start);
					for (size_t i = 0; i + 1 < imageUrl.size(); ++i)
					{
						if (imageUrl[i] == '\\' && imageUrl[i + 1] == '/')
							imageUrl.erase(i, 1);
					}
				}
			}
		}
		std::string png;
		if (!imageUrl.empty())
			HttpGetBytes(imageUrl.c_str(), png);
		std::lock_guard<std::mutex> lock(gAvatarMu);
		gAvatarPending.erase(userId);
		if (!png.empty())
			gAvatarReady.push_back({ userId, std::vector<unsigned char>(png.begin(), png.end()) });
	}).detach();
}

static void PumpAvatars(Renderer& renderer)
{
	std::vector<AvatarPendingBytes> ready;
	{
		std::lock_guard<std::mutex> lock(gAvatarMu);
		ready.swap(gAvatarReady);
	}
	for (auto& item : ready)
	{
		int w = 0, h = 0;
		ID3D11ShaderResourceView* srv{ renderer.LoadTextureFromMemory(item.bytes.data(), (int)item.bytes.size(), w, h) };
		if (!srv)
			continue;
		std::lock_guard<std::mutex> lock(gAvatarMu);
		if (gAvatarSrv[item.userId])
			gAvatarSrv[item.userId]->Release();
		gAvatarSrv[item.userId] = srv;
		gAvatarSize[item.userId] = ImVec2((float)w, (float)h);
	}
}

static ID3D11ShaderResourceView* GetAvatarSrv(int64_t userId, ImVec2* sizeOut)
{
	std::lock_guard<std::mutex> lock(gAvatarMu);
	auto it = gAvatarSrv.find(userId);
	if (it == gAvatarSrv.end())
		return nullptr;
	if (sizeOut)
		*sizeOut = gAvatarSize[userId];
	return it->second;
}

static void DrawLightningBolt(ImDrawList* dl, ImVec2 head)
{
	const ImVec2 p{ head.x, head.y - 34.0f };
	const ImU32 glow{ IM_COL32(255, 210, 40, 70) };
	const ImU32 col{ IM_COL32(255, 230, 80, 255) };
	const ImVec2 pts[6]{
		{ p.x + 2.0f, p.y },
		{ p.x + 8.0f, p.y + 10.0f },
		{ p.x + 1.0f, p.y + 10.0f },
		{ p.x + 10.0f, p.y + 24.0f },
		{ p.x + 3.0f, p.y + 13.0f },
		{ p.x + 8.0f, p.y + 13.0f }
	};
	dl->AddLine(pts[0], pts[1], glow, 5.0f);
	dl->AddLine(pts[1], pts[2], glow, 5.0f);
	dl->AddLine(pts[2], pts[3], glow, 5.0f);
	dl->AddPolyline(pts, 4, col, 0, 2.2f);
}

static bool SaveConfigFile(const std::string& name)
{
	if (name.empty())
		return false;
	json config;
	config["silentaim"]["enabled"] = Settings::silentAimEnabled;
	config["silentaim"]["lockPart"] = Settings::silentAimLockPart;
	config["silentaim"]["FOVradius"] = Settings::silentAimFOVRadius;
	config["aimbot"]["enabled"] = Settings::aimbotEnabled;
	config["aimbot"]["FOVenabled"] = Settings::aimbotFOVEnabled;
	config["aimbot"]["FOVradius"] = Settings::aimbotFOVRadius;
	config["aimbot"]["strenght"] = Settings::aimbotStrenght;
	config["aimbot"]["lockPart"] = Settings::aimbotLockPart;
	config["aimbot"]["key"] = Settings::aimbotKey;
	config["aimbot"]["toggleLock"] = Settings::aimbotToggleLock;
	config["aimbot"]["predictionEnabled"] = Settings::aimbotPredictionEnabled;
	config["aimbot"]["predictionX"] = Settings::aimbotPredictionX;
	config["aimbot"]["predictionY"] = Settings::aimbotPredictionY;
	config["aimbot"]["FOVcolor"] = { Settings::aimbotFovColor.x, Settings::aimbotFovColor.y, Settings::aimbotFovColor.z, Settings::aimbotFovColor.w };
	config["triggerbot"]["enabled"] = Settings::triggerbotEnabled;
	config["triggerbot"]["indicateClicking"] = Settings::triggerbotIndicateClicking;
	config["triggerbot"]["detectionRadius"] = Settings::triggerbotDetectionRadius;
	config["triggerbot"]["triggerPart"] = Settings::triggerbotTriggerPart;
	config["triggerbot"]["key"] = Settings::triggerbotKey;
	config["esp"]["enabled"] = Settings::espEnabled;
	config["esp"]["filled"] = Settings::espFilled;
	config["esp"]["showDistance"] = Settings::espShowDistance;
	config["esp"]["showName"] = Settings::espShowName;
	config["esp"]["showHealth"] = Settings::espShowHealth;
	config["esp"]["ignoreDeadPlayers"] = Settings::espIgnoreDeadPlrs;
	config["esp"]["distance"] = Settings::espDistance;
	config["esp"]["type"] = Settings::espType;
	config["esp"]["color"] = { Settings::espColor.x, Settings::espColor.y, Settings::espColor.z, Settings::espColor.w };
	config["tracers"]["enabled"] = Settings::tracersEnabled;
	config["tracers"]["type"] = Settings::tracerType;
	config["tracers"]["color"] = { Settings::tracerColor.x, Settings::tracerColor.y, Settings::tracerColor.z, Settings::tracerColor.w };
	config["settings"]["rbxWindowNeedsToBeSelected"] = Settings::rbxWindowNeedsToBeSelected;
	config["settings"]["mainLoopDelay"] = Settings::mainLoopDelay;
	config["settings"]["autoSave"] = Settings::autoSaveEnabled;
	config["settings"]["hideSmiteLogo"] = Settings::hideSmiteLogo;
	config["misc"]["noclipEnabled"] = Settings::noclipEnabled;
	config["misc"]["flyEnabled"] = Settings::flyEnabled;
	config["misc"]["flyKey"] = Settings::flyKey;
	config["misc"]["flySpeed"] = Settings::flySpeed;
	config["misc"]["flyMode"] = Settings::flyMode;
	config["misc"]["walkSpeedEnabled"] = Settings::walkSpeedEnabled;
	config["misc"]["walkSpeedSet"] = Settings::walkSpeedSet;
	config["misc"]["walkSpeedKey"] = Settings::walkSpeedKey;
	config["misc"]["jumpPowerEnabled"] = Settings::jumpPowerEnabled;
	config["misc"]["jumpPowerSet"] = Settings::jumpPowerSet;
	config["misc"]["jumpPowerKey"] = Settings::jumpPowerKey;
	config["misc"]["orbitDistanceMultiplier"] = Settings::orbitDistanceMultiplier;
	config["misc"]["orbitSpeedMultiplier"] = Settings::orbitSpeedMultiplier;
	config["misc"]["behindPlayerEnabled"] = Settings::behindPlayerEnabled;
	config["misc"]["behindPlayerKey"] = Settings::behindPlayerKey;
	config["misc"]["behindPlayerDistance"] = Settings::behindPlayerDistance;
	config["misc"]["behindPlayerFOV"] = Settings::behindPlayerFOV;
	config["misc"]["streamproofEnabled"] = Settings::streamproofEnabled;
	std::filesystem::create_directories("configs");
	const std::filesystem::path path{ std::filesystem::path("configs") / (name + ".json") };
	std::ofstream oF(path);
	if (!oF.is_open())
		return false;
	oF << config.dump(4);
	return true;
}

static bool LoadConfigFile(const std::string& name)
{
	if (name.empty())
		return false;
	const std::filesystem::path path{ std::filesystem::path("configs") / (name + ".json") };
	std::ifstream iF(path);
	if (!iF.is_open())
		return false;
	json config;
	try
	{
		iF >> config;
	}
	catch (...)
	{
		return false;
	}

	if (config.contains("silentaim"))
	{
		if (config["silentaim"].contains("enabled")) Settings::silentAimEnabled = config["silentaim"]["enabled"].get<bool>();
		if (config["silentaim"].contains("lockPart")) Settings::silentAimLockPart = config["silentaim"]["lockPart"].get<std::string>();
		if (config["silentaim"].contains("FOVradius")) Settings::silentAimFOVRadius = config["silentaim"]["FOVradius"].get<float>();
	}
	if (config.contains("aimbot"))
	{
		if (config["aimbot"].contains("enabled")) Settings::aimbotEnabled = config["aimbot"]["enabled"].get<bool>();
		if (config["aimbot"].contains("FOVenabled")) Settings::aimbotFOVEnabled = config["aimbot"]["FOVenabled"].get<bool>();
		if (config["aimbot"].contains("FOVradius")) Settings::aimbotFOVRadius = config["aimbot"]["FOVradius"].get<float>();
		if (config["aimbot"].contains("strenght")) Settings::aimbotStrenght = config["aimbot"]["strenght"].get<float>();
		if (config["aimbot"].contains("lockPart")) Settings::aimbotLockPart = config["aimbot"]["lockPart"].get<std::string>();
		if (config["aimbot"].contains("key")) Settings::aimbotKey = config["aimbot"]["key"].get<int>();
		if (config["aimbot"].contains("toggleLock")) Settings::aimbotToggleLock = config["aimbot"]["toggleLock"].get<bool>();
		if (config["aimbot"].contains("predictionEnabled")) Settings::aimbotPredictionEnabled = config["aimbot"]["predictionEnabled"].get<bool>();
		if (config["aimbot"].contains("predictionX")) Settings::aimbotPredictionX = config["aimbot"]["predictionX"].get<float>();
		if (config["aimbot"].contains("predictionY")) Settings::aimbotPredictionY = config["aimbot"]["predictionY"].get<float>();
		if (config["aimbot"].contains("FOVcolor") && config["aimbot"]["FOVcolor"].is_array() && config["aimbot"]["FOVcolor"].size() >= 4)
		{
			Settings::aimbotFovColor.x = config["aimbot"]["FOVcolor"][0].get<float>();
			Settings::aimbotFovColor.y = config["aimbot"]["FOVcolor"][1].get<float>();
			Settings::aimbotFovColor.z = config["aimbot"]["FOVcolor"][2].get<float>();
			Settings::aimbotFovColor.w = config["aimbot"]["FOVcolor"][3].get<float>();
		}
	}
	if (config.contains("triggerbot"))
	{
		if (config["triggerbot"].contains("enabled")) Settings::triggerbotEnabled = config["triggerbot"]["enabled"].get<bool>();
		if (config["triggerbot"].contains("indicateClicking")) Settings::triggerbotIndicateClicking = config["triggerbot"]["indicateClicking"].get<bool>();
		if (config["triggerbot"].contains("detectionRadius")) Settings::triggerbotDetectionRadius = config["triggerbot"]["detectionRadius"].get<float>();
		if (config["triggerbot"].contains("triggerPart")) Settings::triggerbotTriggerPart = config["triggerbot"]["triggerPart"].get<std::string>();
		if (config["triggerbot"].contains("key")) Settings::triggerbotKey = config["triggerbot"]["key"].get<int>();
	}
	if (config.contains("esp"))
	{
		if (config["esp"].contains("enabled")) Settings::espEnabled = config["esp"]["enabled"].get<bool>();
		if (config["esp"].contains("filled")) Settings::espFilled = config["esp"]["filled"].get<bool>();
		if (config["esp"].contains("showDistance")) Settings::espShowDistance = config["esp"]["showDistance"].get<bool>();
		if (config["esp"].contains("showName")) Settings::espShowName = config["esp"]["showName"].get<bool>();
		if (config["esp"].contains("showHealth")) Settings::espShowHealth = config["esp"]["showHealth"].get<bool>();
		if (config["esp"].contains("ignoreDeadPlayers")) Settings::espIgnoreDeadPlrs = config["esp"]["ignoreDeadPlayers"].get<bool>();
		if (config["esp"].contains("distance")) Settings::espDistance = config["esp"]["distance"].get<int>();
		if (config["esp"].contains("type")) Settings::espType = config["esp"]["type"].get<std::string>();
		if (config["esp"].contains("color") && config["esp"]["color"].is_array() && config["esp"]["color"].size() >= 4)
		{
			Settings::espColor.x = config["esp"]["color"][0].get<float>();
			Settings::espColor.y = config["esp"]["color"][1].get<float>();
			Settings::espColor.z = config["esp"]["color"][2].get<float>();
			Settings::espColor.w = config["esp"]["color"][3].get<float>();
		}
	}
	if (config.contains("tracers"))
	{
		if (config["tracers"].contains("enabled")) Settings::tracersEnabled = config["tracers"]["enabled"].get<bool>();
		if (config["tracers"].contains("type")) Settings::tracerType = config["tracers"]["type"].get<std::string>();
		if (config["tracers"].contains("color") && config["tracers"]["color"].is_array() && config["tracers"]["color"].size() >= 4)
		{
			Settings::tracerColor.x = config["tracers"]["color"][0].get<float>();
			Settings::tracerColor.y = config["tracers"]["color"][1].get<float>();
			Settings::tracerColor.z = config["tracers"]["color"][2].get<float>();
			Settings::tracerColor.w = config["tracers"]["color"][3].get<float>();
		}
	}
	if (config.contains("settings"))
	{
		if (config["settings"].contains("rbxWindowNeedsToBeSelected")) Settings::rbxWindowNeedsToBeSelected = config["settings"]["rbxWindowNeedsToBeSelected"].get<bool>();
		if (config["settings"].contains("mainLoopDelay")) Settings::mainLoopDelay = config["settings"]["mainLoopDelay"].get<int>();
		if (config["settings"].contains("autoSave")) Settings::autoSaveEnabled = config["settings"]["autoSave"].get<bool>();
		if (config["settings"].contains("hideSmiteLogo")) Settings::hideSmiteLogo = config["settings"]["hideSmiteLogo"].get<bool>();
	}
	if (config.contains("misc"))
	{
		if (config["misc"].contains("noclipEnabled")) Settings::noclipEnabled = config["misc"]["noclipEnabled"].get<bool>();
		if (config["misc"].contains("flyEnabled")) Settings::flyEnabled = config["misc"]["flyEnabled"].get<bool>();
		if (config["misc"].contains("flyKey")) Settings::flyKey = config["misc"]["flyKey"].get<int>();
		if (config["misc"].contains("flySpeed")) Settings::flySpeed = config["misc"]["flySpeed"].get<float>();
		if (config["misc"].contains("flyMode")) Settings::flyMode = config["misc"]["flyMode"].get<std::string>();
		if (config["misc"].contains("walkSpeedEnabled")) Settings::walkSpeedEnabled = config["misc"]["walkSpeedEnabled"].get<bool>();
		if (config["misc"].contains("walkSpeedSet")) Settings::walkSpeedSet = config["misc"]["walkSpeedSet"].get<int>();
		if (config["misc"].contains("walkSpeedKey")) Settings::walkSpeedKey = config["misc"]["walkSpeedKey"].get<int>();
		if (config["misc"].contains("jumpPowerEnabled")) Settings::jumpPowerEnabled = config["misc"]["jumpPowerEnabled"].get<bool>();
		if (config["misc"].contains("jumpPowerSet")) Settings::jumpPowerSet = config["misc"]["jumpPowerSet"].get<int>();
		if (config["misc"].contains("jumpPowerKey")) Settings::jumpPowerKey = config["misc"]["jumpPowerKey"].get<int>();
		if (config["misc"].contains("orbitDistanceMultiplier")) Settings::orbitDistanceMultiplier = config["misc"]["orbitDistanceMultiplier"].get<float>();
		if (config["misc"].contains("orbitSpeedMultiplier")) Settings::orbitSpeedMultiplier = config["misc"]["orbitSpeedMultiplier"].get<float>();
		if (config["misc"].contains("behindPlayerEnabled")) Settings::behindPlayerEnabled = config["misc"]["behindPlayerEnabled"].get<bool>();
		if (config["misc"].contains("behindPlayerKey")) Settings::behindPlayerKey = config["misc"]["behindPlayerKey"].get<int>();
		if (config["misc"].contains("behindPlayerDistance")) Settings::behindPlayerDistance = config["misc"]["behindPlayerDistance"].get<float>();
		if (config["misc"].contains("behindPlayerFOV")) Settings::behindPlayerFOV = config["misc"]["behindPlayerFOV"].get<float>();
		if (config["misc"].contains("streamproofEnabled")) Settings::streamproofEnabled = config["misc"]["streamproofEnabled"].get<bool>();
	}
	return true;
}

static void RefreshGuiConfigs(SkechStyle::DemoState& st)
{
	const std::vector<std::string> files{ ListConfigFiles() };
	st.configCount = 0;
	st.configIdx = 0;
	for (const std::string& name : files)
	{
		if (st.configCount >= SkechStyle::DemoState::MaxConfigs)
			break;
		strncpy_s(st.configList[st.configCount], name.c_str(), _TRUNCATE);
		st.configListPtrs[st.configCount] = st.configList[st.configCount];
		if (name == Settings::configFileName)
			st.configIdx = st.configCount;
		++st.configCount;
	}
	st.requestRefreshConfigs = false;
}

static int GuiIndexOf(const char* const* items, int n, const std::string& s)
{
	for (int i = 0; i < n; ++i)
		if (s == items[i])
			return i;
	return 0;
}

static const char* kGuiLockParts[]{ "Closest", "Head", "Torso", "Left Arm", "Right Arm", "Left Leg", "Right Leg" };
static const char* kGuiTrigParts[]{ "Closest", "Head", "Torso", "Left Arm", "Right Arm" };
static const char* kGuiEspTypes[]{ "Square", "Skeleton", "Corners" };
static const char* kGuiTracerTypes[]{ "Mouse", "Corner", "Top", "Bottom" };
static const char* kGuiFlyModes[]{ "Default", "CFrame", "Position", "Velocity", "Hybrid", "PlatformStand", "Anchored" };
static const char* kGuiTabs[]{ "Aiming", "Visuals", "Settings", "Misc", "Gambling", "Keybinds" };

static void PullGui(SkechStyle::DemoState& st)
{
	st.handleInsert = false;
	st.requestForceReset = false;
	st.fillBackdrop = false;
	st.hostExtraWindows = true;
	st.menuVisible = Settings::mainMenuVisible;
	st.friendsWin = Settings::friendsListVisible;
	st.themeWin = Settings::themeWinVisible;
	st.adminWin = Settings::adminWinVisible;
	st.explorerWin = Settings::explorerWinVisible;
	st.nav = GuiIndexOf(kGuiTabs, IM_ARRAYSIZE(kGuiTabs), Settings::currentTab);
	st.aimbotEnabled = Settings::aimbotEnabled;
	st.aimbotFOVEnabled = Settings::aimbotFOVEnabled;
	st.aimbotPredictionEnabled = Settings::aimbotPredictionEnabled;
	st.aimbotToggleLock = Settings::aimbotToggleLock;
	st.aimbotFOVRadius = Settings::aimbotFOVRadius;
	st.aimbotStrenght = Settings::aimbotStrenght;
	st.aimbotPredictionX = Settings::aimbotPredictionX;
	st.aimbotPredictionY = Settings::aimbotPredictionY;
	st.aimbotLockPart = GuiIndexOf(kGuiLockParts, IM_ARRAYSIZE(kGuiLockParts), Settings::aimbotLockPart);
	st.aimbotKey = Settings::aimbotKey;
	st.aimbotFovColor = Settings::aimbotFovColor;
	st.triggerbotEnabled = Settings::triggerbotEnabled;
	st.triggerbotIndicateClicking = Settings::triggerbotIndicateClicking;
	st.triggerbotDetectionRadius = Settings::triggerbotDetectionRadius;
	st.triggerbotTriggerPart = GuiIndexOf(kGuiTrigParts, IM_ARRAYSIZE(kGuiTrigParts), Settings::triggerbotTriggerPart);
	st.triggerbotKey = Settings::triggerbotKey;
	st.silentAimEnabled = Settings::silentAimEnabled;
	st.silentAimLockPart = GuiIndexOf(kGuiLockParts, IM_ARRAYSIZE(kGuiLockParts), Settings::silentAimLockPart);
	st.silentAimFOVRadius = Settings::silentAimFOVRadius;
	st.espEnabled = Settings::espEnabled;
	st.espFilled = Settings::espFilled;
	st.espShowName = Settings::espShowName;
	st.espShowHealth = Settings::espShowHealth;
	st.espShowDistance = Settings::espShowDistance;
	st.espIgnoreDeadPlrs = Settings::espIgnoreDeadPlrs;
	st.espType = GuiIndexOf(kGuiEspTypes, IM_ARRAYSIZE(kGuiEspTypes), Settings::espType);
	st.espDistance = Settings::espDistance;
	st.espColor = Settings::espColor;
	st.tracersEnabled = Settings::tracersEnabled;
	st.tracerType = GuiIndexOf(kGuiTracerTypes, IM_ARRAYSIZE(kGuiTracerTypes), Settings::tracerType);
	st.tracerColor = Settings::tracerColor;
	strncpy_s(st.configFileName, Settings::configFileName, _TRUNCATE);
	if (st.requestRefreshConfigs || st.configCount == 0)
		RefreshGuiConfigs(st);
	st.autoSaveEnabled = Settings::autoSaveEnabled;
	st.rbxWindowNeedsToBeSelected = Settings::rbxWindowNeedsToBeSelected;
	st.mainLoopDelay = Settings::mainLoopDelay;
	st.toggleGuiKey = Settings::toggleGuiKey;
	st.tpX = Settings::othersTeleportPos.x;
	st.tpY = Settings::othersTeleportPos.y;
	st.tpZ = Settings::othersTeleportPos.z;
	st.orbitDistanceMultiplier = Settings::orbitDistanceMultiplier;
	st.orbitSpeedMultiplier = Settings::orbitSpeedMultiplier;
	st.flyEnabled = Settings::flyEnabled;
	st.flyKey = Settings::flyKey;
	st.flyMode = GuiIndexOf(kGuiFlyModes, IM_ARRAYSIZE(kGuiFlyModes), Settings::flyMode);
	st.flySpeed = Settings::flySpeed;
	st.behindPlayerEnabled = Settings::behindPlayerEnabled;
	st.behindPlayerKey = Settings::behindPlayerKey;
	st.behindPlayerDistance = Settings::behindPlayerDistance;
	st.behindPlayerFOV = Settings::behindPlayerFOV;
	st.noclipEnabled = Settings::noclipEnabled;
	st.streamproofEnabled = Settings::streamproofEnabled;
	st.walkSpeedEnabled = Settings::walkSpeedEnabled;
	st.walkSpeedSet = Settings::walkSpeedSet;
	st.walkSpeedKey = Settings::walkSpeedKey;
	st.jumpPowerEnabled = Settings::jumpPowerEnabled;
	st.jumpPowerSet = Settings::jumpPowerSet;
	st.jumpPowerKey = Settings::jumpPowerKey;
	st.slot1 = Settings::gamblingSlotsNumber1;
	st.slot2 = Settings::gamblingSlotsNumber2;
	st.slot3 = Settings::gamblingSlotsNumber3;
	st.keybindListVisible = Settings::keybindListVisible;
	strncpy_s(st.themeFileName, Settings::themeFileName, _TRUNCATE);
	st.ownerBring = Settings::ownerBringEnabled;
	st.ownerFollow = Settings::ownerFollowEnabled;
	st.ownerSpin = Settings::ownerSpinEnabled;
	st.ownerFreeze = Settings::ownerFreezeEnabled;
	st.ownerFling = Settings::ownerFlingEnabled;
	st.ownerJumpOnly = Settings::ownerJumpOnlyEnabled;
	st.highEndVisuals = Settings::highEndVisuals;
	st.sessionBoost = Settings::sessionBoost;
	st.espPreviewOpened = Settings::espPreviewOpened;
}

static void PushGui(const SkechStyle::DemoState& st)
{
	Settings::mainMenuVisible = st.menuVisible;
	Settings::friendsListVisible = st.friendsWin;
	Settings::themeWinVisible = st.themeWin;
	Settings::adminWinVisible = st.adminWin;
	Settings::explorerWinVisible = st.explorerWin;
	if (st.nav >= 0 && st.nav < IM_ARRAYSIZE(kGuiTabs))
		Settings::currentTab = kGuiTabs[st.nav];
	Settings::aimbotEnabled = st.aimbotEnabled;
	Settings::aimbotFOVEnabled = st.aimbotFOVEnabled;
	Settings::aimbotPredictionEnabled = st.aimbotPredictionEnabled;
	Settings::aimbotToggleLock = st.aimbotToggleLock;
	Settings::aimbotFOVRadius = st.aimbotFOVRadius;
	Settings::aimbotStrenght = st.aimbotStrenght;
	Settings::aimbotPredictionX = st.aimbotPredictionX;
	Settings::aimbotPredictionY = st.aimbotPredictionY;
	Settings::aimbotLockPart = kGuiLockParts[st.aimbotLockPart];
	Settings::aimbotKey = st.aimbotKey;
	Settings::aimbotFovColor = st.aimbotFovColor;
	Settings::triggerbotEnabled = st.triggerbotEnabled;
	Settings::triggerbotIndicateClicking = st.triggerbotIndicateClicking;
	Settings::triggerbotDetectionRadius = st.triggerbotDetectionRadius;
	Settings::triggerbotTriggerPart = kGuiTrigParts[st.triggerbotTriggerPart];
	Settings::triggerbotKey = st.triggerbotKey;
	Settings::silentAimEnabled = st.silentAimEnabled;
	Settings::silentAimLockPart = kGuiLockParts[st.silentAimLockPart];
	Settings::silentAimFOVRadius = st.silentAimFOVRadius;
	Settings::espEnabled = st.espEnabled;
	Settings::espFilled = st.espFilled;
	Settings::espShowName = st.espShowName;
	Settings::espShowHealth = st.espShowHealth;
	Settings::espShowDistance = st.espShowDistance;
	Settings::espIgnoreDeadPlrs = st.espIgnoreDeadPlrs;
	Settings::espType = kGuiEspTypes[st.espType];
	Settings::espDistance = st.espDistance;
	Settings::espColor = st.espColor;
	Settings::tracersEnabled = st.tracersEnabled;
	Settings::tracerType = kGuiTracerTypes[st.tracerType];
	Settings::tracerColor = st.tracerColor;
	strncpy_s(Settings::configFileName, st.configFileName, _TRUNCATE);
	Settings::autoSaveEnabled = st.autoSaveEnabled;
	Settings::rbxWindowNeedsToBeSelected = st.rbxWindowNeedsToBeSelected;
	Settings::mainLoopDelay = st.mainLoopDelay;
	Settings::toggleGuiKey = st.toggleGuiKey;
	Settings::othersTeleportPos = { st.tpX, st.tpY, st.tpZ };
	Settings::orbitDistanceMultiplier = st.orbitDistanceMultiplier;
	Settings::orbitSpeedMultiplier = st.orbitSpeedMultiplier;
	Settings::flyEnabled = st.flyEnabled;
	Settings::flyKey = st.flyKey;
	Settings::flyMode = kGuiFlyModes[st.flyMode];
	Settings::flySpeed = st.flySpeed;
	Settings::behindPlayerEnabled = st.behindPlayerEnabled;
	Settings::behindPlayerKey = st.behindPlayerKey;
	Settings::behindPlayerDistance = st.behindPlayerDistance;
	Settings::behindPlayerFOV = st.behindPlayerFOV;
	Settings::noclipEnabled = st.noclipEnabled;
	Settings::streamproofEnabled = st.streamproofEnabled;
	Settings::walkSpeedEnabled = st.walkSpeedEnabled;
	Settings::walkSpeedSet = st.walkSpeedSet;
	Settings::walkSpeedKey = st.walkSpeedKey;
	Settings::jumpPowerEnabled = st.jumpPowerEnabled;
	Settings::jumpPowerSet = st.jumpPowerSet;
	Settings::jumpPowerKey = st.jumpPowerKey;
	Settings::gamblingSlotsNumber1 = st.slot1;
	Settings::gamblingSlotsNumber2 = st.slot2;
	Settings::gamblingSlotsNumber3 = st.slot3;
	Settings::gamblingBalance = st.gamblingBalance;
	Settings::gamblingLastYmd = st.gamblingLastYmd;
	Settings::keybindListVisible = st.keybindListVisible;
	strncpy_s(Settings::themeFileName, st.themeFileName, _TRUNCATE);
	Settings::ownerBringEnabled = st.ownerBring;
	Settings::ownerFollowEnabled = st.ownerFollow;
	Settings::ownerSpinEnabled = st.ownerSpin;
	Settings::ownerFreezeEnabled = st.ownerFreeze;
	Settings::ownerFlingEnabled = st.ownerFling;
	Settings::ownerJumpOnlyEnabled = st.ownerJumpOnly;
	Settings::espPreviewOpened = st.espPreviewOpened;
	Settings::sessionBoost = st.sessionBoost;
}

int main()
{
	SetConsoleTitleA("Dk External v1.2.6");

	// Force latest GitHub release before anything else — old builds cannot continue.
	{
		const Updater::Result updateResult = Updater::CheckAndUpdate();
		if (updateResult == Updater::Result::ExitForUpdate)
			ExitProcess(0); // let the updater script replace this exe and relaunch
		if (updateResult == Updater::Result::ExitBlocked)
			return 1;
	}

	std::cout << "Loading local offsets (" << Offsets::clientVersion << ")...\n";

	if (!Offsets::fetchOffsets())
	{
		std::cout << "Failed to load offsets!\n";

		system("pause");
		return 1;
	}
	else
	{
		std::cout << "Loaded offsets.\n";
	}

	if (!KeyAuth::PromptAndAuthenticate())
		return 1;

	std::cout << "\nPerformance mode:\n";
	std::cout << "  [1] High end  (full visuals)\n";
	std::cout << "  [2] Low end   (optimized for weaker PCs)\n";
	std::cout << "Select (1/2): ";

	{
		std::string perfChoice;
		std::getline(std::cin, perfChoice);

		if (!perfChoice.empty() && perfChoice[0] == '2')
		{
			Settings::highEndVisuals = false;
			Settings::tracersEnabled = false;
			if (Settings::mainLoopDelay < 12)
				Settings::mainLoopDelay = 12;
			std::cout << "Low end mode enabled (aim + ESP prioritized).\n";
		}
		else
		{
			Settings::highEndVisuals = true;
			std::cout << "High end mode enabled.\n";
		}
	}

	std::cout << "Logged in as " << (KeyAuth::username.empty() ? "license user" : KeyAuth::username)
		<< " [" << KeyAuth::role << "] (level " << KeyAuth::roleLevel << ")\n";

	std::cout << "\nType logout to switch keys, or press ENTER to attach.\n> ";
	{
		std::string attachLine;
		std::getline(std::cin, attachLine);
		std::string lower = attachLine;
		for (char& c : lower) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
		while (!lower.empty() && (lower.front() == ' ' || lower.front() == '\t')) lower.erase(lower.begin());
		while (!lower.empty() && (lower.back() == ' ' || lower.back() == '\t' || lower.back() == '\r')) lower.pop_back();
		if (lower == "logout" || lower == "log out")
		{
			std::cout << "Logging out and restarting...\n";
			KeyAuth::LogoutAndRestart();
		}
	}

	system("cls");
	std::cout << "\n"; // keep line 0 free for live key timer

	if (RBX::Memory::attach())
	{
		std::cout << "Attached!\n\n";

		Sleep(1000);

		system("cls");
		std::cout << "\n";
	}
	else
	{
		std::cout << "Failed to attach.\n";

		system("pause");

		return 1;
	}

	void* dataModelAddr;
	dataModelAddr = RBX::getDataModel();

	if (RBX::Memory::read<int>((void*)((uintptr_t)dataModelAddr + Offsets::GameId)) == 0)
	{
		std::cout << "You need to join a game.\n";

		while (RBX::Memory::read<int>((void*)((uintptr_t)dataModelAddr + Offsets::GameId)) == 0)
		{
			dataModelAddr = RBX::getDataModel();
			Sleep(1000);
		}

		system("cls");
		std::cout << "\n";
	}

	KeyAuth::StopLiveCountdown();
	FreeConsole();

	json settingsJ;

	if (!std::filesystem::exists("settings.json"))
	{
		std::ofstream oF("settings.json");

		json s;
		s["theme"] = "default";

		oF << s.dump(4);

		oF.close();
	}

	if (!std::filesystem::exists("themes/"))
	{
		std::filesystem::create_directory("themes");
	}

	if (!std::filesystem::exists("configs/"))
	{
		std::filesystem::create_directory("configs");
	}

	std::ifstream settingsIF("settings.json");
	std::string settingsContents((std::istreambuf_iterator<char>(settingsIF)), std::istreambuf_iterator<char>());

	settingsJ = json::parse(settingsContents);

	int monitorWidth{ GetSystemMetrics(SM_CXSCREEN) };
	int monitorHeight{ GetSystemMetrics(SM_CYSCREEN) };

	Renderer renderer;
	renderer.Init();
	SkechStyle::ApplyTheme();

	SkechStyle::DemoState guiSt{};
	int smiteLogoW = 0, smiteLogoH = 0;
	ID3D11ShaderResourceView* smiteLogoImg{ renderer.LoadTexture("Assets/smitdk_logo.png", smiteLogoW, smiteLogoH) };
	if (smiteLogoImg)
	{
		guiSt.logoTex = smiteLogoImg;
		guiSt.logoSize = ImVec2((float)smiteLogoW, (float)smiteLogoH);
	}
	guiSt.onSaveConfig = [&guiSt]()
	{
		const char* name = guiSt.configFileName[0] ? guiSt.configFileName : "autosave";
		if (SaveConfigFile(name))
		{
			strncpy_s(Settings::configFileName, name, _TRUNCATE);
			guiSt.requestRefreshConfigs = true;
		}
	};
	guiSt.onLoadConfig = [&guiSt]()
	{
		if (!guiSt.configFileName[0])
			return;
		if (LoadConfigFile(guiSt.configFileName))
			strncpy_s(Settings::configFileName, guiSt.configFileName, _TRUNCATE);
	};

	if (Settings::highEndVisuals)
		Snowflake::CreateSnowFlakes(snow, SNOW_LIMIT, 5.0f, 15.0f, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), Snowflake::vec3(0.0f, 0.005f), IM_COL32(255, 255, 255, 100));

	ID3D11ShaderResourceView* avatarImg{ nullptr };
	int avatarImgW, avatarImgH;

	avatarImg = renderer.LoadTextureFromResource(IDR_ESP_PREVIEW_IMG, avatarImgW, avatarImgH);

	ID3D11ShaderResourceView* dkLogoImg{ nullptr };
	int dkLogoImgW, dkLogoImgH;
	dkLogoImg = renderer.LoadTextureFromResource(IDR_DK_LOGO, dkLogoImgW, dkLogoImgH);

	ID3D11ShaderResourceView* menuIconImg{ nullptr };
	int menuIconImgW, menuIconImgH;

	menuIconImg = renderer.LoadTextureFromResource(IDR_MENU_ICON, menuIconImgW, menuIconImgH);

	ID3D11ShaderResourceView* explorerIconImg{ nullptr };
	int explorerIconImgW, explorerIconImgH;

	explorerIconImg = renderer.LoadTextureFromResource(IDR_EXPLORER_ICON, explorerIconImgW, explorerIconImgH);

	ID3D11ShaderResourceView* aimingIconImg{ nullptr };
	int aimingIconImgW, aimingIconImgH;

	aimingIconImg = renderer.LoadTextureFromResource(IDR_BULLSEYE_ICON, aimingIconImgW, aimingIconImgH);

	ID3D11ShaderResourceView* visualsIconImg{ nullptr };
	int visualsIconImgW, visualsIconImgH;

	visualsIconImg = renderer.LoadTextureFromResource(IDR_ESP_PERSON_ICON, visualsIconImgW, visualsIconImgH);

	ID3D11ShaderResourceView* settingsIconImg{ nullptr };
	int settingsIconImgW, settingsIconImgH;

	settingsIconImg = renderer.LoadTextureFromResource(IDR_GEAR_ICON, settingsIconImgW, settingsIconImgH);

	ID3D11ShaderResourceView* miscIconImg{ nullptr };
	int miscIconImgW, miscIconImgH;

	miscIconImg = renderer.LoadTextureFromResource(IDR_DICE_ICON, miscIconImgW, miscIconImgH);

	ID3D11ShaderResourceView* themeIconImg{ nullptr };
	int themeIconImgW, themeIconImgH;

	themeIconImg = renderer.LoadTextureFromResource(IDR_PAINT_BOARD_ICON, themeIconImgW, themeIconImgH);

	ID3D11ShaderResourceView* keybindsIconImg{ nullptr };
	int keybindsIconImgW, keybindsIconImgH;

	keybindsIconImg = renderer.LoadTextureFromResource(IDR_KEYBINDS_ICON, keybindsIconImgW, keybindsIconImgH);

	ID3D11ShaderResourceView* friendsIconImg{ nullptr };
	int friendsIconImgW, friendsIconImgH;

	friendsIconImg = renderer.LoadTextureFromResource(IDR_FRIENDS_ICON, friendsIconImgW, friendsIconImgH);

	ID3D11ShaderResourceView* gamblingIconImg{ nullptr };
	int gamblingIconImgW, gamblingIconImgH;

	gamblingIconImg = renderer.LoadTextureFromResource(IDR_CARDS_ICON, gamblingIconImgW, gamblingIconImgH);

	ID3D11ShaderResourceView* adminIconImg{ nullptr };
	int adminIconImgW, adminIconImgH;
	adminIconImg = renderer.LoadTextureFromResource(IDR_ADMIN_ICON, adminIconImgW, adminIconImgH);

	RBX::VisualEngine visualEngine{ RBX::Memory::read<void*>((void*)((uintptr_t)RBX::Memory::getRobloxBaseAddr() + Offsets::VisualEnginePointer)) };

	RBX::Instance dataModel{ dataModelAddr };
	RBX::Instance workspace{ dataModel.findFirstChild("Workspace") };
	RBX::Instance players{ dataModel.findFirstChild("Players") };

	RBX::Instance localPlayer{ RBX::Memory::read<void*>((void*)((uintptr_t)players.address + Offsets::LocalPlayer)) };
	RBX::Instance localPlayerModelInstance{ localPlayer.getModelInstance() };
	RBX::Instance humanoid{ localPlayerModelInstance.findFirstChild("Humanoid") };
	RBX::Instance hrp{ localPlayerModelInstance.findFirstChild("HumanoidRootPart") };

	RBX::Instance camera{ RBX::Memory::read<void*>((void*)((uintptr_t)workspace.address + Offsets::Camera)) };

	RBX::Instance lockedPlr{ nullptr };
	RBX::Instance stickyLockPart{ nullptr };
	bool locked{ false };
	bool keybindPrevDown{ false };

	if (settingsJ["theme"] != "default")
	{
		loadTheme(featureBGColor, glowColor, settingsJ["theme"].get<std::string>());
	}
	else
	{
		ImGuiStyle& style{ ImGui::GetStyle() };

		style.Colors[ImGuiCol_Tab] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		style.Colors[ImGuiCol_TabHovered] = ImVec4(0.5f, 0.0f, 0.0f, 0.2f);
		style.Colors[ImGuiCol_TabActive] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.0f, 0.0f, 0.0f, 0.2f);
		// Cleaner gray window background; black cards/sidebar drawn separately
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.14f, 0.14f, 0.15f, 0.96f);
		style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.08f, 0.08f, 0.08f, 1.0f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.18f, 0.10f, 0.10f, 1.00f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.28f, 0.12f, 0.12f, 1.00f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

		//style.Colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 0.25f, 0.25f, 1.00f);

		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.85f, 0.20f, 0.20f, 1.00f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.25f, 0.25f, 1.00f);

		style.Colors[ImGuiCol_Button] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.22f, 0.10f, 0.10f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.35f, 0.12f, 0.12f, 1.00f);

		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.10f, 0.10f, 0.11f, 0.96f);

		style.WindowPadding = ImVec2(12, 12);
		style.FramePadding = ImVec2(8, 4);
		style.ItemSpacing = ImVec2(10, 6);
		style.WindowRounding = 6.0f;
		style.FrameRounding = 6.0f;
		style.GrabRounding = 6.0f;
		style.TabRounding = 6.0f;
	}

	if (!Settings::highEndVisuals)
	{
		ImGuiStyle& lowStyle{ ImGui::GetStyle() };
		lowStyle.AntiAliasedLines = false;
		lowStyle.AntiAliasedFill = false;
		lowStyle.AntiAliasedLinesUseTex = false;
		lowStyle.WindowRounding = 2.0f;
		lowStyle.FrameRounding = 2.0f;
		lowStyle.GrabRounding = 2.0f;
		lowStyle.TabRounding = 2.0f;
		lowStyle.ScrollbarRounding = 2.0f;
		lowStyle.WindowPadding = ImVec2(10, 10);
		lowStyle.ItemSpacing = ImVec2(8, 4);
	}

	RBX::Instance silent_closestPlr{ nullptr };
	RBX::Vector2 silent_lastPos{};
	RBX::Vector2 silent_targetPos{};

	std::thread([&]() {
		while (true)
		{
			if (!Settings::silentAimEnabled)
			{
				Sleep(100);

				continue;
			}

			RBX::Instance bestPlr{ nullptr };
			RBX::Vector2 bestPos{};

			float closestDistance{ Settings::silentAimFOVRadius };
			silent_closestPlr = nullptr;

			POINT mousePos;
			GetCursorPos(&mousePos);

			RBX::Instance mouseService{ dataModel.findFirstChildOfClass("MouseService") };
			RBX::Instance inputObject{ RBX::Memory::read<void*>((void*)((uintptr_t)mouseService.address + Offsets::InputObject)) };

			for (RBX::Instance player : players.getChildren())
			{
				if (player.className() != "Player")
					continue;

				const std::string playerName{ player.name() };
				if (playerName.empty() || playerName == localPlayer.name() || IsFriend(playerName))
					continue;

				RBX::Instance plr{ player.getModelInstance() };
				if (!plr.address)
					continue;

				RBX::Instance lockPart{ resolveLockPart(plr, Settings::silentAimLockPart, mousePos, visualEngine) };
				if (!lockPart.address)
					continue;

				RBX::Vector3 lockPartPos{ lockPart.getPosition() };
				RBX::Vector2 screenPos{ visualEngine.worldToScreen(lockPartPos) };

				float dx{ screenPos.x - mousePos.x };
				float dy{ screenPos.y - mousePos.y };
				float dist{ sqrtf(dx * dx + dy * dy) };

				if (dist < Settings::silentAimFOVRadius && dist < closestDistance)
				{
					closestDistance = dist;
					bestPlr = plr;
					bestPos = screenPos;
				}
			}

			silent_closestPlr = bestPlr;
			silent_targetPos = bestPos;

			if (silent_closestPlr.address == nullptr)
			{
				silent_targetPos.x = static_cast<float>(mousePos.x);
				silent_targetPos.y = static_cast<float>(mousePos.y);
			}

			Sleep(1);
		}
	}).detach();

	std::thread([&]() {
		while (true)
		{
			if (!Settings::silentAimEnabled)
			{
				Sleep(100);

				continue;
			}

			RBX::Instance mouseService{ dataModel.findFirstChildOfClass("MouseService") };
			RBX::Instance inputObject{ RBX::Memory::read<void*>((void*)((uintptr_t)mouseService.address + Offsets::InputObject)) };

			RBX::Memory::write<RBX::Vector2>((void*)((uintptr_t)inputObject.address + Offsets::MousePosition), silent_targetPos);
			RBX::Memory::write<RBX::Vector2>((void*)((uintptr_t)inputObject.address + Offsets::MousePosition), silent_targetPos);
			RBX::Memory::write<RBX::Vector2>((void*)((uintptr_t)inputObject.address + Offsets::MousePosition), silent_targetPos);
			RBX::Memory::write<RBX::Vector2>((void*)((uintptr_t)inputObject.address + Offsets::MousePosition), silent_targetPos);
			RBX::Memory::write<RBX::Vector2>((void*)((uintptr_t)inputObject.address + Offsets::MousePosition), silent_targetPos);
			RBX::Memory::write<RBX::Vector2>((void*)((uintptr_t)inputObject.address + Offsets::MousePosition), silent_targetPos);
		}
	}).detach();

	std::thread([&]() {
		bool wasOrbit{ false };
		bool savedPlatformStand{ false };
		bool timerPeriodOn{ false };
		uint8_t savedPrimFlags{ 0 };
		float angle{ 0.0f };
		char cachedName[128]{};
		void* cachedTargetPrim{ nullptr };
		void* cachedLocalPrim{ nullptr };
		ULONGLONG lastTargetRefresh{ 0 };
		RBX::Vector3 smoothCenter{};
		bool haveSmooth{ false };
		LARGE_INTEGER freq{};
		LARGE_INTEGER last{};
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&last);

		while (true)
		{
			if (!Settings::orbitEnabled)
			{
				if (wasOrbit)
				{
					if (humanoid.address)
						RBX::Memory::write<bool>((void*)((uintptr_t)humanoid.address + Offsets::PlatformStand), savedPlatformStand);
					if (cachedLocalPrim)
						RBX::Memory::write<uint8_t>((void*)((uintptr_t)cachedLocalPrim + Offsets::Anchored), savedPrimFlags);
					if (timerPeriodOn)
					{
						timeEndPeriod(1);
						timerPeriodOn = false;
					}
				}
				wasOrbit = false;
				haveSmooth = false;
				cachedName[0] = '\0';
				cachedTargetPrim = nullptr;
				cachedLocalPrim = nullptr;
				QueryPerformanceCounter(&last);
				Sleep(40);
				continue;
			}

			if (!timerPeriodOn)
			{
				timeBeginPeriod(1);
				timerPeriodOn = true;
			}

			LARGE_INTEGER now{};
			QueryPerformanceCounter(&now);
			float dt{ static_cast<float>(now.QuadPart - last.QuadPart) / static_cast<float>(freq.QuadPart) };
			last = now;
			if (dt < 0.0002f)
				dt = 0.0002f;
			if (dt > 0.033f)
				dt = 0.033f;

			if (!wasOrbit)
			{
				angle = 0.0f;
				haveSmooth = false;
				lastTargetRefresh = 0;
				if (humanoid.address)
				{
					savedPlatformStand = RBX::Memory::read<bool>((void*)((uintptr_t)humanoid.address + Offsets::PlatformStand));
					RBX::Memory::write<bool>((void*)((uintptr_t)humanoid.address + Offsets::PlatformStand), true);
				}
			}

			if (Settings::othersRobloxPlr[0] == '\0')
			{
				Settings::orbitEnabled = false;
				Sleep(1);
				continue;
			}

			cachedLocalPrim = hrp.address ? hrp.getPrimitive() : nullptr;

			const ULONGLONG nowMs{ GetTickCount64() };
			if (nowMs - lastTargetRefresh > 80ULL || strcmp(cachedName, Settings::othersRobloxPlr) != 0)
			{
				strncpy_s(cachedName, Settings::othersRobloxPlr, _TRUNCATE);
				lastTargetRefresh = nowMs;
				RBX::Instance plr{ players.findFirstChild(Settings::othersRobloxPlr) };
				RBX::Instance plrMi{ plr.address ? plr.getModelInstance() : RBX::Instance(nullptr) };
				RBX::Instance plrHrp{ plrMi.address ? plrMi.findFirstChild("HumanoidRootPart") : RBX::Instance(nullptr) };
				cachedTargetPrim = plrHrp.address ? plrHrp.getPrimitive() : nullptr;
			}

			void* targetPrim{ cachedTargetPrim };
			void* primitive{ cachedLocalPrim };
			if (!targetPrim || !primitive)
			{
				Sleep(1);
				continue;
			}

			if (!wasOrbit)
			{
				savedPrimFlags = RBX::Memory::read<uint8_t>((void*)((uintptr_t)primitive + Offsets::Anchored));
			}
			wasOrbit = true;

			if (humanoid.address)
				RBX::Memory::write<bool>((void*)((uintptr_t)humanoid.address + Offsets::PlatformStand), true);

			uint8_t flags{ savedPrimFlags };
			flags = static_cast<uint8_t>(flags & ~static_cast<uint8_t>(offsets::PrimitiveFlags::CanCollideMask));
			RBX::Memory::write<uint8_t>((void*)((uintptr_t)primitive + Offsets::Anchored), flags);

			const float omega{ 6.28318530718f * Settings::orbitSpeedMultiplier };
			angle += omega * dt;
			if (angle >= 6.28318530718f)
				angle -= 6.28318530718f;

			const float radius{ 8.0f * Settings::orbitDistanceMultiplier };
			const float s{ sinf(angle) };
			const float c{ cosf(angle) };

			const RBX::Vector3 targetPos{ RBX::Memory::read<RBX::Vector3>((void*)((uintptr_t)targetPrim + Offsets::Position)) };
			const RBX::Vector3 targetVel{ RBX::Memory::read<RBX::Vector3>((void*)((uintptr_t)targetPrim + Offsets::Velocity)) };

			if (!haveSmooth)
			{
				smoothCenter = targetPos;
				haveSmooth = true;
			}
			else
			{
				const float follow{ 1.0f - expf(-dt * 22.0f) };
				smoothCenter.x += (targetPos.x - smoothCenter.x) * follow;
				smoothCenter.y += (targetPos.y - smoothCenter.y) * follow;
				smoothCenter.z += (targetPos.z - smoothCenter.z) * follow;
			}

			const float predict{ 0.04f };
			const RBX::Vector3 center{
				smoothCenter.x + targetVel.x * predict,
				smoothCenter.y + targetVel.y * predict,
				smoothCenter.z + targetVel.z * predict
			};

			const RBX::Vector3 newPos{
				center.x + s * radius,
				center.y,
				center.z + c * radius
			};
			const RBX::Vector3 vel{
				targetVel.x + c * radius * omega,
				targetVel.y,
				targetVel.z - s * radius * omega
			};

			const RBX::Vector3 zeroSpin{ 0.0f, 0.0f, 0.0f };
			for (int burst = 0; burst < 3; ++burst)
			{
				RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)primitive + Offsets::Position), newPos);
				RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)primitive + Offsets::Velocity), vel);
				RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)primitive + offsets::Primitive::RotationVelocity), zeroSpin);
			}

			LARGE_INTEGER deadline{};
			deadline.QuadPart = now.QuadPart + (freq.QuadPart / 500);
			for (;;)
			{
				LARGE_INTEGER n{};
				QueryPerformanceCounter(&n);
				if (n.QuadPart >= deadline.QuadPart)
					break;
				const double left{ static_cast<double>(deadline.QuadPart - n.QuadPart) / static_cast<double>(freq.QuadPart) };
				if (left > 0.0015)
					Sleep(1);
				else
					Sleep(0);
			}
		}
	}).detach();

	std::thread([&]() {
		ULONGLONG lastPost{ 0 };
		ULONGLONG lastPull{ 0 };
		ULONGLONG lastCmdPost{ 0 };
		ULONGLONG lastCmdPull{ 0 };
		bool postedClear{ true };
		int64_t lastOutUid{ 0 };
		while (true)
		{
			const ULONGLONG now{ GetTickCount64() };

			if (now - lastPost > 12000ULL)
			{
				lastPost = now;
				const int64_t uid{ ReadPlayerUserId(localPlayer) };
				const std::string name{ localPlayer.address ? localPlayer.name() : std::string() };
				if (uid > 0 || !name.empty())
				{
					if (SmiteLogoHidden())
					{
						DkForgetUser(uid, name);
						std::ostringstream msg;
						msg << "DK|HIDE|" << uid << "|" << name;
						HttpPostText(kDkPresenceUrl, msg.str());
					}
					else
					{
						DkNoteUser(uid, name);
						int64_t placeId{ 0 };
						if (dataModel.address)
							placeId = RBX::Memory::read<int64_t>((void*)((uintptr_t)dataModel.address + Offsets::PlaceId));
						std::ostringstream msg;
						msg << "DK|" << placeId << "|" << uid << "|" << name;
						HttpPostText(kDkPresenceUrl, msg.str());
					}
				}
			}

			if (now - lastPull > 8000ULL)
			{
				lastPull = now;
				std::string body;
				if (HttpGetBytes("https://ntfy.sh/dk-external-users-dvcf1EcOCE/json?poll=1&since=90s", body))
				{
					struct DkEvt { long long time; bool hide; int64_t uid; std::string name; };
					std::vector<DkEvt> evts;
					std::istringstream ss(body);
					std::string line;
					while (std::getline(ss, line))
					{
						if (line.empty() || line[0] != '{')
							continue;
						try
						{
							json j = json::parse(line);
							if (j.value("event", "") != "message")
								continue;
							const std::string msg{ j.value("message", "") };
							if (msg.rfind("DK|", 0) != 0)
								continue;
							const bool hide{ msg.rfind("DK|HIDE|", 0) == 0 };
							const size_t p1{ msg.find('|', 3) };
							if (p1 == std::string::npos)
								continue;
							const size_t p2{ msg.find('|', p1 + 1) };
							if (p2 == std::string::npos)
								continue;
							const int64_t uid{ _strtoi64(msg.c_str() + p1 + 1, nullptr, 10) };
							const std::string name{ msg.substr(p2 + 1) };
							evts.push_back({ j.value("time", 0LL), hide, uid, name });
						}
						catch (...)
						{
						}
					}
					std::sort(evts.begin(), evts.end(), [](const DkEvt& a, const DkEvt& b) { return a.time < b.time; });
					for (const DkEvt& e : evts)
					{
						if (e.hide)
							DkForgetUser(e.uid, e.name);
						else
							DkNoteUser(e.uid, e.name);
					}
				}
			}

			TrollNetCmd outgoing{};
			{
				std::lock_guard<std::mutex> lock(gTrollNetMu);
				outgoing = gOutgoingTroll;
			}
			if (outgoing.Any() && outgoing.targetUid != 0 && now - lastCmdPost > 800ULL)
			{
				lastCmdPost = now;
				postedClear = false;
				lastOutUid = outgoing.targetUid;
				HttpPostText(kDkCmdUrl, PackTrollCmd(outgoing));
			}
			else if (!outgoing.Any() && !postedClear && now - lastCmdPost > 200ULL)
			{
				lastCmdPost = now;
				postedClear = true;
				TrollNetCmd clear{};
				clear.targetUid = lastOutUid;
				if (clear.targetUid != 0)
					HttpPostText(kDkCmdUrl, PackTrollCmd(clear));
			}

			if (now - lastCmdPull > 400ULL)
			{
				lastCmdPull = now;
				const int64_t myUid{ ReadPlayerUserId(localPlayer) };
				std::string body;
				if (myUid > 0 && HttpGetBytes("https://ntfy.sh/dk-external-cmds-dvcf1EcOCE/json?poll=1&since=15s", body))
				{
					TrollNetCmd best{};
					long long bestTime = 0;
					std::istringstream ss(body);
					std::string line;
					while (std::getline(ss, line))
					{
						if (line.empty() || line[0] != '{')
							continue;
						try
						{
							json j = json::parse(line);
							if (j.value("event", "") != "message")
								continue;
							TrollNetCmd parsed{};
							if (!ParseTrollCmd(j.value("message", ""), parsed))
								continue;
							if (parsed.targetUid != myUid)
								continue;
							const long long t{ j.value("time", 0LL) };
							if (t >= bestTime)
							{
								bestTime = t;
								best = parsed;
							}
						}
						catch (...)
						{
						}
					}
					if (bestTime > 0)
					{
						std::lock_guard<std::mutex> lock(gTrollNetMu);
						gIncomingTroll = best;
					}
				}
			}

			Sleep(200);
		}
	}).detach();

	ULONGLONG lastPlrRefresh{ GetTickCount64() };
	while (true)
	{
		if (RBX::Memory::read<int>((void*)((uintptr_t)dataModelAddr + Offsets::GameId)) == 0)
		{
			while (RBX::Memory::read<int>((void*)((uintptr_t)dataModelAddr + Offsets::GameId)) == 0)
			{
				dataModelAddr = RBX::getDataModel();
				Sleep(1000);
			}
		}

		HWND robloxHWND{ FindWindow(NULL, L"Roblox") };
		bool robloxFocused{ GetForegroundWindow() == robloxHWND };

		{
			static bool guiKeyPrev{ false };
			const bool guiKeyDown{ IsBindDown(Settings::toggleGuiKey) };
			if (guiKeyDown && !guiKeyPrev)
				Settings::imguiVisible = !Settings::imguiVisible;
			guiKeyPrev = guiKeyDown;
		}

		dataModel = RBX::Instance(RBX::getDataModel());
		workspace = dataModel.findFirstChild("Workspace");
		players = dataModel.findFirstChild("Players");

		localPlayer = RBX::Instance(RBX::Memory::read<void*>((void*)((uintptr_t)players.address + Offsets::LocalPlayer)));
		localPlayerModelInstance = RBX::Instance(RBX::Memory::read<void*>((void*)((uintptr_t)localPlayer.address + Offsets::ModelInstance)));
		humanoid = localPlayerModelInstance.findFirstChild("Humanoid");
		hrp = localPlayerModelInstance.findFirstChild("HumanoidRootPart");
		if (!CanHideSmiteLogo())
			Settings::hideSmiteLogo = false;
		TagSmiteUser(humanoid);

		camera = RBX::Memory::read<void*>((void*)((uintptr_t)workspace.address + Offsets::Camera));

		const ULONGLONG plrRefreshMs{ (Settings::highEndVisuals || Settings::sessionBoost) ? 100ULL : 350ULL };
		if (GetTickCount64() - lastPlrRefresh > plrRefreshMs)
		{
			playersList.clear();
			playersListNames.clear();
			for (RBX::Instance plr : players.getChildren())
			{
				if (plr.className() != "Player")
					continue;

				const std::string playerName{ plr.name() };
				if (playerName.empty())
					continue;

				RBX::Instance modelInstance{ plr.getModelInstance() };
				if (!modelInstance.address)
					continue;

				if (!modelInstance.findFirstChild("HumanoidRootPart").address)
					continue;

				playersList.push_back(modelInstance);
				playersListNames.push_back(playerName);
			}
			lastPlrRefresh = GetTickCount64();
		}

		renderer.StartRender();

		static bool lastImguiVisible{ true };
		if (Settings::imguiVisible != lastImguiVisible)
		{
			if (Settings::imguiVisible)
				SetWindowLong(renderer.hwnd, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW);
			else
				SetWindowLong(renderer.hwnd, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT);
			lastImguiVisible = Settings::imguiVisible;
		}

		if (Settings::imguiVisible)
		{
			ImGuiIO& imguiIo{ ImGui::GetIO() };
			ImVec2 mousePos{ imguiIo.MousePos };

			ImDrawList* drawList{ ImGui::GetBackgroundDrawList() };

			POINT mouse;
			GetCursorPos(&mouse);

			RECT rc;
			GetWindowRect(renderer.hwnd, &rc);

			if (Settings::highEndVisuals)
				Snowflake::Update(snow, Snowflake::vec3(mouse.x, mouse.y), Snowflake::vec3(rc.left, rc.top));

			PullGui(guiSt);
			PumpAvatars(renderer);
			PopulateGuiPlayers(guiSt, players, localPlayer);
			if (!guiSt.logoTex && dkLogoImg)
			{
				guiSt.logoTex = dkLogoImg;
				guiSt.logoSize = ImVec2((float)dkLogoImgW, (float)dkLogoImgH);
			}
			SkechStyle::DrawDemo(guiSt);
			ProcessGuiTpActions(guiSt, hrp);
			PushGui(guiSt);
			ProcessGuiPlayerActions(guiSt, players, camera, humanoid, hrp);

			if (guiSt.requestForceReset)
			{
				guiSt.requestForceReset = false;
				Settings::flyEnabled = false;
				Settings::flyKeyToggled = false;
				Settings::noclipEnabled = false;
				Settings::orbitEnabled = false;
				gForceResetLeft = 16;
			}

			if (guiSt.requestExit)
			{
				RBX::Memory::detach();
				renderer.Shutdown();
				return 0;
			}

			{
				static bool lastStreamproof{ false };
				if (Settings::streamproofEnabled != lastStreamproof)
				{
					SetWindowDisplayAffinity(renderer.hwnd, Settings::streamproofEnabled ? WDA_EXCLUDEFROMCAPTURE : WDA_NONE);
					lastStreamproof = Settings::streamproofEnabled;
				}
			}

			if (false)
			{
			const float barLeft{ (monitorWidth / 2) - 130.0f };
			const float barRight{ (monitorWidth / 2) + 130.0f };
			drawList->AddRectFilled({ barLeft, monitorHeight - 80.0f }, { barRight, monitorHeight - 40.0f }, ImColor(0.05f, 0.05f, 0.05f, 1.0f), 6.0f);
			if (Settings::highEndVisuals)
				DrawGlow(drawList, { barLeft, monitorHeight - 80.0f }, { barRight, monitorHeight - 40.0f }, glowColor, 3, 0.2f, 6.0f);

			const float midX{ static_cast<float>(monitorWidth / 2) };
			auto drawBarBtn = [&](float x, ID3D11ShaderResourceView* icon, bool& hoveredOut, float iconHalf = 12.0f)
			{
				hoveredOut = ImRect({ x - 18.0f, monitorHeight - 78.0f }, { x + 18.0f, monitorHeight - 42.0f }).Contains(mousePos);
				if (icon)
					drawList->AddImage((void*)icon, { x - iconHalf, monitorHeight - 70.0f - (iconHalf - 10.0f) }, { x + iconHalf, monitorHeight - 50.0f + (iconHalf - 10.0f) });
				drawList->AddRect({ x - 18.0f, monitorHeight - 78.0f }, { x + 18.0f, monitorHeight - 42.0f },
					hoveredOut ? IM_COL32(139, 50, 50, 255) : IM_COL32(50, 50, 50, 255), 6.0f);
			};

			bool menuBtnHovered{}, explorerBtnHovered{}, friendsBtnHovered{}, themeBtnHovered{}, adminBtnHovered{};
			drawBarBtn(midX - 90.0f, menuIconImg, menuBtnHovered, 11.0f);
			drawBarBtn(midX - 45.0f, explorerIconImg, explorerBtnHovered, 11.0f);
			drawBarBtn(midX + 0.0f, friendsIconImg, friendsBtnHovered, 14.0f);
			drawBarBtn(midX + 45.0f, themeIconImg, themeBtnHovered, 11.0f);
			drawBarBtn(midX + 90.0f, adminIconImg, adminBtnHovered, 12.0f);

			if (menuBtnHovered && imguiIo.MouseClicked[0])
				Settings::mainMenuVisible = !Settings::mainMenuVisible;
			if (menuBtnHovered)
				drawList->AddText({ mousePos.x + 15.0f, mousePos.y + 15.0f }, IM_COL32_WHITE, "Menu");

			if (explorerBtnHovered && imguiIo.MouseClicked[0])
				Settings::explorerWinVisible = !Settings::explorerWinVisible;
			if (explorerBtnHovered)
				drawList->AddText({ mousePos.x + 15.0f, mousePos.y + 15.0f }, IM_COL32_WHITE, "Explorer");

			if (friendsBtnHovered && imguiIo.MouseClicked[0])
				Settings::friendsListVisible = !Settings::friendsListVisible;
			if (friendsBtnHovered)
				drawList->AddText({ mousePos.x + 15.0f, mousePos.y + 15.0f }, IM_COL32_WHITE, "Players");

			if (themeBtnHovered && imguiIo.MouseClicked[0])
				Settings::themeWinVisible = !Settings::themeWinVisible;
			if (themeBtnHovered)
				drawList->AddText({ mousePos.x + 15.0f, mousePos.y + 15.0f }, IM_COL32_WHITE, "Theme Changer");

			if (adminBtnHovered && imguiIo.MouseClicked[0])
				Settings::adminWinVisible = !Settings::adminWinVisible;
			if (adminBtnHovered)
				drawList->AddText({ mousePos.x + 15.0f, mousePos.y + 15.0f }, IM_COL32_WHITE, "Admin");

			if (false && Settings::mainMenuVisible)
			{
				ImGui::SetNextWindowSize({ 1057, 720 });

				ImGui::Begin("DK", (bool*)0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

				ImVec2 p{ ImGui::GetCursorScreenPos() };

				ImDrawList* drawList{ ImGui::GetWindowDrawList() };

				ImVec2 winPos{ ImGui::GetWindowPos() };
				ImVec2 winSize{ ImGui::GetWindowSize() };
				if (Settings::highEndVisuals)
					DrawGlow(ImGui::GetBackgroundDrawList(), winPos, { winPos.x + winSize.x, winPos.y + winSize.y }, glowColor, 4, 0.15f, ImGui::GetStyle().WindowRounding);

				// tab bar (black)
				drawList->AddRectFilled({ p.x - 12.0f, p.y - 12.0f }, { p.x + 160.0f, p.y + 720.0f }, IM_COL32(0, 0, 0, 245), 6.0f);

				if (dkLogoImg)
					drawList->AddImage((void*)dkLogoImg, { winPos.x + 8.0f, winPos.y + 4.0f }, { winPos.x + 152.0f, winPos.y + 140.0f });

				{
					// Clip role/user text so long license keys don't spill into the content panel
					drawList->PushClipRect({ winPos.x + 8.0f, winPos.y + 120.0f }, { winPos.x + 156.0f, winPos.y + 158.0f }, true);
					const std::string roleLabel{ "[" + KeyAuth::role + "] lv" + std::to_string(KeyAuth::roleLevel) };
					const ImU32 roleCol{ KeyAuth::IsOwner() ? IM_COL32(255, 200, 60, 255)
						: (KeyAuth::IsCoOwner() ? IM_COL32(180, 140, 255, 255)
						: (KeyAuth::IsStaff() ? IM_COL32(120, 200, 255, 255) : IM_COL32(180, 180, 180, 255))) };
					drawList->AddText({ winPos.x + 14.0f, winPos.y + 124.0f }, roleCol, roleLabel.c_str());
					if (!KeyAuth::username.empty())
					{
						std::string shown{ KeyAuth::username };
						// Don't dump full license-looking keys into the sidebar
						if (shown.size() > 18)
							shown = shown.substr(0, 16) + "..";
						drawList->AddText({ winPos.x + 14.0f, winPos.y + 140.0f }, IM_COL32(120, 120, 120, 255), shown.c_str());
					}
					drawList->PopClipRect();
				}

				const ImU32 navIdle{ IM_COL32(0, 0, 0, 255) };
				const ImU32 navHover{ IM_COL32(50, 12, 12, 255) };
				const ImU32 navActive{ IM_COL32(90, 20, 20, 255) };

				if (DrawButtonWithImage(aimingIconImg, { 30.0f, 30.0f }, { 120.0f, 50.0f }, { 26.0f, 155.0f }, "Aiming", navIdle, navHover, navActive, 6.0f))
				{
					Settings::currentTab = "Aiming";
				}

				if (DrawButtonWithImage(visualsIconImg, { 30.0f, 30.0f }, { 120.0f, 50.0f }, { 26.0f, 215.0f }, "Visuals", navIdle, navHover, navActive, 6.0f))
				{
					Settings::currentTab = "Visuals";
				}

				if (DrawButtonWithImage(settingsIconImg, { 30.0f, 30.0f }, { 120.0f, 50.0f }, { 26.0f, 275.0f }, "Settings", navIdle, navHover, navActive, 6.0f))
				{
					Settings::currentTab = "Settings";
				}

				if (DrawButtonWithImage(miscIconImg, { 30.0f, 30.0f }, { 120.0f, 50.0f }, { 26.0f, 335.0f }, "Misc", navIdle, navHover, navActive, 6.0f))
				{
					Settings::currentTab = "Misc";
				}

				if (DrawButtonWithImage(gamblingIconImg, { 30.0f, 30.0f }, { 120.0f, 50.0f }, { 26.0f, 395.0f }, "Gambling", navIdle, navHover, navActive, 6.0f))
				{
					Settings::currentTab = "Gambling";
				}

				if (DrawButtonWithImage(keybindsIconImg, { 30.0f, 30.0f }, { 120.0f, 50.0f }, { 26.0f, 455.0f }, "Keybinds", navIdle, navHover, navActive, 6.0f))
				{
					Settings::currentTab = "Keybinds";
					Settings::keybindListVisible = !Settings::keybindListVisible;
				}

				ImGui::SetCursorPos({ 12.0f, 40.0f });

				//ImGui::Text("To toggle this menu press INSERT.\n\n");
				//ImGui::Text("TIPS:\nFeatures that write memory are detected!\nRoblox needs to be maximized for position accuracy!\n\n");

				if (Settings::currentTab == "Aiming")
				{
					drawList->AddRectFilled({ p.x + 170.0f, p.y }, { p.x + 454.0f, p.y + 360.0f }, featureBGColor, 6.0f);
					drawList->AddRect({ p.x + 170.0f, p.y }, { p.x + 454.0f, p.y + 360.0f }, IM_COL32(20, 20, 20, 255), 6.0f);

					drawList->AddRectFilled({ p.x + 460.0f, p.y }, { p.x + 744.0f, p.y + 250.0f }, featureBGColor, 6.0f);
					drawList->AddRect({ p.x + 460.0f, p.y }, { p.x + 744.0f, p.y + 250.0f }, IM_COL32(20, 20, 20, 255), 6.0f);

					drawList->AddRectFilled({ p.x + 750.0f, p.y }, { p.x + 1034.0f, p.y + 250.0f }, featureBGColor, 6.0f);
					drawList->AddRect({ p.x + 750.0f, p.y }, { p.x + 1034.0f, p.y + 250.0f }, IM_COL32(20, 20, 20, 255), 6.0f);
					ImGui::SetCursorPos({ 185.0f, 15.0f });

					ImGui::Checkbox("Toggle aimbot", &Settings::aimbotEnabled);
					ImGui::SetCursorPosX(185.0f);

					ImGui::Checkbox("Toggle FOV", &Settings::aimbotFOVEnabled);
					ImGui::SetCursorPosX(185.0f);

					ImGui::Checkbox("Toggle prediction", &Settings::aimbotPredictionEnabled);
					ImGui::SetCursorPosX(185.0f);

					ImGui::PushItemWidth(276);
					ImGui::Text("Lock Parts");
					ImGui::SetCursorPosX(185.0f);
					if (ImGui::BeginCombo("##Lock Parts", Settings::aimbotLockPart.c_str()))
					{
						for (const std::string& part : aimbotLockPartsUI)
						{
							bool selected{ Settings::aimbotLockPart == part };
							if (ImGui::Selectable(part.c_str(), selected))
							{
								Settings::aimbotLockPart = part;
							}

							if (selected)
							{
								ImGui::SetItemDefaultFocus();
							}
						}
						ImGui::EndCombo();
					}
					ImGui::SetCursorPosX(185.0f);

					ImGui::Text("FOV radius");
					ImGui::SetCursorPosX(185.0f);
					ImGui::SliderFloat("##FOV radius", &Settings::aimbotFOVRadius, 1.0f, 400.0f, "%.1f");
					ImGui::SetCursorPosX(185.0f);

					ImGui::Text("Aimbot strength");
					ImGui::SetCursorPosX(185.0f);
					ImGui::SliderFloat("##Aimbot strength", &Settings::aimbotStrenght, 0.05f, 1.0f, "%.2f");
					ImGui::SetCursorPosX(185.0f);

					ImGui::Text("Prediction X");
					ImGui::SetCursorPosX(185.0f);
					ImGui::SliderFloat("##Prediction X", &Settings::aimbotPredictionX, 0.0f, 20.0f, "%.1f");
					ImGui::SetCursorPosX(185.0f);

					ImGui::Text("Prediction Y");
					ImGui::SetCursorPosX(185.0f);
					ImGui::SliderFloat("##Prediction Y", &Settings::aimbotPredictionY, 0.0f, 20.0f, "%.1f");
					ImGui::SetCursorPosX(185.0f);

					ImGui::Text("FOV color");
					ImGui::SetCursorPosX(185.0f);
					ImGui::ColorEdit4("##FOV color", (float*)&Settings::aimbotFovColor);

					ImGui::PopItemWidth();

					ImGui::SetCursorPos({ 360.0f, 40.0f });
					ImGui::Hotkey(&Settings::aimbotKey, { 100, 20 });
					ImGui::SetCursorPos({ 360.0f, 65.0f });
					ImGui::Checkbox("Toggle lock", &Settings::aimbotToggleLock);
					if (Settings::aimbotToggleLock && Settings::aimbotLockToggled)
					{
						ImGui::SetCursorPos({ 360.0f, 88.0f });
						ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.3f, 1.0f), "Locked");
					}

					ImGui::SetCursorPos({ 385.0f, 25.0f });
					ImGui::Text("[Aimbot]");

					ImGui::SetCursorPos({ 658.0f, 25.0f });
					ImGui::Text("[Triggerbot]");

					ImGui::SetCursorPos({ 475.0f, 15.0f });
					ImGui::Checkbox("Toggle triggerbot", &Settings::triggerbotEnabled);
					ImGui::SetCursorPosX(475.0f);
					ImGui::Checkbox("Indicate clicking", &Settings::triggerbotIndicateClicking);

					ImGui::PushItemWidth(276);
					ImGui::SetCursorPosX(475.0f);
					ImGui::Text("Trigger parts");
					ImGui::SetCursorPosX(475.0f);
					if (ImGui::BeginCombo("##Trigger parts", Settings::triggerbotTriggerPart.c_str()))
					{
						for (const std::string& part : aimbotLockPartsUI)
						{
							bool selected{ Settings::triggerbotTriggerPart == part };
							if (ImGui::Selectable(part.c_str(), selected))
							{
								Settings::triggerbotTriggerPart = part;
							}

							if (selected)
							{
								ImGui::SetItemDefaultFocus();
							}
						}

						ImGui::EndCombo();
					}
					ImGui::SetCursorPosX(475.0f);
					ImGui::Text("Detection radius");
					ImGui::SetCursorPosX(475.0f);
					ImGui::SliderFloat("##Detection radius", &Settings::triggerbotDetectionRadius, 1.0f, 100.0f, "%.1f");
					ImGui::PopItemWidth();

					ImGui::SetCursorPos({ 650.0f, 40.0f });
					ImGui::Hotkey(&Settings::triggerbotKey, { 100, 20 });

					ImGui::SetCursorPos({ 765.0f, 15.0f });
					ImGui::Checkbox("Toggle silent aim", &Settings::silentAimEnabled);

					ImGui::PushItemWidth(276);

					ImGui::SetCursorPosX(765.0f);
					ImGui::Text("Lock Parts");
					ImGui::SetCursorPosX(765.0f);
					if (ImGui::BeginCombo("##Silent Aim Lock Parts", Settings::silentAimLockPart.c_str()))
					{
						for (const std::string& part : aimbotLockPartsUI)
						{
							bool selected{ Settings::silentAimLockPart == part };
							if (ImGui::Selectable(part.c_str(), selected))
							{
								Settings::silentAimLockPart = part;
							}

							if (selected)
							{
								ImGui::SetItemDefaultFocus();
							}
						}
						ImGui::EndCombo();
					}

					ImGui::SetCursorPosX(765.0f);
					ImGui::Text("FOV Radius");
					ImGui::SetCursorPosX(765.0f);
					ImGui::SliderFloat("##Silent Aim FOV Radius", &Settings::silentAimFOVRadius, 1, 1000, "%.0f");

					ImGui::PopItemWidth();

					ImGui::SetCursorPos({ 950.0f, 25.0f });
					ImGui::Text("[Silent Aim]");
				}

				if (Settings::currentTab == "Visuals")
				{
					drawList->AddRectFilled({ p.x + 170.0f, p.y }, { p.x + 454.0f, p.y + 340.0f }, featureBGColor, 6.0f);
					drawList->AddRect({ p.x + 170.0f, p.y }, { p.x + 454.0f, p.y + 340.0f }, IM_COL32(20, 20, 20, 255), 6.0f);

					drawList->AddRectFilled({ p.x + 460.0f, p.y }, { p.x + 744.0f, p.y + 250.0f }, featureBGColor, 6.0f);
					drawList->AddRect({ p.x + 460.0f, p.y }, { p.x + 744.0f, p.y + 250.0f }, IM_COL32(20, 20, 20, 255), 6.0f);
					ImGui::SetCursorPos({ 185.0f, 15.0f });

					ImGui::PushItemWidth(276);
					ImGui::Checkbox("Toggle ESP", &Settings::espEnabled);

					ImGui::SetCursorPosX(185.0f);
					ImGui::Text("ESP Type");
					ImGui::SetCursorPosX(185.0f);
					if (ImGui::BeginCombo("##ESP Type", Settings::espType.c_str()))
					{
						for (const std::string& type : espTypes)
						{
							bool selected{ Settings::espType == type };
							if (ImGui::Selectable(type.c_str(), selected))
							{
								Settings::espType = type;
							}

							if (selected)
							{
								ImGui::SetItemDefaultFocus();
							}
						}
						ImGui::EndCombo();
					}
					ImGui::SetCursorPosX(185.0f);
					ImGui::Checkbox("Filled ESP", &Settings::espFilled);
					ImGui::SetCursorPosX(185.0f);
					ImGui::Checkbox("Show name", &Settings::espShowName);
					ImGui::SetCursorPosX(185.0f);
					ImGui::Checkbox("Show health", &Settings::espShowHealth);
					ImGui::SetCursorPosX(185.0f);
					ImGui::Checkbox("Show distance", &Settings::espShowDistance);
					ImGui::SetCursorPosX(185.0f);
					if (ImGui::Button("Preview ESP"))
					{
						Settings::espPreviewOpened = !Settings::espPreviewOpened;
					}
					ImGui::SetCursorPosX(185.0f);
					ImGui::Checkbox("Ignore dead players", &Settings::espIgnoreDeadPlrs);
					ImGui::SetCursorPosX(185.0f);
					ImGui::Text("ESP distance");
					ImGui::SetCursorPosX(185.0f);
					ImGui::SliderInt("##ESP distance", &Settings::espDistance, 0, 500);
					ImGui::SetCursorPosX(185.0f);
					ImGui::Text("ESP color");
					ImGui::SetCursorPosX(185.0f);
					ImGui::ColorEdit4("##ESP color", (float*)&Settings::espColor);
					ImGui::PopItemWidth();

					ImGui::SetCursorPos({ 390.0f, 25.0f });
					ImGui::Text("[ESP]");

					ImGui::PushItemWidth(276);

					ImGui::SetCursorPos({ 475.0f, 15.0f });
					ImGui::Checkbox("Toggle tracers", &Settings::tracersEnabled);
					ImGui::SetCursorPosX(475.0f);
					ImGui::Text("Tracer Type");
					ImGui::SetCursorPosX(475.0f);
					if (ImGui::BeginCombo("##Tracer Type", Settings::tracerType.c_str()))
					{
						for (const std::string& type : tracerTypes)
						{
							bool selected{ Settings::tracerType == type };
							if (ImGui::Selectable(type.c_str(), selected))
							{
								Settings::tracerType = type;
							}

							if (selected)
							{
								ImGui::SetItemDefaultFocus();
							}
						}
						ImGui::EndCombo();
					}
					ImGui::SetCursorPosX(475.0f);
					ImGui::Text("Tracer color");
					ImGui::SetCursorPosX(475.0f);
					ImGui::ColorEdit4("##Tracer color", (float*)&Settings::tracerColor);

					ImGui::PopItemWidth();

					ImGui::SetCursorPos({ 665.0f, 25.0f });
					ImGui::Text("[Tracers]");
				}

				if (Settings::currentTab == "Settings")
				{
					static std::vector<std::string> configList{};
					static ULONGLONG lastConfigRefresh{ 0 };
					if (GetTickCount64() - lastConfigRefresh > 1000)
					{
						configList = ListConfigFiles();
						lastConfigRefresh = GetTickCount64();
					}

					ImGui::SetCursorPosY(15.0f);
					ImGui::SetCursorPosX(175.0f);
					ImGui::Text("Config list");
					ImGui::SetCursorPosX(175.0f);
					if (ImGui::BeginCombo("##Config list", Settings::configFileName[0] ? Settings::configFileName : "Select config"))
					{
						for (const std::string& cfg : configList)
						{
							const bool selected{ cfg == Settings::configFileName };
							if (ImGui::Selectable(cfg.c_str(), selected))
							{
								strncpy_s(Settings::configFileName, cfg.c_str(), _TRUNCATE);
							}
							if (selected)
								ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}
					ImGui::SetCursorPosX(175.0f);
					ImGui::Text("New config name");
					ImGui::SetCursorPosX(175.0f);
					ImGui::InputText("##Config name", Settings::configFileName, 30);
					ImGui::SetCursorPosX(175.0f);
					if (ImGui::Button("Load config"))
					{
						const std::filesystem::path path{ std::filesystem::path("configs") / (std::string(Settings::configFileName) + ".json") };
						std::ifstream iF(path);
						if (iF.is_open())
						{
							std::string contents((std::istreambuf_iterator<char>(iF)), std::istreambuf_iterator<char>());
							json config{ json::parse(contents) };

							Settings::silentAimEnabled = config["silentaim"]["enabled"].get<bool>();
							Settings::silentAimLockPart = config["silentaim"]["lockPart"].get<std::string>();
							Settings::silentAimFOVRadius = config["silentaim"]["FOVradius"].get<float>();

							Settings::aimbotEnabled = config["aimbot"]["enabled"].get<bool>();
							Settings::aimbotFOVEnabled = config["aimbot"]["FOVenabled"].get<bool>();
							Settings::aimbotFOVRadius = config["aimbot"]["FOVradius"].get<float>();
							Settings::aimbotStrenght = config["aimbot"]["strenght"].get<float>();
							Settings::aimbotLockPart = config["aimbot"]["lockPart"].get<std::string>();
							Settings::aimbotKey = config["aimbot"]["key"].get<int>();
							if (config["aimbot"].contains("toggleLock"))
								Settings::aimbotToggleLock = config["aimbot"]["toggleLock"].get<bool>();
							Settings::aimbotFovColor.x = config["aimbot"]["FOVcolor"][0].get<float>();
							Settings::aimbotFovColor.y = config["aimbot"]["FOVcolor"][1].get<float>();
							Settings::aimbotFovColor.z = config["aimbot"]["FOVcolor"][2].get<float>();
							Settings::aimbotFovColor.w = config["aimbot"]["FOVcolor"][3].get<float>();

							Settings::triggerbotEnabled = config["triggerbot"]["enabled"].get<bool>();
							Settings::triggerbotIndicateClicking = config["triggerbot"]["indicateClicking"].get<bool>();
							Settings::triggerbotDetectionRadius = config["triggerbot"]["detectionRadius"].get<float>();
							Settings::triggerbotTriggerPart = config["triggerbot"]["triggerPart"].get<std::string>();
							Settings::triggerbotKey = config["triggerbot"]["key"].get<int>();

							Settings::espEnabled = config["esp"]["enabled"].get<bool>();
							Settings::espFilled = config["esp"]["filled"].get<bool>();
							Settings::espShowDistance = config["esp"]["showDistance"].get<bool>();
							Settings::espShowName = config["esp"]["showName"].get<bool>();
							Settings::espShowHealth = config["esp"]["showHealth"].get<bool>();
							Settings::espIgnoreDeadPlrs = config["esp"]["ignoreDeadPlayers"].get<bool>();
							Settings::espDistance = config["esp"]["distance"].get<int>();
							Settings::espType = config["esp"]["type"].get<std::string>();
							Settings::espColor.x = config["esp"]["color"][0].get<float>();
							Settings::espColor.y = config["esp"]["color"][1].get<float>();
							Settings::espColor.z = config["esp"]["color"][2].get<float>();
							Settings::espColor.w = config["esp"]["color"][3].get<float>();

							Settings::tracersEnabled = config["tracers"]["enabled"].get<bool>();
							Settings::tracerType = config["tracers"]["type"].get<std::string>();
							Settings::tracerColor.x = config["tracers"]["color"][0].get<float>();
							Settings::tracerColor.y = config["tracers"]["color"][1].get<float>();
							Settings::tracerColor.z = config["tracers"]["color"][2].get<float>();
							Settings::tracerColor.w = config["tracers"]["color"][3].get<float>();

							Settings::rbxWindowNeedsToBeSelected = config["settings"]["rbxWindowNeedsToBeSelected"].get<bool>();
							Settings::mainLoopDelay = config["settings"]["mainLoopDelay"].get<int>();

							Settings::noclipEnabled = config["misc"]["noclipEnabled"].get<bool>();
							Settings::flyEnabled = config["misc"]["flyEnabled"].get<bool>();
							Settings::flyKey = config["misc"]["flyKey"].get<int>();
							if (config["misc"].contains("flySpeed"))
								Settings::flySpeed = config["misc"]["flySpeed"].get<float>();
							if (config["misc"].contains("flyMode"))
								Settings::flyMode = config["misc"]["flyMode"].get<std::string>();
							if (config["misc"].contains("walkSpeedEnabled"))
								Settings::walkSpeedEnabled = config["misc"]["walkSpeedEnabled"].get<bool>();
							if (config["misc"].contains("walkSpeedSet"))
								Settings::walkSpeedSet = config["misc"]["walkSpeedSet"].get<int>();
							if (config["misc"].contains("walkSpeedKey"))
								Settings::walkSpeedKey = config["misc"]["walkSpeedKey"].get<int>();
							if (config["misc"].contains("jumpPowerEnabled"))
								Settings::jumpPowerEnabled = config["misc"]["jumpPowerEnabled"].get<bool>();
							if (config["misc"].contains("jumpPowerSet"))
								Settings::jumpPowerSet = config["misc"]["jumpPowerSet"].get<int>();
							if (config["misc"].contains("jumpPowerKey"))
								Settings::jumpPowerKey = config["misc"]["jumpPowerKey"].get<int>();
							if (config["misc"].contains("orbitDistanceMultiplier"))
								Settings::orbitDistanceMultiplier = config["misc"]["orbitDistanceMultiplier"].get<float>();
							if (config["misc"].contains("orbitSpeedMultiplier"))
								Settings::orbitSpeedMultiplier = config["misc"]["orbitSpeedMultiplier"].get<float>();
							if (config["misc"].contains("behindPlayerEnabled"))
								Settings::behindPlayerEnabled = config["misc"]["behindPlayerEnabled"].get<bool>();
							if (config["misc"].contains("behindPlayerKey"))
								Settings::behindPlayerKey = config["misc"]["behindPlayerKey"].get<int>();
							if (config["misc"].contains("behindPlayerDistance"))
								Settings::behindPlayerDistance = config["misc"]["behindPlayerDistance"].get<float>();
							if (config["misc"].contains("behindPlayerFOV"))
								Settings::behindPlayerFOV = config["misc"]["behindPlayerFOV"].get<float>();

							iF.close();
							configList = ListConfigFiles();
						}
						else
						{
							MessageBoxA(renderer.hwnd, "Failed to open config file.", "DK Error", MB_ICONERROR | MB_OK);
						}
					}
					ImGui::SameLine();
					if (ImGui::Button("Save config"))
					{
						if (Settings::configFileName[0] == '\0')
						{
							MessageBoxA(renderer.hwnd, "Enter a config name first.", "DK Error", MB_ICONERROR | MB_OK);
						}
						else
						{
							json config;

							config["silentaim"]["enabled"] = Settings::silentAimEnabled;
							config["silentaim"]["lockPart"] = Settings::silentAimLockPart;
							config["silentaim"]["FOVradius"] = Settings::silentAimFOVRadius;

							config["aimbot"]["enabled"] = Settings::aimbotEnabled;
							config["aimbot"]["FOVenabled"] = Settings::aimbotFOVEnabled;
							config["aimbot"]["FOVradius"] = Settings::aimbotFOVRadius;
							config["aimbot"]["strenght"] = Settings::aimbotStrenght;
							config["aimbot"]["lockPart"] = Settings::aimbotLockPart;
							config["aimbot"]["key"] = Settings::aimbotKey;
							config["aimbot"]["toggleLock"] = Settings::aimbotToggleLock;
							config["aimbot"]["FOVcolor"] = { Settings::aimbotFovColor.x, Settings::aimbotFovColor.y, Settings::aimbotFovColor.z, Settings::aimbotFovColor.w };

							config["triggerbot"]["enabled"] = Settings::triggerbotEnabled;
							config["triggerbot"]["indicateClicking"] = Settings::triggerbotIndicateClicking;
							config["triggerbot"]["detectionRadius"] = Settings::triggerbotDetectionRadius;
							config["triggerbot"]["triggerPart"] = Settings::triggerbotTriggerPart;
							config["triggerbot"]["key"] = Settings::triggerbotKey;

							config["esp"]["enabled"] = Settings::espEnabled;
							config["esp"]["filled"] = Settings::espFilled;
							config["esp"]["showDistance"] = Settings::espShowDistance;
							config["esp"]["showName"] = Settings::espShowName;
							config["esp"]["showHealth"] = Settings::espShowHealth;
							config["esp"]["ignoreDeadPlayers"] = Settings::espIgnoreDeadPlrs;
							config["esp"]["distance"] = Settings::espDistance;
							config["esp"]["type"] = Settings::espType;
							config["esp"]["color"] = { Settings::espColor.x, Settings::espColor.y, Settings::espColor.z, Settings::espColor.w };

							config["tracers"]["enabled"] = Settings::tracersEnabled;
							config["tracers"]["type"] = Settings::tracerType;
							config["tracers"]["color"] = { Settings::tracerColor.x, Settings::tracerColor.y, Settings::tracerColor.z, Settings::tracerColor.w };

							config["settings"]["rbxWindowNeedsToBeSelected"] = Settings::rbxWindowNeedsToBeSelected;
							config["settings"]["mainLoopDelay"] = Settings::mainLoopDelay;

							config["misc"]["noclipEnabled"] = Settings::noclipEnabled;
							config["misc"]["flyEnabled"] = Settings::flyEnabled;
							config["misc"]["flyKey"] = Settings::flyKey;
							config["misc"]["flySpeed"] = Settings::flySpeed;
							config["misc"]["flyMode"] = Settings::flyMode;
							config["misc"]["walkSpeedEnabled"] = Settings::walkSpeedEnabled;
							config["misc"]["walkSpeedSet"] = Settings::walkSpeedSet;
							config["misc"]["walkSpeedKey"] = Settings::walkSpeedKey;
							config["misc"]["jumpPowerEnabled"] = Settings::jumpPowerEnabled;
							config["misc"]["jumpPowerSet"] = Settings::jumpPowerSet;
							config["misc"]["jumpPowerKey"] = Settings::jumpPowerKey;
							config["misc"]["orbitDistanceMultiplier"] = Settings::orbitDistanceMultiplier;
							config["misc"]["orbitSpeedMultiplier"] = Settings::orbitSpeedMultiplier;
							config["misc"]["behindPlayerEnabled"] = Settings::behindPlayerEnabled;
							config["misc"]["behindPlayerKey"] = Settings::behindPlayerKey;
							config["misc"]["behindPlayerDistance"] = Settings::behindPlayerDistance;
							config["misc"]["behindPlayerFOV"] = Settings::behindPlayerFOV;

							const std::filesystem::path path{ std::filesystem::path("configs") / (std::string(Settings::configFileName) + ".json") };
							std::ofstream oF(path);
							if (oF.is_open())
							{
								oF << config.dump(4);
								oF.close();
								configList = ListConfigFiles();
							}
							else
							{
								MessageBoxA(renderer.hwnd, "Failed to write config file.", "DK Error", MB_ICONERROR | MB_OK);
							}
						}
					}
					ImGui::SetCursorPosX(175.0f);
					if (ImGui::Button("Refresh list"))
						configList = ListConfigFiles();
					ImGui::Text("\n");

					ImGui::SetCursorPosX(175.0f);
					ImGui::Text("Use the bottom Theme button to change themes.");
					ImGui::SetCursorPosX(175.0f);
					ImGui::Checkbox("Roblox window needs to be selected", &Settings::rbxWindowNeedsToBeSelected);
					ImGui::SetCursorPosX(175.0f);
					ImGui::Text("Main loop delay (ms)");
					ImGui::SetCursorPosX(175.0f);
					if (ImGui::InputInt("##Main loop delay (ms)", &Settings::mainLoopDelay))
					{
						if (Settings::mainLoopDelay < 0)
							Settings::mainLoopDelay = 0;
					}

					ImGui::SetCursorPosX(175.0f);
					ImGui::Text("Toggle GUI key");
					ImGui::SetCursorPosX(175.0f);
					ImGui::Hotkey(&Settings::toggleGuiKey);

					ImGui::Text("\n");
					ImGui::SetCursorPosX(175.0f);
					if (ImGui::Button("Exit"))
					{
						RBX::Memory::detach();
						renderer.Shutdown();

						return 0;
					}
				}

				if (Settings::currentTab == "Misc")
				{
					constexpr float col1X{ 170.0f };
					constexpr float col2X{ 450.0f };
					constexpr float col3X{ 730.0f };
					constexpr float colW{ 270.0f };
					constexpr float topH{ 450.0f };
					constexpr float humY{ 465.0f };
					constexpr float humH{ 210.0f };
					constexpr float pad{ 12.0f };
					constexpr float itemW{ 240.0f };
					constexpr float btnW{ 240.0f };

					drawList->AddRectFilled({ p.x + col1X, p.y }, { p.x + col1X + colW, p.y + topH }, featureBGColor, 6.0f);
					drawList->AddRect({ p.x + col1X, p.y }, { p.x + col1X + colW, p.y + topH }, IM_COL32(20, 20, 20, 255), 6.0f);
					drawList->AddRectFilled({ p.x + col2X, p.y }, { p.x + col2X + colW, p.y + topH }, featureBGColor, 6.0f);
					drawList->AddRect({ p.x + col2X, p.y }, { p.x + col2X + colW, p.y + topH }, IM_COL32(20, 20, 20, 255), 6.0f);
					drawList->AddRectFilled({ p.x + col3X, p.y }, { p.x + col3X + colW, p.y + topH }, featureBGColor, 6.0f);
					drawList->AddRect({ p.x + col3X, p.y }, { p.x + col3X + colW, p.y + topH }, IM_COL32(20, 20, 20, 255), 6.0f);
					drawList->AddRectFilled({ p.x + col1X, p.y + humY }, { p.x + col3X + colW, p.y + humY + humH }, featureBGColor, 6.0f);
					drawList->AddRect({ p.x + col1X, p.y + humY }, { p.x + col3X + colW, p.y + humY + humH }, IM_COL32(20, 20, 20, 255), 6.0f);

					ImGui::PushItemWidth(itemW);

					ImGui::SetCursorPos({ col1X + pad, 15.0f });
					ImGui::BeginGroup();
					ImGui::Text("[Player]");
					ImGui::Text("Player");
					const char* playerPreview{ Settings::othersRobloxPlr[0] ? Settings::othersRobloxPlr : "Select player" };
					if (ImGui::BeginCombo("##Player select", playerPreview))
					{
						for (RBX::Instance plr : players.getChildren())
						{
							const std::string name{ plr.name() };
							if (name.empty())
								continue;

							const bool selected{ name == Settings::othersRobloxPlr };
							if (ImGui::Selectable(name.c_str(), selected))
							{
								strncpy_s(Settings::othersRobloxPlr, name.c_str(), _TRUNCATE);
							}
							if (selected)
								ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}
					if (ImGui::Button("Spectate player", { btnW, 0.0f }))
					{
						RBX::Instance targetPlr{ players.findFirstChild(Settings::othersRobloxPlr) };
						RBX::Instance targetMi{ targetPlr.getModelInstance() };
						RBX::Instance targetHum{ targetMi.findFirstChild("Humanoid") };
						if (targetHum.address)
							RBX::Memory::write<void*>((void*)((uintptr_t)camera.address + Offsets::CameraSubject), targetHum.address);
					}
					if (ImGui::Button("Stop spectating", { btnW, 0.0f }))
					{
						RBX::Memory::write<void*>((void*)((uintptr_t)camera.address + Offsets::CameraSubject), humanoid.address);
					}

					ImGui::EndGroup();

					ImGui::SetCursorPos({ col2X + pad, 15.0f });
					ImGui::BeginGroup();
					ImGui::Text("[Teleport / Orbit]");
					ImGui::Text("X");
					ImGui::InputFloat("##TPX", &Settings::othersTeleportPos.x, 0.0f, 0.0f, "%.0f");
					ImGui::Text("Y");
					ImGui::InputFloat("##TPY", &Settings::othersTeleportPos.y, 0.0f, 0.0f, "%.0f");
					ImGui::Text("Z");
					ImGui::InputFloat("##TPZ", &Settings::othersTeleportPos.z, 0.0f, 0.0f, "%.0f");
					if (ImGui::Button("Set coordinates", { btnW, 0.0f }))
					{
						Settings::othersTeleportPos = hrp.getPosition();
					}
					if (ImGui::Button("Clear coordinates", { btnW, 0.0f }))
					{
						Settings::othersTeleportPos = { 0.0f, 0.0f, 0.0f };
					}
					if (ImGui::Button("Teleport to coordinates", { btnW, 0.0f }))
					{
						RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)hrp.getPrimitive() + Offsets::Position), Settings::othersTeleportPos);
					}
					if (ImGui::Button("Teleport to player", { btnW, 0.0f }))
					{
						RBX::Instance plr{ players.findFirstChild(Settings::othersRobloxPlr) };
						RBX::Instance plrMi{ plr.getModelInstance() };
						RBX::Instance plrHrp{ plrMi.findFirstChild("HumanoidRootPart") };

						RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)hrp.getPrimitive() + Offsets::Position), plrHrp.getPosition());
					}
					if (ImGui::Button("Orbit player", { btnW, 0.0f }))
					{
						Settings::orbitEnabled = true;
					}
					if (ImGui::Button("Stop orbiting", { btnW, 0.0f }))
					{
						Settings::orbitEnabled = false;
					}
					ImGui::Text("Orbit distance");
					ImGui::SliderFloat("##Orbit distance", &Settings::orbitDistanceMultiplier, 0.25f, 5.0f, "%.2fx");
					ImGui::Text("Orbit speed");
					ImGui::SliderFloat("##Orbit speed", &Settings::orbitSpeedMultiplier, 0.1f, 5.0f, "%.2fx");
					ImGui::EndGroup();

					ImGui::SetCursorPos({ col3X + pad, 15.0f });
					ImGui::BeginGroup();
					ImGui::Text("[Movement / Stream]");
					ImGui::Checkbox("Toggle fly", &Settings::flyEnabled);
					ImGui::Hotkey(&Settings::flyKey, { 100, 20 });
					ImGui::Text("Fly mode");
					if (ImGui::BeginCombo("##Fly mode", Settings::flyMode.c_str()))
					{
						static const char* flyModes[]{ "Default", "CFrame", "Position", "Velocity", "Hybrid", "PlatformStand", "Anchored" };
						for (const char* mode : flyModes)
						{
							const bool selected{ Settings::flyMode == mode };
							if (ImGui::Selectable(mode, selected))
								Settings::flyMode = mode;
							if (selected)
								ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}
					ImGui::Text("Fly speed");
					ImGui::SliderFloat("##Fly speed", &Settings::flySpeed, 1.0f, 200.0f, "%.1f");
					ImGui::Checkbox("Behind player", &Settings::behindPlayerEnabled);
					ImGui::Hotkey(&Settings::behindPlayerKey, { 100, 20 });
					ImGui::Text("Behind distance");
					ImGui::SliderFloat("##Behind distance", &Settings::behindPlayerDistance, 1.0f, 20.0f, "%.1f");
					ImGui::Text("Behind FOV");
					ImGui::SliderFloat("##Behind FOV", &Settings::behindPlayerFOV, 50.0f, 500.0f, "%.0f");
					ImGui::Checkbox("Toggle noclip", &Settings::noclipEnabled);
					if (ImGui::Checkbox("Hide Stream", &Settings::streamproofEnabled))
					{
						if (Settings::streamproofEnabled)
							SetWindowDisplayAffinity(renderer.hwnd, WDA_EXCLUDEFROMCAPTURE);
						else
							SetWindowDisplayAffinity(renderer.hwnd, WDA_NONE);
					}
					ImGui::PushTextWrapPos(ImGui::GetCursorPosX() + itemW);
					ImGui::TextWrapped("Hides the overlay from OBS and other capture software.");
					ImGui::PopTextWrapPos();
					ImGui::EndGroup();

					ImGui::SetCursorPos({ col1X + pad, humY + 15.0f });
					ImGui::BeginGroup();
					ImGui::Text("[Humanoid]");
					ImGui::Checkbox("WalkSpeed active", &Settings::walkSpeedEnabled);
					ImGui::Text("WalkSpeed");
					ImGui::SetNextItemWidth(col3X + colW - col1X - pad * 2.0f);
					ImGui::SliderInt("##WalkSpeed", &Settings::walkSpeedSet, 0, 1000);
					ImGui::Checkbox("JumpPower active", &Settings::jumpPowerEnabled);
					ImGui::Text("JumpPower");
					ImGui::SetNextItemWidth(col3X + colW - col1X - pad * 2.0f);
					ImGui::SliderInt("##JumpPower", &Settings::jumpPowerSet, 0, 1000);
					ImGui::TextDisabled("Toggles keep applying while on. Turn off to restore.");
					ImGui::EndGroup();

					ImGui::PopItemWidth();
				}

				if (Settings::currentTab == "Gambling")
				{
					ImGui::SetCursorPosY(15.0f);
					ImGui::SetCursorPosX(175.0f);
					ImGui::Text("%d %d %d", Settings::gamblingSlotsNumber1, Settings::gamblingSlotsNumber2, Settings::gamblingSlotsNumber3);

					ImGui::SetCursorPosX(175.0f);
					if (ImGui::Button("Spin"))
					{
						Settings::gamblingSlotsNumber1 = getRandomNumber(0, 9);
						Settings::gamblingSlotsNumber2 = getRandomNumber(0, 9);
						Settings::gamblingSlotsNumber3 = getRandomNumber(0, 9);
					}
				}

				if (Settings::currentTab == "Keybinds")
				{
					ImGui::SetCursorPosY(15.0f);
					ImGui::SetCursorPosX(175.0f);
					ImGui::Text("Keybind List");
					ImGui::SetCursorPosX(175.0f);
					ImGui::Checkbox("Show floating keybind list", &Settings::keybindListVisible);
					ImGui::SetCursorPosX(175.0f);
					ImGui::TextWrapped("Active binds turn green in the floating list.");
					ImGui::SetCursorPosX(175.0f);
					ImGui::Separator();
					ImGui::SetCursorPosX(175.0f);
					DrawKeybindProp("Toggle GUI", "TOGGLE", Settings::toggleGuiKey, Settings::imguiVisible);
					ImGui::SetCursorPosX(175.0f);
					DrawKeybindProp("Aimbot", Settings::aimbotToggleLock ? "TOGGLE" : "HOLD", Settings::aimbotKey, Settings::aimbotEnabled && (Settings::aimbotToggleLock ? Settings::aimbotLockToggled : IsBindDown(Settings::aimbotKey)));
					ImGui::SetCursorPosX(175.0f);
					DrawKeybindProp("Triggerbot", "HOLD", Settings::triggerbotKey, Settings::triggerbotEnabled && IsBindDown(Settings::triggerbotKey));
					ImGui::SetCursorPosX(175.0f);
					DrawKeybindProp("Fly", "TOGGLE", Settings::flyKey, Settings::flyEnabled && Settings::flyKeyToggled);
					ImGui::SetCursorPosX(175.0f);
					DrawKeybindProp("Behind player", "PRESS", Settings::behindPlayerKey, Settings::behindPlayerEnabled && IsBindDown(Settings::behindPlayerKey));
				}

				ImGui::End();
			}
			}

			if (Settings::espPreviewOpened)
			{
				ImGui::SetNextWindowSize({ 290, 380 });
				ImGui::Begin("DK - ESP Preview", (bool*)0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize);

				ImVec2 p{ ImGui::GetCursorScreenPos() };
				ImDrawList* drawList{ ImGui::GetWindowDrawList() };

				ImVec2 winPos{ ImGui::GetWindowPos() };
				ImVec2 winSize{ ImGui::GetWindowSize() };
				if (Settings::highEndVisuals)
					DrawGlow(ImGui::GetBackgroundDrawList(), winPos, { winPos.x + winSize.x, winPos.y + winSize.y }, glowColor, 4, 0.15f, 6.0f);

				if (avatarImg)
				{
					ImGui::Image((void*)avatarImg, { (float)avatarImgW, (float)avatarImgH });
				}

				if (Settings::espEnabled)
				{
					if (Settings::espType == "Square")
					{
						if (!Settings::espFilled)
						{
							drawList->AddRect({ p.x + 50.0f, p.y + 70.0f }, { p.x + 220.0f, p.y + 260.0f }, ImColor(Settings::espColor));
						}
						else
						{
							drawList->AddRectFilled({ p.x + 50.0f, p.y + 70.0f }, { p.x + 220.0f, p.y + 260.0f }, ImColor(Settings::espColor));
						}
					}
					else if (Settings::espType == "Skeleton")
					{
						drawList->AddLine({ p.x + 132.0f, p.y + 70.0f }, { p.x + 132.0f, p.y + 150.0f }, ImColor(Settings::espColor));

						drawList->AddLine({ p.x + 50.0f, p.y + 150.0f }, { p.x + 132.0f, p.y + 150.0f }, ImColor(Settings::espColor));
						drawList->AddLine({ p.x + 220.0f, p.y + 150.0f }, { p.x + 132.0f, p.y + 150.0f }, ImColor(Settings::espColor));

						drawList->AddLine({ p.x + 105.0f, p.y + 270.0f }, { p.x + 132.0f, p.y + 150.0f }, ImColor(Settings::espColor));
						drawList->AddLine({ p.x + 157.0f, p.y + 270.0f }, { p.x + 132.0f, p.y + 150.0f }, ImColor(Settings::espColor));
					}
					else if (Settings::espType == "Corners")
					{
						drawList->AddLine({ p.x + 50.0f, p.y + 70.0f }, { p.x + 60.0f, p.y + 70.0f }, ImColor(Settings::espColor));
						drawList->AddLine({ p.x + 50.0f, p.y + 70.0f }, { p.x + 50.0f, p.y + 80.0f }, ImColor(Settings::espColor));

						drawList->AddLine({ p.x + 220.0f, p.y + 70.0f }, { p.x + 210.0f, p.y + 70.0f }, ImColor(Settings::espColor));
						drawList->AddLine({ p.x + 220.0f, p.y + 70.0f }, { p.x + 220.0f, p.y + 80.0f }, ImColor(Settings::espColor));

						drawList->AddLine({ p.x + 50.0f, p.y + 260.0f }, { p.x + 50.0f, p.y + 250.0f }, ImColor(Settings::espColor));
						drawList->AddLine({ p.x + 50.0f, p.y + 260.0f }, { p.x + 60.0f, p.y + 260.0f }, ImColor(Settings::espColor));

						drawList->AddLine({ p.x + 220.0f, p.y + 260.0f }, { p.x + 220.0f, p.y + 250.0f }, ImColor(Settings::espColor));
						drawList->AddLine({ p.x + 220.0f, p.y + 260.0f }, { p.x + 210.0f, p.y + 260.0f }, ImColor(Settings::espColor));
					}

					if (Settings::espShowName)
					{
						drawList->AddText({ p.x + 114.0f, p.y + 50.0f }, IM_COL32_WHITE, "abc123");
					}

					if (Settings::espShowHealth)
					{
						drawList->AddRectFilled({ p.x + 48.0f, p.y + 70.0f }, { p.x + 50.0f, p.y + 260.0f }, IM_COL32(0, 255, 0, 255));
					}

					if (Settings::espShowDistance)
					{
						drawList->AddText({ p.x + 120.0f, p.y + 240.0f }, IM_COL32_WHITE, "10");
					}
				}

				ImGui::End();
			}

			if (Settings::explorerWinVisible)
			{
				ImGui::SetNextWindowSize({ 500, 600 });

				ImGui::Begin("DK - Explorer", (bool*)0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize);

				ImVec2 winPos{ ImGui::GetWindowPos() };
				ImVec2 winSize{ ImGui::GetWindowSize() };
				if (Settings::highEndVisuals)
					DrawGlow(ImGui::GetBackgroundDrawList(), winPos, { winPos.x + winSize.x, winPos.y + winSize.y }, glowColor, 4, 0.15f, 6.0f);

				for (RBX::Instance chld : dataModel.getChildren())
				{
					showExplorerChildren(chld);
				}

				ImGui::End();
			}

			if (Settings::friendsListVisible)
			{
				ImGui::SetNextWindowSize({ 620, 420 }, ImGuiCond_Appearing);
				ImGui::Begin("Players", (bool*)0, ImGuiWindowFlags_NoSavedSettings);

				ImVec2 winPos{ ImGui::GetWindowPos() };
				ImVec2 winSize{ ImGui::GetWindowSize() };
				if (Settings::highEndVisuals)
					DrawGlow(ImGui::GetBackgroundDrawList(), winPos, { winPos.x + winSize.x, winPos.y + winSize.y }, glowColor, 4, 0.15f, 6.0f);

				ImGui::Text("Players");
				ImGui::TextWrapped("Click a name, then Orbit / Spectate. Friend = green ESP, ignored by aim.");
				ImGui::Separator();

				const float listW = ImGui::GetContentRegionAvail().x * 0.46f;
				ImGui::BeginChild("##PlayersScroll", { listW, 0 }, true);

				const std::string localName{ localPlayer.name() };
				static int selectedPlayerRow{ -1 };
				static char selectedPlayerName[64]{};
				static int64_t selectedPlayerUserId{ 0 };
				int row = 0;
				for (RBX::Instance plr : players.getChildren())
				{
					if (plr.className() != "Player")
						continue;
					const std::string name{ plr.name() };
					if (name.empty())
						continue;

					const bool isLocal{ name == localName };
					const bool friendMarked{ IsFriend(name) };
					ImGui::PushID(name.c_str());
					if (isLocal)
					{
						ImGui::TextColored(ImVec4(0.4f, 0.8f, 1.0f, 1.0f), "%s (you)", name.c_str());
					}
					else
					{
						if (ImGui::Selectable(name.c_str(), selectedPlayerRow == row))
						{
							selectedPlayerRow = row;
							strncpy_s(selectedPlayerName, name.c_str(), _TRUNCATE);
							strncpy_s(Settings::othersRobloxPlr, name.c_str(), _TRUNCATE);
							selectedPlayerUserId = ReadPlayerUserId(plr);
							RequestAvatar(selectedPlayerUserId);
						}
						if (friendMarked)
						{
							ImGui::SameLine();
							ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.3f, 1.0f), "friend");
						}
					}
					ImGui::PopID();
					++row;
				}
				ImGui::EndChild();

				ImGui::SameLine();
				ImGui::BeginChild("##PlayerActions", { 0, 0 }, true);
				if (selectedPlayerName[0] != '\0')
				{
					RequestAvatar(selectedPlayerUserId);
					ImVec2 avSz{};
					if (ID3D11ShaderResourceView* av{ GetAvatarSrv(selectedPlayerUserId, &avSz) })
						ImGui::Image((void*)av, ImVec2(96.0f, 96.0f));
					ImGui::Text("%s", selectedPlayerName);
					RBX::Instance selPlr{ players.findFirstChild(selectedPlayerName) };
					if (PlayerIsSmiteUser(selPlr))
						ImGui::TextColored(ImVec4(0.92f, 0.12f, 0.14f, 1.0f), "Using this");
					ImGui::Separator();
					if (ImGui::Button("Orbit", { -1, 0 }))
					{
						strncpy_s(Settings::othersRobloxPlr, selectedPlayerName, _TRUNCATE);
						Settings::orbitEnabled = true;
					}
					if (ImGui::Button("Spectate", { -1, 0 }))
					{
						strncpy_s(Settings::othersRobloxPlr, selectedPlayerName, _TRUNCATE);
						RBX::Instance targetPlr{ players.findFirstChild(selectedPlayerName) };
						RBX::Instance targetMi{ targetPlr.getModelInstance() };
						RBX::Instance targetHum{ targetMi.findFirstChild("Humanoid") };
						if (targetHum.address)
							RBX::Memory::write<void*>((void*)((uintptr_t)camera.address + Offsets::CameraSubject), targetHum.address);
					}
					if (ImGui::Button("Stop spectating", { -1, 0 }))
					{
						if (humanoid.address)
							RBX::Memory::write<void*>((void*)((uintptr_t)camera.address + Offsets::CameraSubject), humanoid.address);
					}
					if (ImGui::Button("Stop orbit", { -1, 0 }))
						Settings::orbitEnabled = false;
					if (ImGui::Button("Behind", { -1, 0 }))
					{
						strncpy_s(Settings::othersRobloxPlr, selectedPlayerName, _TRUNCATE);
						TeleportBehindPlayer(players.findFirstChild(selectedPlayerName), hrp, camera);
					}
					if (ImGui::Button("Teleport", { -1, 0 }))
					{
						strncpy_s(Settings::othersRobloxPlr, selectedPlayerName, _TRUNCATE);
						RBX::Instance plr{ players.findFirstChild(selectedPlayerName) };
						RBX::Instance plrMi{ plr.getModelInstance() };
						RBX::Instance plrHrp{ plrMi.findFirstChild("HumanoidRootPart") };
						if (plrHrp.address && hrp.address)
							RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)hrp.getPrimitive() + Offsets::Position), plrHrp.getPosition());
					}
					ImGui::Spacing();
					if (ImGui::Button(IsFriend(selectedPlayerName) ? "Remove friend" : "Add friend", { -1, 0 }))
						ToggleFriend(selectedPlayerName);
				}
				else
				{
					ImGui::TextDisabled("Select a player.");
				}
				ImGui::EndChild();
				ImGui::End();
			}

			if (Settings::themeWinVisible)
			{
				ImGui::SetNextWindowSize({ 320, 180 });
				ImGui::Begin("DK - Theme Changer", (bool*)0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize);

				ImVec2 winPos{ ImGui::GetWindowPos() };
				ImVec2 winSize{ ImGui::GetWindowSize() };
				if (Settings::highEndVisuals)
					DrawGlow(ImGui::GetBackgroundDrawList(), winPos, { winPos.x + winSize.x, winPos.y + winSize.y }, glowColor, 4, 0.15f, 6.0f);

				ImGui::Text("Theme name");
				ImGui::InputText("##Theme name popup", Settings::themeFileName, 30);
				if (ImGui::Button("Set theme"))
				{
					if (loadTheme(featureBGColor, glowColor, std::string(Settings::themeFileName)))
					{
						std::ofstream oF("settings.json");
						if (oF.is_open())
						{
							json settingsJ2{ settingsJ };
							settingsJ2["theme"] = Settings::themeFileName;
							oF << settingsJ2.dump(4);
							oF.close();
						}
					}
				}
				ImGui::SameLine();
				if (ImGui::Button("Reset theme"))
				{
					std::ofstream oF("settings.json");
					if (oF.is_open())
					{
						json settingsJ2{ settingsJ };
						settingsJ2["theme"] = "default";
						oF << settingsJ2.dump(4);
						oF.close();

						ImGuiStyle& style{ ImGui::GetStyle() };
						style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0627451f, 0.05882353f, 0.0627451f, 0.9f);
						style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.05f, 0.05f, 1.00f);
						style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.35f, 0.10f, 0.10f, 1.00f);
						style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.50f, 0.15f, 0.15f, 1.00f);
						style.Colors[ImGuiCol_Button] = ImVec4(0.20f, 0.05f, 0.05f, 1.00f);
						style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.35f, 0.10f, 0.10f, 1.00f);
						style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.50f, 0.15f, 0.15f, 1.00f);
						style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.85f, 0.20f, 0.20f, 1.00f);
						style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.25f, 0.25f, 1.00f);
						style.WindowRounding = 6.0f;
						style.FrameRounding = 6.0f;
						style.GrabRounding = 6.0f;
						featureBGColor = { 0, 0, 0, 230 };
						glowColor = { 1.0f, 0.0f, 0.0f, 0.8f };
					}
				}

				ImGui::End();
			}

			if (Settings::adminWinVisible)
			{
				ImGui::SetNextWindowSize({ 360, 420 });
				ImGui::Begin("DK - Admin", (bool*)0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize);

				ImVec2 winPos{ ImGui::GetWindowPos() };
				ImVec2 winSize{ ImGui::GetWindowSize() };
				if (Settings::highEndVisuals)
					DrawGlow(ImGui::GetBackgroundDrawList(), winPos, { winPos.x + winSize.x, winPos.y + winSize.y }, glowColor, 4, 0.15f, 6.0f);

				ImGui::Text("Role: %s", KeyAuth::role.c_str());
				ImGui::Text("Level: %d", KeyAuth::roleLevel);
				if (!KeyAuth::username.empty())
					ImGui::Text("User: %s", KeyAuth::username.c_str());

				ImGui::Text("Subscriptions:");
				if (KeyAuth::subscriptions.empty())
					ImGui::TextDisabled("(none parsed — check KeyAuth subscription name)");
				else
				{
					for (const auto& sub : KeyAuth::subscriptions)
						ImGui::BulletText("%s  (rank %d)", sub.c_str(), KeyAuth::RankRole(sub));
				}

				ImGui::Separator();
				ImGui::TextWrapped("KeyAuth subscription names: Owner (5), CoOwner (4), Staff (3), default (1). Set the subscription name on the license in the KeyAuth panel.");

				if (!KeyAuth::IsStaff())
				{
					ImGui::Spacing();
					ImGui::TextColored(ImVec4(1.0f, 0.35f, 0.35f, 1.0f), "Staff+ required for admin tools.");
					ImGui::TextWrapped("If your license should be Owner, the subscription name must contain Owner (not only a custom note).");
				}
				else
				{
					ImGui::Spacing();
					ImGui::Text("[Session]");
					if (ImGui::Button("Logout key (restart)", { -1, 0 }))
						KeyAuth::LogoutAndRestart();
					ImGui::TextWrapped("Clears saved license and restarts so you can enter another key.");

					ImGui::Separator();
					ImGui::Text("[Stealth]");
					ImGui::Checkbox("Hide DK logo from others", &Settings::hideSmiteLogo);
					ImGui::TextWrapped("Other DK users will not see the mark above your head. Default licenses cannot use this.");

					if (KeyAuth::IsCoOwner())
					{
						ImGui::Separator();
						ImGui::Text("[Trolls] CoOwner+  (DK users only)");
						ImGui::TextWrapped("They must have this open. Bring/spin/freeze/fling run on their game, not just yours.");
						ImGui::Text("Target");
						const char* playerPreview{ Settings::othersRobloxPlr[0] ? Settings::othersRobloxPlr : "Select DK user" };
						if (ImGui::BeginCombo("##Admin player", playerPreview))
						{
							int listed = 0;
							for (RBX::Instance plr : players.getChildren())
							{
								if (plr.className() != "Player")
									continue;
								const std::string name{ plr.name() };
								if (name.empty() || name == localPlayer.name())
									continue;
								if (!PlayerIsSmiteUser(plr))
									continue;
								++listed;
								const bool selected{ name == Settings::othersRobloxPlr };
								if (ImGui::Selectable(name.c_str(), selected))
									strncpy_s(Settings::othersRobloxPlr, name.c_str(), _TRUNCATE);
								if (selected)
									ImGui::SetItemDefaultFocus();
							}
							if (listed == 0)
								ImGui::TextDisabled("No other DK users in this server.");
							ImGui::EndCombo();
						}
						ImGui::Checkbox("Bring to me", &Settings::ownerBringEnabled);
						ImGui::Checkbox("Follow me", &Settings::ownerFollowEnabled);
						ImGui::Checkbox("Spin", &Settings::ownerSpinEnabled);
						ImGui::Checkbox("Freeze", &Settings::ownerFreezeEnabled);
						ImGui::Checkbox("Fling", &Settings::ownerFlingEnabled);
						ImGui::Checkbox("Jump only", &Settings::ownerJumpOnlyEnabled);
					}
					else
					{
						ImGui::Spacing();
						ImGui::TextDisabled("Troll tools need CoOwner or Owner.");
					}
				}

				ImGui::End();
			}
		}

		if (Settings::keybindListVisible)
		{
			ImGui::SetNextWindowSize({ 300, 250 });
			ImGui::Begin("DK - Keybind List", (bool*)0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize);

			ImVec2 winPos{ ImGui::GetWindowPos() };
			ImVec2 winSize{ ImGui::GetWindowSize() };
			if (Settings::highEndVisuals)
				DrawGlow(ImGui::GetBackgroundDrawList(), winPos, { winPos.x + winSize.x, winPos.y + winSize.y }, glowColor, 4, 0.15f, 6.0f);

			const bool aimActive{ Settings::aimbotEnabled && (Settings::aimbotToggleLock ? Settings::aimbotLockToggled : IsBindDown(Settings::aimbotKey)) };
			const bool triggerActive{ Settings::triggerbotEnabled && IsBindDown(Settings::triggerbotKey) };
			const bool flyActive{ Settings::flyEnabled && Settings::flyKeyToggled };
			const bool behindActive{ Settings::behindPlayerEnabled && IsBindDown(Settings::behindPlayerKey) };

			DrawKeybindProp("Toggle GUI", "TOGGLE", Settings::toggleGuiKey, Settings::imguiVisible);
			DrawKeybindProp("Aimbot", Settings::aimbotToggleLock ? "TOGGLE" : "HOLD", Settings::aimbotKey, aimActive);
			DrawKeybindProp("Triggerbot", "HOLD", Settings::triggerbotKey, triggerActive);
			DrawKeybindProp("Fly", "TOGGLE", Settings::flyKey, flyActive);
			DrawKeybindProp("Behind player", "PRESS", Settings::behindPlayerKey, behindActive);
			DrawKeybindProp("WalkSpeed", "TOGGLE", Settings::walkSpeedKey, Settings::walkSpeedEnabled);
			DrawKeybindProp("JumpPower", "TOGGLE", Settings::jumpPowerKey, Settings::jumpPowerEnabled);
			DrawKeybindProp("Silent Aim", "FEATURE", 0, Settings::silentAimEnabled);
			DrawKeybindProp("ESP", "FEATURE", 0, Settings::espEnabled);

			ImGui::End();
		}

		ImDrawList* drawList{ ImGui::GetBackgroundDrawList() };

		if (Settings::aimbotEnabled && (!Settings::rbxWindowNeedsToBeSelected || robloxFocused))
		{
			const bool keybindDown{ IsBindDown(Settings::aimbotKey) };
			static float prevErrX{ 0.0f };
			static float prevErrY{ 0.0f };
			static ULONGLONG lastAimTickMs{ 0 };

			auto clearAimLock = [&]()
			{
				locked = false;
				lockedPlr = RBX::Instance(nullptr);
				stickyLockPart = RBX::Instance(nullptr);
				prevErrX = 0.0f;
				prevErrY = 0.0f;
			};

			auto acquireClosestTarget = [&]()
			{
				float closestDistance{ Settings::aimbotFOVRadius };
				RBX::Instance closestPlr{ nullptr };
				POINT mousePos{};
				GetCursorPos(&mousePos);

				for (size_t pi = 0; pi < playersList.size(); ++pi)
				{
					RBX::Instance plr{ playersList[pi] };
					const std::string plrName{ GetPlayersListName(pi, plr) };
					if (plrName == localPlayer.name() || IsFriend(plrName))
						continue;

					RBX::Instance lockPart{ resolveLockPart(plr, Settings::aimbotLockPart, mousePos, visualEngine) };
					if (!lockPart.address)
						continue;

					RBX::Vector2 screenPos{ visualEngine.worldToScreen(lockPart.getPosition()) };
					float dx{ screenPos.x - mousePos.x };
					float dy{ screenPos.y - mousePos.y };
					float dist{ sqrtf(dx * dx + dy * dy) };

					if (dist < Settings::aimbotFOVRadius && dist < closestDistance)
					{
						closestDistance = dist;
						closestPlr = plr;
					}
				}

				if (closestPlr.address != nullptr)
				{
					lockedPlr = closestPlr;
					locked = true;
					stickyLockPart = resolveLockPart(lockedPlr, Settings::aimbotLockPart, mousePos, visualEngine);
					prevErrX = 0.0f;
					prevErrY = 0.0f;
					return true;
				}
				return false;
			};

			if (Settings::aimbotToggleLock)
			{
				if (keybindDown && !keybindPrevDown)
				{
					if (!Settings::aimbotLockToggled)
					{
						if (acquireClosestTarget())
							Settings::aimbotLockToggled = true;
					}
					else
					{
						Settings::aimbotLockToggled = false;
						clearAimLock();
					}
				}
			}
			else
			{
				Settings::aimbotLockToggled = false;
				if (keybindDown && !keybindPrevDown && !locked)
					acquireClosestTarget();

				if (!keybindDown && keybindPrevDown)
					clearAimLock();
			}

			if (locked && lockedPlr.address != nullptr && IsFriend(lockedPlr.name()))
			{
				Settings::aimbotLockToggled = false;
				clearAimLock();
			}

			const bool shouldTrack{ Settings::aimbotToggleLock ? Settings::aimbotLockToggled : keybindDown };
			if (shouldTrack && locked && lockedPlr.address != nullptr)
			{
				// Overlay can run hundreds of FPS; aim only ~120Hz like Roblox RenderStepped.
				const ULONGLONG nowMs{ GetTickCount64() };
				if (nowMs - lastAimTickMs >= 8)
				{
					lastAimTickMs = nowMs;

					POINT mousePos{};
					GetCursorPos(&mousePos);

					RBX::Instance lockPart{ stickyLockPart };
					if (!lockPart.address)
						lockPart = resolveLockPart(lockedPlr, Settings::aimbotLockPart, mousePos, visualEngine);
					else if (Settings::aimbotLockPart != "Closest")
						lockPart = resolveLockPart(lockedPlr, Settings::aimbotLockPart, mousePos, visualEngine);

					if (lockPart.address)
					{
						stickyLockPart = lockPart;
						RBX::Vector3 lockPartPos{ lockPart.getPosition() };

						if (Settings::aimbotPredictionEnabled)
						{
							RBX::Vector3 lockPartVelocity{ RBX::Memory::read<RBX::Vector3>((void*)((uintptr_t)lockPart.getPrimitive() + Offsets::Velocity)) };
							const float predScale{ 0.045f };
							lockPartPos.x += lockPartVelocity.x * Settings::aimbotPredictionX * predScale;
							lockPartPos.y += lockPartVelocity.y * Settings::aimbotPredictionY * predScale;
							lockPartPos.z += lockPartVelocity.z * Settings::aimbotPredictionX * predScale;
						}

						// trackBehind=true: keep turning camera when target goes behind you
						RBX::Vector2 screenPos{ visualEngine.worldToScreen(lockPartPos, true) };

						const float errX{ screenPos.x - static_cast<float>(mousePos.x) };
						const float errY{ screenPos.y - static_cast<float>(mousePos.y) };
						const float dist{ sqrtf(errX * errX + errY * errY) };
						constexpr float deadzone{ 2.5f };

						if (dist <= deadzone)
						{
							prevErrX = 0.0f;
							prevErrY = 0.0f;
						}
						else
						{
							const float strength{ std::clamp(Settings::aimbotStrenght, 0.05f, 1.0f) };
							// Higher strength = lower divisor = much faster snap (still rate-limited).
							const float divisor{ 9.0f - strength * 7.2f }; // ~8.6 .. 1.8
							const float maxStep{ 10.0f + strength * 38.0f }; // ~12 .. 48

							float moveX{ errX / divisor };
							float moveY{ errY / divisor };

							// Soft-cap only the extreme far swings so we stay fast without flying.
							const float softCap{ maxStep * (0.55f + 0.45f * tanhf(dist / 180.0f)) };
							moveX = std::clamp(moveX, -softCap, softCap);
							moveY = std::clamp(moveY, -softCap, softCap);

							// If we crossed the target, brake hard (keeps the no-oscillation fix).
							if (prevErrX != 0.0f && errX * prevErrX < 0.0f)
								moveX *= 0.15f;
							if (prevErrY != 0.0f && errY * prevErrY < 0.0f)
								moveY *= 0.15f;

							if (fabsf(moveX) > fabsf(errX)) moveX = errX;
							if (fabsf(moveY) > fabsf(errY)) moveY = errY;

							prevErrX = errX;
							prevErrY = errY;

							MoveMouse(moveX, moveY);
						}
					}
				}
			}
			else if (!shouldTrack)
			{
				prevErrX = 0.0f;
				prevErrY = 0.0f;
			}

			keybindPrevDown = keybindDown;
		}

		if (Settings::aimbotFOVEnabled && (!Settings::rbxWindowNeedsToBeSelected || robloxFocused))
		{
			POINT mousePos;
			GetCursorPos(&mousePos);

			drawList->AddCircle({ static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) }, Settings::aimbotFOVRadius, ImColor(Settings::aimbotFovColor));
		}

		if (Settings::triggerbotEnabled && IsBindDown(Settings::triggerbotKey) && (!Settings::rbxWindowNeedsToBeSelected || robloxFocused))
		{
			POINT mousePos;
			GetCursorPos(&mousePos);

			for (size_t pi = 0; pi < playersList.size(); ++pi)
			{
				RBX::Instance plr{ playersList[pi] };
				const std::string plrName{ GetPlayersListName(pi, plr) };
				if (plrName == localPlayer.name() || IsFriend(plrName))
				{
					continue;
				}

				RBX::Instance triggerPart{ resolveLockPart(plr, Settings::triggerbotTriggerPart, mousePos, visualEngine) };
				if (!triggerPart.address)
					continue;

				RBX::Vector3 triggerPartPos{ triggerPart.getPosition() };
				RBX::Vector2 screenPos{ visualEngine.worldToScreen(triggerPartPos) };

				float dx{ screenPos.x - mousePos.x };
				float dy{ screenPos.y - mousePos.y };
				float dist{ sqrtf(dx * dx + dy * dy) };

				if (dist < Settings::triggerbotDetectionRadius)
				{
					INPUT input{ 0 };
					input.type = INPUT_MOUSE;
					input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
					SendInput(1, &input, sizeof(input));

					ZeroMemory(&input, sizeof(input));

					input.type = INPUT_MOUSE;
					input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
					SendInput(1, &input, sizeof(input));

					if (Settings::triggerbotIndicateClicking)
						drawList->AddCircleFilled({ static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) }, Settings::triggerbotDetectionRadius, IM_COL32(255, 0, 0, 255));
				}
			}
		}

		// Low-end: draw ESP every other frame (aim stays every tick).
		static unsigned espFrame{ 0 };
		++espFrame;
		const bool drawEspThisFrame{ Settings::highEndVisuals || Settings::sessionBoost || (espFrame % 2u) == 0u };

		if (Settings::espEnabled && drawEspThisFrame && (!Settings::rbxWindowNeedsToBeSelected || robloxFocused))
		{
			for (size_t pi = 0; pi < playersList.size(); ++pi)
			{
				RBX::Instance plr{ playersList[pi] };
				const std::string plrName{ GetPlayersListName(pi, plr) };
				if (Settings::espIgnoreDeadPlrs)
				{
					float health{ RBX::Memory::read<float>((void*)((uintptr_t)plr.findFirstChild("Humanoid").address + Offsets::Health)) };

					if (health <= 0.0f)
					{
						continue;
					}
				}

				if (plrName == localPlayer.name())
				{
					continue;
				}

				const bool friendMarked{ IsFriend(plrName) };
				const ImVec4 drawColor{ friendMarked ? ImVec4(0.15f, 1.0f, 0.25f, 1.0f) : Settings::espColor };

				RBX::Instance torso{ plr.findFirstChild("Torso") };
				RBX::Instance plrHrp{ plr.findFirstChild("HumanoidRootPart") };

				RBX::Vector3 BOX_TOP;
				RBX::Vector3 LEFT_ARM;
				RBX::Vector3 RIGHT_ARM;
				RBX::Vector3 BOX_BOTTOM;

				if (torso.address) // R6
				{
					BOX_TOP = plr.findFirstChild("Head").getPosition();
					LEFT_ARM = plr.findFirstChild("Left Arm").getPosition();
					RIGHT_ARM = plr.findFirstChild("Right Arm").getPosition();
					BOX_BOTTOM = plr.findFirstChild("Right Leg").getPosition();
				}
				else // R15
				{
					BOX_TOP = plr.findFirstChild("Head").getPosition();
					LEFT_ARM = plr.findFirstChild("LeftLowerArm").getPosition();
					RIGHT_ARM = plr.findFirstChild("RightLowerArm").getPosition();
					BOX_BOTTOM = plr.findFirstChild("RightFoot").getPosition();
				}

				RBX::Vector2 BOX_TOP_DRAW{ visualEngine.worldToScreen(BOX_TOP) };
				RBX::Vector2 BOX_BOTTOM_DRAW{ visualEngine.worldToScreen(BOX_BOTTOM) };
				RBX::Vector2 pos1{ visualEngine.worldToScreen({ LEFT_ARM.x, BOX_TOP.y, LEFT_ARM.z }) };
				RBX::Vector2 pos2{ visualEngine.worldToScreen({ RIGHT_ARM.x, BOX_BOTTOM.y, RIGHT_ARM.z }) };

				float dist{ hrp.getDistance(plrHrp.getPosition()) };

				if ((pos1.x == 0 && pos1.y == 0) && (pos2.x == 0 && pos2.y == 0)) continue;
				if (Settings::espDistance != 0 && dist > Settings::espDistance) continue;

				if (Settings::espType == "Square")
				{
					if (!Settings::espFilled)
						drawList->AddRect({ pos1.x, pos1.y }, { pos2.x, pos2.y }, ImColor(drawColor));
					else
						drawList->AddRectFilled({ pos1.x, pos1.y }, { pos2.x, pos2.y }, ImColor(drawColor));
				}
				else if (Settings::espType == "Skeleton")
				{
					RBX::Vector3 torsoPos;
					RBX::Vector3 leftLegPos;
					RBX::Vector3 rightLegPos;

					if (torso.address)
					{
						torsoPos = torso.getPosition();
						leftLegPos = plr.findFirstChild("Left Leg").getPosition();
						rightLegPos = plr.findFirstChild("Right Leg").getPosition();
					}
					else
					{
						torsoPos = plr.findFirstChild("UpperTorso").getPosition();
						leftLegPos = plr.findFirstChild("LeftUpperLeg").getPosition();
						rightLegPos = plr.findFirstChild("RightUpperLeg").getPosition();
					}

					RBX::Vector2 torsoDraw{ visualEngine.worldToScreen(torsoPos) };
					RBX::Vector2 leftLegDraw{ visualEngine.worldToScreen(leftLegPos) };
					RBX::Vector2 rightLegDraw{ visualEngine.worldToScreen(rightLegPos) };
					RBX::Vector2 rightArmDraw{ visualEngine.worldToScreen(RIGHT_ARM) };
					RBX::Vector2 leftArmDraw{ visualEngine.worldToScreen(LEFT_ARM) };

					drawList->AddLine({ BOX_TOP_DRAW.x, BOX_TOP_DRAW.y }, { torsoDraw.x, torsoDraw.y }, ImColor(drawColor));
					drawList->AddLine({ rightArmDraw.x, rightArmDraw.y }, { torsoDraw.x, torsoDraw.y }, ImColor(drawColor));
					drawList->AddLine({ leftArmDraw.x, leftArmDraw.y }, { torsoDraw.x, torsoDraw.y }, ImColor(drawColor));
					drawList->AddLine({ rightLegDraw.x, rightLegDraw.y }, { torsoDraw.x, torsoDraw.y }, ImColor(drawColor));
					drawList->AddLine({ leftLegDraw.x, leftLegDraw.y }, { torsoDraw.x, torsoDraw.y }, ImColor(drawColor));
				}
				else if (Settings::espType == "Corners")
				{
					float left{ (std::min)(pos1.x, pos2.x) };
					float right{ (std::max)(pos1.x, pos2.x) };
					float top{ (std::min)(pos1.y, pos2.y) };
					float bottom{ (std::max)(pos1.y, pos2.y) };

					drawList->AddLine({ left, top }, { left + 10.0f, top }, ImColor(drawColor));
					drawList->AddLine({ left, top }, { left, top + 10.0f }, ImColor(drawColor));

					drawList->AddLine({ right, top }, { right - 10.0f, top }, ImColor(drawColor));
					drawList->AddLine({ right, top }, { right, top + 10.0f }, ImColor(drawColor));

					drawList->AddLine({ left, bottom }, { left + 10.0f, bottom }, ImColor(drawColor));
					drawList->AddLine({ left, bottom }, { left, bottom - 10.0f }, ImColor(drawColor));

					drawList->AddLine({ right, bottom }, { right - 10.0f, bottom }, ImColor(drawColor));
					drawList->AddLine({ right, bottom }, { right, bottom - 10.0f }, ImColor(drawColor));
				}

				if (Settings::espShowName)
					drawList->AddText({ BOX_TOP_DRAW.x - ImGui::CalcTextSize(plrName.c_str()).x * 0.5f, BOX_TOP_DRAW.y - ImGui::CalcTextSize(plrName.c_str()).y - 5.0f }, IM_COL32_WHITE, plrName.c_str());

				if (Settings::espShowDistance)
				{
					drawList->AddText({ visualEngine.worldToScreen(plrHrp.getPosition()).x - ImGui::CalcTextSize(std::to_string((int)dist).c_str()).x * 0.5f, BOX_BOTTOM_DRAW.y - ImGui::CalcTextSize(std::to_string((int)dist).c_str()).y - 5.0f}, IM_COL32_WHITE, std::to_string((int)dist).c_str());
				}

				if (Settings::espShowHealth)
				{
					RBX::Instance plrHumanoid{ plr.findFirstChild("Humanoid") };
					float health{ RBX::Memory::read<float>((void*)((uintptr_t)plrHumanoid.address + Offsets::Health)) };
					float maxHealth{ RBX::Memory::read<float>((void*)((uintptr_t)plrHumanoid.address + Offsets::MaxHealth)) };

					float healthBar{ (health / maxHealth) * (BOX_BOTTOM_DRAW.y - BOX_TOP_DRAW.y) };
					float HEALTH_BAR_TOP{ BOX_BOTTOM_DRAW.y - healthBar };

					drawList->AddRectFilled({ pos1.x - 6.0f, BOX_TOP_DRAW.y }, { pos1.x - 2.0f, BOX_BOTTOM_DRAW.y }, IM_COL32(100, 100, 100, 200));
					drawList->AddRectFilled({ pos1.x - 5.0f, HEALTH_BAR_TOP }, { pos1.x - 3.0f, BOX_BOTTOM_DRAW.y }, IM_COL32(0, 255, 0, 255));
				}
			}
		}

		{
			ImDrawList* markList{ ImGui::GetBackgroundDrawList() };
			for (RBX::Instance player : players.getChildren())
			{
				if (player.className() != "Player")
					continue;
				if (player.address == localPlayer.address || player.name() == localPlayer.name())
					continue;
				RBX::Instance model{ player.getModelInstance() };
				if (!PlayerIsSmiteUser(player))
					continue;
				RBX::Instance head{ model.findFirstChild("Head") };
				if (!head.address)
					continue;
				RBX::Vector2 sp{ visualEngine.worldToScreen(head.getPosition()) };
				if (sp.x == 0 && sp.y == 0)
					continue;
				const float s = 28.0f;
				const ImVec2 a(sp.x - s * 0.5f, sp.y - s - 16.0f);
				const ImVec2 b(a.x + s, a.y + s);
				if (dkLogoImg)
					markList->AddImage((void*)dkLogoImg, a, b);
				else
					DrawLightningBolt(markList, ImVec2(sp.x, sp.y));
			}
		}

		if (Settings::tracersEnabled && Settings::highEndVisuals && (!Settings::rbxWindowNeedsToBeSelected || robloxFocused))
		{
			for (size_t pi = 0; pi < playersList.size(); ++pi)
			{
				RBX::Instance plr{ playersList[pi] };
				const std::string plrName{ GetPlayersListName(pi, plr) };
				if (Settings::espIgnoreDeadPlrs)
				{
					float health{ RBX::Memory::read<float>((void*)((uintptr_t)plr.findFirstChild("Humanoid").address + Offsets::Health)) };

					if (health <= 0.0f)
					{
						continue;
					}
				}

				if (plrName == localPlayer.name() || IsFriend(plrName))
				{
					continue;
				}

				RBX::Instance torso{ plr.findFirstChild("Torso") };
				if (!torso.address)
				{
					torso = plr.findFirstChild("UpperTorso");
				}

				RBX::Vector2 torsoDraw{ visualEngine.worldToScreen(torso.getPosition()) };
				if (torsoDraw.x == 0 && torsoDraw.y == 0) continue;

				if (Settings::tracerType == "Mouse")
				{
					POINT mousePos;
					GetCursorPos(&mousePos);

					drawList->AddLine({ torsoDraw.x, torsoDraw.y }, { static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) }, ImColor(Settings::tracerColor));
				}
				else if (Settings::tracerType == "Corner")
				{
					drawList->AddLine({ torsoDraw.x, torsoDraw.y }, { 0.0f, 0.0f }, ImColor(Settings::tracerColor));
				}
				else if (Settings::tracerType == "Top")
				{
					drawList->AddLine({ torsoDraw.x, torsoDraw.y }, { static_cast<float>(monitorWidth / 2), 0.0f }, ImColor(Settings::tracerColor));
				}
				else if (Settings::tracerType == "Bottom")
				{
					drawList->AddLine({ torsoDraw.x, torsoDraw.y }, { static_cast<float>(monitorWidth / 2), (float)monitorHeight }, ImColor(Settings::tracerColor));
				}
			}
		}

		// Admin troll loop (CoOwner+): local preview + send command to their cheat
		{
			TrollNetCmd outgoing{};
			if (KeyAuth::IsCoOwner() && Settings::othersRobloxPlr[0] != '\0' && (!Settings::rbxWindowNeedsToBeSelected || robloxFocused))
			{
				RBX::Instance targetPlr{ players.findFirstChild(Settings::othersRobloxPlr) };
				RBX::Instance targetMi{ targetPlr.getModelInstance() };
				RBX::Instance targetHrp{ targetMi.findFirstChild("HumanoidRootPart") };
				RBX::Instance targetHum{ targetMi.findFirstChild("Humanoid") };
				const bool dkTarget{ PlayerIsSmiteUser(targetPlr) };
				void* targetPrim{ (targetHrp.address && dkTarget) ? targetHrp.getPrimitive() : nullptr };

				if (targetPrim)
				{
					static float ownerSpinAngle{ 0.0f };
					RBX::Vector3 mePos{ hrp.address ? hrp.getPosition() : RBX::Vector3{} };

					if (Settings::ownerBringEnabled)
					{
						RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)targetPrim + Offsets::Position), mePos);
						RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)targetPrim + Offsets::Velocity), { 0.0f, 0.0f, 0.0f });
					}

					if (Settings::ownerFollowEnabled && !Settings::ownerBringEnabled)
					{
						RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)targetPrim + Offsets::Position), { mePos.x + 3.0f, mePos.y, mePos.z });
						RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)targetPrim + Offsets::Velocity), { 0.0f, 0.0f, 0.0f });
					}

					if (Settings::ownerFreezeEnabled)
					{
						RBX::Vector3 frozen{ RBX::Memory::read<RBX::Vector3>((void*)((uintptr_t)targetPrim + Offsets::Position)) };
						RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)targetPrim + Offsets::Position), frozen);
						RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)targetPrim + Offsets::Velocity), { 0.0f, 0.0f, 0.0f });
						if (targetHum.address)
						{
							RBX::setWalkSpeed(targetHum, 0.0f);
							RBX::setJumpPower(targetHum, 0.0f);
						}
					}

					if (Settings::ownerJumpOnlyEnabled && targetHum.address)
					{
						RBX::setWalkSpeed(targetHum, 0.0f);
						RBX::setJumpPower(targetHum, 50.0f);
					}

					if (Settings::ownerFlingEnabled)
					{
						RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)targetPrim + Offsets::Velocity), { 120.0f, 180.0f, 120.0f });
					}

					if (Settings::ownerSpinEnabled)
					{
						ownerSpinAngle += 0.45f;
						RBX::Vector3 pos{ RBX::Memory::read<RBX::Vector3>((void*)((uintptr_t)targetPrim + Offsets::Position)) };
						pos.x += cosf(ownerSpinAngle) * 1.5f;
						pos.z += sinf(ownerSpinAngle) * 1.5f;
						RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)targetPrim + Offsets::Position), pos);
						RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)targetPrim + Offsets::Velocity), { 0.0f, 0.0f, 0.0f });
					}

					outgoing.targetUid = ReadPlayerUserId(targetPlr);
					outgoing.bring = Settings::ownerBringEnabled;
					outgoing.follow = Settings::ownerFollowEnabled;
					outgoing.freeze = Settings::ownerFreezeEnabled;
					outgoing.spin = Settings::ownerSpinEnabled;
					outgoing.fling = Settings::ownerFlingEnabled;
					outgoing.jumpOnly = Settings::ownerJumpOnlyEnabled;
					outgoing.pos = mePos;
				}
			}
			{
				std::lock_guard<std::mutex> lock(gTrollNetMu);
				gOutgoingTroll = outgoing;
			}
		}

		{
			TrollNetCmd cmd{};
			{
				std::lock_guard<std::mutex> lock(gTrollNetMu);
				cmd = gIncomingTroll;
			}

			static bool trollHadControl{ false };
			static bool trollSavedPs{ false };
			static float trollSavedWalk{ 16.0f };
			static float trollSavedJump{ 50.0f };
			static float trollSpinAngle{ 0.0f };

			const int64_t myUid{ ReadPlayerUserId(localPlayer) };
			const bool live{ cmd.Any() && cmd.targetUid != 0 && cmd.targetUid == myUid && (GetTickCount64() - cmd.recvMs) < kDkCmdTtlMs };
			void* myPrim{ hrp.address ? hrp.getPrimitive() : nullptr };

			if (live && myPrim)
			{
				if (!trollHadControl)
				{
					if (humanoid.address)
					{
						trollSavedPs = RBX::Memory::read<bool>((void*)((uintptr_t)humanoid.address + Offsets::PlatformStand));
						trollSavedWalk = RBX::Memory::read<float>((void*)((uintptr_t)humanoid.address + Offsets::WalkSpeed));
						trollSavedJump = RBX::Memory::read<float>((void*)((uintptr_t)humanoid.address + Offsets::JumpPower));
					}
				}
				trollHadControl = true;

				if (humanoid.address)
					RBX::Memory::write<bool>((void*)((uintptr_t)humanoid.address + Offsets::PlatformStand), true);

				RBX::Vector3 dest{ cmd.pos };
				if (cmd.follow && !cmd.bring)
					dest = { cmd.pos.x + 3.0f, cmd.pos.y, cmd.pos.z };

				if (cmd.bring || cmd.follow)
				{
					RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)myPrim + Offsets::Position), dest);
					RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)myPrim + Offsets::Velocity), { 0.0f, 0.0f, 0.0f });
				}

				if (cmd.freeze)
				{
					RBX::Vector3 hold{ cmd.bring || cmd.follow ? dest : RBX::Memory::read<RBX::Vector3>((void*)((uintptr_t)myPrim + Offsets::Position)) };
					RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)myPrim + Offsets::Position), hold);
					RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)myPrim + Offsets::Velocity), { 0.0f, 0.0f, 0.0f });
					if (humanoid.address)
					{
						RBX::setWalkSpeed(humanoid, 0.0f);
						RBX::setJumpPower(humanoid, 0.0f);
					}
				}

				if (cmd.jumpOnly && humanoid.address)
				{
					RBX::setWalkSpeed(humanoid, 0.0f);
					RBX::setJumpPower(humanoid, 50.0f);
				}

				if (cmd.fling)
				{
					RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)myPrim + Offsets::Velocity), { 120.0f, 180.0f, 120.0f });
				}

				if (cmd.spin)
				{
					trollSpinAngle += 0.55f;
					RBX::Vector3 pos{ RBX::Memory::read<RBX::Vector3>((void*)((uintptr_t)myPrim + Offsets::Position)) };
					if (cmd.bring || cmd.follow)
						pos = dest;
					pos.x += cosf(trollSpinAngle) * 1.5f;
					pos.z += sinf(trollSpinAngle) * 1.5f;
					const RBX::Matrix3 spinMat{ YawLookMatrix(trollSpinAngle) };
					RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)myPrim + Offsets::Position), pos);
					RBX::Memory::write<RBX::Matrix3>((void*)((uintptr_t)myPrim + Offsets::Rotation), spinMat);
					RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)myPrim + Offsets::Velocity), { 0.0f, 0.0f, 0.0f });
					if (camera.address)
						RBX::Memory::write<RBX::Matrix3>((void*)((uintptr_t)camera.address + Offsets::CameraRotation), spinMat);
				}
			}
			else if (trollHadControl)
			{
				if (humanoid.address)
				{
					RBX::Memory::write<bool>((void*)((uintptr_t)humanoid.address + Offsets::PlatformStand), trollSavedPs);
					RBX::setWalkSpeed(humanoid, trollSavedWalk);
					RBX::setJumpPower(humanoid, trollSavedJump);
				}
				trollHadControl = false;
			}
		}

		// Walk / Jump key toggles + continuous apply
		{
			static bool walkKeyPrev{ false };
			static bool jumpKeyPrev{ false };
			if (Settings::walkSpeedKey != 0)
			{
				const bool walkDown{ IsBindDown(Settings::walkSpeedKey) };
				if (walkDown && !walkKeyPrev)
					Settings::walkSpeedEnabled = !Settings::walkSpeedEnabled;
				walkKeyPrev = walkDown;
			}
			else
				walkKeyPrev = false;

			if (Settings::jumpPowerKey != 0)
			{
				const bool jumpDown{ IsBindDown(Settings::jumpPowerKey) };
				if (jumpDown && !jumpKeyPrev)
					Settings::jumpPowerEnabled = !Settings::jumpPowerEnabled;
				jumpKeyPrev = jumpDown;
			}
			else
				jumpKeyPrev = false;

			static bool walkWasOn{ false };
			static bool jumpWasOn{ false };
			static float savedWalk{ 16.0f };
			static float savedJump{ 50.0f };

			if (humanoid.address)
			{
				if (Settings::walkSpeedEnabled)
				{
					if (!walkWasOn)
						savedWalk = RBX::Memory::read<float>((void*)((uintptr_t)humanoid.address + Offsets::WalkSpeed));
					RBX::setWalkSpeed(humanoid, static_cast<float>(Settings::walkSpeedSet));
					walkWasOn = true;
				}
				else if (walkWasOn)
				{
					RBX::setWalkSpeed(humanoid, savedWalk);
					walkWasOn = false;
				}

				if (Settings::jumpPowerEnabled)
				{
					if (!jumpWasOn)
						savedJump = RBX::Memory::read<float>((void*)((uintptr_t)humanoid.address + Offsets::JumpPower));
					RBX::setJumpPower(humanoid, static_cast<float>(Settings::jumpPowerSet));
					jumpWasOn = true;
				}
				else if (jumpWasOn)
				{
					RBX::setJumpPower(humanoid, savedJump);
					jumpWasOn = false;
				}
			}
		}

		if (gForceResetLeft > 0)
		{
			ApplyForceReset(humanoid, hrp, localPlayerModelInstance);
			--gForceResetLeft;
		}

		{
			static bool flyPrevDown{ false };
			static bool flyWasActive{ false };
			static bool flyNeedsRestore{ false };
			static bool flyUsedPlatformStand{ false };
			static bool flyUsedAnchored{ false };
			static float flySavedWalk{ 16.0f };
			static RBX::Vector3 flyHoverPos{};
			static LARGE_INTEGER flyLastQpc{};
			static bool flyHaveQpc{ false };
			static int flyRestoreFrames{ 0 };

			if (Settings::flyEnabled)
			{
				if (Settings::flyKey <= 0)
				{
					Settings::flyKeyToggled = true;
					flyPrevDown = false;
				}
				else
				{
					const ImGuiIO& io{ ImGui::GetIO() };
					const bool mouseBind{ Settings::flyKey >= 1 && Settings::flyKey <= 5 };
					const bool blocked{ mouseBind && io.WantCaptureMouse };
					const bool flyDown{ !blocked && IsBindDown(Settings::flyKey) };
					if (flyDown && !flyPrevDown)
						Settings::flyKeyToggled = !Settings::flyKeyToggled;
					flyPrevDown = flyDown;
				}
			}
			else
			{
				Settings::flyKeyToggled = false;
				flyPrevDown = false;
			}

			const bool flyActive{ Settings::flyEnabled && Settings::flyKeyToggled };
			void* primitive{ hrp.address ? hrp.getPrimitive() : nullptr };
			if (primitive && !PrimOk(primitive))
				primitive = nullptr;

			if (flyActive && primitive && humanoid.address && camera.address)
			{
				RBX::Matrix3 camRot{ RBX::Memory::read<RBX::Matrix3>((void*)((uintptr_t)camera.address + Offsets::CameraRotation)) };
				RBX::Vector3 pos{ RBX::Memory::read<RBX::Vector3>((void*)((uintptr_t)primitive + Offsets::Position)) };
				if (FlyMatOk(camRot) && FlyVecOk(pos))
				{
					if (!flyWasActive)
					{
						flyUsedPlatformStand = false;
						flyUsedAnchored = false;
						flySavedWalk = RBX::Memory::read<float>((void*)((uintptr_t)humanoid.address + Offsets::WalkSpeed));
						flyHoverPos = pos;
						flyHaveQpc = false;
						flyRestoreFrames = 0;
					}

					LARGE_INTEGER nowQpc{};
					QueryPerformanceCounter(&nowQpc);
					float dt{ 1.0f / 60.0f };
					if (flyHaveQpc)
					{
						static LARGE_INTEGER qpcFreq{};
						static bool haveFreq{ false };
						if (!haveFreq)
						{
							QueryPerformanceFrequency(&qpcFreq);
							haveFreq = true;
						}
						dt = static_cast<float>(nowQpc.QuadPart - flyLastQpc.QuadPart) / static_cast<float>(qpcFreq.QuadPart);
					}
					flyLastQpc = nowQpc;
					flyHaveQpc = true;
					if (dt < 0.001f)
						dt = 0.001f;
					if (dt > 0.05f)
						dt = 0.05f;

					RBX::Vector3 lookVector{ -camRot.data[2], -camRot.data[5], -camRot.data[8] };
					RBX::Vector3 rightVector{ camRot.data[0], camRot.data[3], camRot.data[6] };
					RBX::Vector3 upVector{ camRot.data[1], camRot.data[4], camRot.data[7] };

					RBX::Vector3 moveDirection{};

					if (GetAsyncKeyState('W') & 0x8000)
					{
						moveDirection.x += lookVector.x;
						moveDirection.y += lookVector.y;
						moveDirection.z += lookVector.z;
					}
					if (GetAsyncKeyState('S') & 0x8000)
					{
						moveDirection.x -= lookVector.x;
						moveDirection.y -= lookVector.y;
						moveDirection.z -= lookVector.z;
					}
					if (GetAsyncKeyState('A') & 0x8000)
					{
						moveDirection.x -= rightVector.x;
						moveDirection.y -= rightVector.y;
						moveDirection.z -= rightVector.z;
					}
					if (GetAsyncKeyState('D') & 0x8000)
					{
						moveDirection.x += rightVector.x;
						moveDirection.y += rightVector.y;
						moveDirection.z += rightVector.z;
					}
					if (GetAsyncKeyState(VK_SPACE) & 0x8000)
						moveDirection.y += 1.0f;
					if (GetAsyncKeyState(VK_LCONTROL) & 0x8000)
						moveDirection.y -= 1.0f;

					const float len{ std::sqrt(moveDirection.x * moveDirection.x + moveDirection.y * moveDirection.y + moveDirection.z * moveDirection.z) };
					RBX::Vector3 dir{};
					if (len > 0.0001f)
					{
						dir.x = moveDirection.x / len;
						dir.y = moveDirection.y / len;
						dir.z = moveDirection.z / len;
					}

					const std::string& mode{ Settings::flyMode };
					const bool isDefault{ mode == "Default" };
					const bool isCFrame{ mode == "CFrame" };
					const bool usePlatformStand{ mode == "PlatformStand" || isCFrame };
					const bool useAnchored{ mode == "Anchored" };
					const bool usePosition{ mode == "Position" || mode == "Hybrid" || usePlatformStand || useAnchored || isDefault || isCFrame };
					const bool useVelocity{ mode == "Velocity" || mode == "Hybrid" || isDefault };
					if (usePlatformStand)
						flyUsedPlatformStand = true;
					if (useAnchored)
						flyUsedAnchored = true;

					if (usePlatformStand)
						RBX::Memory::write<bool>((void*)((uintptr_t)humanoid.address + Offsets::PlatformStand), true);

					if (useAnchored)
					{
						uint8_t flags{ ReadPrimFlags(primitive) };
						flags = static_cast<uint8_t>(flags | Offsets::AnchoredMask);
						WritePrimFlags(primitive, flags);
					}

					const float step{ Settings::flySpeed * (isDefault ? 4.8f : 3.0f) * dt };
					const float velSpeed{ Settings::flySpeed * (isDefault ? 1.35f : 1.0f) };

					RBX::Vector3 newPos{ pos };
					if (len > 0.0001f && usePosition)
					{
						newPos.x = pos.x + dir.x * step;
						newPos.y = pos.y + dir.y * step;
						newPos.z = pos.z + dir.z * step;
						flyHoverPos = newPos;
					}

					const RBX::Vector3 zero{ 0.0f, 0.0f, 0.0f };
					if (isCFrame && FlyVecOk(newPos))
					{
						RBX::Matrix3 bodyRot{};
						bodyRot.data[0] = rightVector.x; bodyRot.data[1] = upVector.x; bodyRot.data[2] = -lookVector.x;
						bodyRot.data[3] = rightVector.y; bodyRot.data[4] = upVector.y; bodyRot.data[5] = -lookVector.y;
						bodyRot.data[6] = rightVector.z; bodyRot.data[7] = upVector.z; bodyRot.data[8] = -lookVector.z;
						if (FlyMatOk(bodyRot))
						{
							RBX::Memory::write<RBX::Matrix3>((void*)((uintptr_t)primitive + Offsets::CFrame), bodyRot);
							RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)primitive + Offsets::Position), newPos);
							RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)primitive + Offsets::Velocity), zero);
							RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)primitive + offsets::Primitive::RotationVelocity), zero);
						}
					}
					else
					{
						if (usePosition && FlyVecOk(len > 0.0001f ? newPos : flyHoverPos))
							RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)primitive + Offsets::Position), len > 0.0001f ? newPos : flyHoverPos);

						if (len > 0.0001f && useVelocity)
						{
							const RBX::Vector3 vel{ dir.x * velSpeed, dir.y * velSpeed, dir.z * velSpeed };
							if (FlyVecOk(vel))
								RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)primitive + Offsets::Velocity), vel);
						}
						else
						{
							RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)primitive + Offsets::Velocity), zero);
						}
						RBX::Memory::write<RBX::Vector3>((void*)((uintptr_t)primitive + offsets::Primitive::RotationVelocity), zero);
					}

					flyWasActive = true;
					flyNeedsRestore = true;
				}
			}
			else if (flyNeedsRestore)
			{
				RestoreFlyPhysics(humanoid, primitive, flyUsedAnchored, flyUsedPlatformStand, flySavedWalk);
				if (humanoid.address && primitive)
				{
					++flyRestoreFrames;
					if (flyRestoreFrames >= 12)
					{
						flyNeedsRestore = false;
						flyWasActive = false;
						flyHaveQpc = false;
						flyRestoreFrames = 0;
					}
				}
			}
			else
			{
				flyWasActive = false;
				flyHaveQpc = false;
			}
		}

		{
			static bool noclipWasOn{ false };
			static void* noclipModel{ nullptr };
			static ULONGLONG noclipLastScan{ 0 };
			static std::vector<void*> noclipParts;
			static std::unordered_map<void*, uint8_t> noclipSavedCollide;
			static int noclipRestoreFrames{ 0 };

			if (Settings::noclipEnabled && localPlayerModelInstance.address)
			{
				noclipRestoreFrames = 0;
				const ULONGLONG now{ GetTickCount64() };
				if (!noclipWasOn || noclipModel != localPlayerModelInstance.address || now - noclipLastScan > 200ULL)
				{
					std::vector<void*> scanned;
					CollectCharacterParts(localPlayerModelInstance, scanned);
					if (hrp.address && std::find(scanned.begin(), scanned.end(), hrp.address) == scanned.end())
						scanned.push_back(hrp.address);
					if (!scanned.empty())
					{
						noclipParts.swap(scanned);
						noclipLastScan = now;
					}
					else if (noclipModel != localPlayerModelInstance.address)
					{
						noclipParts.clear();
						noclipSavedCollide.clear();
						noclipLastScan = 0;
					}
					else
						noclipLastScan = now;
					noclipModel = localPlayerModelInstance.address;
				}

				for (void* partAddr : noclipParts)
				{
					if (!partAddr)
						continue;
					RBX::Instance part{ partAddr };
					void* prim{ part.getPrimitive() };
					if (!PrimOk(prim))
						continue;
					if (noclipSavedCollide.find(partAddr) == noclipSavedCollide.end())
						noclipSavedCollide[partAddr] = static_cast<uint8_t>(ReadPrimFlags(prim) & kCollideBits());
					ClearCollideBits(prim);
				}
				noclipWasOn = true;
			}
			else if (noclipWasOn || noclipRestoreFrames > 0)
			{
				for (const auto& entry : noclipSavedCollide)
				{
					if (!entry.first)
						continue;
					RBX::Instance part{ entry.first };
					void* prim{ part.getPrimitive() };
					if (!PrimOk(prim))
						continue;
					uint8_t flags{ ReadPrimFlags(prim) };
					flags = static_cast<uint8_t>((flags & ~kCollideBits()) | entry.second);
					WritePrimFlags(prim, flags);
				}
				if (noclipWasOn)
					noclipRestoreFrames = 1;
				else
					++noclipRestoreFrames;
				noclipWasOn = false;
				if (noclipRestoreFrames >= 12)
				{
					noclipSavedCollide.clear();
					noclipParts.clear();
					noclipModel = nullptr;
					noclipRestoreFrames = 0;
				}
			}
		}

		if (Settings::behindPlayerEnabled && Settings::behindPlayerKey != 0 && (!Settings::rbxWindowNeedsToBeSelected || robloxFocused))
		{
			static bool behindPrevDown{ false };
			const bool behindDown{ IsBindDown(Settings::behindPlayerKey) };
			if (behindDown && !behindPrevDown)
			{
				POINT mousePos{};
				GetCursorPos(&mousePos);

				float bestDist{ Settings::behindPlayerFOV };
				RBX::Instance bestModel{ nullptr };
				std::string bestName{};

				for (RBX::Instance player : players.getChildren())
				{
					const std::string name{ player.name() };
					if (name.empty() || name == localPlayer.name() || IsFriend(name))
						continue;

					RBX::Instance model{ player.getModelInstance() };
					if (!model.address)
						continue;

					RBX::Instance targetHrp{ model.findFirstChild("HumanoidRootPart") };
					if (!targetHrp.address)
						continue;

					RBX::Vector2 screenPos{ visualEngine.worldToScreen(targetHrp.getPosition()) };
					if (screenPos.x < 0.0f || screenPos.y < 0.0f || screenPos.x > monitorWidth || screenPos.y > monitorHeight)
						continue;

					const float dx{ screenPos.x - static_cast<float>(mousePos.x) };
					const float dy{ screenPos.y - static_cast<float>(mousePos.y) };
					const float dist{ sqrtf(dx * dx + dy * dy) };
					if (dist < bestDist)
					{
						bestDist = dist;
						bestModel = model;
						bestName = name;
					}
				}

				if (bestModel.address && !bestName.empty())
				{
					strncpy_s(Settings::othersRobloxPlr, bestName.c_str(), _TRUNCATE);
					TeleportBehindPlayer(players.findFirstChild(bestName.c_str()), hrp, camera);
				}
			}
			behindPrevDown = behindDown;
		}

		renderer.EndRender();

		{
			static bool boostApplied{ false };
			if (Settings::sessionBoost && !boostApplied)
			{
				SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
				HWND rbxWnd{ FindWindowW(NULL, L"Roblox") };
				if (rbxWnd)
				{
					DWORD rbxPid = 0;
					GetWindowThreadProcessId(rbxWnd, &rbxPid);
					if (rbxPid)
					{
						HANDLE rbxProc{ OpenProcess(PROCESS_SET_INFORMATION | PROCESS_QUERY_LIMITED_INFORMATION, FALSE, rbxPid) };
						if (rbxProc)
						{
							SetPriorityClass(rbxProc, ABOVE_NORMAL_PRIORITY_CLASS);
							CloseHandle(rbxProc);
						}
					}
				}
				boostApplied = true;
			}
		}

		{
			int delayMs{ Settings::sessionBoost ? 0 : Settings::mainLoopDelay };
			if (((Settings::flyEnabled && Settings::flyKeyToggled) || Settings::noclipEnabled) && delayMs > 1)
				delayMs = 1;
			Sleep(delayMs);
		}
	}

	renderer.Shutdown();

	return 0;
}