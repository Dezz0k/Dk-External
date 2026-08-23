#pragma once

#include <cstdint>
#include <string>

// Sourced from https://offsets.imtheo.lol (RbxDumperV2)
// Roblox Version: version-ddf602d9cfe44005
// Dumped At: 22:59 11/08/2026 (GMT)

inline std::string ClientVersion = "version-ddf602d9cfe44005";

namespace offsets {

	namespace Animation {
		inline constexpr uintptr_t AnimationId = 0xC0;
	}

	namespace BasePart {
		inline constexpr uintptr_t BrickColor = 0x1A8;
		inline constexpr uintptr_t CastShadow = 0x135;
		inline constexpr uintptr_t Locked = 0x136;
		inline constexpr uintptr_t Massless = 0x137;
		inline constexpr uintptr_t Primitive = 0x188;
		inline constexpr uintptr_t Reflectance = 0x10C;
		inline constexpr uintptr_t Shape = 0x1B9;
		inline constexpr uintptr_t Transparency = 0x130;
	}

	namespace Beam {
		inline constexpr uintptr_t Attachment0 = 0x160;
		inline constexpr uintptr_t Attachment1 = 0x170;
		inline constexpr uintptr_t Brightness = 0x180;
		inline constexpr uintptr_t Color = 0x10C;
		inline constexpr uintptr_t CurveSize0 = 0x184;
		inline constexpr uintptr_t CurveSize1 = 0x188;
		inline constexpr uintptr_t LightEmission = 0x18C;
		inline constexpr uintptr_t LightInfluence = 0x190;
		inline constexpr uintptr_t Texture = 0x140;
		inline constexpr uintptr_t TextureLength = 0x19C;
		inline constexpr uintptr_t TextureSpeed = 0x1A4;
		inline constexpr uintptr_t Width0 = 0x1A8;
		inline constexpr uintptr_t Width1 = 0x1AC;
		inline constexpr uintptr_t ZOffset = 0x1B0;
	}

	namespace BloomEffect {
		inline constexpr uintptr_t Enabled = 0xB0;
		inline constexpr uintptr_t Intensity = 0xB8;
		inline constexpr uintptr_t Size = 0xBC;
		inline constexpr uintptr_t Threshold = 0xC0;
	}

	namespace ByteCode {
		inline constexpr uintptr_t Pointer = 0x10;
		inline constexpr uintptr_t Size = 0x20;
	}

	namespace Camera {
		inline constexpr uintptr_t FOV = 0x140;
		inline constexpr uintptr_t Focus = 0x108;
		inline constexpr uintptr_t Position = 0xFC;
		inline constexpr uintptr_t Rotation = 0xD8;
		inline constexpr uintptr_t Subject = 0xC8;
		inline constexpr uintptr_t Type = 0x138;
		inline constexpr uintptr_t ViewportInt16 = 0x28C;
		inline constexpr uintptr_t ViewportSize = 0x2CC;
	}

	namespace CharacterMesh {
		inline constexpr uintptr_t BaseTextureId = 0xC8;
		inline constexpr uintptr_t BodyPart = 0x148;
		inline constexpr uintptr_t MeshId = 0xF8;
		inline constexpr uintptr_t OverlayTextureId = 0x128;
	}

	namespace DataModel {
		inline constexpr uintptr_t CreatorId = 0x178;
		inline constexpr uintptr_t GameId = 0x180;
		inline constexpr uintptr_t GameLoaded = 0x570;
		inline constexpr uintptr_t JobId = 0x118;
		inline constexpr uintptr_t PlaceId = 0x188;
		inline constexpr uintptr_t PlaceVersion = 0x1A4;
		inline constexpr uintptr_t PrimitiveCount = 0x3B8;
		inline constexpr uintptr_t ScriptContext = 0x440;
		inline constexpr uintptr_t ServerIp = 0x558;
		inline constexpr uintptr_t ToRenderView1 = 0x1C0;
		inline constexpr uintptr_t ToRenderView2 = 0x8;
		inline constexpr uintptr_t ToRenderView3 = 0x28;
		inline constexpr uintptr_t Workspace = 0x158;
	}

	namespace FakeDataModel {
		// Deleter is typically Pointer - 8
		inline constexpr uintptr_t DataModelDeleterPointer = 0x8B79B50;
		inline constexpr uintptr_t Pointer = 0x8B79B58;
		inline constexpr uintptr_t ToRealDataModel = 0x1D8;
	}

	namespace GuiObject {
		inline constexpr uintptr_t AbsolutePositionX = 0x10C;
		inline constexpr uintptr_t AbsolutePositionY = 0x110;
		inline constexpr uintptr_t AbsoluteSizeX = 0x114;
		inline constexpr uintptr_t AbsoluteSizeY = 0x118;
		inline constexpr uintptr_t BackgroundColor3 = 0x540;
		inline constexpr uintptr_t BackgroundTransparency = 0x54C;
		inline constexpr uintptr_t BorderColor3 = 0x54C;
		inline constexpr uintptr_t LayoutOrder = 0x580;
		inline constexpr uintptr_t PositionOffsetX = 0x514;
		inline constexpr uintptr_t PositionOffsetY = 0x51C;
		inline constexpr uintptr_t PositionX = 0x510;
		inline constexpr uintptr_t PositionY = 0x518;
		inline constexpr uintptr_t Rotation = 0xE8;
		inline constexpr uintptr_t SizeOffsetX = 0x538;
		inline constexpr uintptr_t SizeOffsetY = 0x53C;
		inline constexpr uintptr_t SizeX = 0x530;
		inline constexpr uintptr_t SizeY = 0x534;
		inline constexpr uintptr_t Visible = 0x5AD;
		inline constexpr uintptr_t ZIndex = 0x5A4;
	}

	namespace Highlight {
		inline constexpr uintptr_t Adornee = 0xF0;
	}

	namespace Humanoid {
		inline constexpr uintptr_t AutoJump = 0x1D4;
		inline constexpr uintptr_t AutoRotate = 0x1D5;
		inline constexpr uintptr_t AutomaticScalingEnabled = 0x1D6;
		inline constexpr uintptr_t BreakJointsOnDeath = 0x1D7;
		inline constexpr uintptr_t CameraOffset = 0x128;
		inline constexpr uintptr_t DisplayDistanceType = 0x180;
		inline constexpr uintptr_t DisplayName = 0xB8;
		inline constexpr uintptr_t EvaluateStateMachine = 0x1D8;
		inline constexpr uintptr_t FloorMaterial = 0x184;
		inline constexpr uintptr_t Health = 0x190;
		inline constexpr uintptr_t HealthDisplayDistance = 0x188;
		inline constexpr uintptr_t HealthDisplayType = 0x18C;
		inline constexpr uintptr_t HipHeight = 0x194;
		inline constexpr uintptr_t HumanoidRootPart = 0x478;
		inline constexpr uintptr_t HumanoidState = 0x898;
		inline constexpr uintptr_t HumanoidStateId = 0x20;
		inline constexpr uintptr_t IsWalking = 0x93F;
		inline constexpr uintptr_t Jump = 0x1DA;
		inline constexpr uintptr_t JumpHeight = 0x1A0;
		inline constexpr uintptr_t JumpPower = 0x1A4;
		inline constexpr uintptr_t MaxHealth = 0x1A8;
		inline constexpr uintptr_t MaxSlopeAngle = 0x1AC;
		inline constexpr uintptr_t MoveDirection = 0x140;
		inline constexpr uintptr_t MoveToPart = 0x118;
		inline constexpr uintptr_t MoveToPoint = 0x164;
		inline constexpr uintptr_t NameDisplayDistance = 0x1B0;
		inline constexpr uintptr_t NameOcclusion = 0x1B4;
		// Dump lists 0xC5 (looks bad); keep prior known-good layout beside Sit
		inline constexpr uintptr_t PlatformStand = 0x1DC;
		inline constexpr uintptr_t RequiresNeck = 0x1DD;
		inline constexpr uintptr_t RigType = 0x1C0;
		inline constexpr uintptr_t SeatPart = 0x108;
		inline constexpr uintptr_t Sit = 0x1DD;
		inline constexpr uintptr_t TargetPoint = 0x14C;
		inline constexpr uintptr_t UseJumpPower = 0x1E0;
		inline constexpr uintptr_t WalkSpeed = 0x1D0;
		inline constexpr uintptr_t WalkSpeedCheck = 0x3BC;
	}

	namespace InputObject {
		inline constexpr uintptr_t InputObject = 0xF0;
		inline constexpr uintptr_t InputObject2 = 0x100;
		inline constexpr uintptr_t MousePosition = 0xD4;
	}

	namespace Instance {
		// NameContainer is the readable name pointer; dump's Name(0x8) is not usable here.
		inline constexpr uintptr_t Children = 0x78;
		inline constexpr uintptr_t ChildrenSize = 0x8;
		inline constexpr uintptr_t ClassDescriptor = 0x18;
		inline constexpr uintptr_t ClassDescriptorToClassName = 0x8;
		inline constexpr uintptr_t Deleter = 0x10;
		inline constexpr uintptr_t Name = 0x70;
		inline constexpr uintptr_t NameSize = 0x10;
		inline constexpr uintptr_t Parent = 0x68;
	}

	namespace Lighting {
		inline constexpr uintptr_t Ambient = 0xD0;
		inline constexpr uintptr_t Brightness = 0x118;
		inline constexpr uintptr_t ClockTime = 0xC8;
		inline constexpr uintptr_t ColorShiftBottom = 0xE8;
		inline constexpr uintptr_t ColorShiftTop = 0xDC;
		inline constexpr uintptr_t EnvironmentDiffuseScale = 0x11C;
		inline constexpr uintptr_t EnvironmentSpecularScale = 0x120;
		inline constexpr uintptr_t ExposureCompensation = 0x124;
		inline constexpr uintptr_t FogColor = 0xF4;
		inline constexpr uintptr_t FogEnd = 0x12C;
		inline constexpr uintptr_t FogStart = 0x130;
		inline constexpr uintptr_t GeographicLatitude = 0x134;
		inline constexpr uintptr_t GlobalShadows = 0x144;
		inline constexpr uintptr_t OutDoorAmbient = 0x100;
		inline constexpr uintptr_t ShadowColor = 0x10C;
		inline constexpr uintptr_t Sky = 0x1C8;
	}

	namespace LocalPlayer {
		inline constexpr uintptr_t PlayerMouse = 0x11F0;
	}

	namespace LocalScript {
		// Dump ByteCode is 0 — keep known working embed offset
		inline constexpr uintptr_t ByteCode = 0x190;
		inline constexpr uintptr_t GUID = 0xD0;
		inline constexpr uintptr_t Hash = 0x1A0;
	}

	namespace MeshPart {
		inline constexpr uintptr_t MeshId = 0x308;
		inline constexpr uintptr_t TextureId = 0x338;
	}

	namespace ModelInstance {
		inline constexpr uintptr_t PrimaryPart = 0x258;
		inline constexpr uintptr_t Scale = 0x144;
	}

	namespace ModuleScript {
		// Dump ByteCode is 0 — keep known working embed offset
		inline constexpr uintptr_t ByteCode = 0x138;
		inline constexpr uintptr_t GUID = 0xD0;
		inline constexpr uintptr_t Hash = 0x148;
	}

	namespace Ping {
		inline constexpr uintptr_t Value = 0xC8;
	}

	namespace Player {
		inline constexpr uintptr_t AccountAge = 0x35C;
		inline constexpr uintptr_t CameraMode = 0x370;
		inline constexpr uintptr_t DisplayName = 0x138;
		inline constexpr uintptr_t HealthDisplayDistance = 0x394;
		inline constexpr uintptr_t LocaleId = 0x118;
		inline constexpr uintptr_t MaxZoomDistance = 0x368;
		inline constexpr uintptr_t MinZoomDistance = 0x36C;
		inline constexpr uintptr_t ModelInstance = 0x298;
		inline constexpr uintptr_t Mouse = 0x11F0;
		inline constexpr uintptr_t NameDisplayDistance = 0x3A4;
		inline constexpr uintptr_t Team = 0x2D8;
		inline constexpr uintptr_t TeamColor = 0x3B0;
		inline constexpr uintptr_t UserId = 0x300;
	}

	namespace Players {
		inline constexpr uintptr_t LocalPlayer = 0x130;
		inline constexpr uintptr_t RespawnTime = 0x148;
	}

	namespace Pointers {
		inline constexpr uintptr_t PlayerConfigurer = 0x0;
		inline constexpr uintptr_t Print = 0x4C27BF0;
		inline constexpr uintptr_t Sensitivity = 0x0;
		inline constexpr uintptr_t TaskScheduler = 0x88B64C8;
	}

	namespace Primitive {
		inline constexpr uintptr_t CFrame = 0xC8;
		// Dump Material is 0 — keep prior known value
		inline constexpr uintptr_t Material = 0x23E;
		inline constexpr uintptr_t Position = 0xEC;
		inline constexpr uintptr_t PrimitiveFlags = 0x1B6;
		inline constexpr uintptr_t Rotation = 0xC8;
		inline constexpr uintptr_t RotationVelocity = 0x104;
		inline constexpr uintptr_t Size = 0x1BC;
		inline constexpr uintptr_t ValidateValue = 0x6;
		inline constexpr uintptr_t Velocity = 0xF8;
	}

	namespace PrimitiveFlags {
		inline constexpr uintptr_t AnchoredMask = 0x2;
		inline constexpr uintptr_t CanCollideMask = 0x8;
		inline constexpr uintptr_t CanTouchMask = 0x10;
		inline constexpr uintptr_t CanQueryMask = 0x20;
	}

	namespace RenderJob {
		inline constexpr uintptr_t DataModel = 0x1D0;
		inline constexpr uintptr_t FakeDataModel = 0x38;
		inline constexpr uintptr_t ToRenderView = 0x1D8;
	}

	namespace RenderView {
		inline constexpr uintptr_t DeviceD3D11 = 0x8;
		inline constexpr uintptr_t InvalidateLighting = 0x150;
		inline constexpr uintptr_t InvalidateSkyBox = 0x28D;
		inline constexpr uintptr_t ToVisualEngine = 0x10;
	}

	namespace RunService {
		inline constexpr uintptr_t HeartbeatFPS = 0xF4;
		inline constexpr uintptr_t HeartbeatTask = 0x3B8;
	}

	namespace Sky {
		inline constexpr uintptr_t CelestialBodiesShown = 0x250;
		inline constexpr uintptr_t MoonAngularSize = 0x244;
		inline constexpr uintptr_t MoonTextureId = 0xC8;
		inline constexpr uintptr_t SkyboxBk = 0xF8;
		inline constexpr uintptr_t SkyboxDn = 0x128;
		inline constexpr uintptr_t SkyboxFt = 0x158;
		inline constexpr uintptr_t SkyboxLf = 0x188;
		inline constexpr uintptr_t SkyboxOrientation = 0x238;
		inline constexpr uintptr_t SkyboxRt = 0x1B8;
		inline constexpr uintptr_t SkyboxUp = 0x1E8;
		inline constexpr uintptr_t StarCount = 0x248;
		inline constexpr uintptr_t SunAngularSize = 0x23C;
		inline constexpr uintptr_t SunTextureId = 0x218;
	}

	namespace SpecialMesh {
		inline constexpr uintptr_t MeshId = 0xF8;
		inline constexpr uintptr_t Scale = 0xC4;
	}

	namespace TaskScheduler {
		inline constexpr uintptr_t JobEnd = 0xD0;
		inline constexpr uintptr_t JobName = 0x18;
		inline constexpr uintptr_t JobStart = 0xC8;
		inline constexpr uintptr_t JobsPointer = 0x88B64C8;
		inline constexpr uintptr_t MaxFPS = 0xB0;
	}

	namespace Team {
		inline constexpr uintptr_t TeamColor = 0xB8;
	}

	namespace TextLabel {
		inline constexpr uintptr_t RichText = 0xB88;
		inline constexpr uintptr_t Text = 0xDF8;
		inline constexpr uintptr_t TextColor3 = 0xEA8;
	}

	namespace Texture {
		inline constexpr uintptr_t TextureId = 0x180;
	}

	namespace Tool {
		inline constexpr uintptr_t CanBeDropped = 0x4B8;
		inline constexpr uintptr_t Enabled = 0x4B9;
		inline constexpr uintptr_t GripPosition = 0x4AC;
		inline constexpr uintptr_t ManualActivationOnly = 0x4BA;
		inline constexpr uintptr_t RequiresHandle = 0x4BB;
		inline constexpr uintptr_t TextureId = 0x360;
		inline constexpr uintptr_t Tooltip = 0x468;
	}

	namespace Value {
		inline constexpr uintptr_t Value = 0xB8;
	}

	namespace VisualEngine {
		inline constexpr uintptr_t DataModel = 0x1D8;
		inline constexpr uintptr_t Dimensions = 0xAE0;
		inline constexpr uintptr_t FakeDataModel = 0xAC0;
		inline constexpr uintptr_t Pointer = 0x8136228;
		inline constexpr uintptr_t ToRenderView = 0xC00;
		inline constexpr uintptr_t ViewMatrix = 0x180;
	}

	namespace Workspace {
		inline constexpr uintptr_t Camera = 0x498;
		inline constexpr uintptr_t DistributedGameTime = 0x4B8;
		inline constexpr uintptr_t ReadOnlyGravity = 0x9C0;
		inline constexpr uintptr_t World = 0x3F0;
	}

	namespace World {
		inline constexpr uintptr_t AirProperties = 0x220;
		inline constexpr uintptr_t FallenPartsDestroyHeight = 0x208;
		inline constexpr uintptr_t Gravity = 0x210;
		inline constexpr uintptr_t PhysicsStepTime = 0x708;
		inline constexpr uintptr_t PrimitiveList = 0x290;
	}

}
