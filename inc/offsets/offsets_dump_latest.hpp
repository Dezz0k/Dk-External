#pragma once
#include <cstdint>

//  X    = 0x1D0            field of the object
//  X[]  = { 0x128, 0x1C0 } deref every entry but the last, then add it

namespace Offsets {

namespace Accessory { // : Accoutrement
                      // AccessoryType                              = ?;   // E1
} // namespace Accessory

namespace AccessoryDescription {      // : Instance
constexpr uintptr_t AssetId = 0xC0;   // int64
constexpr uintptr_t Position = 0xC8;  // Vector3
constexpr uintptr_t Rotation = 0xD4;  // Vector3
constexpr uintptr_t Order = 0xF0;     // int
constexpr uintptr_t Puffiness = 0xF4; // float
constexpr uintptr_t IsLayered = 0xF8; // bool
// AccessoryType                              = ?;   // E1
// Instance                                   = ?;   // E4
// Scale                                      = ?;   // E3
} // namespace AccessoryDescription

namespace Accoutrement {                             // : Instance
constexpr uintptr_t AttachmentForward = 0xC0;        // Vector3
constexpr uintptr_t AttachmentRight = 0xD0;          // Vector3
constexpr uintptr_t AttachmentUp = 0xD4;             // Vector3
constexpr uintptr_t AttachmentPos = 0xDC;            // Vector3
constexpr uintptr_t BackendAccoutrementState = 0xE8; // int
// AttachmentPoint                            = ?;   // E1
} // namespace Accoutrement

namespace AdGui {                                 // : SurfaceGuiBase
constexpr uintptr_t FallbackImage = 0x848;        // ContentId
constexpr uintptr_t FallbackImageContent = 0x848; // Content
constexpr uintptr_t EnableVideoAds = 0x874;       // bool
// AdShape                                    = ?;   // E1
// Status                                     = ?;   // E1
} // namespace AdGui

namespace AirController {                            // : ControllerBase
constexpr uintptr_t LinearImpulse = 0xE0;            // Vector3
constexpr uintptr_t BalanceMaxTorque = 0xEC;         // float
constexpr uintptr_t BalanceSpeed = 0xF0;             // float
constexpr uintptr_t TurnMaxTorque = 0xF8;            // float
constexpr uintptr_t TurnSpeedFactor = 0xFC;          // float
constexpr uintptr_t MaintainAngularMomentum = 0x100; // bool
constexpr uintptr_t MaintainLinearMomentum = 0x101;  // bool
// MoveMaxForce                               = ?;   // E3
} // namespace AirController

namespace AlignOrientation {                       // : Constraint
constexpr uintptr_t CFrame = 0x170;                // CoordinateFrame
constexpr uintptr_t PrimaryAxis = 0x188;           // Vector3
constexpr uintptr_t SecondaryAxis = 0x18C;         // Vector3
constexpr uintptr_t LookAtPosition = 0x19C;        // Vector3
constexpr uintptr_t MaxAngularVelocity = 0x1A4;    // float
constexpr uintptr_t MaxTorque = 0x1A8;             // float
constexpr uintptr_t Responsiveness = 0x1B0;        // float
constexpr uintptr_t PrimaryAxisOnly = 0x1B4;       // bool
constexpr uintptr_t ReactionTorqueEnabled = 0x1B5; // bool
constexpr uintptr_t RigidityEnabled = 0x1B6;       // bool
// AlignType                                  = ?;   // E1
// Mode                                       = ?;   // E1
} // namespace AlignOrientation

namespace AlignPosition {                         // : Constraint
constexpr uintptr_t MaxAxesForce = 0x170;         // Vector3
constexpr uintptr_t Position = 0x17C;             // Vector3
constexpr uintptr_t MaxForce = 0x190;             // float
constexpr uintptr_t MaxVelocity = 0x194;          // float
constexpr uintptr_t Responsiveness = 0x19C;       // float
constexpr uintptr_t ReactionForceEnabled = 0x1A1; // bool
constexpr uintptr_t RigidityEnabled = 0x1A2;      // bool
// ApplyAtCenterOfMass                        = ?;   // E3
// ForceLimitMode                             = ?;   // E1
// ForceRelativeTo                            = ?;   // E1
// Mode                                       = ?;   // E1
} // namespace AlignPosition

namespace AnalyticsService {                // : Instance
constexpr uintptr_t ApiKey[] = {0xC8, 0x0}; // string, deref 1, then add
} // namespace AnalyticsService

namespace AngularVelocity {                        // : Constraint
constexpr uintptr_t AngularVelocity = 0x170;       // Vector3
constexpr uintptr_t MaxTorque = 0x17C;             // float
constexpr uintptr_t ReactionTorqueEnabled = 0x184; // bool
// RelativeTo                                 = ?;   // E1
} // namespace AngularVelocity

namespace Animation {                   // : Instance
constexpr uintptr_t AnimationId = 0xB8; // ContentId
// AnimationContent                           = ?;   // E1
} // namespace Animation

namespace AnimationConstraint {              // : Constraint
constexpr uintptr_t C0 = 0x110;              // CoordinateFrame
constexpr uintptr_t C1 = 0x130;              // CoordinateFrame
constexpr uintptr_t AngularDamping = 0x170;  // float
constexpr uintptr_t AngularStrength = 0x174; // float
constexpr uintptr_t LinearDamping = 0x178;   // float
constexpr uintptr_t LinearStrength = 0x17C;  // float
constexpr uintptr_t MaxForce = 0x180;        // float
constexpr uintptr_t EnableSkinning = 0x188;  // bool
constexpr uintptr_t Transform[] = {
    0xE8, 0x10,
    0x20}; // CoordinateFrame, obscured, deref all but the last, then add
           // IsKinematic                                = ?;   // E3
           // MaxTorque                                  = ?;   // E3
           // Part0                                      = ?;   // E4
           // Part1                                      = ?;   // E4
} // namespace AnimationConstraint

namespace AnimationRigData { // : Instance
// Generic                                    = ?;   // E3
// label                                      = ?;   // E3
// name                                       = ?;   // E3
// parent                                     = ?;   // E3
// postTransform                              = ?;   // E3
// preTransform                               = ?;   // E3
// transform                                  = ?;   // E3
} // namespace AnimationRigData

namespace Animator {                              // : Instance
constexpr uintptr_t FacsReplicationData = 0xE0;   // ���4�
constexpr uintptr_t AnimTrackPlayState0 = 0xF0;   // @��4�
constexpr uintptr_t AnimTrackPlayState1 = 0x100;  // @��4�
constexpr uintptr_t AnimTrackPlayState10 = 0x110; // @��4�
constexpr uintptr_t AnimTrackPlayState11 = 0x120; // @��4�
constexpr uintptr_t AnimTrackPlayState12 = 0x130; // @��4�
constexpr uintptr_t AnimTrackPlayState13 = 0x140; // @��4�
constexpr uintptr_t AnimTrackPlayState14 = 0x150; // @��4�
constexpr uintptr_t AnimTrackPlayState15 = 0x160; // @��4�
constexpr uintptr_t AnimTrackPlayState2 = 0x170;  // @��4�
constexpr uintptr_t AnimTrackPlayState3 = 0x180;  // @��4�
constexpr uintptr_t AnimTrackPlayState4 = 0x190;  // @��4�
constexpr uintptr_t AnimTrackPlayState5 = 0x1A0;  // @��4�
constexpr uintptr_t AnimTrackPlayState6 = 0x1B0;  // @��4�
constexpr uintptr_t AnimTrackPlayState7 = 0x1C0;  // @��4�
constexpr uintptr_t AnimTrackPlayState8 = 0x1D0;  // @��4�
constexpr uintptr_t AnimTrackPlayState9 = 0x1E0;  // @��4�
constexpr uintptr_t AnimTrackWeight0 = 0x1F0;     // AnimTrackWeight
constexpr uintptr_t AnimTrackWeight1 = 0x200;     // AnimTrackWeight
constexpr uintptr_t AnimTrackWeight10 = 0x210;    // AnimTrackWeight
constexpr uintptr_t AnimTrackWeight11 = 0x220;    // AnimTrackWeight
constexpr uintptr_t AnimTrackWeight12 = 0x230;    // AnimTrackWeight
constexpr uintptr_t AnimTrackWeight13 = 0x240;    // AnimTrackWeight
constexpr uintptr_t AnimTrackWeight14 = 0x250;    // AnimTrackWeight
constexpr uintptr_t AnimTrackWeight15 = 0x260;    // AnimTrackWeight
constexpr uintptr_t AnimTrackWeight2 = 0x270;     // AnimTrackWeight
constexpr uintptr_t AnimTrackWeight3 = 0x280;     // AnimTrackWeight
constexpr uintptr_t AnimTrackWeight4 = 0x290;     // AnimTrackWeight
constexpr uintptr_t AnimTrackWeight5 = 0x2A0;     // AnimTrackWeight
constexpr uintptr_t AnimTrackWeight6 = 0x2B0;     // AnimTrackWeight
constexpr uintptr_t AnimTrackWeight7 = 0x2C0;     // AnimTrackWeight
constexpr uintptr_t AnimTrackWeight8 = 0x2D0;     // AnimTrackWeight
constexpr uintptr_t AnimTrackWeight9 = 0x2E0;     // AnimTrackWeight
constexpr uintptr_t AnimationId0 = 0x2F0;         // int64
constexpr uintptr_t AnimationId1 = 0x2F8;         // int64
constexpr uintptr_t AnimationId10 = 0x300;        // int64
constexpr uintptr_t AnimationId11 = 0x308;        // int64
constexpr uintptr_t AnimationId12 = 0x310;        // int64
constexpr uintptr_t AnimationId13 = 0x318;        // int64
constexpr uintptr_t AnimationId14 = 0x320;        // int64
constexpr uintptr_t AnimationId15 = 0x328;        // int64
constexpr uintptr_t AnimationId2 = 0x330;         // int64
constexpr uintptr_t AnimationId3 = 0x338;         // int64
constexpr uintptr_t AnimationId4 = 0x340;         // int64
constexpr uintptr_t AnimationId5 = 0x348;         // int64
constexpr uintptr_t AnimationId6 = 0x350;         // int64
constexpr uintptr_t AnimationId7 = 0x358;         // int64
constexpr uintptr_t AnimationId8 = 0x360;         // int64
constexpr uintptr_t AnimationId9 = 0x368;         // int64
constexpr uintptr_t RootMotion = 0x370;           // CoordinateFrame
constexpr uintptr_t RootMotionWeight = 0x3A0;     // float
constexpr uintptr_t AnimTrackMetadata0 = 0x3A4;   // ?
constexpr uintptr_t AnimTrackMetadata1 = 0x3A8;   // ?
constexpr uintptr_t AnimTrackMetadata10 = 0x3AC;  // ?
constexpr uintptr_t AnimTrackMetadata11 = 0x3B0;  // ?
constexpr uintptr_t AnimTrackMetadata12 = 0x3B4;  // ?
constexpr uintptr_t AnimTrackMetadata13 = 0x3B8;  // ?
constexpr uintptr_t AnimTrackMetadata14 = 0x3BC;  // ?
constexpr uintptr_t AnimTrackMetadata15 = 0x3C0;  // ?
constexpr uintptr_t AnimTrackMetadata2 = 0x3C4;   // ?
constexpr uintptr_t AnimTrackMetadata3 = 0x3C8;   // ?
constexpr uintptr_t AnimTrackMetadata4 = 0x3CC;   // ?
constexpr uintptr_t AnimTrackMetadata5 = 0x3D0;   // ?
constexpr uintptr_t AnimTrackMetadata6 = 0x3D4;   // ?
constexpr uintptr_t AnimTrackMetadata7 = 0x3D8;   // ?
constexpr uintptr_t AnimTrackMetadata8 = 0x3DC;   // ?
constexpr uintptr_t AnimTrackMetadata9 = 0x3E0;   // ?
constexpr uintptr_t PreferLodEnabled = 0x3E4;     // bool
// EvaluationThrottled                        = ?;   // E2
} // namespace Animator

namespace ArcHandles {                                       // : HandlesBase
constexpr uintptr_t Axes = 0x120;                            // Axes
constexpr uintptr_t MouseButton1DownConnectionCount = 0x124; // int
constexpr uintptr_t MouseButton1UpConnectionCount = 0x128;   // int
constexpr uintptr_t MouseDragConnectionCount = 0x12C;        // int
constexpr uintptr_t MouseEnterConnectionCount = 0x130;       // int
constexpr uintptr_t MouseLeaveConnectionCount = 0x134;       // int
} // namespace ArcHandles

namespace AssetService {                          // : Instance
constexpr uintptr_t AllowInsertFreeAssets = 0xC0; // bool
} // namespace AssetService

namespace Atmosphere {              // : Instance
constexpr uintptr_t Density = 0xD0; // float
constexpr uintptr_t Glare = 0xD4;   // float
constexpr uintptr_t Haze = 0xD8;    // float
constexpr uintptr_t Offset = 0xDC;  // float
// Color                                      = ?;   // E1
// Decay                                      = ?;   // E1
} // namespace Atmosphere

namespace AtmosphereSensor { // : SensorBase
// AirDensity                                 = ?;   // E3
// RelativeWindVelocity                       = ?;   // E3
} // namespace AtmosphereSensor

namespace Attachment {                          // : Instance
constexpr uintptr_t Axis = 0xB8;                // Vector3
constexpr uintptr_t Position = 0xC4;            // Vector3
constexpr uintptr_t SecondaryAxis = 0xD0;       // Vector3
constexpr uintptr_t Visible = 0xDC;             // bool
constexpr uintptr_t WorldAxis[] = {0x68, 0x18}; // Vector3, deref 1, then add
constexpr uintptr_t WorldCFrame[] = {
    0x68, 0x18}; // CoordinateFrame, deref 1, then add
constexpr uintptr_t WorldOrientation[] = {0x68,
                                          0x18}; // Vector3, deref 1, then add
constexpr uintptr_t WorldPosition[] = {0x68,
                                       0x18}; // Vector3, deref 1, then add
constexpr uintptr_t WorldRotation[] = {0x68,
                                       0x18}; // Vector3, deref 1, then add
constexpr uintptr_t WorldSecondaryAxis[] = {0x68,
                                            0x18}; // Vector3, deref 1, then add
// CFrame                                     = ?;   // E0
// Orientation                                = ?;   // E6
// Rotation                                   = ?;   // E6
} // namespace Attachment

namespace AudioAnalyzer {                    // : Instance
constexpr uintptr_t SpectrumEnabled = 0x12C; // bool
// PeakLevel                                  = ?;   // E0
// RmsLevel                                   = ?;   // E9
// WindowSize                                 = ?;   // E1
} // namespace AudioAnalyzer

namespace AudioChannelMixer { // : Instance
// Layout                                     = ?;   // E1
} // namespace AudioChannelMixer

namespace AudioChannelSplitter { // : Instance
// Layout                                     = ?;   // E1
} // namespace AudioChannelSplitter

namespace AudioChorus {             // : Instance
constexpr uintptr_t Depth = 0x128;  // float
constexpr uintptr_t Mix = 0x12C;    // float
constexpr uintptr_t Rate = 0x130;   // float
constexpr uintptr_t Bypass = 0x134; // bool
} // namespace AudioChorus

namespace AudioCompressor {             // : Instance
constexpr uintptr_t Attack = 0x128;     // float
constexpr uintptr_t MakeupGain = 0x12C; // float
constexpr uintptr_t Ratio = 0x130;      // float
constexpr uintptr_t Release = 0x134;    // float
constexpr uintptr_t Threshold = 0x138;  // float
constexpr uintptr_t Bypass = 0x13C;     // bool
// Editor                                     = ?;   // E1
} // namespace AudioCompressor

namespace AudioDeviceInput {                  // : Instance
constexpr uintptr_t Volume = 0x164;           // float
constexpr uintptr_t Active = 0x168;           // bool
constexpr uintptr_t EchoCancellation = 0x169; // bool
constexpr uintptr_t GainControl = 0x16A;      // bool
constexpr uintptr_t Muted = 0x16B;            // bool
constexpr uintptr_t MutedByLocalUser = 0x16C; // bool
constexpr uintptr_t NoiseSuppression = 0x16D; // bool
constexpr uintptr_t AccessList[] = {
    0x120, 0x10}; // BinaryString, obscured, deref 1, then add
                  // AccessType                                 = ?;   // E1
                  // IsReady                                    = ?;   // E9
                  // Player                                     = ?;   // E4
} // namespace AudioDeviceInput

namespace AudioDeviceOutput { // : Instance
// Player                                     = ?;   // E4
} // namespace AudioDeviceOutput

namespace AudioDistortion {         // : Instance
constexpr uintptr_t Level = 0x128;  // float
constexpr uintptr_t Bypass = 0x12C; // bool
} // namespace AudioDistortion

namespace AudioEcho {                  // : Instance
constexpr uintptr_t DelayTime = 0x128; // float
constexpr uintptr_t DryLevel = 0x12C;  // float
constexpr uintptr_t Feedback = 0x130;  // float
constexpr uintptr_t RampTime = 0x134;  // float
constexpr uintptr_t WetLevel = 0x138;  // float
constexpr uintptr_t Bypass = 0x13C;    // bool
} // namespace AudioEcho

namespace AudioEmitter {                               // : Instance
constexpr uintptr_t AcousticSimulationEnabled = 0x170; // bool
// AngleAttenuation                           = ?;   // E3
// AudioInteractionGroup                      = ?;   // E3
// DiffractionEnabled                         = ?;   // E1
// DistanceAttenuation                        = ?;   // E3
// DistanceAttenuationBounds                  = ?;   // E3
// DistanceAttenuationMode                    = ?;   // E1
// OcclusionEnabled                           = ?;   // E1
// PositionInstance                           = ?;   // E4
// PositionType                               = ?;   // E1
// ReverbEnabled                              = ?;   // E1
// SimulationFidelity                         = ?;   // E1
} // namespace AudioEmitter

namespace AudioEqualizer {            // : Instance
constexpr uintptr_t MidRange = 0x128; // NumberRange
constexpr uintptr_t HighGain = 0x130; // float
constexpr uintptr_t LowGain = 0x134;  // float
constexpr uintptr_t MidGain = 0x138;  // float
constexpr uintptr_t Bypass = 0x13C;   // bool
// Editor                                     = ?;   // E1
} // namespace AudioEqualizer

namespace AudioFader {              // : Instance
constexpr uintptr_t Volume = 0x128; // float
constexpr uintptr_t Bypass = 0x12C; // bool
} // namespace AudioFader

namespace AudioFilter {                // : Instance
constexpr uintptr_t Frequency = 0x12C; // float
constexpr uintptr_t Gain = 0x130;      // float
constexpr uintptr_t Q = 0x134;         // float
constexpr uintptr_t Bypass = 0x138;    // bool
// Editor                                     = ?;   // E1
// FilterType                                 = ?;   // E1
} // namespace AudioFilter

namespace AudioFlanger {            // : Instance
constexpr uintptr_t Depth = 0x128;  // float
constexpr uintptr_t Mix = 0x12C;    // float
constexpr uintptr_t Rate = 0x130;   // float
constexpr uintptr_t Bypass = 0x134; // bool
} // namespace AudioFlanger

namespace AudioGate {                  // : Instance
constexpr uintptr_t Threshold = 0x128; // NumberRange
constexpr uintptr_t Attack = 0x130;    // float
constexpr uintptr_t Release = 0x134;   // float
constexpr uintptr_t Bypass = 0x138;    // bool
} // namespace AudioGate

namespace AudioLimiter {              // : Instance
constexpr uintptr_t MaxLevel = 0x128; // float
constexpr uintptr_t Release = 0x12C;  // float
constexpr uintptr_t Bypass = 0x130;   // bool
// Editor                                     = ?;   // E1
} // namespace AudioLimiter

namespace AudioListener {                              // : Instance
constexpr uintptr_t AcousticSimulationEnabled = 0x164; // bool
// AngleAttenuation                           = ?;   // E3
// AudioInteractionGroup                      = ?;   // E3
// DiffractionEnabled                         = ?;   // E1
// DistanceAttenuation                        = ?;   // E3
// OcclusionEnabled                           = ?;   // E1
// PositionInstance                           = ?;   // E4
// PositionType                               = ?;   // E1
// ReverbEnabled                              = ?;   // E1
// SimulationFidelity                         = ?;   // E1
} // namespace AudioListener

namespace AudioPitchShifter {       // : Instance
constexpr uintptr_t Pitch = 0x128;  // float
constexpr uintptr_t Bypass = 0x130; // bool
// WindowSize                                 = ?;   // E1
} // namespace AudioPitchShifter

namespace AudioPlayer {                     // : Instance
constexpr uintptr_t Asset = 0x130;          // ContentId
constexpr uintptr_t LoopRegion = 0x148;     // NumberRange
constexpr uintptr_t PlaybackRegion = 0x150; // NumberRange
constexpr uintptr_t Volume = 0x15C;         // float
constexpr uintptr_t AutoPlay = 0x161;       // bool
constexpr uintptr_t IsPlaying = 0x162;      // bool
// AssetId                                    = ?;   // E3
// AssetRepresentation                        = ?;   // E1
// AudioContent                               = ?;   // E3
// AutoLoad                                   = ?;   // E3
// IsReady                                    = ?;   // E3
// Looping                                    = ?;   // E3
// PlaybackSpeed                              = ?;   // E3
// TimeLength                                 = ?;   // E3
// TimePosition                               = ?;   // E3
} // namespace AudioPlayer

namespace AudioRecorder {                // : Instance
constexpr uintptr_t IsRecording = 0x128; // bool
// TimeLength                                 = ?;   // E3
} // namespace AudioRecorder

namespace AudioReverb {                         // : Instance
constexpr uintptr_t DecayRatio = 0x128;         // float
constexpr uintptr_t DecayTime = 0x12C;          // float
constexpr uintptr_t Density = 0x130;            // float
constexpr uintptr_t Diffusion = 0x134;          // float
constexpr uintptr_t DryLevel = 0x138;           // float
constexpr uintptr_t HighCutFrequency = 0x140;   // float
constexpr uintptr_t LateDelayTime = 0x144;      // float
constexpr uintptr_t LowShelfFrequency = 0x148;  // float
constexpr uintptr_t LowShelfGain = 0x14C;       // float
constexpr uintptr_t ReferenceFrequency = 0x150; // float
constexpr uintptr_t WetLevel = 0x154;           // float
// Bypass                                     = ?;   // E3
// EarlyDelayTime                             = ?;   // E3
} // namespace AudioReverb

namespace AudioSearchParams {                      // : Instance
constexpr uintptr_t MaxDuration = 0x15C;           // int
constexpr uintptr_t MinDuration = 0x160;           // int
constexpr uintptr_t Album[] = {0xB8, 0x0};         // string, deref 1, then add
constexpr uintptr_t Artist[] = {0xD8, 0x0};        // string, deref 1, then add
constexpr uintptr_t SearchKeyword[] = {0xF8, 0x0}; // string, deref 1, then add
constexpr uintptr_t Title[] = {0x138, 0x0};        // string, deref 1, then add
// AudioSubType                               = ?;   // E1
// AudioSubtype                               = ?;   // E1
// Tag                                        = ?;   // E3
} // namespace AudioSearchParams

namespace AudioSpeechToText {                 // : Instance
constexpr uintptr_t DictationEnabled = 0x148; // bool
constexpr uintptr_t Enabled = 0x149;          // bool
constexpr uintptr_t Text[] = {0x128, 0x0};    // string, deref 1, then add
// VoiceDetected                              = ?;   // E3
} // namespace AudioSpeechToText

namespace AudioTextToSpeech {                 // : Instance
constexpr uintptr_t Pitch = 0x170;            // float
constexpr uintptr_t PlaybackSpeed = 0x174;    // float
constexpr uintptr_t Speed = 0x178;            // float
constexpr uintptr_t Volume = 0x17C;           // float
constexpr uintptr_t IsPlaying = 0x180;        // bool
constexpr uintptr_t Looping = 0x181;          // bool
constexpr uintptr_t Text[] = {0x128, 0x0};    // string, deref 1, then add
constexpr uintptr_t VoiceId[] = {0x148, 0x0}; // string, deref 1, then add
// IsLoaded                                   = ?;   // E3
// TimeLength                                 = ?;   // E3
// TimePosition                               = ?;   // E3
} // namespace AudioTextToSpeech

namespace AvatarAbilityRules {
constexpr uintptr_t EnableClimbing = 0xB4;    // bool
constexpr uintptr_t EnableFallingDown = 0xB6; // bool
constexpr uintptr_t EnableGettingUp = 0xB7;   // bool
constexpr uintptr_t EnableHolding = 0xB8;     // bool
constexpr uintptr_t EnableJumping = 0xB9;     // bool
constexpr uintptr_t EnableSitting = 0xBC;     // bool
// CharacterControllerMode                    = ?;   // E1
// EnableCrouching                            = ?;   // E3
// EnableReaching                             = ?;   // E3
// EnableRunning                              = ?;   // E3
// EnableSprinting                            = ?;   // E3
// EnableStrafing                             = ?;   // E3
// EnableSwimming                             = ?;   // E3
} // namespace AvatarAbilityRules

namespace AvatarAccessoryRules {                            // : Instance
constexpr uintptr_t CustomBackAccessoryId = 0xB0;           // int64
constexpr uintptr_t CustomFaceAccessoryId = 0xB8;           // int64
constexpr uintptr_t CustomFrontAccessoryId = 0xC0;          // int64
constexpr uintptr_t CustomHairAccessoryId = 0xC8;           // int64
constexpr uintptr_t CustomHeadAccessoryId = 0xD0;           // int64
constexpr uintptr_t CustomNeckAccessoryId = 0xD8;           // int64
constexpr uintptr_t CustomShoulderAccessoryId = 0xE0;       // int64
constexpr uintptr_t CustomWaistAccessoryId = 0xE8;          // int64
constexpr uintptr_t LimitBounds = 0xF0;                     // Vector3
constexpr uintptr_t CustomBackAccessoryEnabled = 0x108;     // bool
constexpr uintptr_t CustomFaceAccessoryEnabled = 0x109;     // bool
constexpr uintptr_t CustomFrontAccessoryEnabled = 0x10A;    // bool
constexpr uintptr_t CustomHeadAccessoryEnabled = 0x10C;     // bool
constexpr uintptr_t CustomNeckAccessoryEnabled = 0x10D;     // bool
constexpr uintptr_t CustomShoulderAccessoryEnabled = 0x10E; // bool
constexpr uintptr_t CustomWaistAccessoryEnabled = 0x10F;    // bool
constexpr uintptr_t EnableEmissives = 0x110;                // bool
constexpr uintptr_t EnableSound = 0x111;                    // bool
constexpr uintptr_t EnableVFX = 0x112;                      // bool
// AccessoryMode                              = ?;   // E1
// CustomAccessoryMode                        = ?;   // E1
// CustomHairAccessoryEnabled                 = ?;   // E3
// LimitMethod                                = ?;   // E1
} // namespace AvatarAccessoryRules

namespace AvatarAnimationRules {                            // : Instance
constexpr uintptr_t CustomClimbAnimationId = 0xB0;          // int64
constexpr uintptr_t CustomFallAnimationId = 0xB8;           // int64
constexpr uintptr_t CustomIdleAlt1AnimationId = 0xC0;       // int64
constexpr uintptr_t CustomIdleAlt2AnimationId = 0xC8;       // int64
constexpr uintptr_t CustomIdleAnimationId = 0xD0;           // int64
constexpr uintptr_t CustomJumpAnimationId = 0xD8;           // int64
constexpr uintptr_t CustomRunAnimationId = 0xE0;            // int64
constexpr uintptr_t CustomSwimAnimationId = 0xE8;           // int64
constexpr uintptr_t CustomSwimIdleAnimationId = 0xF0;       // int64
constexpr uintptr_t CustomWalkAnimationId = 0xF8;           // int64
constexpr uintptr_t CustomClimbAnimationEnabled = 0x108;    // bool
constexpr uintptr_t CustomFallAnimationEnabled = 0x109;     // bool
constexpr uintptr_t CustomIdleAlt1AnimationEnabled = 0x10A; // bool
constexpr uintptr_t CustomIdleAnimationEnabled = 0x10C;     // bool
constexpr uintptr_t CustomJumpAnimationEnabled = 0x10D;     // bool
constexpr uintptr_t CustomRunAnimationEnabled = 0x10E;      // bool
constexpr uintptr_t CustomSwimAnimationEnabled = 0x10F;     // bool
constexpr uintptr_t CustomSwimIdleAnimationEnabled = 0x110; // bool
constexpr uintptr_t CustomWalkAnimationEnabled = 0x111;     // bool
// AnimationClipsMode                         = ?;   // E1
// AnimationPacksMode                         = ?;   // E1
// CustomIdleAlt2AnimationEnabled             = ?;   // E3
} // namespace AvatarAnimationRules

namespace AvatarBodyRules {                        // : Instance
constexpr uintptr_t CustomBodyBundleId = 0xB0;     // int64
constexpr uintptr_t CustomEyebrowId = 0xB8;        // int64
constexpr uintptr_t CustomEyelashId = 0xC0;        // int64
constexpr uintptr_t CustomFaceId = 0xC8;           // int64
constexpr uintptr_t CustomHeadId = 0xD0;           // int64
constexpr uintptr_t CustomLeftArmId = 0xD8;        // int64
constexpr uintptr_t CustomLeftLegId = 0xE0;        // int64
constexpr uintptr_t CustomMoodId = 0xE8;           // int64
constexpr uintptr_t CustomRightArmId = 0xF0;       // int64
constexpr uintptr_t CustomRightLegId = 0xF8;       // int64
constexpr uintptr_t CustomTorsoId = 0x100;         // int64
constexpr uintptr_t CustomBodyTypeScale = 0x108;   // NumberRange
constexpr uintptr_t CustomHeadScale = 0x110;       // NumberRange
constexpr uintptr_t CustomHeight = 0x118;          // NumberRange
constexpr uintptr_t CustomHeightScale = 0x120;     // NumberRange
constexpr uintptr_t CustomEyebrowEnabled = 0x148;  // bool
constexpr uintptr_t CustomEyelashEnabled = 0x149;  // bool
constexpr uintptr_t CustomFaceEnabled = 0x14A;     // bool
constexpr uintptr_t CustomHeadEnabled = 0x14B;     // bool
constexpr uintptr_t CustomLeftArmEnabled = 0x14C;  // bool
constexpr uintptr_t CustomLeftLegEnabled = 0x14D;  // bool
constexpr uintptr_t CustomMoodEnabled = 0x14E;     // bool
constexpr uintptr_t CustomRightArmEnabled = 0x14F; // bool
constexpr uintptr_t CustomRightLegEnabled = 0x150; // bool
constexpr uintptr_t CustomTorsoEnabled = 0x151;    // bool
// AppearanceMode                             = ?;   // E1
// BuildMode                                  = ?;   // E1
// CustomBodyType                             = ?;   // E1
// CustomProportionsScale                     = ?;   // E3
// CustomWidthScale                           = ?;   // E3
// KeepPlayerHead                             = ?;   // E3
// ScaleMode                                  = ?;   // E1
} // namespace AvatarBodyRules

namespace AvatarChatService { // : Instance
// ClientFeatures                             = ?;   // E3
// ClientFeaturesInitialized                  = ?;   // E3
// ServerFeatures                             = ?;   // E3
} // namespace AvatarChatService

namespace AvatarClothingRules {                                   // : Instance
constexpr uintptr_t CustomClassicPantsAccessoryId = 0xB0;         // int64
constexpr uintptr_t CustomClassicShirtsAccessoryId = 0xB8;        // int64
constexpr uintptr_t CustomClassicTShirtsAccessoryId = 0xC0;       // int64
constexpr uintptr_t CustomDressSkirtAccessoryId = 0xC8;           // int64
constexpr uintptr_t CustomJacketAccessoryId = 0xD0;               // int64
constexpr uintptr_t CustomLeftShoesAccessoryId = 0xD8;            // int64
constexpr uintptr_t CustomPantsAccessoryId = 0xE0;                // int64
constexpr uintptr_t CustomRightShoesAccessoryId = 0xE8;           // int64
constexpr uintptr_t CustomShirtAccessoryId = 0xF0;                // int64
constexpr uintptr_t CustomShortsAccessoryId = 0xF8;               // int64
constexpr uintptr_t CustomSweaterAccessoryId = 0x100;             // int64
constexpr uintptr_t CustomTShirtAccessoryId = 0x108;              // int64
constexpr uintptr_t CustomClassicPantsAccessoryEnabled = 0x124;   // bool
constexpr uintptr_t CustomClassicShirtsAccessoryEnabled = 0x125;  // bool
constexpr uintptr_t CustomClassicTShirtsAccessoryEnabled = 0x126; // bool
constexpr uintptr_t CustomDressSkirtAccessoryEnabled = 0x127;     // bool
constexpr uintptr_t CustomJacketAccessoryEnabled = 0x128;         // bool
constexpr uintptr_t CustomLeftShoesAccessoryEnabled = 0x129;      // bool
constexpr uintptr_t CustomPantsAccessoryEnabled = 0x12A;          // bool
constexpr uintptr_t CustomRightShoesAccessoryEnabled = 0x12B;     // bool
constexpr uintptr_t CustomShirtAccessoryEnabled = 0x12C;          // bool
constexpr uintptr_t CustomSweaterAccessoryEnabled = 0x12E;        // bool
constexpr uintptr_t CustomTShirtAccessoryEnabled = 0x12F;         // bool
// ClothingMode                               = ?;   // E1
// CustomClothingMode                         = ?;   // E1
// CustomShortsAccessoryEnabled               = ?;   // E3
// LimitBounds                                = ?;   // E3
} // namespace AvatarClothingRules

namespace AvatarCollisionRules {               // : Instance
constexpr uintptr_t SingleColliderSize = 0xB0; // Vector3
// CollisionMode                              = ?;   // E1
// HitAndTouchDetectionMode                   = ?;   // E1
// LegacyCollisionMode                        = ?;   // E1
} // namespace AvatarCollisionRules

namespace AvatarRules { // : Instance
// AvatarType                                 = ?;   // E1
} // namespace AvatarRules

namespace AvatarSettings {         // : Instance
constexpr uintptr_t Loaded = 0xE0; // bool
} // namespace AvatarSettings

namespace BallSocketConstraint {                  // : Constraint
constexpr uintptr_t MaxFrictionTorque = 0x170;    // float
constexpr uintptr_t MaxFrictionTorqueXml = 0x170; // float
constexpr uintptr_t Radius = 0x174;               // float
constexpr uintptr_t Restitution = 0x178;          // float
constexpr uintptr_t TwistLowerAngle = 0x17C;      // float
constexpr uintptr_t TwistUpperAngle = 0x180;      // float
constexpr uintptr_t EnableSkinning = 0x188;       // bool
// LimitsEnabled                              = ?;   // E3
// TwistLimitsEnabled                         = ?;   // E3
// UpperAngle                                 = ?;   // E3
} // namespace BallSocketConstraint

namespace Beam {                                       // : Instance
constexpr uintptr_t Brightness = 0x180;                // float
constexpr uintptr_t CurveSize0 = 0x184;                // float
constexpr uintptr_t CurveSize1 = 0x188;                // float
constexpr uintptr_t LightEmission = 0x18C;             // float
constexpr uintptr_t LightInfluence = 0x190;            // float
constexpr uintptr_t LocalTransparencyModifier = 0x194; // float
constexpr uintptr_t Segments = 0x198;                  // int
constexpr uintptr_t TextureLength = 0x19C;             // float
constexpr uintptr_t TextureSpeed = 0x1A4;              // float
constexpr uintptr_t Width0 = 0x1A8;                    // float
constexpr uintptr_t Width1 = 0x1AC;                    // float
constexpr uintptr_t ZOffset = 0x1B0;                   // float
constexpr uintptr_t Enabled = 0x1B4;                   // bool
constexpr uintptr_t FaceCamera = 0x1B5;                // bool
// Attachment0                                = ?;   // E4
// Attachment1                                = ?;   // E4
// Color                                      = ?;   // E3
// Texture                                    = ?;   // E3
// TextureContent                             = ?;   // E3
// TextureMode                                = ?;   // E1
// Transparency                               = ?;   // E3
} // namespace Beam

namespace BillboardGui {                        // : LayerCollector
constexpr uintptr_t Size = 0x760;               // UDim2
constexpr uintptr_t Brightness = 0x7A8;         // float
constexpr uintptr_t CurrentDistance = 0x7AC;    // float
constexpr uintptr_t DistanceLowerLimit = 0x7B0; // float
constexpr uintptr_t DistanceStep = 0x7B4;       // float
constexpr uintptr_t DistanceUpperLimit = 0x7B8; // float
constexpr uintptr_t LightInfluence = 0x7BC;     // float
constexpr uintptr_t MaxDistance = 0x7C0;        // float
constexpr uintptr_t Active = 0x7C4;             // bool
constexpr uintptr_t AlwaysOnTop = 0x7C5;        // bool
// Adornee                                    = ?;   // E4
// ClipsDescendants                           = ?;   // E3
// ExtentsOffset                              = ?;   // E1
// ExtentsOffsetWorldSpace                    = ?;   // E1
// PlayerToHideFrom                           = ?;   // E4
// SizeOffset                                 = ?;   // E1
// StudsOffset                                = ?;   // E1
// StudsOffsetWorldSpace                      = ?;   // E1
} // namespace BillboardGui

namespace BinaryStringValue { // : ValueBase
// Value                                      = ?;   // E3
} // namespace BinaryStringValue

namespace BloomEffect {               // : PostEffect
constexpr uintptr_t Intensity = 0xB8; // float
constexpr uintptr_t Size = 0xBC;      // float
constexpr uintptr_t Threshold = 0xC0; // float
} // namespace BloomEffect

namespace BlurEffect {           // : PostEffect
constexpr uintptr_t Size = 0xB8; // float
} // namespace BlurEffect

namespace BodyAngularVelocity { // : BodyMover
// AngularVelocity                            = ?;   // E3
// MaxTorque                                  = ?;   // E3
// P                                          = ?;   // E3
// angularvelocity                            = ?;   // E3
// maxTorque                                  = ?;   // E3
} // namespace BodyAngularVelocity

namespace BodyColors {                      // : CharacterAppearance
constexpr uintptr_t HeadColor = 0xC0;       // BrickColor
constexpr uintptr_t HeadColor3 = 0xC4;      // Color3
constexpr uintptr_t LeftArmColor = 0xD0;    // BrickColor
constexpr uintptr_t LeftArmColor3 = 0xD4;   // Color3
constexpr uintptr_t LeftLegColor = 0xE0;    // BrickColor
constexpr uintptr_t LeftLegColor3 = 0xE4;   // Color3
constexpr uintptr_t RightArmColor = 0xF0;   // BrickColor
constexpr uintptr_t RightArmColor3 = 0xF4;  // Color3
constexpr uintptr_t RightLegColor = 0x100;  // BrickColor
constexpr uintptr_t RightLegColor3 = 0x104; // Color3
constexpr uintptr_t TorsoColor = 0x110;     // BrickColor
constexpr uintptr_t TorsoColor3 = 0x114;    // Color3
} // namespace BodyColors

namespace BodyForce { // : BodyMover
                      // Force                                      = ?;   // E3
                      // force                                      = ?;   // E3
} // namespace BodyForce

namespace BodyGyro { // : BodyMover
                     // CFrame                                     = ?;   // E3
                     // D                                          = ?;   // E3
                     // MaxTorque                                  = ?;   // E3
                     // P                                          = ?;   // E3
                     // cframe                                     = ?;   // E3
                     // maxTorque                                  = ?;   // E3
} // namespace BodyGyro

namespace BodyPartDescription {                // : Instance
constexpr uintptr_t AssetId = 0xE0;            // int64
constexpr uintptr_t HeadShape[] = {0xB0, 0x0}; // string, deref 1, then add
// BodyPart                                   = ?;   // E1
// Color                                      = ?;   // E3
// Instance                                   = ?;   // E4
} // namespace BodyPartDescription

namespace BodyPosition { // : BodyMover
// D                                          = ?;   // E3
// MaxForce                                   = ?;   // E3
// P                                          = ?;   // E3
// Position                                   = ?;   // E3
// maxForce                                   = ?;   // E3
// position                                   = ?;   // E3
} // namespace BodyPosition

namespace BodyThrust { // : BodyMover
// Force                                      = ?;   // E3
// Location                                   = ?;   // E3
// force                                      = ?;   // E3
// location                                   = ?;   // E3
} // namespace BodyThrust

namespace BodyVelocity { // : BodyMover
// MaxForce                                   = ?;   // E3
// P                                          = ?;   // E3
// Velocity                                   = ?;   // E3
// maxForce                                   = ?;   // E3
// velocity                                   = ?;   // E3
} // namespace BodyVelocity

namespace BoolValue {             // : ValueBase
constexpr uintptr_t Value = 0xB8; // bool
} // namespace BoolValue

namespace BoxHandleAdornment {    // : HandleAdornment
constexpr uintptr_t Size = 0x1A8; // Vector3
// Shading                                    = ?;   // E1
} // namespace BoxHandleAdornment

namespace BrickColorValue {       // : ValueBase
constexpr uintptr_t Value = 0xB8; // BrickColor
} // namespace BrickColorValue

namespace BubbleChatConfiguration {                // : TextChatConfigurations
constexpr uintptr_t TextSize = 0xE8;               // int64
constexpr uintptr_t BackgroundColor3 = 0xF0;       // Color3
constexpr uintptr_t LocalPlayerStudsOffset = 0xFC; // Vector3
constexpr uintptr_t TextColor3 = 0x108;            // Color3
constexpr uintptr_t BubbleDuration = 0x114;        // float
constexpr uintptr_t BubblesSpacing = 0x118;        // float
constexpr uintptr_t MaxBubbles = 0x11C;            // float
constexpr uintptr_t MaxDistance = 0x120;           // float
constexpr uintptr_t MinimizeDistance = 0x124;      // float
constexpr uintptr_t VerticalStudsOffset = 0x128;   // float
constexpr uintptr_t Enabled = 0x12C;               // bool
constexpr uintptr_t AdorneeName[] = {0xB8, 0x0};   // string, deref 1, then add
// BackgroundTransparency                     = ?;   // E3
// Font                                       = ?;   // E1
// FontFace                                   = ?;   // E3
// TailVisible                                = ?;   // E3
} // namespace BubbleChatConfiguration

namespace BubbleChatMessageProperties { // : TextChatMessageProperties
constexpr uintptr_t BackgroundTransparency = 0x110; // double
constexpr uintptr_t TextSize = 0x120;               // int64
constexpr uintptr_t BackgroundColor3 = 0x128;       // Color3
constexpr uintptr_t TextColor3 = 0x134;             // Color3
constexpr uintptr_t TailVisible = 0x140;            // bool
// FontFace                                   = ?;   // E1
} // namespace BubbleChatMessageProperties

namespace BuoyancySensor { // : SensorBase
// FullySubmerged                             = ?;   // E5
// TouchingSurface                            = ?;   // E5
} // namespace BuoyancySensor

namespace CFrameValue {           // : ValueBase
constexpr uintptr_t Value = 0xB8; // CoordinateFrame
} // namespace CFrameValue

namespace Camera {                                // : PVInstance
constexpr uintptr_t FieldOfView = 0x140;          // float
constexpr uintptr_t HeadScale = 0x148;            // float
constexpr uintptr_t MaxAxisFieldOfView = 0x14C;   // float
constexpr uintptr_t NearPlaneZ = 0x150;           // float
constexpr uintptr_t HeadLocked = 0x154;           // bool
constexpr uintptr_t VRTiltAndRollEnabled = 0x155; // bool
constexpr uintptr_t ViewportSize = 0x29C;         // Vector2
// CFrame                                     = ?;   // E1
// CameraSubject                              = ?;   // E4
// CameraType                                 = ?;   // E1
// CoordinateFrame                            = ?;   // E1
// DiagonalFieldOfView                        = ?;   // E9
// FieldOfViewMode                            = ?;   // E1
// Focus                                      = ?;   // E1
// focus                                      = ?;   // E1
} // namespace Camera

namespace CanvasGroup {                      // : GuiObject
constexpr uintptr_t GroupColor3 = 0x1F0;     // Color3
constexpr uintptr_t ResolutionScale = 0x988; // float
// GroupTransparency                          = ?;   // E9
} // namespace CanvasGroup

namespace ChannelTabsConfiguration {               // : TextChatConfigurations
constexpr uintptr_t BackgroundTransparency = 0xB8; // double
constexpr uintptr_t TextSize = 0xC8;               // int64
constexpr uintptr_t BackgroundColor3 = 0xD8;       // Color3
constexpr uintptr_t HoverBackgroundColor3 = 0xE4;  // Color3
constexpr uintptr_t SelectedTabTextColor3 = 0xF0;  // Color3
constexpr uintptr_t TextColor3 = 0xFC;             // Color3
constexpr uintptr_t TextStrokeColor3 = 0x108;      // Color3
constexpr uintptr_t Enabled = 0x124;               // bool
// AbsolutePosition                           = ?;   // E3
// AbsoluteSize                               = ?;   // E3
// FontFace                                   = ?;   // E3
// TextStrokeTransparency                     = ?;   // E3
} // namespace ChannelTabsConfiguration

namespace CharacterMesh {                          // : CharacterAppearance
constexpr uintptr_t BaseTextureContent = 0xC8;     // Content
constexpr uintptr_t BaseTextureId = 0xC8;          // int64
constexpr uintptr_t MeshContent = 0xF8;            // Content
constexpr uintptr_t MeshId = 0xF8;                 // int64
constexpr uintptr_t OverlayTextureContent = 0x128; // Content
constexpr uintptr_t OverlayTextureId = 0x128;      // int64
// BodyPart                                   = ?;   // E1
} // namespace CharacterMesh

namespace Chat {                                    // : Instance
constexpr uintptr_t BubbleChatEnabled = 0x128;      // bool
constexpr uintptr_t IsAutoMigrated = 0x129;         // bool
constexpr uintptr_t LoadDefaultChat = 0x12A;        // bool
constexpr uintptr_t ModerationMode[] = {0xC0, 0x0}; // string, deref 1, then add
} // namespace Chat

namespace ChatInputBarConfiguration {            // : TextChatConfigurations
constexpr uintptr_t TextSize = 0xE8;             // int64
constexpr uintptr_t AutocompleteEnabled = 0x13C; // bool
constexpr uintptr_t Enabled = 0x13D;             // bool
// AbsolutePosition                           = ?;   // E3
// AbsolutePositionWrite                      = ?;   // E3
// AbsoluteSize                               = ?;   // E3
// AbsoluteSizeWrite                          = ?;   // E3
// BackgroundColor3                           = ?;   // E3
// BackgroundTransparency                     = ?;   // E3
// FontFace                                   = ?;   // E3
// IsFocused                                  = ?;   // E3
// IsFocusedWrite                             = ?;   // E3
// KeyboardKeyCode                            = ?;   // E1
// PlaceholderColor3                          = ?;   // E3
// TargetTextChannel                          = ?;   // E4
// TextBox                                    = ?;   // E4
// TextColor3                                 = ?;   // E3
// TextStrokeColor3                           = ?;   // E3
// TextStrokeTransparency                     = ?;   // E3
} // namespace ChatInputBarConfiguration

namespace ChatWindowConfiguration {                // : TextChatConfigurations
constexpr uintptr_t BackgroundTransparency = 0xB8; // double
constexpr uintptr_t TextSize = 0xC8;               // int64
constexpr uintptr_t BackgroundColor3 = 0xD8;       // Color3
constexpr uintptr_t TextColor3 = 0xE4;             // Color3
constexpr uintptr_t TextStrokeColor3 = 0xF0;       // Color3
constexpr uintptr_t AbsolutePosition = 0xFC;       // Vector2
constexpr uintptr_t AbsolutePositionWrite = 0xFC;  // Vector2
constexpr uintptr_t AbsoluteSize = 0x104;          // Vector2
constexpr uintptr_t AbsoluteSizeWrite = 0x104;     // Vector2
constexpr uintptr_t HeightScale = 0x10C;           // float
constexpr uintptr_t WidthScale = 0x118;            // float
constexpr uintptr_t Enabled = 0x11C;               // bool
// FontFace                                   = ?;   // E3
// HorizontalAlignment                        = ?;   // E1
// TextStrokeTransparency                     = ?;   // E3
// VerticalAlignment                          = ?;   // E1
} // namespace ChatWindowConfiguration

namespace ChorusSoundEffect {     // : SoundEffect
constexpr uintptr_t Depth = 0xE8; // float
constexpr uintptr_t Mix = 0xEC;   // float
constexpr uintptr_t Rate = 0xF0;  // float
} // namespace ChorusSoundEffect

namespace ClickDetector {                         // : Instance
constexpr uintptr_t CursorIconContent = 0xC8;     // Content
constexpr uintptr_t MaxActivationDistance = 0xE8; // float
// CursorIcon                                 = ?;   // E3
} // namespace ClickDetector

namespace ClimbController {                  // : ControllerBase
constexpr uintptr_t AccelerationTime = 0xE0; // float
constexpr uintptr_t BalanceMaxTorque = 0xE4; // float
constexpr uintptr_t BalanceSpeed = 0xE8;     // float
constexpr uintptr_t MoveMaxForce = 0xEC;     // float
} // namespace ClimbController

namespace Clouds {                  // : Instance
constexpr uintptr_t Cover = 0xBC;   // float
constexpr uintptr_t Density = 0xC0; // float
constexpr uintptr_t Enabled = 0xC4; // bool
// Color                                      = ?;   // E1
} // namespace Clouds

namespace Color3Value {           // : ValueBase
constexpr uintptr_t Value = 0xB8; // Color3
} // namespace Color3Value

namespace ColorCorrectionEffect {      // : PostEffect
constexpr uintptr_t TintColor = 0xB8;  // Color3
constexpr uintptr_t Brightness = 0xC4; // float
constexpr uintptr_t Contrast = 0xC8;   // float
constexpr uintptr_t Saturation = 0xCC; // float
} // namespace ColorCorrectionEffect

namespace ColorGradingEffect { // : PostEffect
// TonemapperPreset                           = ?;   // E1
} // namespace ColorGradingEffect

namespace CompressorSoundEffect {      // : SoundEffect
constexpr uintptr_t Attack = 0xF8;     // float
constexpr uintptr_t Ratio = 0x100;     // float
constexpr uintptr_t Release = 0x104;   // float
constexpr uintptr_t Threshold = 0x108; // float
// GainMakeup                                 = ?;   // E3
// SideChain                                  = ?;   // E4
} // namespace CompressorSoundEffect

namespace ConeHandleAdornment {     // : HandleAdornment
constexpr uintptr_t Height = 0x1A8; // float
constexpr uintptr_t Radius = 0x1AC; // float
constexpr uintptr_t Hollow = 0x1B4; // bool
// Shading                                    = ?;   // E1
} // namespace ConeHandleAdornment

namespace ContentProvider { // : Instance
// BaseUrl                                    = ?;   // E3
// RequestQueueSize                           = ?;   // E3
} // namespace ContentProvider

namespace ControllerManager { // : Instance
// ActiveController                           = ?;   // E4
// BaseMoveSpeed                              = ?;   // E3
// BaseTurnSpeed                              = ?;   // E3
// ClimbSensor                                = ?;   // E4
// FacingDirection                            = ?;   // E3
// GroundSensor                               = ?;   // E4
// MovingDirection                            = ?;   // E3
// RootPart                                   = ?;   // E4
// UpDirection                                = ?;   // E3
} // namespace ControllerManager

namespace ControllerPartSensor {                // : ControllerSensor
constexpr uintptr_t LadderSearchHeight = 0x280; // float
constexpr uintptr_t LadderSearchOffset = 0x284; // float
constexpr uintptr_t SearchDistance = 0x288;     // float
// HitFrame                                   = ?;   // E3
// HitNormal                                  = ?;   // E3
// SensedMaterial                             = ?;   // E1
// SensedPart                                 = ?;   // E4
// SensorMode                                 = ?;   // E1
} // namespace ControllerPartSensor

namespace CoreGui { // : BasePlayerGui
                    // SelectionImageObject                       = ?;   // E4
                    // Version                                    = ?;   // E3
} // namespace CoreGui

namespace CustomEvent {                           // : Instance
constexpr uintptr_t PersistedCurrentValue = 0xB0; // float
} // namespace CustomEvent

namespace CustomEventReceiver { // : Instance
// Source                                     = ?;   // E4
} // namespace CustomEventReceiver

namespace CylinderHandleAdornment {      // : HandleAdornment
constexpr uintptr_t Angle = 0x1A8;       // float
constexpr uintptr_t Height = 0x1AC;      // float
constexpr uintptr_t InnerRadius = 0x1B0; // float
constexpr uintptr_t Radius = 0x1B4;      // float
// Shading                                    = ?;   // E1
} // namespace CylinderHandleAdornment

namespace CylindricalConstraint { // : SlidingBallConstraint
// AngularActuatorType                        = ?;   // E1
// AngularLimitsEnabled                       = ?;   // E3
// AngularResponsiveness                      = ?;   // E3
// AngularRestitution                         = ?;   // E3
// AngularSpeed                               = ?;   // E3
// AngularVelocity                            = ?;   // E3
// CurrentAngle                               = ?;   // E3
// InclinationAngle                           = ?;   // E3
// LowerAngle                                 = ?;   // E3
// MotorMaxAngularAcceleration                = ?;   // E3
// MotorMaxTorque                             = ?;   // E3
// RotationAxisVisible                        = ?;   // E3
// ServoMaxTorque                             = ?;   // E3
// SoftlockAngularServoUponReachingTarget     = ?;   // E3
// TargetAngle                                = ?;   // E3
// UpperAngle                                 = ?;   // E3
// WorldRotationAxis                          = ?;   // E3
} // namespace CylindricalConstraint

namespace DataModel {                             // : ServiceProvider
constexpr uintptr_t CreatorId = 0x180;            // int64
constexpr uintptr_t GameId = 0x188;               // int64
constexpr uintptr_t PlaceId = 0x190;              // int64
constexpr uintptr_t PlaceVersion = 0x1AC;         // int
constexpr uintptr_t ForceR15 = 0x1B0;             // bool
constexpr uintptr_t Environment[] = {0x100, 0x0}; // string, deref 1, then add
constexpr uintptr_t JobId[] = {0x120, 0x0};       // string, deref 1, then add
// CreatorType                                = ?;   // E1
// GameAvatarType                             = ?;   // E1
// GearGenreSetting                           = ?;   // E1
// Genre                                      = ?;   // E1
// IsPioneerBuild                             = ?;   // E9
// IsSFFlagsLoaded                            = ?;   // E5
// MatchmakingType                            = ?;   // E1
// PioneerSource                              = ?;   // E1
// PrivateServerId                            = ?;   // E5
// PrivateServerOwnerId                       = ?;   // E5
// R15CollisionType                           = ?;   // E1
// RunService                                 = ?;   // E4
// VIPServerId                                = ?;   // E5
// VIPServerOwnerId                           = ?;   // E5
// Workspace                                  = ?;   // E4
// lighting                                   = ?;   // E4
// workspace                                  = ?;   // E4
} // namespace DataModel

namespace DataStoreGetOptions {      // : Instance
constexpr uintptr_t UseCache = 0xB0; // bool
} // namespace DataStoreGetOptions

namespace DataStoreOptions {          // : Instance
constexpr uintptr_t AllScopes = 0xB0; // bool
} // namespace DataStoreOptions

namespace Debris {                   // : Instance
constexpr uintptr_t MaxItems = 0xC8; // int
} // namespace Debris

namespace Decal {                                      // : FaceInstance
constexpr uintptr_t MetalnessMap = 0xE8;               // ContentId
constexpr uintptr_t TexturePack = 0x1B0;               // ContentId
constexpr uintptr_t TexturePackContent = 0x1B0;        // Content
constexpr uintptr_t UVOffset = 0x1FC;                  // Vector2
constexpr uintptr_t UVScale = 0x204;                   // Vector2
constexpr uintptr_t LocalTransparencyModifier = 0x20C; // float
constexpr uintptr_t Rotation = 0x210;                  // float
constexpr uintptr_t Shiny = 0x214;                     // float
constexpr uintptr_t Specular = 0x218;                  // float
constexpr uintptr_t Transparency = 0x21C;              // float
constexpr uintptr_t ZIndex = 0x220;                    // int
constexpr uintptr_t AutoLocalize = 0x224;              // bool
constexpr uintptr_t TexturePackMetadata[] = {0x1D0,
                                             0x0}; // string, deref 1, then add
// Color3                                     = ?;   // E3
// ColorMap                                   = ?;   // E9
// ColorMapContent                            = ?;   // E1
// Face                                       = ?;   // E1
// MetalnessMapContent                        = ?;   // E1
// NormalMap                                  = ?;   // E9
// NormalMapContent                           = ?;   // E1
// RoughnessMap                               = ?;   // E9
// RoughnessMapContent                        = ?;   // E1
// Texture                                    = ?;   // E9
// TextureContent                             = ?;   // E1
} // namespace Decal

namespace DepthOfFieldEffect {            // : PostEffect
constexpr uintptr_t FarIntensity = 0xB8;  // float
constexpr uintptr_t FocusDistance = 0xBC; // float
constexpr uintptr_t InFocusRadius = 0xC0; // float
constexpr uintptr_t NearIntensity = 0xC4; // float
} // namespace DepthOfFieldEffect

namespace Dialog {                                 // : Instance
constexpr uintptr_t TriggerOffset = 0xF0;          // Vector3
constexpr uintptr_t ConversationDistance = 0x100;  // float
constexpr uintptr_t TriggerDistance = 0x10C;       // float
constexpr uintptr_t GoodbyeChoiceActive = 0x110;   // bool
constexpr uintptr_t InUse = 0x111;                 // bool
constexpr uintptr_t GoodbyeDialog[] = {0xB0, 0x0}; // string, deref 1, then add
constexpr uintptr_t InitialPrompt[] = {0xD0, 0x0}; // string, deref 1, then add
// BehaviorType                               = ?;   // E1
// Purpose                                    = ?;   // E1
// Tone                                       = ?;   // E1
} // namespace Dialog

namespace DialogChoice {                            // : Instance
constexpr uintptr_t GoodbyeChoiceActive = 0x118;    // bool
constexpr uintptr_t GoodbyeDialog[] = {0xB8, 0x0};  // string, deref 1, then add
constexpr uintptr_t ResponseDialog[] = {0xD8, 0x0}; // string, deref 1, then add
constexpr uintptr_t UserDialog[] = {0xF8, 0x0};     // string, deref 1, then add
} // namespace DialogChoice

namespace DistortionSoundEffect { // : SoundEffect
constexpr uintptr_t Level = 0xE8; // float
} // namespace DistortionSoundEffect

namespace DoubleConstrainedValue {   // : ValueBase
constexpr uintptr_t MaxValue = 0xB8; // double
// ConstrainedValue                           = ?;   // E3
// MinValue                                   = ?;   // E3
// Value                                      = ?;   // E3
// value                                      = ?;   // E3
} // namespace DoubleConstrainedValue

namespace DragDetector {                                // : ClickDetector
constexpr uintptr_t ActivatedCursorIconContent = 0x1C0; // Content
constexpr uintptr_t DragFrame = 0x200;                  // CoordinateFrame
constexpr uintptr_t PhysicalDragTargetFrame = 0x230;    // CoordinateFrame
constexpr uintptr_t MaxDragTranslation = 0x26C;         // Vector3
constexpr uintptr_t MinDragTranslation = 0x278;         // Vector3
constexpr uintptr_t PhysicalDragHitPoint = 0x284;       // Vector3
constexpr uintptr_t SecondaryAxis = 0x290;              // Vector3
constexpr uintptr_t MaxDragAngle = 0x2A8;               // float
constexpr uintptr_t MaxForce = 0x2AC;                   // float
constexpr uintptr_t MaxTorque = 0x2B0;                  // float
constexpr uintptr_t MinDragAngle = 0x2B4;               // float
constexpr uintptr_t Responsiveness = 0x2C0;             // float
constexpr uintptr_t TrackballRadialPullFactor = 0x2C4;  // float
constexpr uintptr_t TrackballRollFactor = 0x2C8;        // float
constexpr uintptr_t ApplyAtCenterOfMass = 0x2D0;        // bool
constexpr uintptr_t Enabled = 0x2D1;                    // bool
constexpr uintptr_t PhysicalDragIsInVR = 0x2D2;         // bool
constexpr uintptr_t RunLocally = 0x2D3;                 // bool
// ActivatedCursorIcon                        = ?;   // E3
// Axis                                       = ?;   // E3
// DragStyle                                  = ?;   // E1
// GamepadModeSwitchKeyCode                   = ?;   // E1
// KeyboardModeSwitchKeyCode                  = ?;   // E1
// Orientation                                = ?;   // E6
// PermissionPolicy                           = ?;   // E1
// PhysicalDragClickedPart                    = ?;   // E4
// ReferenceInstance                          = ?;   // E4
// ResponseStyle                              = ?;   // E1
// VRSwitchKeyCode                            = ?;   // E1
// WorldAxis                                  = ?;   // E3
// WorldSecondaryAxis                         = ?;   // E0
} // namespace DragDetector

namespace EchoSoundEffect {          // : SoundEffect
constexpr uintptr_t Delay = 0xE8;    // float
constexpr uintptr_t DryLevel = 0xEC; // float
constexpr uintptr_t Feedback = 0xF0; // float
constexpr uintptr_t WetLevel = 0xF4; // float
} // namespace EchoSoundEffect

namespace EditableService { // : Instance
// EditableStatus                             = ?;   // E1
} // namespace EditableService

namespace EqualizerSoundEffect {     // : SoundEffect
constexpr uintptr_t HighGain = 0xE8; // float
constexpr uintptr_t LowGain = 0xEC;  // float
constexpr uintptr_t MidGain = 0xF0;  // float
} // namespace EqualizerSoundEffect

namespace EulerRotationCurve { // : Instance
// RotationOrder                              = ?;   // E1
} // namespace EulerRotationCurve

namespace ExperienceInviteOptions {     // : Instance
constexpr uintptr_t InviteUser = 0x110; // int64
constexpr uintptr_t InviteMessageId[] = {0xB0,
                                         0x0};     // string, deref 1, then add
constexpr uintptr_t LaunchData[] = {0xD0, 0x0};    // string, deref 1, then add
constexpr uintptr_t PromptMessage[] = {0xF0, 0x0}; // string, deref 1, then add
} // namespace ExperienceInviteOptions

namespace ExperienceStateCaptureService {          // : Instance
constexpr uintptr_t HiddenSelectionEnabled = 0xC4; // bool
constexpr uintptr_t IsInCaptureMode = 0xC6;        // bool
// IsInBackground                             = ?;   // E3
// SelectionMode                              = ?;   // E1
} // namespace ExperienceStateCaptureService

namespace FaceAnimatorService { // : Instance
// AudioAnimationEnabled                      = ?;   // E1
// FaceTrackingStatusEnum                     = ?;   // E1
// FlipHeadOrientation                        = ?;   // E1
// VideoAnimationEnabled                      = ?;   // E1
} // namespace FaceAnimatorService

namespace FaceControls {                            // : Instance
constexpr uintptr_t ChinRaiser = 0xE0;              // float
constexpr uintptr_t ChinRaiserUpperLip = 0xE4;      // float
constexpr uintptr_t Corrugator = 0xE8;              // float
constexpr uintptr_t EyesLookDown = 0xEC;            // float
constexpr uintptr_t EyesLookLeft = 0xF0;            // float
constexpr uintptr_t EyesLookRight = 0xF4;           // float
constexpr uintptr_t EyesLookUp = 0xF8;              // float
constexpr uintptr_t FlatPucker = 0xFC;              // float
constexpr uintptr_t Funneler = 0x100;               // float
constexpr uintptr_t JawDrop = 0x104;                // float
constexpr uintptr_t JawLeft = 0x108;                // float
constexpr uintptr_t JawRight = 0x10C;               // float
constexpr uintptr_t LeftBrowLowerer = 0x110;        // float
constexpr uintptr_t LeftCheekPuff = 0x114;          // float
constexpr uintptr_t LeftCheekRaiser = 0x118;        // float
constexpr uintptr_t LeftDimpler = 0x11C;            // float
constexpr uintptr_t LeftEyeClosed = 0x120;          // float
constexpr uintptr_t LeftEyeUpperLidRaiser = 0x124;  // float
constexpr uintptr_t LeftInnerBrowRaiser = 0x128;    // float
constexpr uintptr_t LeftLipCornerDown = 0x12C;      // float
constexpr uintptr_t LeftLipCornerPuller = 0x130;    // float
constexpr uintptr_t LeftLipStretcher = 0x134;       // float
constexpr uintptr_t LeftLowerLipDepressor = 0x138;  // float
constexpr uintptr_t LeftNoseWrinkler = 0x13C;       // float
constexpr uintptr_t LeftOuterBrowRaiser = 0x140;    // float
constexpr uintptr_t LeftUpperLipRaiser = 0x144;     // float
constexpr uintptr_t LipPresser = 0x148;             // float
constexpr uintptr_t LipsTogether = 0x14C;           // float
constexpr uintptr_t LowerLipSuck = 0x150;           // float
constexpr uintptr_t MouthLeft = 0x154;              // float
constexpr uintptr_t MouthRight = 0x158;             // float
constexpr uintptr_t Pucker = 0x15C;                 // float
constexpr uintptr_t RightBrowLowerer = 0x160;       // float
constexpr uintptr_t RightCheekPuff = 0x164;         // float
constexpr uintptr_t RightCheekRaiser = 0x168;       // float
constexpr uintptr_t RightDimpler = 0x16C;           // float
constexpr uintptr_t RightEyeClosed = 0x170;         // float
constexpr uintptr_t RightEyeUpperLidRaiser = 0x174; // float
constexpr uintptr_t RightInnerBrowRaiser = 0x178;   // float
constexpr uintptr_t RightLipCornerDown = 0x17C;     // float
constexpr uintptr_t RightLipCornerPuller = 0x180;   // float
constexpr uintptr_t RightLipStretcher = 0x184;      // float
constexpr uintptr_t RightLowerLipDepressor = 0x188; // float
constexpr uintptr_t RightNoseWrinkler = 0x18C;      // float
constexpr uintptr_t RightOuterBrowRaiser = 0x190;   // float
constexpr uintptr_t RightUpperLipRaiser = 0x194;    // float
constexpr uintptr_t TongueDown = 0x198;             // float
constexpr uintptr_t TongueOut = 0x19C;              // float
constexpr uintptr_t TongueUp = 0x1A0;               // float
constexpr uintptr_t UpperLipSuck = 0x1A4;           // float
// InternalOverrideFACSData                   = ?;   // E1
} // namespace FaceControls

namespace FileMesh {                        // : DataModelMesh
constexpr uintptr_t MeshContent = 0xF8;     // Content
constexpr uintptr_t MeshId = 0xF8;          // ContentId
constexpr uintptr_t TextureContent = 0x128; // Content
constexpr uintptr_t TextureId = 0x128;      // ContentId
} // namespace FileMesh

namespace Fire {                                      // : Instance
constexpr uintptr_t Color = 0xB8;                     // Color3
constexpr uintptr_t SecondaryColor = 0xC4;            // Color3
constexpr uintptr_t LocalTransparencyModifier = 0xD0; // float
constexpr uintptr_t TimeScale = 0xD4;                 // float
constexpr uintptr_t Heat = 0xD8;                      // float
constexpr uintptr_t heat_xml = 0xD8;                  // float
constexpr uintptr_t Size = 0xDC;                      // float
constexpr uintptr_t size = 0xDC;                      // float
constexpr uintptr_t size_xml = 0xDC;                  // float
constexpr uintptr_t Enabled = 0xE0;                   // bool
} // namespace Fire

namespace Flag { // : Tool
                 // TeamColor                                  = ?;   // E3
} // namespace Flag

namespace FlagStand {                  // : Part
constexpr uintptr_t TeamColor = 0x178; // BrickColor
} // namespace FlagStand

namespace FlangeSoundEffect {     // : SoundEffect
constexpr uintptr_t Depth = 0xE8; // float
constexpr uintptr_t Mix = 0xEC;   // float
constexpr uintptr_t Rate = 0xF0;  // float
} // namespace FlangeSoundEffect

namespace FloatCurve { // : Instance
// Length                                     = ?;   // E3
// ValuesAndTimes                             = ?;   // E3
} // namespace FloatCurve

namespace FloorWire {                             // : GuiBase3d
constexpr uintptr_t Texture = 0x100;              // ContentId
constexpr uintptr_t TextureSize = 0x140;          // Vector2
constexpr uintptr_t CycleOffset = 0x148;          // float
constexpr uintptr_t StudsBetweenTextures = 0x14C; // float
constexpr uintptr_t Velocity = 0x150;             // float
constexpr uintptr_t WireRadius = 0x154;           // float
// From                                       = ?;   // E4
// To                                         = ?;   // E4
} // namespace FloorWire

namespace FluidForceSensor { // : SensorBase
// CenterOfPressure                           = ?;   // E3
// Force                                      = ?;   // E3
// Torque                                     = ?;   // E3
} // namespace FluidForceSensor

namespace Folder { // : Instance
constexpr uintptr_t ReplicatedGuiInsertionOrder[] = {
    0xB8, 0x0}; // int, deref 1, then add
} // namespace Folder

namespace ForceField {              // : Instance
constexpr uintptr_t Visible = 0xB8; // bool
} // namespace ForceField

namespace Frame { // : GuiObject
                  // Style                                      = ?;   // E1
} // namespace Frame

namespace FunctionalTest {                                   // : Instance
constexpr uintptr_t AllowSleep = 0xD8;                       // bool
constexpr uintptr_t HasMigratedSettingsToTestService = 0xD9; // bool
constexpr uintptr_t PhysicsEnvironmentalThrottle = 0xDB;     // bool
constexpr uintptr_t Description[] = {0xB0, 0x0}; // string, deref 1, then add
// Is30FpsThrottleEnabled                     = ?;   // E3
// Timeout                                    = ?;   // E3
} // namespace FunctionalTest

namespace GamepadService {                       // : Instance
constexpr uintptr_t GamepadCursorEnabled = 0xC8; // bool
} // namespace GamepadService

namespace Glue { // : JointInstance
                 // F0                                         = ?;   // E3
                 // F1                                         = ?;   // E3
                 // F2                                         = ?;   // E3
                 // F3                                         = ?;   // E3
} // namespace Glue

namespace GroundController {                 // : ControllerBase
constexpr uintptr_t AccelerationLean = 0xE0; // float
constexpr uintptr_t AccelerationTime = 0xE4; // float
constexpr uintptr_t BalanceMaxTorque = 0xE8; // float
constexpr uintptr_t BalanceSpeed = 0xEC;     // float
constexpr uintptr_t DecelerationTime = 0xF0; // float
constexpr uintptr_t FrictionWeight = 0xF8;   // float
constexpr uintptr_t GroundOffset = 0xFC;     // float
constexpr uintptr_t StandForce = 0x100;      // float
constexpr uintptr_t StandSpeed = 0x104;      // float
constexpr uintptr_t TurnSpeedFactor = 0x108; // float
// Friction                                   = ?;   // E3
} // namespace GroundController

namespace GuiService {                               // : Instance
constexpr uintptr_t ViewportSizeInMM = 0xF8;         // Vector2
constexpr uintptr_t GuiNavigationEnabled = 0x108;    // bool
constexpr uintptr_t MenuIsOpen = 0x109;              // bool
constexpr uintptr_t TouchControlsEnabled = 0x10A;    // bool
constexpr uintptr_t IsModalDialog[] = {0x6E8, 0x10}; // bool, deref 1, then add
// AutoSelectGuiEnabled                       = ?;   // E5
// CoreEffectFolder                           = ?;   // E4
// CoreGuiFolder                              = ?;   // E4
// CoreGuiNavigationEnabled                   = ?;   // E0
// DisplayScalingMode                         = ?;   // E1
// IsWindows                                  = ?;   // E1
// PreferredTextSize                          = ?;   // E1
// PreferredTransparency                      = ?;   // E1
// ReducedMotionEnabled                       = ?;   // E1
// SelectedCoreObject                         = ?;   // E4
// SelectedObject                             = ?;   // E4
// TopbarInset                                = ?;   // E0
// ViewportDisplaySize                        = ?;   // E1
} // namespace GuiService

namespace Handles {                                          // : HandlesBase
constexpr uintptr_t Faces = 0x120;                           // Faces
constexpr uintptr_t MouseButton1DownConnectionCount = 0x124; // int
constexpr uintptr_t MouseButton1UpConnectionCount = 0x128;   // int
constexpr uintptr_t MouseDragConnectionCount = 0x12C;        // int
constexpr uintptr_t MouseEnterConnectionCount = 0x130;       // int
constexpr uintptr_t MouseLeaveConnectionCount = 0x134;       // int
// Style                                      = ?;   // E1
} // namespace Handles

namespace HapticEffect {             // : Instance
constexpr uintptr_t Position = 0xD8; // Vector3
constexpr uintptr_t Radius = 0xE4;   // float
constexpr uintptr_t Looped = 0xEC;   // bool
constexpr uintptr_t WaveformData[] = {0xB8,
                                      0x0}; // BinaryString, deref 1, then add
// Type                                       = ?;   // E1
} // namespace HapticEffect

namespace HiddenSurfaceRemovalAsset { // : Instance
// HSRData                                    = ?;   // E3
// HSRMeshIdData                              = ?;   // E3
} // namespace HiddenSurfaceRemovalAsset

namespace Highlight {                           // : Instance
constexpr uintptr_t FillColor = 0xC8;           // Color3
constexpr uintptr_t OutlineColor = 0xD4;        // Color3
constexpr uintptr_t FillTransparency = 0xE4;    // float
constexpr uintptr_t LineThickness = 0xE8;       // int
constexpr uintptr_t OutlineTransparency = 0xEC; // float
constexpr uintptr_t Enabled = 0xF4;             // bool
// Adornee                                    = ?;   // E4
// DepthMode                                  = ?;   // E1
// ReservedId                                 = ?;   // E1
} // namespace Highlight

namespace HingeConstraint {                                  // : Constraint
constexpr uintptr_t AngularResponsiveness = 0x174;           // float
constexpr uintptr_t AngularSpeed = 0x178;                    // float
constexpr uintptr_t AngularVelocity = 0x17C;                 // float
constexpr uintptr_t LowerAngle = 0x180;                      // float
constexpr uintptr_t MotorMaxTorque = 0x188;                  // float
constexpr uintptr_t Radius = 0x18C;                          // float
constexpr uintptr_t Restitution = 0x190;                     // float
constexpr uintptr_t ServoMaxTorque = 0x194;                  // float
constexpr uintptr_t TargetAngle = 0x198;                     // float
constexpr uintptr_t UpperAngle = 0x19C;                      // float
constexpr uintptr_t SoftlockServoUponReachingTarget = 0x1A1; // bool
// ActuatorType                               = ?;   // E1
// CurrentAngle                               = ?;   // E1
// LimitsEnabled                              = ?;   // E3
// MotorMaxAcceleration                       = ?;   // E3
} // namespace HingeConstraint

namespace HttpService {                 // : Instance
constexpr uintptr_t HttpEnabled = 0xC0; // bool
} // namespace HttpService

namespace Humanoid {                                   // : Instance
constexpr uintptr_t InternalBodyScale = 0x134;         // Vector3
constexpr uintptr_t MoveDirection = 0x140;             // Vector3
constexpr uintptr_t MoveDirectionInternal = 0x140;     // Vector3
constexpr uintptr_t WalkDirection = 0x158;             // Vector3
constexpr uintptr_t CameraMaxDistance = 0x170;         // float
constexpr uintptr_t CameraMinDistance = 0x174;         // float
constexpr uintptr_t HealthDisplayDistance = 0x188;     // float
constexpr uintptr_t Health_XML = 0x190;                // float
constexpr uintptr_t HipHeight = 0x194;                 // float
constexpr uintptr_t InternalHeadScale = 0x198;         // float
constexpr uintptr_t InternalOriginalHipHeight = 0x19C; // float
constexpr uintptr_t JumpHeight = 0x1A0;                // float
constexpr uintptr_t JumpPower = 0x1A4;                 // float
constexpr uintptr_t MaxHealth = 0x1A8;                 // float
constexpr uintptr_t maxHealth = 0x1A8;                 // float
constexpr uintptr_t MaxSlopeAngle = 0x1AC;             // float
constexpr uintptr_t NameDisplayDistance = 0x1B0;       // float
constexpr uintptr_t NoFloorTimerState = 0x1BC;         // float
constexpr uintptr_t TimerState = 0x1C8;                // float
constexpr uintptr_t WalkAngleError = 0x1CC;            // float
constexpr uintptr_t WalkSpeed = 0x1D0;                 // float
constexpr uintptr_t AutoJumpEnabled = 0x1D4;           // bool
constexpr uintptr_t AutoRotate = 0x1D5;                // bool
constexpr uintptr_t AutomaticScalingEnabled = 0x1D6;   // bool
constexpr uintptr_t BreakJointsOnDeath = 0x1D7;        // bool
constexpr uintptr_t EvaluateStateMachine = 0x1D8;      // bool
constexpr uintptr_t FinishedState = 0x1D9;             // bool
constexpr uintptr_t Jump = 0x1DA;                      // bool
constexpr uintptr_t JumpReplicate = 0x1DA;             // bool
constexpr uintptr_t OverrideDefaultCollisions = 0x1DB; // bool
constexpr uintptr_t PlatformStand = 0x1DC;             // bool
constexpr uintptr_t RequiresNeck = 0x1DD;              // bool
constexpr uintptr_t Sit = 0x1DE;                       // bool
constexpr uintptr_t Strafe = 0x1DF;                    // bool
constexpr uintptr_t UseJumpPower = 0x1E0;              // bool
constexpr uintptr_t DisplayName[] = {0xB8, 0x0}; // string, deref 1, then add
constexpr uintptr_t Health[] = {0xB0,
                                0x70}; // float, obscured, deref 1, then add
constexpr uintptr_t InternalDisplayName[] = {0xD8,
                                             0x0}; // string, deref 1, then add
// CameraMode                                 = ?;   // E1
// CameraOffset                               = ?;   // E1
// CollisionType                              = ?;   // E1
// DisplayDistanceType                        = ?;   // E1
// FloorMaterial                              = ?;   // E1
// HealthDisplayType                          = ?;   // E1
// LeftLeg                                    = ?;   // E4
// NameOcclusion                              = ?;   // E1
// NetworkHumanoidState                       = ?;   // E1
// RigType                                    = ?;   // E1
// RightLeg                                   = ?;   // E4
// RootPart                                   = ?;   // E4
// RotationType                               = ?;   // E1
// SeatPart                                   = ?;   // E4
// TargetPoint                                = ?;   // E1
// Torso                                      = ?;   // E4
// WalkToPart                                 = ?;   // E4
// WalkToPoint                                = ?;   // E1
} // namespace Humanoid

namespace HumanoidDescription {                     // : Instance
constexpr uintptr_t ClimbAnimation = 0xB8;          // int64
constexpr uintptr_t Face = 0xC0;                    // int64
constexpr uintptr_t FallAnimation = 0xC8;           // int64
constexpr uintptr_t GraphicTShirt = 0xD0;           // int64
constexpr uintptr_t IdleAnimation = 0xD8;           // int64
constexpr uintptr_t JumpAnimation = 0xE0;           // int64
constexpr uintptr_t MoodAnimation = 0xE8;           // int64
constexpr uintptr_t Pants = 0xF0;                   // int64
constexpr uintptr_t RunAnimation = 0xF8;            // int64
constexpr uintptr_t Shirt = 0x100;                  // int64
constexpr uintptr_t SwimAnimation = 0x108;          // int64
constexpr uintptr_t WalkAnimation = 0x110;          // int64
constexpr uintptr_t BodyTypeScale = 0x118;          // float
constexpr uintptr_t DepthScale = 0x11C;             // float
constexpr uintptr_t HeadScale = 0x120;              // float
constexpr uintptr_t HeightScale = 0x124;            // float
constexpr uintptr_t NumberEmotesLoaded = 0x128;     // int
constexpr uintptr_t ProportionScale = 0x12C;        // float
constexpr uintptr_t WidthScale = 0x130;             // float
constexpr uintptr_t ResetIncludesBodyParts = 0x134; // bool
constexpr uintptr_t StaticFacialAnimation = 0x135;  // bool
constexpr uintptr_t UseAvatarSettings = 0x136;      // bool
// AccessoryBlob                              = ?;   // E3
// BackAccessory                              = ?;   // E3
// EmotesDataInternal                         = ?;   // E3
// EquippedEmotesDataInternal                 = ?;   // E3
// FaceAccessory                              = ?;   // E3
// FrontAccessory                             = ?;   // E3
// HairAccessory                              = ?;   // E3
// HatAccessory                               = ?;   // E3
// Head                                       = ?;   // E3
// HeadColor                                  = ?;   // E3
// LeftArm                                    = ?;   // E3
// LeftArmColor                               = ?;   // E3
// LeftLeg                                    = ?;   // E3
// LeftLegColor                               = ?;   // E3
// NeckAccessory                              = ?;   // E3
// RightArm                                   = ?;   // E3
// RightArmColor                              = ?;   // E3
// RightLeg                                   = ?;   // E3
// RightLegColor                              = ?;   // E3
// ShouldersAccessory                         = ?;   // E3
// Torso                                      = ?;   // E3
// TorsoColor                                 = ?;   // E3
// WaistAccessory                             = ?;   // E3
} // namespace HumanoidDescription

namespace HumanoidRigDescription {                        // : Instance
constexpr uintptr_t LeftHipTposeAdjustment = 0x320;       // CoordinateFrame
constexpr uintptr_t LeftKneeTposeAdjustment = 0x350;      // CoordinateFrame
constexpr uintptr_t LeftShoulderTposeAdjustment = 0x380;  // CoordinateFrame
constexpr uintptr_t LeftToeBaseTposeAdjustment = 0x3B0;   // CoordinateFrame
constexpr uintptr_t LeftWristTposeAdjustment = 0x3E0;     // CoordinateFrame
constexpr uintptr_t NeckTposeAdjustment = 0x410;          // CoordinateFrame
constexpr uintptr_t OriginOffset = 0x440;                 // CoordinateFrame
constexpr uintptr_t RightAnkleTposeAdjustment = 0x470;    // CoordinateFrame
constexpr uintptr_t RightClavicleTposeAdjustment = 0x4A0; // CoordinateFrame
constexpr uintptr_t RightElbowTposeAdjustment = 0x4D0;    // CoordinateFrame
constexpr uintptr_t RightHipTposeAdjustment = 0x500;      // CoordinateFrame
constexpr uintptr_t RightKneeTposeAdjustment = 0x530;     // CoordinateFrame
constexpr uintptr_t RightShoulderTposeAdjustment = 0x560; // CoordinateFrame
constexpr uintptr_t RightToeBaseTposeAdjustment = 0x590;  // CoordinateFrame
constexpr uintptr_t RightWristTposeAdjustment = 0x5C0;    // CoordinateFrame
constexpr uintptr_t RootTposeAdjustment = 0x5F0;          // CoordinateFrame
constexpr uintptr_t SpineTposeAdjustment = 0x620;         // CoordinateFrame
constexpr uintptr_t WaistTposeAdjustment = 0x650;         // CoordinateFrame
constexpr uintptr_t LeftHipRangeMin = 0x704;              // Vector3
constexpr uintptr_t LeftKneeRangeMax = 0x710;             // Vector3
constexpr uintptr_t LeftKneeRangeMin = 0x71C;             // Vector3
constexpr uintptr_t LeftShoulderRangeMax = 0x728;         // Vector3
constexpr uintptr_t LeftShoulderRangeMin = 0x734;         // Vector3
constexpr uintptr_t LeftToeBaseRangeMax = 0x740;          // Vector3
constexpr uintptr_t LeftToeBaseRangeMin = 0x74C;          // Vector3
constexpr uintptr_t LeftWristRangeMax = 0x758;            // Vector3
constexpr uintptr_t LeftWristRangeMin = 0x764;            // Vector3
constexpr uintptr_t NeckRangeMax = 0x770;                 // Vector3
constexpr uintptr_t NeckRangeMin = 0x77C;                 // Vector3
constexpr uintptr_t RightAnkleRangeMax = 0x788;           // Vector3
constexpr uintptr_t RightAnkleRangeMin = 0x794;           // Vector3
constexpr uintptr_t RightClavicleRangeMax = 0x7A0;        // Vector3
constexpr uintptr_t RightClavicleRangeMin = 0x7AC;        // Vector3
constexpr uintptr_t RightElbowRangeMax = 0x7B8;           // Vector3
constexpr uintptr_t RightElbowRangeMin = 0x7C4;           // Vector3
constexpr uintptr_t RightHipRangeMax = 0x7D0;             // Vector3
constexpr uintptr_t RightHipRangeMin = 0x7DC;             // Vector3
constexpr uintptr_t RightKneeRangeMax = 0x7E8;            // Vector3
constexpr uintptr_t RightKneeRangeMin = 0x7F4;            // Vector3
constexpr uintptr_t RightShoulderRangeMax = 0x800;        // Vector3
constexpr uintptr_t RightShoulderRangeMin = 0x80C;        // Vector3
constexpr uintptr_t RightToeBaseRangeMax = 0x818;         // Vector3
constexpr uintptr_t RightToeBaseRangeMin = 0x824;         // Vector3
constexpr uintptr_t RightWristRangeMax = 0x830;           // Vector3
constexpr uintptr_t RightWristRangeMin = 0x83C;           // Vector3
constexpr uintptr_t RootRangeMax = 0x848;                 // Vector3
constexpr uintptr_t RootRangeMin = 0x854;                 // Vector3
constexpr uintptr_t SpineRangeMax = 0x860;                // Vector3
constexpr uintptr_t SpineRangeMin = 0x86C;                // Vector3
constexpr uintptr_t WaistRangeMax = 0x878;                // Vector3
constexpr uintptr_t WaistRangeMin = 0x884;                // Vector3
constexpr uintptr_t LeftHipSize = 0x8A4;                  // float
constexpr uintptr_t LeftKneeSize = 0x8A8;                 // float
constexpr uintptr_t LeftShoulderSize = 0x8AC;             // float
constexpr uintptr_t LeftToeBaseSize = 0x8B0;              // float
constexpr uintptr_t LeftWristSize = 0x8B4;                // float
constexpr uintptr_t NeckSize = 0x8B8;                     // float
constexpr uintptr_t RightAnkleSize = 0x8BC;               // float
constexpr uintptr_t RightClavicleSize = 0x8C0;            // float
constexpr uintptr_t RightElbowSize = 0x8C4;               // float
constexpr uintptr_t RightHipSize = 0x8C8;                 // float
constexpr uintptr_t RightKneeSize = 0x8CC;                // float
constexpr uintptr_t RightShoulderSize = 0x8D0;            // float
constexpr uintptr_t RightToeBaseSize = 0x8D4;             // float
constexpr uintptr_t RightWristSize = 0x8D8;               // float
constexpr uintptr_t RootSize = 0x8DC;                     // float
constexpr uintptr_t SpineSize = 0x8E0;                    // float
constexpr uintptr_t WaistSize = 0x8E4;                    // float
// Chest                                      = ?;   // E4
// ChestRangeMax                              = ?;   // E3
// ChestRangeMin                              = ?;   // E3
// ChestSize                                  = ?;   // E3
// ChestTposeAdjustment                       = ?;   // E3
// HeadBase                                   = ?;   // E4
// HeadBaseRangeMax                           = ?;   // E3
// HeadBaseRangeMin                           = ?;   // E3
// HeadBaseSize                               = ?;   // E3
// HeadBaseTposeAdjustment                    = ?;   // E3
// LeftAnkle                                  = ?;   // E4
// LeftAnkleRangeMax                          = ?;   // E3
// LeftAnkleRangeMin                          = ?;   // E3
// LeftAnkleSize                              = ?;   // E3
// LeftAnkleTposeAdjustment                   = ?;   // E3
// LeftClavicle                               = ?;   // E4
// LeftClavicleRangeMax                       = ?;   // E3
// LeftClavicleRangeMin                       = ?;   // E3
// LeftClavicleSize                           = ?;   // E3
// LeftClavicleTposeAdjustment                = ?;   // E3
// LeftElbow                                  = ?;   // E4
// LeftElbowRangeMax                          = ?;   // E3
// LeftElbowRangeMin                          = ?;   // E3
// LeftElbowSize                              = ?;   // E3
// LeftElbowTposeAdjustment                   = ?;   // E3
// LeftHip                                    = ?;   // E4
// LeftHipRangeMax                            = ?;   // E3
// LeftKnee                                   = ?;   // E4
// LeftShoulder                               = ?;   // E4
// LeftToeBase                                = ?;   // E4
// LeftWrist                                  = ?;   // E4
// Neck                                       = ?;   // E4
// RightAnkle                                 = ?;   // E4
// RightClavicle                              = ?;   // E4
// RightElbow                                 = ?;   // E4
// RightHip                                   = ?;   // E4
// RightKnee                                  = ?;   // E4
// RightShoulder                              = ?;   // E4
// RightToeBase                               = ?;   // E4
// RightWrist                                 = ?;   // E4
// Root                                       = ?;   // E4
// Spine                                      = ?;   // E4
// Waist                                      = ?;   // E4
} // namespace HumanoidRigDescription

namespace IKControl {                         // : Instance
constexpr uintptr_t EndEffectorOffset = 0xF8; // CoordinateFrame
constexpr uintptr_t Offset = 0x128;           // CoordinateFrame
constexpr uintptr_t Priority = 0x158;         // int
constexpr uintptr_t SmoothTime = 0x15C;       // float
constexpr uintptr_t Weight = 0x164;           // float
constexpr uintptr_t Enabled = 0x168;          // bool
// ChainRoot                                  = ?;   // E4
// EndEffector                                = ?;   // E4
// Pole                                       = ?;   // E4
// Target                                     = ?;   // E4
// Type                                       = ?;   // E1
} // namespace IKControl

namespace ImageButton {                       // : GuiButton
constexpr uintptr_t ContentImageSize = 0xD3C; // Vector2
// HoverImage                                 = ?;   // E2
// HoverImageContent                          = ?;   // E2
// Image                                      = ?;   // E2
// ImageColor3                                = ?;   // E2
// ImageContent                               = ?;   // E2
// ImageRectOffset                            = ?;   // E9
// ImageRectSize                              = ?;   // E2
// ImageTransparency                          = ?;   // E9
// IsLoaded                                   = ?;   // E9
// PressedImage                               = ?;   // E2
// PressedImageContent                        = ?;   // E2
// ResampleMode                               = ?;   // E1
// ScaleType                                  = ?;   // E1
// SliceCenter                                = ?;   // E2
// SliceScale                                 = ?;   // E2
// TileSize                                   = ?;   // E2
} // namespace ImageButton

namespace ImageHandleAdornment {          // : HandleAdornment
constexpr uintptr_t ImageContent = 0x1B8; // Content
// Image                                      = ?;   // E3
// Size                                       = ?;   // E3
} // namespace ImageHandleAdornment

namespace ImageLabel { // : GuiLabel
// ContentImageSize                           = ?;   // E3
// Image                                      = ?;   // E2
// ImageColor3                                = ?;   // E2
// ImageContent                               = ?;   // E2
// ImageRectOffset                            = ?;   // E2
// ImageRectSize                              = ?;   // E2
// ImageTransparency                          = ?;   // E2
// IsLoaded                                   = ?;   // E9
// ResampleMode                               = ?;   // E1
// ScaleType                                  = ?;   // E1
// SliceCenter                                = ?;   // E2
// SliceScale                                 = ?;   // E2
// TileSize                                   = ?;   // E2
} // namespace ImageLabel

namespace InputAction {             // : Instance
constexpr uintptr_t Enabled = 0xEC; // bool
// BoolState                                  = ?;   // E3
// Direction1DState                           = ?;   // E3
// Direction2DState                           = ?;   // E3
// Direction3DState                           = ?;   // E3
// PreferredBinding                           = ?;   // E4
// Type                                       = ?;   // E1
// ViewportPositionState                      = ?;   // E3
} // namespace InputAction

namespace InputBinding {                         // : Instance
constexpr uintptr_t DisplayImage = 0xC8;         // Content
constexpr uintptr_t Vector3Scale = 0x128;        // Vector3
constexpr uintptr_t Vector2Scale = 0x134;        // Vector2
constexpr uintptr_t PointerIndex = 0x150;        // int
constexpr uintptr_t PressedThreshold = 0x154;    // float
constexpr uintptr_t ResponseCurve = 0x160;       // float
constexpr uintptr_t Scale = 0x168;               // float
constexpr uintptr_t ClampMagnitudeToOne = 0x178; // bool
// Backward                                   = ?;   // E1
// DisplayName                                = ?;   // E3
// Down                                       = ?;   // E1
// Forward                                    = ?;   // E1
// KeyCode                                    = ?;   // E1
// Left                                       = ?;   // E1
// PrimaryModifier                            = ?;   // E1
// ReleasedThreshold                          = ?;   // E3
// Right                                      = ?;   // E1
// SecondaryModifier                          = ?;   // E1
// Type                                       = ?;   // E1
// UIButton                                   = ?;   // E4
// UIModifier                                 = ?;   // E4
// Up                                         = ?;   // E1
} // namespace InputBinding

namespace InputContext {             // : Instance
constexpr uintptr_t Priority = 0xB8; // int
constexpr uintptr_t Enabled = 0xBC;  // bool
// Sink                                       = ?;   // E3
} // namespace InputContext

namespace InsertService {                         // : Instance
constexpr uintptr_t AllowInsertFreeModels = 0xC0; // bool
} // namespace InsertService

namespace Instance {                            // : Object
constexpr uintptr_t Name = 0x98;                // string
constexpr uintptr_t Archivable = 0xAA;          // bool
constexpr uintptr_t DefinesCapabilities = 0xAA; // bool
constexpr uintptr_t Sandboxed = 0xAA;           // bool
constexpr uintptr_t archivable = 0xAA;          // bool
// Attributes                                 = ?;   // E9
// AttributesReplicate                        = ?;   // E9
// AttributesSerialize                        = ?;   // E9
// Capabilities                               = ?;   // E1
// ClassName                                  = ?;   // E2
// DataCost                                   = ?;   // E2
// HistoryId                                  = ?;   // E1
// IsInSandbox                                = ?;   // E2
// Parent                                     = ?;   // E4
// PredictionMode                             = ?;   // E1
// PropertyStatusStudio                       = ?;   // E1
// RobloxLocked                               = ?;   // E1
// SourceAssetId                              = ?;   // E1
// Tags                                       = ?;   // E3
// UniqueId                                   = ?;   // E1
// className                                  = ?;   // E2
// numExpectedDirectChildren                  = ?;   // E3
} // namespace Instance

namespace IntConstrainedValue {              // : ValueBase
constexpr uintptr_t MaxValue = 0xB8;         // int64
constexpr uintptr_t MinValue = 0xC0;         // int64
constexpr uintptr_t ConstrainedValue = 0xC8; // int64
constexpr uintptr_t Value = 0xC8;            // int64
constexpr uintptr_t value = 0xC8;            // int64
} // namespace IntConstrainedValue

namespace IntValue {              // : ValueBase
constexpr uintptr_t Value = 0xB8; // int64
} // namespace IntValue

namespace Keyframe {             // : Instance
constexpr uintptr_t Time = 0xB8; // float
} // namespace Keyframe

namespace KeyframeMarker {                 // : Instance
constexpr uintptr_t Value[] = {0xB8, 0x0}; // string, deref 1, then add
} // namespace KeyframeMarker

namespace KeyframeSequence {                  // : AnimationClip
constexpr uintptr_t AuthoredHipHeight = 0xE0; // float
} // namespace KeyframeSequence

namespace Lighting {                                   // : Instance
constexpr uintptr_t ClockTime = 0xC8;                  // float
constexpr uintptr_t Ambient = 0xD0;                    // Color3
constexpr uintptr_t ColorShift_Bottom = 0xDC;          // Color3
constexpr uintptr_t ColorShift_Top = 0xE8;             // Color3
constexpr uintptr_t FogColor = 0xF4;                   // Color3
constexpr uintptr_t OutdoorAmbient = 0x100;            // Color3
constexpr uintptr_t ShadowColor = 0x10C;               // Color3
constexpr uintptr_t Brightness = 0x118;                // float
constexpr uintptr_t EnvironmentDiffuseScale = 0x11C;   // float
constexpr uintptr_t EnvironmentSpecularScale = 0x120;  // float
constexpr uintptr_t ExposureCompensation = 0x124;      // float
constexpr uintptr_t FogEnd = 0x12C;                    // float
constexpr uintptr_t FogStart = 0x130;                  // float
constexpr uintptr_t GeographicLatitude = 0x134;        // float
constexpr uintptr_t ShadowSoftness = 0x13C;            // float
constexpr uintptr_t GlobalShadows = 0x144;             // bool
constexpr uintptr_t Outlines = 0x145;                  // bool
constexpr uintptr_t PrioritizeLightingQuality = 0x146; // bool
constexpr uintptr_t TimeOfDay[] = {0xC0,
                                   0x98}; // string, obscured, deref 1, then add
// ExtendLightRangeTo120                      = ?;   // E1
// LightingStyle                              = ?;   // E1
// Technology                                 = ?;   // E1
} // namespace Lighting

namespace LineForce {                             // : Constraint
constexpr uintptr_t Magnitude = 0x170;            // float
constexpr uintptr_t MaxForce = 0x174;             // float
constexpr uintptr_t ApplyAtCenterOfMass = 0x178;  // bool
constexpr uintptr_t InverseSquareLaw = 0x179;     // bool
constexpr uintptr_t ReactionForceEnabled = 0x17A; // bool
} // namespace LineForce

namespace LineHandleAdornment {        // : HandleAdornment
constexpr uintptr_t Length = 0x1A8;    // float
constexpr uintptr_t Thickness = 0x1AC; // float
} // namespace LineHandleAdornment

namespace LinearVelocity {                        // : Constraint
constexpr uintptr_t ReactionForceEnabled = 0x174; // bool
// ForceLimitMode                             = ?;   // E1
// ForceLimitsEnabled                         = ?;   // E3
// LineDirection                              = ?;   // E3
// LineVelocity                               = ?;   // E3
// MaxAxesForce                               = ?;   // E3
// MaxForce                                   = ?;   // E3
// MaxPlanarAxesForce                         = ?;   // E3
// PlaneVelocity                              = ?;   // E3
// PrimaryTangentAxis                         = ?;   // E3
// RelativeTo                                 = ?;   // E1
// SecondaryTangentAxis                       = ?;   // E3
// VectorVelocity                             = ?;   // E3
// VelocityConstraintMode                     = ?;   // E1
} // namespace LinearVelocity

namespace LocalizationService {                  // : Instance
constexpr uintptr_t ShouldUseCloudTable = 0x138; // bool
constexpr uintptr_t SystemLocaleId = 0x3E0;      // string
constexpr uintptr_t LocaleManifest = 0x438;      // string
constexpr uintptr_t ForcePlayModeGameLocaleId[] = {
    0xC8, 0x0}; // string, deref 1, then add
constexpr uintptr_t ForcePlayModeRobloxLocaleId[] = {
    0xE8, 0x0}; // string, deref 1, then add
constexpr uintptr_t GameSourceLanguageId[] = {0x108,
                                              0x0}; // string, deref 1, then add
constexpr uintptr_t IsTextScraperRunning[] = {0x2F8,
                                              0x13}; // bool, deref 1, then add
constexpr uintptr_t RobloxForcePlayModeGameLocaleId[] = {
    0xC8, 0x0}; // string, deref 1, then add
constexpr uintptr_t RobloxForcePlayModeRobloxLocaleId[] = {
    0xE8, 0x0}; // string, deref 1, then add
                // RobloxLocaleId                             = ?;   // E1
} // namespace LocalizationService

namespace LocalizationTable { // : Instance
// Contents                                   = ?;   // E3
// DevelopmentLanguage                        = ?;   // E1
// IsExemptFromUGCAnalytics                   = ?;   // E3
// Root                                       = ?;   // E4
// SourceLocaleId                             = ?;   // E1
} // namespace LocalizationTable

namespace LodDataEntity {                               // : Instance
constexpr uintptr_t SlimReplicationTimestampSec = 0xE0; // double
constexpr uintptr_t EntityPosition = 0xE8;              // CoordinateFrame
constexpr uintptr_t IsSlimEnabled = 0x132;              // bool
// EntityData                                 = ?;   // E0
// EntityLodEnabled                           = ?;   // E3
// EntityModelSize                            = ?;   // E3
// EntityScale                                = ?;   // E3
// EntitySource                               = ?;   // E4
// EntityVisible                              = ?;   // E3
// SlimAnimationSource                        = ?;   // E4
} // namespace LodDataEntity

namespace MarkerCurve { // : Instance
// Length                                     = ?;   // E3
// ValuesAndTimes                             = ?;   // E3
} // namespace MarkerCurve

namespace MaterialService {                      // : Instance
constexpr uintptr_t Use2022Materials = 0x5D0;    // bool
constexpr uintptr_t Use2022MaterialsXml = 0x5D0; // bool
// AsphaltName                                = ?;   // E3
// BasaltName                                 = ?;   // E3
// BrickName                                  = ?;   // E3
// CardboardName                              = ?;   // E3
// CarpetName                                 = ?;   // E3
// CeramicTilesName                           = ?;   // E3
// ClayRoofTilesName                          = ?;   // E3
// CobblestoneName                            = ?;   // E3
// ConcreteName                               = ?;   // E3
// CorrodedMetalName                          = ?;   // E3
// CrackedLavaName                            = ?;   // E3
// DiamondPlateName                           = ?;   // E3
// FabricName                                 = ?;   // E3
// FoilName                                   = ?;   // E3
// GlacierName                                = ?;   // E3
// GraniteName                                = ?;   // E3
// GrassName                                  = ?;   // E3
// GroundName                                 = ?;   // E3
// IceName                                    = ?;   // E3
// LeafyGrassName                             = ?;   // E3
// LeatherName                                = ?;   // E3
// LimestoneName                              = ?;   // E3
// MarbleName                                 = ?;   // E3
// MetalName                                  = ?;   // E3
// MudName                                    = ?;   // E3
// PavementName                               = ?;   // E3
// PebbleName                                 = ?;   // E3
// PlasterName                                = ?;   // E3
// PlasticName                                = ?;   // E3
// RockName                                   = ?;   // E3
// RoofShinglesName                           = ?;   // E3
// RubberName                                 = ?;   // E3
// SaltName                                   = ?;   // E3
// SandName                                   = ?;   // E3
// SandstoneName                              = ?;   // E3
// SlateName                                  = ?;   // E3
// SmoothPlasticName                          = ?;   // E3
// SnowName                                   = ?;   // E3
// WoodName                                   = ?;   // E3
// WoodPlanksName                             = ?;   // E3
} // namespace MaterialService

namespace MaterialVariant {                     // : Instance
constexpr uintptr_t TexturePack = 0x1B8;        // ContentId
constexpr uintptr_t TexturePackContent = 0x1B8; // Content
constexpr uintptr_t EmissiveTint = 0x1F4;       // Color3
constexpr uintptr_t AvgMetalness = 0x204;       // int
constexpr uintptr_t AvgRoughness = 0x208;       // int
constexpr uintptr_t EmissiveStrength = 0x210;   // float
// AlphaMode                                  = ?;   // E1
// BaseMaterial                               = ?;   // E1
// ColorMap                                   = ?;   // E3
// ColorMapContent                            = ?;   // E1
// CustomPhysicalProperties                   = ?;   // E3
// EmissiveMaskContent                        = ?;   // E1
// MaterialPattern                            = ?;   // E1
// MetalnessMap                               = ?;   // E3
// MetalnessMapContent                        = ?;   // E1
// NormalMap                                  = ?;   // E3
// NormalMapContent                           = ?;   // E1
// RoughnessMap                               = ?;   // E3
// RoughnessMapContent                        = ?;   // E1
// StudsPerTile                               = ?;   // E3
} // namespace MaterialVariant

namespace MeshPart {                        // : TriangleMeshPart
constexpr uintptr_t InitialSize = 0x1D0;    // Vector3
constexpr uintptr_t MeshID = 0x2A0;         // ContentId
constexpr uintptr_t MeshId = 0x2A0;         // ContentId
constexpr uintptr_t TextureID = 0x2D0;      // ContentId
constexpr uintptr_t VertexCount = 0x310;    // int
constexpr uintptr_t DoubleSided = 0x315;    // bool
constexpr uintptr_t HasSkinnedMesh = 0x316; // bool
constexpr uintptr_t AlternateMeshHash[] = {0x340,
                                           0x28}; // int64, deref 1, then add
constexpr uintptr_t PhysicsData[] = {0x200,
                                     0x0}; // BinaryString, deref 1, then add
// HasJointOffset                             = ?;   // E3
// JointOffset                                = ?;   // E1
// MeshContent                                = ?;   // E1
// RenderFidelity                             = ?;   // E1
// RenderFidelityReplicate                    = ?;   // E1
// SolidMeshHolder                            = ?;   // E3
// TextureContent                             = ?;   // E1
} // namespace MeshPart

namespace Message { // : Instance
                    // Text                                       = ?;   // E1
} // namespace Message

namespace MicroProfilerService {                  // : Instance
constexpr uintptr_t ContextLabel[] = {0xC0, 0x0}; // string, deref 1, then add
} // namespace MicroProfilerService

namespace Model {                        // : PVInstance
constexpr uintptr_t WorldPivot = 0xF8;   // CoordinateFrame
constexpr uintptr_t Scale = 0x144;       // float
constexpr uintptr_t ScaleFactor = 0x144; // float
// LevelOfDetail                              = ?;   // E1
// LodEntity                                  = ?;   // E4
// ModelMeshCFrame                            = ?;   // E1
// ModelMeshData                              = ?;   // E1
// ModelMeshSize                              = ?;   // E1
// ModelStreamingMode                         = ?;   // E1
// NeedsPivotMigration                        = ?;   // E1
// PrimaryPart                                = ?;   // E4
// SlimAnimationTarget                        = ?;   // E4
// SlimHash                                   = ?;   // E1
// WorldPivotData                             = ?;   // E1
} // namespace Model

namespace ModuleScript {                                // : LuaSourceContainer
constexpr uintptr_t UnrestrictedRequireAllowed = 0x168; // bool
constexpr uintptr_t Confidential = 0x198;               // bool
// LinkedSource                               = ?;   // E1
// Source                                     = ?;   // E0
} // namespace ModuleScript

namespace Motor { // : JointInstance
                  // CurrentAngle                               = ?;   // E3
                  // DesiredAngle                               = ?;   // E3
                  // MaxVelocity                                = ?;   // E3
                  // ReplicateCurrentAngle                      = ?;   // E3
} // namespace Motor

namespace Motor6D {                         // : Motor
constexpr uintptr_t EnableSkinning = 0x1B0; // bool
constexpr uintptr_t ChildName[] = {0x190,
                                   0x18}; // string, obscured, deref 1, then add
constexpr uintptr_t ParentName[] = {
    0x190, 0x10}; // string, obscured, deref 1, then add
constexpr uintptr_t ReplicateCurrentAngle6D[] = {
    0xE0, 0x0}; // Vector3, obscured, deref 1, then add
constexpr uintptr_t ReplicateCurrentOffset6D[] = {
    0xE0, 0x0}; // Vector3, obscured, deref 1, then add
                // Transform                                  = ?;   // E9
} // namespace Motor6D

namespace NoCollisionConstraint {   // : Instance
constexpr uintptr_t Enabled = 0xD8; // bool
// Part0                                      = ?;   // E4
// Part1                                      = ?;   // E4
} // namespace NoCollisionConstraint

namespace NotificationService {                    // : Instance
constexpr uintptr_t IsConnected = 0xE0;            // bool
constexpr uintptr_t SelectedTheme[] = {0xC0, 0x0}; // string, deref 1, then add
// IsLuaChatEnabled                           = ?;   // E3
// IsLuaGameDetailsEnabled                    = ?;   // E3
} // namespace NotificationService

namespace NumberPose {            // : PoseBase
constexpr uintptr_t Value = 0xD0; // double
} // namespace NumberPose

namespace NumberValue {           // : ValueBase
constexpr uintptr_t Value = 0xB8; // double
} // namespace NumberValue

namespace ObjectValue { // : ValueBase
// Value                                      = ?;   // E4
} // namespace ObjectValue

namespace Packages {
constexpr uintptr_t ShellPackagesCount = 0xC0;    // int
constexpr uintptr_t SkippedInstancesCount = 0xC4; // int
constexpr uintptr_t IsDehydrated = 0xC8;          // bool
} // namespace Packages

namespace Pants {                                // : Clothing
constexpr uintptr_t PantsTemplate = 0xD0;        // ContentId
constexpr uintptr_t PantsTemplateContent = 0xD0; // Content
} // namespace Pants

namespace Part { // : FormFactorPart
                 // Shape                                      = ?;   // E1
                 // shap                                       = ?;   // E1
                 // shape                                      = ?;   // E1
} // namespace Part

namespace ParticleEmitter {                            // : Instance
constexpr uintptr_t SpreadAngle = 0x214;               // Vector2
constexpr uintptr_t Brightness = 0x21C;                // float
constexpr uintptr_t Drag = 0x220;                      // float
constexpr uintptr_t FlipbookSizeX = 0x230;             // int
constexpr uintptr_t FlipbookSizeY = 0x234;             // int
constexpr uintptr_t LightEmission = 0x238;             // float
constexpr uintptr_t LightInfluence = 0x23C;            // float
constexpr uintptr_t LocalTransparencyModifier = 0x240; // float
constexpr uintptr_t Rate = 0x248;                      // float
constexpr uintptr_t ShapePartial = 0x254;              // float
constexpr uintptr_t TimeScale = 0x25C;                 // float
constexpr uintptr_t VelocityInheritance = 0x260;       // float
constexpr uintptr_t ZOffset = 0x264;                   // float
constexpr uintptr_t Enabled = 0x268;                   // bool
constexpr uintptr_t FlipbookBlendFrames = 0x269;       // bool
constexpr uintptr_t FlipbookStartRandom = 0x26A;       // bool
constexpr uintptr_t LockedToPart = 0x26B;              // bool
constexpr uintptr_t WindAffectsDrag = 0x26C;           // bool
// Acceleration                               = ?;   // E1
// Color                                      = ?;   // E3
// EmissionDirection                          = ?;   // E1
// FlipbookFramerate                          = ?;   // E3
// FlipbookIncompatible                       = ?;   // E3
// FlipbookLayout                             = ?;   // E1
// FlipbookMode                               = ?;   // E1
// Lifetime                                   = ?;   // E3
// Orientation                                = ?;   // E1
// RotSpeed                                   = ?;   // E3
// Rotation                                   = ?;   // E3
// Shape                                      = ?;   // E1
// ShapeInOut                                 = ?;   // E1
// ShapeStyle                                 = ?;   // E1
// Size                                       = ?;   // E3
// Speed                                      = ?;   // E3
// Squash                                     = ?;   // E3
// Texture                                    = ?;   // E3
// TextureContent                             = ?;   // E3
// Transparency                               = ?;   // E3
// VelocitySpread                             = ?;   // E3
} // namespace ParticleEmitter

namespace Path2D {                               // : GuiBase
constexpr uintptr_t SelectedControlPoint = 0xEC; // int
constexpr uintptr_t Transparency = 0xF4;         // float
// Closed                                     = ?;   // E3
// Color3                                     = ?;   // E3
// PropertiesSerialize                        = ?;   // E3
// SelectedControlPointData                   = ?;   // E3
// Thickness                                  = ?;   // E3
// Visible                                    = ?;   // E3
// ZIndex                                     = ?;   // E3
} // namespace Path2D

namespace PathfindingLink {                 // : Instance
constexpr uintptr_t IsBidirectional = 0xF8; // bool
// Attachment0                                = ?;   // E4
// Attachment1                                = ?;   // E4
// Label                                      = ?;   // E1
} // namespace PathfindingLink

namespace PathfindingModifier {         // : Instance
constexpr uintptr_t PassThrough = 0xD8; // bool
// Label                                      = ?;   // E1
} // namespace PathfindingModifier

namespace PathfindingService { // : Instance
// EmptyCutoff                                = ?;   // E1
} // namespace PathfindingService

namespace PitchShiftSoundEffect {  // : SoundEffect
constexpr uintptr_t Octave = 0xE8; // float
} // namespace PitchShiftSoundEffect

namespace Player {                                          // : Instance
constexpr uintptr_t CharacterAppearanceId = 0x300;          // int64
constexpr uintptr_t FollowUserId = 0x308;                   // int64
constexpr uintptr_t FollowUserIdReplicated = 0x308;         // int64
constexpr uintptr_t Guest = 0x310;                          // bool
constexpr uintptr_t UserId = 0x310;                         // int64
constexpr uintptr_t userId = 0x310;                         // int64
constexpr uintptr_t CloudEditCameraCoordinateFrame = 0x318; // CoordinateFrame
constexpr uintptr_t ChararacterRegionId = 0x348;            // Vector3
constexpr uintptr_t CameraViewportSize = 0x354;             // Vector2
constexpr uintptr_t CameraFieldOfView = 0x364;              // float
constexpr uintptr_t CameraMaxZoomDistance = 0x368;          // float
constexpr uintptr_t CameraMinZoomDistance = 0x36C;          // float
constexpr uintptr_t DataComplexityLimit = 0x378;            // int
constexpr uintptr_t HealthDisplayDistance = 0x390;          // float
constexpr uintptr_t InputLatency = 0x394;                   // int
constexpr uintptr_t MaximumSimulationRadius = 0x398;        // float
constexpr uintptr_t NameDisplayDistance = 0x3A0;            // float
constexpr uintptr_t TeamColor = 0x3AC;                      // BrickColor
constexpr uintptr_t VoiceChatVolume = 0x3B8;                // float
constexpr uintptr_t AppearanceDidLoad = 0x3BC;              // bool
constexpr uintptr_t AutoJumpEnabled = 0x3BD;                // bool
constexpr uintptr_t CameraFrustumRequested = 0x3BE;         // bool
constexpr uintptr_t CanLoadCharacterAppearance = 0x3BF;     // bool
constexpr uintptr_t CloudEditPlayerActive = 0x3C0;          // bool
constexpr uintptr_t DataReady = 0x3C1;                      // bool
constexpr uintptr_t DevEnableMouseLock = 0x3C2;             // bool
constexpr uintptr_t GameplayPaused = 0x3C3;                 // bool
constexpr uintptr_t HasVerifiedBadge = 0x3C5;               // bool
constexpr uintptr_t InternalCharacterAppearanceLoaded = 0x3C6; // bool
constexpr uintptr_t NeedRegionalFallback = 0x3C7;              // bool
constexpr uintptr_t Teleported = 0x3C9;                        // bool
constexpr uintptr_t TeleportedIn = 0x3CA;                      // bool
constexpr uintptr_t VREnabled = 0x3CC;                         // bool
constexpr uintptr_t LocaleId = 0x740;                          // string
constexpr uintptr_t CharacterAppearance[] = {0xD8,
                                             0x0}; // string, deref 1, then add
constexpr uintptr_t ChatAvailabilityStatus[] = {
    0xF8, 0x0}; // string, deref 1, then add
constexpr uintptr_t DataComplexity[] = {0xA38, 0x10}; // int, deref 1, then add
constexpr uintptr_t DisplayName[] = {0x138, 0x0};  // string, deref 1, then add
constexpr uintptr_t PartyId[] = {0x178, 0x0};      // string, deref 1, then add
constexpr uintptr_t PlatformName[] = {0x198, 0x0}; // string, deref 1, then add
// AccountAge                                 = ?;   // E3
// AccountAgeReplicate                        = ?;   // E3
// AgeChecked                                 = ?;   // E1
// CameraMode                                 = ?;   // E1
// Character                                  = ?;   // E4
// ChatMode                                   = ?;   // E1
// ChatPrivacyMode                            = ?;   // E1
// CountryRegionCodeReplicate                 = ?;   // E3
// DevCameraOcclusionMode                     = ?;   // E1
// DevComputerCameraMode                      = ?;   // E1
// DevComputerMovementMode                    = ?;   // E1
// DevTouchCameraMode                         = ?;   // E1
// DevTouchMovementMode                       = ?;   // E1
// HasRobloxSubscription                      = ?;   // E3
// MaxSimulationRadius                        = ?;   // E1
// MembershipType                             = ?;   // E1
// MembershipTypeReplicate                    = ?;   // E1
// Neutral                                    = ?;   // E3
// OsPlatform                                 = ?;   // E3
// PendingRequestedTool                       = ?;   // E4
// RawJoinData                                = ?;   // E1
// ReplicationFocus                           = ?;   // E4
// RespawnLocation                            = ?;   // E4
// SimulationRadius                           = ?;   // E3
// StepIdOffset                               = ?;   // E3
// SuperSafeChatReplicate                     = ?;   // E9
// Team                                       = ?;   // E4
// ThirdPartyTextChatRestrictionStatus        = ?;   // E1
// UnfilteredChat                             = ?;   // E9
// User                                       = ?;   // E3
// UserIdModeReplicate                        = ?;   // E1
// VRDevice                                   = ?;   // E3
} // namespace Player

namespace PlayerEmulatorService {                  // : Instance
constexpr uintptr_t TextElongationFactor = 0x128;  // int
constexpr uintptr_t CustomPoliciesEnabled = 0x12C; // bool
constexpr uintptr_t EmulatedCountryCode[] = {0xC8,
                                             0x0}; // string, deref 1, then add
constexpr uintptr_t EmulatedGameLocale[] = {0xE8,
                                            0x0}; // string, deref 1, then add
constexpr uintptr_t SerializedEmulatedPolicyInfo[] = {
    0x108, 0x0}; // BinaryString, deref 1, then add
                 // PlayerEmulationEnabled                     = ?;   // E3
                 // PseudolocalizationEnabled                  = ?;   // E3
} // namespace PlayerEmulatorService

namespace PlayerGui { // : BasePlayerGui
                      // CurrentScreenOrientation                   = ?;   // E1
                      // InputBindingMappingsRaw                    = ?;   // E3
                      // ScreenOrientation                          = ?;   // E1
                      // SelectionImageObject                       = ?;   // E4
} // namespace PlayerGui

namespace Players {                                   // : Instance
constexpr uintptr_t MaxPlayers = 0x140;               // int
constexpr uintptr_t MaxPlayersInternal = 0x140;       // int
constexpr uintptr_t PreferredPlayers = 0x144;         // int
constexpr uintptr_t PreferredPlayersInternal = 0x144; // int
constexpr uintptr_t RespawnTime = 0x148;              // float
constexpr uintptr_t BanningEnabled = 0x14C;           // bool
constexpr uintptr_t CharacterAutoLoads = 0x14D;       // bool
constexpr uintptr_t BubbleChat = 0x36C;               // bool
constexpr uintptr_t NumPlayers[] = {0x250, 0x8};      // int, deref 1, then add
constexpr uintptr_t ServerGitHash[] = {0xC0, 0x0}; // string, deref 1, then add
constexpr uintptr_t ServerLogPrefix[] = {0xE0,
                                         0x0};   // string, deref 1, then add
constexpr uintptr_t numPlayers[] = {0x250, 0x8}; // int, deref 1, then add
// ClassicChat                                = ?;   // E1
// LocalPlayer                                = ?;   // E4
// UseStrafingAnimations                      = ?;   // E3
// localPlayer                                = ?;   // E4
} // namespace Players

namespace PointLight {            // : Light
constexpr uintptr_t Range = 0xD8; // float
} // namespace PointLight

namespace PolicyService { // : Instance
// IsLuobuServer                              = ?;   // E1
// LuobuWhitelisted                           = ?;   // E1
} // namespace PolicyService

namespace Pose { // : PoseBase
                 // CFrame                                     = ?;   // E3
                 // MaskWeight                                 = ?;   // E1
} // namespace Pose

namespace ProximityPrompt {                        // : Instance
constexpr uintptr_t UIOffset = 0x110;              // Vector2
constexpr uintptr_t HoldDuration = 0x120;          // float
constexpr uintptr_t MaxActivationDistance = 0x128; // float
constexpr uintptr_t MaxIndicatorDistance = 0x12C;  // float
constexpr uintptr_t AutoLocalize = 0x134;          // bool
constexpr uintptr_t ClickablePrompt = 0x135;       // bool
constexpr uintptr_t Enabled = 0x136;               // bool
constexpr uintptr_t RequiresLineOfSight = 0x137;   // bool
constexpr uintptr_t ActionText[] = {0xB0, 0x0};    // string, deref 1, then add
constexpr uintptr_t ObjectText[] = {0xD0, 0x0};    // string, deref 1, then add
// Exclusivity                                = ?;   // E1
// GamepadKeyCode                             = ?;   // E1
// KeyboardKeyCode                            = ?;   // E1
// RootLocalizationTable                      = ?;   // E4
// Style                                      = ?;   // E1
} // namespace ProximityPrompt

namespace ProximityPromptService {               // : Instance
constexpr uintptr_t MaxIndicatorsVisible = 0xE0; // int
constexpr uintptr_t MaxPromptsVisible = 0xE4;    // int
constexpr uintptr_t Enabled = 0xE8;              // bool
} // namespace ProximityPromptService

namespace RayValue { // : ValueBase
                     // Value                                      = ?;   // E3
} // namespace RayValue

namespace RenderingTest {                            // : Instance
constexpr uintptr_t RenderingTestFrameCount = 0x134; // int
constexpr uintptr_t Timeout = 0x138;                 // int
constexpr uintptr_t PerfTest = 0x13C;                // bool
constexpr uintptr_t ShouldSkip = 0x13D;              // bool
// CFrame                                     = ?;   // E3
// ComparisonDiffThreshold                    = ?;   // E3
// ComparisonMethod                           = ?;   // E1
// ComparisonPsnrThreshold                    = ?;   // E3
// Description                                = ?;   // E1
// FieldOfView                                = ?;   // E3
// Orientation                                = ?;   // E3
// Position                                   = ?;   // E3
// QualityAuto                                = ?;   // E3
// QualityLevel                               = ?;   // E3
// Ticket                                     = ?;   // E1
} // namespace RenderingTest

namespace ReverbSoundEffect {         // : SoundEffect
constexpr uintptr_t DecayTime = 0xE8; // float
constexpr uintptr_t Density = 0xEC;   // float
constexpr uintptr_t Diffusion = 0xF0; // float
constexpr uintptr_t DryLevel = 0xF4;  // float
constexpr uintptr_t WetLevel = 0xF8;  // float
} // namespace ReverbSoundEffect

namespace RigidConstraint {                 // : Constraint
constexpr uintptr_t EnableSkinning = 0x168; // bool
} // namespace RigidConstraint

namespace RocketPropulsion { // : BodyMover
// Active                                     = ?;   // E3
// CartoonFactor                              = ?;   // E3
// MaxSpeed                                   = ?;   // E3
// MaxThrust                                  = ?;   // E3
// MaxTorque                                  = ?;   // E3
// Target                                     = ?;   // E4
// TargetOffset                               = ?;   // E3
// TargetRadius                               = ?;   // E3
// ThrustD                                    = ?;   // E3
// ThrustP                                    = ?;   // E3
// TurnD                                      = ?;   // E3
// TurnP                                      = ?;   // E3
} // namespace RocketPropulsion

namespace RodConstraint {                  // : Constraint
constexpr uintptr_t Length = 0x170;        // float
constexpr uintptr_t LimitAngle0 = 0x174;   // float
constexpr uintptr_t LimitAngle1 = 0x178;   // float
constexpr uintptr_t Thickness = 0x17C;     // float
constexpr uintptr_t LimitsEnabled = 0x180; // bool
// CurrentDistance                            = ?;   // E9
} // namespace RodConstraint

namespace RopeConstraint {                       // : Constraint
constexpr uintptr_t Length = 0x170;              // float
constexpr uintptr_t Restitution = 0x174;         // float
constexpr uintptr_t Thickness = 0x178;           // float
constexpr uintptr_t WinchForce = 0x17C;          // float
constexpr uintptr_t WinchResponsiveness = 0x180; // float
constexpr uintptr_t WinchTarget = 0x188;         // float
// CurrentDistance                            = ?;   // E9
// WinchEnabled                               = ?;   // E3
// WinchSpeed                                 = ?;   // E3
} // namespace RopeConstraint

namespace RotationCurve { // : Instance
// Length                                     = ?;   // E3
// ValuesAndTimes                             = ?;   // E3
} // namespace RotationCurve

namespace RunService {                   // : Instance
constexpr uintptr_t ClientGitHash = 0x0; // string, obscured
// FrameNumber                                = ?;   // E5
// RunState                                   = ?;   // E1
} // namespace RunService

namespace SafetyService {                          // : Instance
constexpr uintptr_t IsCaptureModeForReport = 0xC0; // bool
} // namespace SafetyService

namespace ScreenGui {                             // : LayerCollector
constexpr uintptr_t DisplayOrder = 0x740;         // int
constexpr uintptr_t IgnoreGuiInset = 0x748;       // bool
constexpr uintptr_t ClipToDeviceSafeArea = 0x74C; // bool
constexpr uintptr_t OnTopOfCoreBlur = 0x74D;      // bool
// SafeAreaCompatibility                      = ?;   // E1
// ScreenInsets                               = ?;   // E1
} // namespace ScreenGui

namespace ScreenshotHud {                           // : Instance
constexpr uintptr_t CameraButtonIconContent = 0xC0; // Content
constexpr uintptr_t CloseButtonPosition = 0xF0;     // UDim2
constexpr uintptr_t UsernameOverlayEnabled = 0x108; // bool
constexpr uintptr_t Visible = 0x109;                // bool
// CameraButtonIcon                           = ?;   // E3
// CameraButtonPosition                       = ?;   // E3
// CloseWhenScreenshotTaken                   = ?;   // E3
// ExperienceNameOverlayEnabled               = ?;   // E3
// HideCoreGuiForCaptures                     = ?;   // E3
// HidePlayerGuiForCaptures                   = ?;   // E3
// OverlayFont                                = ?;   // E1
} // namespace ScreenshotHud

namespace Script { // : BaseScript
                   // Source                                     = ?;   // E1
} // namespace Script

namespace ScriptContext {                   // : Instance
constexpr uintptr_t ScriptsDisabled = 0xC8; // bool
} // namespace ScriptContext

namespace ScrollingFrame {                     // : GuiObject
constexpr uintptr_t HorizontalBarRect = 0xA20; // Rect2D
constexpr uintptr_t VerticalBarRect = 0xA30;   // Rect2D
constexpr uintptr_t ScrollRate = 0xA74;        // float
constexpr uintptr_t SmoothScroll = 0xA85;      // bool
constexpr uintptr_t ScrollVelocity = 0xE48;    // Vector2
// AbsoluteCanvasSize                         = ?;   // E0
// AbsoluteWindowSize                         = ?;   // E0
// AutomaticCanvasSize                        = ?;   // E1
// BottomImage                                = ?;   // E2
// BottomImageContent                         = ?;   // E2
// CanvasPosition                             = ?;   // E1
// CanvasSize                                 = ?;   // E2
// DraggingScrollBar                          = ?;   // E1
// ElasticBehavior                            = ?;   // E1
// HorizontalScrollBarInset                   = ?;   // E1
// MaxCanvasPosition                          = ?;   // E1
// MidImage                                   = ?;   // E2
// MidImageContent                            = ?;   // E2
// ScrollBarImageColor3                       = ?;   // E2
// ScrollBarImageTransparency                 = ?;   // E2
// ScrollBarThickness                         = ?;   // E2
// ScrollingDirection                         = ?;   // E1
// ScrollingEnabled                           = ?;   // E2
// TopImage                                   = ?;   // E2
// TopImageContent                            = ?;   // E2
// VerticalScrollBarInset                     = ?;   // E1
// VerticalScrollBarPosition                  = ?;   // E1
} // namespace ScrollingFrame

namespace Seat { // : Part
                 // Disabled                                   = ?;   // E3
                 // Occupant                                   = ?;   // E4
} // namespace Seat

namespace Selection {                                   // : Instance
constexpr uintptr_t ShowActiveInstanceHighlight = 0xCC; // bool
// ActiveInstance                             = ?;   // E4
// RenderMode                                 = ?;   // E1
// SelectionBoxThickness                      = ?;   // E3
// SelectionLineThickness                     = ?;   // E3
// SelectionThickness                         = ?;   // E3
} // namespace Selection

namespace SelectionBox { // : InstanceAdornment
// Adornee                                    = ?;   // E4
// LineThickness                              = ?;   // E3
// StudioSelectionBox                         = ?;   // E3
// SurfaceColor                               = ?;   // E3
// SurfaceColor3                              = ?;   // E3
// SurfaceTransparency                        = ?;   // E3
} // namespace SelectionBox

namespace SelectionPartLasso { // : SelectionLasso
// Part                                       = ?;   // E4
} // namespace SelectionPartLasso

namespace SelectionPointLasso { // : SelectionLasso
// Point                                      = ?;   // E3
} // namespace SelectionPointLasso

namespace SelectionSphere { // : PVAdornment
// SurfaceColor                               = ?;   // E3
// SurfaceColor3                              = ?;   // E3
// SurfaceTransparency                        = ?;   // E3
} // namespace SelectionSphere

namespace Shirt {                                 // : Clothing
constexpr uintptr_t ShirtTemplate = 0x100;        // ContentId
constexpr uintptr_t ShirtTemplateContent = 0x100; // Content
} // namespace Shirt

namespace ShirtGraphic {                   // : CharacterAppearance
constexpr uintptr_t Graphic = 0xD0;        // ContentId
constexpr uintptr_t TextureContent = 0xD0; // Content
// Color3                                     = ?;   // E3
} // namespace ShirtGraphic

namespace SkateboardController { // : Controller
// Steer                                      = ?;   // E3
// Throttle                                   = ?;   // E3
} // namespace SkateboardController

namespace SkateboardPlatform { // : Part
// Controller                                 = ?;   // E4
// ControllingHumanoid                        = ?;   // E4
// MoveState                                  = ?;   // E1
// Steer                                      = ?;   // E3
// StickyWheels                               = ?;   // E3
// Throttle                                   = ?;   // E3
} // namespace SkateboardPlatform

namespace Skin {                      // : CharacterAppearance
constexpr uintptr_t SkinColor = 0xC0; // BrickColor
} // namespace Skin

namespace Sky {                                   // : Instance
constexpr uintptr_t MoonTextureContent = 0xC8;    // Content
constexpr uintptr_t MoonTextureId = 0xC8;         // ContentId
constexpr uintptr_t SkyboxBackContent = 0xF8;     // Content
constexpr uintptr_t SkyboxBk = 0xF8;              // ContentId
constexpr uintptr_t SkyboxDn = 0x128;             // ContentId
constexpr uintptr_t SkyboxDownContent = 0x128;    // Content
constexpr uintptr_t SkyboxFrontContent = 0x158;   // Content
constexpr uintptr_t SkyboxFt = 0x158;             // ContentId
constexpr uintptr_t SkyboxLeftContent = 0x188;    // Content
constexpr uintptr_t SkyboxLf = 0x188;             // ContentId
constexpr uintptr_t SkyboxRightContent = 0x1B8;   // Content
constexpr uintptr_t SkyboxRt = 0x1B8;             // ContentId
constexpr uintptr_t SkyboxUp = 0x1E8;             // ContentId
constexpr uintptr_t SkyboxUpContent = 0x1E8;      // Content
constexpr uintptr_t SunTextureContent = 0x218;    // Content
constexpr uintptr_t SunTextureId = 0x218;         // ContentId
constexpr uintptr_t SkyboxOrientation = 0x238;    // Vector3
constexpr uintptr_t MoonAngularSize = 0x244;      // float
constexpr uintptr_t StarCount = 0x248;            // int
constexpr uintptr_t SunAngularSize = 0x24C;       // float
constexpr uintptr_t CelestialBodiesShown = 0x250; // bool
} // namespace Sky

namespace Smoke {                                     // : Instance
constexpr uintptr_t Color = 0xB8;                     // Color3
constexpr uintptr_t LocalTransparencyModifier = 0xC4; // float
constexpr uintptr_t Opacity = 0xC8;                   // float
constexpr uintptr_t opacity_xml = 0xC8;               // float
constexpr uintptr_t Size = 0xD0;                      // float
constexpr uintptr_t size_xml = 0xD0;                  // float
constexpr uintptr_t TimeScale = 0xD4;                 // float
constexpr uintptr_t Enabled = 0xD8;                   // bool
// RiseVelocity                               = ?;   // E3
// riseVelocity_xml                           = ?;   // E3
} // namespace Smoke

namespace Sound {                                      // : Instance
constexpr uintptr_t AudioContent = 0xC8;               // Content
constexpr uintptr_t SoundId = 0xC8;                    // ContentId
constexpr uintptr_t LoopRegion = 0xF8;                 // NumberRange
constexpr uintptr_t PlaybackRegion = 0x100;            // NumberRange
constexpr uintptr_t Pitch = 0x11C;                     // float
constexpr uintptr_t PlaybackSpeed = 0x11C;             // float
constexpr uintptr_t MaxDistance = 0x120;               // float
constexpr uintptr_t RollOffMaxDistance = 0x120;        // float
constexpr uintptr_t xmlRead_MaxDistance_3 = 0x120;     // float
constexpr uintptr_t EmitterSize = 0x124;               // float
constexpr uintptr_t MinDistance = 0x124;               // float
constexpr uintptr_t RollOffMinDistance = 0x124;        // float
constexpr uintptr_t xmlRead_MinDistance_3 = 0x124;     // float
constexpr uintptr_t Volume = 0x130;                    // float
constexpr uintptr_t AcousticSimulationEnabled = 0x13C; // bool
constexpr uintptr_t Looped = 0x13D;                    // bool
constexpr uintptr_t PlaybackRegionsEnabled = 0x13F;    // bool
constexpr uintptr_t IsPlaying = 0x140;                 // bool
constexpr uintptr_t Playing = 0x140;                   // bool
constexpr uintptr_t PlayingReplicator = 0x140;         // bool
constexpr uintptr_t isPlaying = 0x140;                 // bool
constexpr uintptr_t IsLoaded[] = {
    0x200, 0x0, 0xF0}; // bool, obscured, deref all but the last, then add
constexpr uintptr_t IsSpatial[] = {
    0x200, 0x0, 0xB0}; // bool, obscured, deref all but the last, then add
constexpr uintptr_t PlaybackLoudness[] = {
    0x200, 0x0, 0x20}; // double, obscured, deref all but the last, then add
constexpr uintptr_t RollOffGain[] = {
    0x200, 0x0, 0xC0}; // float, obscured, deref all but the last, then add
constexpr uintptr_t TimeLength[] = {
    0x200, 0x0, 0x98}; // double, obscured, deref all but the last, then add
constexpr uintptr_t TimePosition[] = {
    0x200, 0x0, 0x88}; // double, obscured, deref all but the last, then add
constexpr uintptr_t TimePositionReplicator[] = {
    0x200, 0x0, 0x88}; // double, obscured, deref all but the last, then add
// AssetRepresentation                        = ?;   // E1
// ChannelCount                               = ?;   // E1
// IsPaused                                   = ?;   // E9
// PlayOnRemove                               = ?;   // E3
// RollOffMode                                = ?;   // E1
// SoundGroup                                 = ?;   // E4
// UsageContextPermission                     = ?;   // E1
} // namespace Sound

namespace SoundGroup {             // : Instance
constexpr uintptr_t Volume = 0xB8; // float
} // namespace SoundGroup

namespace SoundService {                                  // : Instance
constexpr uintptr_t ListenerCFrame = 0x120;               // CoordinateFrame
constexpr uintptr_t DistanceFactor = 0x164;               // float
constexpr uintptr_t DopplerScale = 0x168;                 // float
constexpr uintptr_t RolloffScale = 0x170;                 // float
constexpr uintptr_t AcousticSimulationEnabled = 0x178;    // bool
constexpr uintptr_t DiffractionEnabled = 0x179;           // bool
constexpr uintptr_t IsNewExpForAudioApiByDefault = 0x17A; // bool
constexpr uintptr_t OcclusionEnabled = 0x17B;             // bool
constexpr uintptr_t RespectFilteringEnabled = 0x17C;      // bool
constexpr uintptr_t ReverbEnabled = 0x17D;                // bool
// AmbientReverb                              = ?;   // E1
// AudioApiByDefault                          = ?;   // E1
// CharacterSoundsUseNewApi                   = ?;   // E1
// DefaultListenerLocation                    = ?;   // E1
// ListenerObject                             = ?;   // E4
// ListenerType                               = ?;   // E1
// VolumetricAudio                            = ?;   // E1
} // namespace SoundService

namespace Sparkles {                                  // : Instance
constexpr uintptr_t SparkleColor = 0xB8;              // Color3
constexpr uintptr_t LocalTransparencyModifier = 0xC4; // float
constexpr uintptr_t TimeScale = 0xC8;                 // float
constexpr uintptr_t Enabled = 0xCC;                   // bool
// Color                                      = ?;   // E3
} // namespace Sparkles

namespace SpawnLocation {                           // : Part
constexpr uintptr_t Duration = 0x180;               // int
constexpr uintptr_t TeamColor = 0x184;              // BrickColor
constexpr uintptr_t AllowTeamChangeOnTouch = 0x188; // bool
constexpr uintptr_t Enabled = 0x189;                // bool
constexpr uintptr_t Neutral = 0x18A;                // bool
} // namespace SpawnLocation

namespace SpecialMesh { // : FileMesh
// MeshType                                   = ?;   // E1
} // namespace SpecialMesh

namespace SphereHandleAdornment {   // : HandleAdornment
constexpr uintptr_t Radius = 0x1A8; // float
// Shading                                    = ?;   // E1
} // namespace SphereHandleAdornment

namespace SpotLight {             // : Light
constexpr uintptr_t Angle = 0xD8; // float
constexpr uintptr_t Range = 0xE0; // float
// Face                                       = ?;   // E1
} // namespace SpotLight

namespace SpringConstraint {               // : Constraint
constexpr uintptr_t Coils = 0x170;         // float
constexpr uintptr_t Damping = 0x174;       // float
constexpr uintptr_t FreeLength = 0x178;    // float
constexpr uintptr_t MaxForce = 0x17C;      // float
constexpr uintptr_t MaxLength = 0x180;     // float
constexpr uintptr_t Radius = 0x188;        // float
constexpr uintptr_t Stiffness = 0x18C;     // float
constexpr uintptr_t Thickness = 0x190;     // float
constexpr uintptr_t LimitsEnabled = 0x194; // bool
// CurrentLength                              = ?;   // E1
// MinLength                                  = ?;   // E3
} // namespace SpringConstraint

namespace StarterGui { // : BasePlayerGui
// ClipsDescendantsSupportsRotation           = ?;   // E1
// ProcessUserInput                           = ?;   // E3
// ResetPlayerGuiOnSpawn                      = ?;   // E3
// RtlTextSupport                             = ?;   // E1
// ScreenOrientation                          = ?;   // E1
// ShowDevelopmentGui                         = ?;   // E3
// StudioDefaultStyleSheet                    = ?;   // E4
// StudioInsertWidgetLayerCollectorAutoLinkStyleSheet = ?;   // E4
// VirtualCursorMode                          = ?;   // E1
} // namespace StarterGui

namespace StarterPlayer {                                // : Instance
constexpr uintptr_t CameraMaxZoomDistance = 0xCC;        // float
constexpr uintptr_t CameraMinZoomDistance = 0xD0;        // float
constexpr uintptr_t CharacterJumpHeight = 0xD8;          // float
constexpr uintptr_t CharacterMaxSlopeAngle = 0xE0;       // float
constexpr uintptr_t CharacterWalkSpeed = 0xE4;           // float
constexpr uintptr_t HealthDisplayDistance = 0x108;       // float
constexpr uintptr_t NameDisplayDistance = 0x114;         // float
constexpr uintptr_t PlayerModuleStatus = 0x118;          // int
constexpr uintptr_t AllowCustomAnimations = 0x11C;       // bool
constexpr uintptr_t AutoJumpEnabled = 0x11D;             // bool
constexpr uintptr_t CharacterBreakJointsOnDeath = 0x11E; // bool
constexpr uintptr_t CharacterUseJumpPower = 0x11F;       // bool
constexpr uintptr_t ClassicDeath = 0x120;                // bool
constexpr uintptr_t CreateDefaultPlayerModule = 0x121;   // bool
constexpr uintptr_t EnableMouseLockOption = 0x122;       // bool
constexpr uintptr_t UserEmotesEnabled = 0x124;           // bool
// AvatarJointUpgrade                         = ?;   // E1
// AvatarJointUpgrade_SerializedRollout       = ?;   // E1
// CameraMode                                 = ?;   // E1
// CharacterJumpPower                         = ?;   // E3
// DevCameraOcclusionMode                     = ?;   // E1
// DevComputerCameraMovementMode              = ?;   // E1
// DevComputerMovementMode                    = ?;   // E1
// DevTouchCameraMovementMode                 = ?;   // E1
// DevTouchMovementMode                       = ?;   // E1
// EnableDynamicHeads                         = ?;   // E1
// GameSettingsAssetIDFace                    = ?;   // E3
// GameSettingsAssetIDHead                    = ?;   // E3
// GameSettingsAssetIDLeftArm                 = ?;   // E3
// GameSettingsAssetIDLeftLeg                 = ?;   // E3
// GameSettingsAssetIDPants                   = ?;   // E3
// GameSettingsAssetIDRightArm                = ?;   // E3
// GameSettingsAssetIDRightLeg                = ?;   // E3
// GameSettingsAssetIDShirt                   = ?;   // E3
// GameSettingsAssetIDTeeShirt                = ?;   // E3
// GameSettingsAssetIDTorso                   = ?;   // E3
// GameSettingsAvatar                         = ?;   // E1
// GameSettingsR15Collision                   = ?;   // E1
// GameSettingsScaleRangeBodyType             = ?;   // E3
// GameSettingsScaleRangeHead                 = ?;   // E3
// GameSettingsScaleRangeHeight               = ?;   // E3
// GameSettingsScaleRangeProportion           = ?;   // E3
// GameSettingsScaleRangeWidth                = ?;   // E3
// LoadCharacterAppearance                    = ?;   // E3
// LoadCharacterLayeredClothing               = ?;   // E1
// LoadCharacterLayeredClothing_              = ?;   // E1
// LuaCharacterController                     = ?;   // E1
} // namespace StarterPlayer

namespace Stats {                                 // : Instance
constexpr uintptr_t FrameTime = 0x200;            // float
constexpr uintptr_t RenderCPUFrameTime = 0x204;   // float
constexpr uintptr_t RenderGPUFrameTime = 0x208;   // float
constexpr uintptr_t SceneTriangleCount = 0x20C;   // int
constexpr uintptr_t SceneDrawcallCount = 0x210;   // int
constexpr uintptr_t UI2DDrawcallCount = 0x218;    // int
constexpr uintptr_t UI3DTriangleCount = 0x21C;    // int
constexpr uintptr_t UI3DDrawcallCount = 0x220;    // int
constexpr uintptr_t ShadowsTriangleCount = 0x224; // int
constexpr uintptr_t ShadowsDrawcallCount = 0x228; // int
constexpr uintptr_t InstanceCount[] = {
    0x58, 0x20, 0x0, 0x28}; // int, obscured, deref all but the last, then add
// ContactsCount                              = ?;   // E5
// DataReceiveKbps                            = ?;   // E2
// DataSendKbps                               = ?;   // E2
// HeartbeatTime                              = ?;   // E5
// HeartbeatTimeMs                            = ?;   // E9
// MemoryTrackingEnabled                      = ?;   // E9
// MovingPrimitivesCount                      = ?;   // E9
// PhysicsReceiveKbps                         = ?;   // E2
// PhysicsSendKbps                            = ?;   // E9
// PhysicsStepTime                            = ?;   // E5
// PhysicsStepTimeMs                          = ?;   // E5
// PrimitivesCount                            = ?;   // E5
// UI2DTriangleCount                          = ?;   // E9
} // namespace Stats

namespace StatsItem { // : Instance
                      // DisplayName                                = ?;   // E2
} // namespace StatsItem

namespace StringValue {                    // : ValueBase
constexpr uintptr_t Value[] = {0xB8, 0x0}; // string, deref 1, then add
} // namespace StringValue

namespace StudioData {                                        // : Instance
constexpr uintptr_t EnableScriptCollabByDefaultOnLoad = 0xC8; // bool
} // namespace StudioData

namespace StyleDerive {              // : Instance
constexpr uintptr_t Index = 0xC8;    // int
constexpr uintptr_t Priority = 0xCC; // int
// StyleSheet                                 = ?;   // E4
} // namespace StyleDerive

namespace StyleLink { // : Instance
                      // StyleSheet                                 = ?;   // E4
} // namespace StyleLink

namespace StyleRule {                               // : StyleBase
constexpr uintptr_t Priority = 0x174;               // int
constexpr uintptr_t Selector[] = {0x130, 0x0};      // string, deref 1, then add
constexpr uintptr_t SelectorError[] = {0x150, 0x0}; // string, deref 1, then add
// Index                                      = ?;   // E3
// PropertiesSerialize                        = ?;   // E1
// PropertyTransitionsSerialize               = ?;   // E1
} // namespace StyleRule

namespace SunRaysEffect {             // : PostEffect
constexpr uintptr_t Intensity = 0xB8; // float
constexpr uintptr_t Spread = 0xBC;    // float
} // namespace SunRaysEffect

namespace SurfaceAppearance {                   // : Instance
constexpr uintptr_t TexturePack = 0x1B8;        // ContentId
constexpr uintptr_t TexturePackContent = 0x1B8; // Content
constexpr uintptr_t Color = 0x278;              // Color3
constexpr uintptr_t EmissiveTint = 0x284;       // Color3
constexpr uintptr_t EmissiveStrength = 0x294;   // float
// AlphaMode                                  = ?;   // E1
// ColorMap                                   = ?;   // E9
// ColorMapContent                            = ?;   // E1
// EmissiveMaskContent                        = ?;   // E1
// MetalnessMap                               = ?;   // E3
// MetalnessMapContent                        = ?;   // E1
// NormalMap                                  = ?;   // E9
// NormalMapContent                           = ?;   // E1
// ResampleMode                               = ?;   // E1
// RoughnessMap                               = ?;   // E3
// RoughnessMapContent                        = ?;   // E1
} // namespace SurfaceAppearance

namespace SurfaceGui {                                // : SurfaceGuiBase
constexpr uintptr_t ZOffset = 0xC8;                   // float
constexpr uintptr_t AlwaysOnTop = 0x768;              // bool
constexpr uintptr_t LightInfluence = 0x76C;           // float
constexpr uintptr_t Brightness = 0x770;               // float
constexpr uintptr_t CanvasSize = 0x774;               // Vector2
constexpr uintptr_t PixelsPerStud = 0x77C;            // float
constexpr uintptr_t ToolPunchThroughDistance = 0x790; // float
constexpr uintptr_t HorizontalCurvature = 0x838;      // float
constexpr uintptr_t MaxDistance = 0x83C;              // float
// ClipsDescendants                           = ?;   // E2
// Shape                                      = ?;   // E1
// SizingMode                                 = ?;   // E1
} // namespace SurfaceGui

namespace SurfaceLight {          // : Light
constexpr uintptr_t Angle = 0xD8; // float
constexpr uintptr_t Range = 0xE0; // float
// Face                                       = ?;   // E1
} // namespace SurfaceLight

namespace SurfaceSelection { // : PartAdornment
// TargetSurface                              = ?;   // E1
} // namespace SurfaceSelection

namespace SwimController {                   // : ControllerBase
constexpr uintptr_t AccelerationTime = 0xE0; // float
constexpr uintptr_t PitchMaxTorque = 0xE4;   // float
constexpr uintptr_t PitchSpeedFactor = 0xE8; // float
constexpr uintptr_t RollMaxTorque = 0xEC;    // float
constexpr uintptr_t RollSpeedFactor = 0xF0;  // float
} // namespace SwimController

namespace Team {                           // : Instance
constexpr uintptr_t ChildOrder = 0xB0;     // int
constexpr uintptr_t Score = 0xB4;          // int
constexpr uintptr_t TeamColor = 0xB8;      // BrickColor
constexpr uintptr_t AutoAssignable = 0xBC; // bool
// AutoColorCharacters                        = ?;   // E3
} // namespace Team

namespace TeleportOptions { // : Instance
constexpr uintptr_t ReservedServerAccessCode[] = {
    0xB0, 0x0}; // string, deref 1, then add
constexpr uintptr_t ServerInstanceId[] = {0xD0,
                                          0x0}; // string, deref 1, then add
// ShouldReserveServer                        = ?;   // E3
} // namespace TeleportOptions

namespace TeleportService {                      // : Instance
constexpr uintptr_t CustomizedTeleportUI = 0xC8; // bool
} // namespace TeleportService

namespace Terrain {                            // : BasePart
constexpr uintptr_t WaterColor = 0x178;        // Color3
constexpr uintptr_t GrassLength = 0x188;       // float
constexpr uintptr_t WaterReflectance = 0x190;  // float
constexpr uintptr_t WaterTransparency = 0x194; // float
constexpr uintptr_t WaterWaveSize = 0x198;     // float
constexpr uintptr_t WaterWaveSpeed = 0x19C;    // float
constexpr uintptr_t Decoration = 0x1A0;        // bool
// AcquisitionMethod                          = ?;   // E1
// ClusterGrid                                = ?;   // E1
// ClusterGridV2                              = ?;   // E1
// ClusterGridV3                              = ?;   // E1
// IsSmooth                                   = ?;   // E1
// LastUsedModificationMethod                 = ?;   // E1
// MaterialColors                             = ?;   // E1
// Materials                                  = ?;   // E3
// MaxExtents                                 = ?;   // E3
// PhysicsGrid                                = ?;   // E3
// SmoothGrid                                 = ?;   // E3
// SmoothVoxelsUpgraded                       = ?;   // E3
// ValidationAssetContentMap                  = ?;   // E9
// VoxelGridAssetContentMap                   = ?;   // E1
} // namespace Terrain

namespace TestService {                                // : Instance
constexpr uintptr_t ErrorCount = 0xF0;                 // int
constexpr uintptr_t NumberOfPlayers = 0xF4;            // int
constexpr uintptr_t TestCount = 0xF8;                  // int
constexpr uintptr_t WarnCount = 0xFC;                  // int
constexpr uintptr_t Is30FpsThrottleEnabled = 0x104;    // bool
constexpr uintptr_t ThrottlePhysicsToRealtime = 0x104; // bool
constexpr uintptr_t Description[] = {0xC0, 0x0}; // string, deref 1, then add
// AutoRuns                                   = ?;   // E3
// ExecuteWithStudioRun                       = ?;   // E3
// IsPhysicsEnvironmentalThrottled            = ?;   // E3
// IsSleepAllowed                             = ?;   // E3
// SimulateSecondsLag                         = ?;   // E3
// Timeout                                    = ?;   // E3
} // namespace TestService

namespace TextBox {                                         // : GuiObject
constexpr uintptr_t CursorPosition = 0xED4;                 // int
constexpr uintptr_t SelectionStart = 0xEEC;                 // int
constexpr uintptr_t HasFocus = 0xF12;                       // bool
constexpr uintptr_t ManualFocusRelease = 0xF13;             // bool
constexpr uintptr_t OverlayNativeInput = 0xF15;             // bool
constexpr uintptr_t ShouldEmitReturnEvents = 0xF17;         // bool
constexpr uintptr_t ShouldEmitTabEvents = 0xF18;            // bool
constexpr uintptr_t ShouldEmitUpAndDownArrowEvents = 0xF19; // bool
constexpr uintptr_t OpenTypeFeaturesError[] = {
    0xDA8, 0x0}; // string, deref 1, then add
                 // ClearTextOnFocus                           = ?;   // E9
                 // Confidential                               = ?;   // E3
                 // ContentText                                = ?;   // E1
                 // Font                                       = ?;   // E1
                 // FontFace                                   = ?;   // E2
                 // FontSize                                   = ?;   // E1
                 // LineHeight                                 = ?;   // E2
                 // LocalizationMatchIdentifier                = ?;   // E1
                 // LocalizationMatchedSourceText              = ?;   // E1
                 // LocalizedPlaceholderText                   = ?;   // E1
                 // MaxVisibleGraphemes                        = ?;   // E2
                 // MultiLine                                  = ?;   // E2
                 // OpenTypeFeatures                           = ?;   // E9
                 // PlaceholderColor3                          = ?;   // E9
                 // PlaceholderText                            = ?;   // E2
                 // ReturnKeyType                              = ?;   // E1
                 // RichText                                   = ?;   // E2
                 // ShowNativeInput                            = ?;   // E2
                 // Text                                       = ?;   // E2
                 // TextBounds                                 = ?;   // E2
                 // TextColor                                  = ?;   // E2
                 // TextColor3                                 = ?;   // E2
                 // TextDirection                              = ?;   // E1
                 // TextEditable                               = ?;   // E9
                 // TextFits                                   = ?;   // E2
                 // TextInputType                              = ?;   // E1
                 // TextScaled                                 = ?;   // E2
                 // TextSize                                   = ?;   // E2
                 // TextStrokeColor3                           = ?;   // E2
                 // TextStrokeTransparency                     = ?;   // E2
                 // TextTransparency                           = ?;   // E2
                 // TextTruncate                               = ?;   // E1
                 // TextWrap                                   = ?;   // E2
                 // TextWrapped                                = ?;   // E2
                 // TextXAlignment                             = ?;   // E1
                 // TextYAlignment                             = ?;   // E1
} // namespace TextBox

namespace TextButton {                     // : GuiButton
constexpr uintptr_t Confidential = 0x115C; // bool
constexpr uintptr_t OpenTypeFeaturesError[] = {
    0x1030, 0x0}; // string, deref 1, then add
                  // ContentText                                = ?;   // E1
                  // Font                                       = ?;   // E1
                  // FontFace                                   = ?;   // E2
                  // FontSize                                   = ?;   // E1
                  // LineHeight                                 = ?;   // E2
                  // LocalizationMatchIdentifier                = ?;   // E1
                  // LocalizationMatchedSourceText              = ?;   // E1
                  // LocalizedText                              = ?;   // E3
                  // MaxVisibleGraphemes                        = ?;   // E2
                  // OpenTypeFeatures                           = ?;   // E2
                  // RichText                                   = ?;   // E2
                  // Text                                       = ?;   // E2
                  // TextBounds                                 = ?;   // E2
                  // TextColor                                  = ?;   // E2
                  // TextColor3                                 = ?;   // E2
                  // TextDirection                              = ?;   // E1
                  // TextFits                                   = ?;   // E2
                  // TextScaled                                 = ?;   // E2
                  // TextSize                                   = ?;   // E2
                  // TextStrokeColor3                           = ?;   // E2
                  // TextStrokeTransparency                     = ?;   // E2
                  // TextTransparency                           = ?;   // E2
                  // TextTruncate                               = ?;   // E1
                  // TextWrap                                   = ?;   // E2
                  // TextWrapped                                = ?;   // E2
                  // TextXAlignment                             = ?;   // E1
                  // TextYAlignment                             = ?;   // E1
} // namespace TextButton

namespace TextChannel { // : Instance
// DirectChatRequester                        = ?;   // E4
} // namespace TextChannel

namespace TextChatCommand {                         // : Instance
constexpr uintptr_t PrimaryAlias[] = {0xB0, 0x0};   // string, deref 1, then add
constexpr uintptr_t SecondaryAlias[] = {0xD0, 0x0}; // string, deref 1, then add
// AutocompleteVisible                        = ?;   // E3
// Enabled                                    = ?;   // E3
} // namespace TextChatCommand

namespace TextChatMessageProperties { // : Instance
// PrefixText                                 = ?;   // E3
// Text                                       = ?;   // E3
// Translation                                = ?;   // E3
} // namespace TextChatMessageProperties

namespace TextChatService {                            // : Instance
constexpr uintptr_t CreateDefaultTextChannels = 0x1F4; // bool
constexpr uintptr_t HasSeenDeprecationDialog = 0x1F5;  // bool
constexpr uintptr_t IsLegacyChatDisabled = 0x1F6;      // bool
// ChatTranslationEnabled                     = ?;   // E3
// ChatTranslationFTUXShown                   = ?;   // E3
// ChatTranslationToggleEnabled               = ?;   // E3
// ChatVersion                                = ?;   // E1
// CreateDefaultCommands                      = ?;   // E3
// PlatformIntegratedChat                     = ?;   // E1
} // namespace TextChatService

namespace TextLabel {                     // : GuiLabel
constexpr uintptr_t Confidential = 0xEDC; // bool
constexpr uintptr_t OpenTypeFeaturesError[] = {
    0xDB0, 0x0}; // string, deref 1, then add
                 // ContentText                                = ?;   // E1
                 // Font                                       = ?;   // E1
                 // FontFace                                   = ?;   // E2
                 // FontSize                                   = ?;   // E1
                 // LineHeight                                 = ?;   // E2
                 // LocalizationMatchIdentifier                = ?;   // E1
                 // LocalizationMatchedSourceText              = ?;   // E1
                 // LocalizedText                              = ?;   // E3
                 // MaxVisibleGraphemes                        = ?;   // E2
                 // OpenTypeFeatures                           = ?;   // E2
                 // RichText                                   = ?;   // E9
                 // Text                                       = ?;   // E2
                 // TextBounds                                 = ?;   // E2
                 // TextColor                                  = ?;   // E2
                 // TextColor3                                 = ?;   // E9
                 // TextDirection                              = ?;   // E1
                 // TextFits                                   = ?;   // E2
                 // TextScaled                                 = ?;   // E2
                 // TextSize                                   = ?;   // E2
                 // TextStrokeColor3                           = ?;   // E2
                 // TextStrokeTransparency                     = ?;   // E2
                 // TextTransparency                           = ?;   // E2
                 // TextTruncate                               = ?;   // E1
                 // TextWrap                                   = ?;   // E2
                 // TextWrapped                                = ?;   // E2
                 // TextXAlignment                             = ?;   // E1
                 // TextYAlignment                             = ?;   // E1
} // namespace TextLabel

namespace TextSource {                           // : Instance
constexpr uintptr_t UserId = 0xF0;               // int64
constexpr uintptr_t UserIdReplicated = 0xF0;     // int64
constexpr uintptr_t CanSend = 0xF8;              // bool
constexpr uintptr_t DisplayName[] = {0xB0, 0x0}; // string, deref 1, then add
constexpr uintptr_t Username[] = {0xD0, 0x0};    // string, deref 1, then add
} // namespace TextSource

namespace Texture {                        // : Decal
constexpr uintptr_t OffsetStudsU = 0x270;  // float
constexpr uintptr_t OffsetStudsV = 0x274;  // float
constexpr uintptr_t StudsPerTileU = 0x278; // float
constexpr uintptr_t StudsPerTileV = 0x27C; // float
} // namespace Texture

namespace ThirdPartyUserService {         // : Instance
constexpr uintptr_t HasActiveUser = 0xC8; // bool
// FriendCommunicationRestrictionStatus       = ?;   // E1
// VoiceChatRestrictionStatus                 = ?;   // E1
} // namespace ThirdPartyUserService

namespace Tool {                                  // : BackpackItem
constexpr uintptr_t CanBeDropped = 0x4B8;         // bool
constexpr uintptr_t Enabled = 0x4B9;              // bool
constexpr uintptr_t ManualActivationOnly = 0x4BA; // bool
constexpr uintptr_t ToolTip[] = {0x468, 0x0};     // string, deref 1, then add
// Grip                                       = ?;   // E3
// GripForward                                = ?;   // E3
// GripPos                                    = ?;   // E3
// GripRight                                  = ?;   // E3
// GripUp                                     = ?;   // E3
// RequiresHandle                             = ?;   // E3
// TextureContent                             = ?;   // E3
// TextureId                                  = ?;   // E3
} // namespace Tool

namespace Torque {                  // : Constraint
constexpr uintptr_t Torque = 0x170; // Vector3
// RelativeTo                                 = ?;   // E1
} // namespace Torque

namespace TorsionSpringConstraint {    // : Constraint
constexpr uintptr_t Coils = 0x170;     // float
constexpr uintptr_t Damping = 0x174;   // float
constexpr uintptr_t MaxAngle = 0x178;  // float
constexpr uintptr_t MaxTorque = 0x17C; // float
constexpr uintptr_t Radius = 0x180;    // float
constexpr uintptr_t Stiffness = 0x188; // float
// CurrentAngle                               = ?;   // E3
// LimitEnabled                               = ?;   // E3
// LimitsEnabled                              = ?;   // E3
// Restitution                                = ?;   // E3
} // namespace TorsionSpringConstraint

namespace TrackerLodController { // : Instance
// AudioMode                                  = ?;   // E1
// VideoExtrapolationMode                     = ?;   // E1
// VideoLodMode                               = ?;   // E1
// VideoMode                                  = ?;   // E1
} // namespace TrackerLodController

namespace Trail {                                      // : Instance
constexpr uintptr_t Texture = 0x180;                   // ContentId
constexpr uintptr_t TextureContent = 0x180;            // Content
constexpr uintptr_t Brightness = 0x1C0;                // float
constexpr uintptr_t Lifetime = 0x1C4;                  // float
constexpr uintptr_t LightEmission = 0x1C8;             // float
constexpr uintptr_t LightInfluence = 0x1CC;            // float
constexpr uintptr_t LocalTransparencyModifier = 0x1D0; // float
constexpr uintptr_t MaxLength = 0x1D4;                 // float
constexpr uintptr_t MinLength = 0x1D8;                 // float
constexpr uintptr_t TextureLength = 0x1DC;             // float
constexpr uintptr_t Enabled = 0x1E4;                   // bool
constexpr uintptr_t FaceCamera = 0x1E5;                // bool
// Attachment0                                = ?;   // E4
// Attachment1                                = ?;   // E4
// Color                                      = ?;   // E3
// TextureMode                                = ?;   // E1
// Transparency                               = ?;   // E3
// WidthScale                                 = ?;   // E3
} // namespace Trail

namespace TremoloSoundEffect {        // : SoundEffect
constexpr uintptr_t Depth = 0xE8;     // float
constexpr uintptr_t Duty = 0xEC;      // float
constexpr uintptr_t Frequency = 0xF0; // float
} // namespace TremoloSoundEffect

namespace TrussPart { // : BasePart
                      // Style                                      = ?;   // E1
                      // style                                      = ?;   // E1
} // namespace TrussPart

namespace Tween { // : TweenBase
                  // Instance                                   = ?;   // E4
                  // PlaybackState                              = ?;   // E1
                  // TweenInfo                                  = ?;   // E3
} // namespace Tween

namespace UIAspectRatioConstraint { // : UIConstraint
// AspectRatio                                = ?;   // E2
// AspectType                                 = ?;   // E1
// DominantAxis                               = ?;   // E1
} // namespace UIAspectRatioConstraint

namespace UICorner { // : UIComponent
                     // BottomLeftRadius                           = ?;   // E3
                     // BottomRightRadius                          = ?;   // E3
                     // CornerRadius                               = ?;   // E3
                     // TopLeftRadius                              = ?;   // E3
                     // TopRightRadius                             = ?;   // E3
} // namespace UICorner

namespace UIDragDetector {                            // : UIComponent
constexpr uintptr_t DragRotation = 0x1B8;             // float
constexpr uintptr_t MaxDragAngle = 0x1C4;             // float
constexpr uintptr_t MinDragAngle = 0x1C8;             // float
constexpr uintptr_t SelectionModeRotateSpeed = 0x1D0; // float
constexpr uintptr_t Enabled = 0x1D8;                  // bool
// ActivatedCursorIcon                        = ?;   // E3
// ActivatedCursorIconContent                 = ?;   // E3
// BoundingBehavior                           = ?;   // E1
// BoundingUI                                 = ?;   // E4
// CursorIcon                                 = ?;   // E3
// CursorIconContent                          = ?;   // E3
// DragAxis                                   = ?;   // E3
// DragRelativity                             = ?;   // E1
// DragSpace                                  = ?;   // E1
// DragStyle                                  = ?;   // E1
// DragUDim2                                  = ?;   // E3
// MaxDragTranslation                         = ?;   // E3
// MinDragTranslation                         = ?;   // E3
// ReferenceUIInstance                        = ?;   // E4
// ResponseStyle                              = ?;   // E1
// SelectionModeDragSpeed                     = ?;   // E3
// UIDragSpeedAxisMapping                     = ?;   // E1
} // namespace UIDragDetector

namespace UIFlexItem { // : UIComponent
// FlexMode                                   = ?;   // E1
// GrowRatio                                  = ?;   // E2
// ItemLineAlignment                          = ?;   // E1
// ShrinkRatio                                = ?;   // E2
} // namespace UIFlexItem

namespace UIGradient { // : UIComponent
// Color                                      = ?;   // E2
// Enabled                                    = ?;   // E2
// Offset                                     = ?;   // E3
// Rotation                                   = ?;   // E2
// Scale                                      = ?;   // E2
// TileMode                                   = ?;   // E1
// Transparency                               = ?;   // E2
// Type                                       = ?;   // E1
} // namespace UIGradient

namespace UIGridLayout { // : UIGridStyleLayout
// AbsoluteCellCount                          = ?;   // E3
// AbsoluteCellSize                           = ?;   // E3
// CellPadding                                = ?;   // E3
// CellSize                                   = ?;   // E3
// FillDirectionMaxCells                      = ?;   // E3
// StartCorner                                = ?;   // E1
} // namespace UIGridLayout

namespace UIListLayout { // : UIGridStyleLayout
// HorizontalFlex                             = ?;   // E1
// HorizontalPadding                          = ?;   // E3
// ItemLineAlignment                          = ?;   // E1
// Padding                                    = ?;   // E3
// VerticalFlex                               = ?;   // E1
// VerticalPadding                            = ?;   // E3
// Wraps                                      = ?;   // E3
} // namespace UIListLayout

namespace UIPadding { // : UIComponent
                      // PaddingBottom                              = ?;   // E3
                      // PaddingLeft                                = ?;   // E3
                      // PaddingRight                               = ?;   // E3
                      // PaddingTop                                 = ?;   // E3
} // namespace UIPadding

namespace UIPageLayout { // : UIGridStyleLayout
// Animated                                   = ?;   // E3
// Circular                                   = ?;   // E3
// CurrentPage                                = ?;   // E4
// EasingDirection                            = ?;   // E1
// EasingStyle                                = ?;   // E1
// GamepadInputEnabled                        = ?;   // E3
// Padding                                    = ?;   // E3
// ScrollWheelInputEnabled                    = ?;   // E3
// TouchInputEnabled                          = ?;   // E3
// TweenTime                                  = ?;   // E3
} // namespace UIPageLayout

namespace UIScale { // : UIComponent
                    // Scale                                      = ?;   // E2
} // namespace UIScale

namespace UISizeConstraint { // : UIConstraint
// MaxSize                                    = ?;   // E3
// MinSize                                    = ?;   // E3
} // namespace UISizeConstraint

namespace UIStroke { // : UIComponent
                     // ApplyStrokeMode                            = ?;   // E1
                     // BorderOffset                               = ?;   // E3
                     // BorderStrokePosition                       = ?;   // E1
                     // Color                                      = ?;   // E3
                     // Enabled                                    = ?;   // E2
                     // LineJoinMode                               = ?;   // E1
                     // StrokeSizingMode                           = ?;   // E1
                     // Thickness                                  = ?;   // E2
                     // Transparency                               = ?;   // E2
                     // ZIndex                                     = ?;   // E2
} // namespace UIStroke

namespace UITableLayout { // : UIGridStyleLayout
// FillEmptySpaceColumns                      = ?;   // E3
// FillEmptySpaceRows                         = ?;   // E3
// MajorAxis                                  = ?;   // E1
// Padding                                    = ?;   // E3
} // namespace UITableLayout

namespace UITextSizeConstraint { // : UIConstraint
// MaxTextSize                                = ?;   // E2
// MinTextSize                                = ?;   // E2
} // namespace UITextSizeConstraint

namespace UnionOperation {                  // : PartOperation
constexpr uintptr_t InitialSize = 0x1D0;    // Vector3
constexpr uintptr_t AssetId = 0x2A8;        // ContentId
constexpr uintptr_t Content = 0x2A8;        // Content
constexpr uintptr_t ComponentIndex = 0x340; // int
constexpr uintptr_t SmoothingAngle = 0x348; // float
constexpr uintptr_t TriangleCount = 0x34C;  // int
constexpr uintptr_t OffCentered = 0x350;    // bool
constexpr uintptr_t UsePartColor = 0x351;   // bool
// ChildData                                  = ?;   // E1
// ChildData2                                 = ?;   // E1
// DCDPropertyData                            = ?;   // E1
// FormFactor                                 = ?;   // E1
// ManifoldMesh_DEPRECATED                    = ?;   // E3
// MeshData                                   = ?;   // E1
// MeshData2                                  = ?;   // E1
// PhysicsData                                = ?;   // E1
// RenderFidelity                             = ?;   // E1
// SolidMeshHolder                            = ?;   // E3
} // namespace UnionOperation

namespace UniversalConstraint {            // : Constraint
constexpr uintptr_t MaxAngle = 0x170;      // float
constexpr uintptr_t Radius = 0x174;        // float
constexpr uintptr_t Restitution = 0x178;   // float
constexpr uintptr_t LimitsEnabled = 0x17C; // bool
} // namespace UniversalConstraint

namespace UserInputService {                         // : Instance
constexpr uintptr_t BottomBarSize = 0xC8;            // Vector2
constexpr uintptr_t NavBarSize = 0xD0;               // Vector2
constexpr uintptr_t RightBarSize = 0xD8;             // Vector2
constexpr uintptr_t StatusBarSize = 0xE0;            // Vector2
constexpr uintptr_t LegacyInputEventsEnabled = 0xF0; // bool
constexpr uintptr_t TouchScreenEnabled = 0xF3;       // bool
// AccelerometerEnabled                       = ?;   // E9
// GamepadEnabled                             = ?;   // E5
// GyroscopeEnabled                           = ?;   // E5
// KeyboardEnabled                            = ?;   // E5
// ModalEnabled                               = ?;   // E5
// MouseBehavior                              = ?;   // E1
// MouseDeltaSensitivity                      = ?;   // E5
// MouseEnabled                               = ?;   // E5
// MouseIcon                                  = ?;   // E5
// MouseIconContent                           = ?;   // E5
// MouseIconEnabled                           = ?;   // E5
// OnScreenKeyboardAnimationDuration          = ?;   // E9
// OnScreenKeyboardPosition                   = ?;   // E5
// OnScreenKeyboardSize                       = ?;   // E5
// OnScreenKeyboardVisible                    = ?;   // E5
// OverrideMouseIconBehavior                  = ?;   // E1
// PreferredInput                             = ?;   // E1
// TouchEnabled                               = ?;   // E5
// UserHeadCFrame                             = ?;   // E5
// VREnabled                                  = ?;   // E5
} // namespace UserInputService

namespace VRService {                                // : Instance
constexpr uintptr_t QuestDisplayRefreshRate = 0x128; // float
constexpr uintptr_t AvatarGestures = 0x130;          // bool
constexpr uintptr_t DidPointerHit = 0x131;           // bool
constexpr uintptr_t FadeOutViewOnCollision = 0x132;  // bool
constexpr uintptr_t QuestASWState = 0x133;           // bool
constexpr uintptr_t VRDeviceAvailable = 0x134;       // bool
constexpr uintptr_t VREnabled = 0x135;               // bool
// AutomaticScaling                           = ?;   // E1
// ControllerModels                           = ?;   // E1
// GuiInputUserCFrame                         = ?;   // E1
// LaserDistance                              = ?;   // E5
// LaserPointer                               = ?;   // E1
// PointerHitCFrame                           = ?;   // E1
// ThirdPersonFollowCamEnabled                = ?;   // E3
// VRDeviceName                               = ?;   // E1
// VRSessionState                             = ?;   // E1
} // namespace VRService

namespace Vector3Value {          // : ValueBase
constexpr uintptr_t Value = 0xB8; // Vector3
} // namespace Vector3Value

namespace VectorForce {                          // : Constraint
constexpr uintptr_t Force = 0x170;               // Vector3
constexpr uintptr_t ApplyAtCenterOfMass = 0x180; // bool
// RelativeTo                                 = ?;   // E1
} // namespace VectorForce

namespace VehicleSeat {                        // : BasePart
constexpr uintptr_t Disabled = 0x1B8;          // bool
constexpr uintptr_t MaxSpeed = 0x1C8;          // float
constexpr uintptr_t Steer = 0x1CC;             // int
constexpr uintptr_t SteerFloat = 0x1D0;        // float
constexpr uintptr_t Throttle = 0x1D4;          // int
constexpr uintptr_t ThrottleFloat = 0x1D8;     // float
constexpr uintptr_t TurnSpeed = 0x1E0;         // float
constexpr uintptr_t AreHingesDetected = 0x304; // int
// HeadsUpDisplay                             = ?;   // E3
// Occupant                                   = ?;   // E4
// Torque                                     = ?;   // E3
} // namespace VehicleSeat

namespace VelocityMotor {                           // : JointInstance
constexpr uintptr_t CurrentAngle[] = {0x180, 0xD8}; // float, deref 1, then add
constexpr uintptr_t DesiredAngle[] = {0x180, 0xF0}; // float, deref 1, then add
constexpr uintptr_t MaxVelocity[] = {0x180, 0xEC};  // float, deref 1, then add
// Hole                                       = ?;   // E4
} // namespace VelocityMotor

namespace VideoCaptureService {               // : Instance
constexpr uintptr_t CameraID[] = {0xC8, 0x0}; // string, deref 1, then add
// Active                                     = ?;   // E3
} // namespace VideoCaptureService

namespace VideoDisplay {                       // : GuiObject
constexpr uintptr_t TileSize = 0x9F8;          // UDim2
constexpr uintptr_t VideoColor3 = 0xA08;       // Color3
constexpr uintptr_t VideoRectOffset = 0xA14;   // Vector2
constexpr uintptr_t VideoRectSize = 0xA1C;     // Vector2
constexpr uintptr_t VideoTransparency = 0xA2C; // float
// ResampleMode                               = ?;   // E1
// ScaleType                                  = ?;   // E1
} // namespace VideoDisplay

namespace VideoFrame {                               // : GuiObject
constexpr uintptr_t Video = 0x988;                   // ContentId
constexpr uintptr_t TimePosition = 0x9D8;            // double
constexpr uintptr_t TimePositionReplicating = 0x9D8; // double
constexpr uintptr_t RollOffMaxDistance = 0x9E8;      // float
constexpr uintptr_t RollOffMinDistance = 0x9EC;      // float
constexpr uintptr_t Volume = 0x9F4;                  // float
constexpr uintptr_t IsLoaded[] = {
    0xA68, 0x0, 0x108}; // bool, obscured, deref all but the last, then add
constexpr uintptr_t Resolution[] = {
    0xA68, 0x0, 0x108}; // Vector2, obscured, deref all but the last, then add
constexpr uintptr_t TimeLength[] = {
    0xA68, 0x0, 0x118}; // double, obscured, deref all but the last, then add
// InternalVideoUsage                         = ?;   // E1
// Looped                                     = ?;   // E3
// MaximumResolution                          = ?;   // E1
// Playing                                    = ?;   // E3
// PlayingReplicating                         = ?;   // E3
// RollOffMode                                = ?;   // E1
// VideoContent                               = ?;   // E1
} // namespace VideoFrame

namespace VideoPlayer {                         // : Instance
constexpr uintptr_t TimePosition = 0x158;       // double
constexpr uintptr_t PlaybackSpeed = 0x168;      // float
constexpr uintptr_t Volume = 0x16C;             // float
constexpr uintptr_t PlayingReplicating = 0x170; // bool
// AutoLoadInStudio                           = ?;   // E3
// AutoPlayInStudio                           = ?;   // E3
// InternalVideoUsage                         = ?;   // E1
// IsLoaded                                   = ?;   // E3
// IsPlaying                                  = ?;   // E3
// Looping                                    = ?;   // E3
// MaximumResolution                          = ?;   // E1
// Resolution                                 = ?;   // E3
// TimeLength                                 = ?;   // E3
// VideoContent                               = ?;   // E1
} // namespace VideoPlayer

namespace ViewportFrame {                      // : GuiObject
constexpr uintptr_t CameraFieldOfView = 0x9F0; // float
// Ambient                                    = ?;   // E2
// CameraCFrame                               = ?;   // E3
// CurrentCamera                              = ?;   // E4
// ImageColor3                                = ?;   // E9
// ImageTransparency                          = ?;   // E3
// IsMirrored                                 = ?;   // E3
// LightColor                                 = ?;   // E3
// LightDirection                             = ?;   // E3
} // namespace ViewportFrame

namespace VisualizationMode {                // : Instance
constexpr uintptr_t Title[] = {0xB0, 0x0};   // string, deref 1, then add
constexpr uintptr_t ToolTip[] = {0xD0, 0x0}; // string, deref 1, then add
// Enabled                                    = ?;   // E3
} // namespace VisualizationMode

namespace VisualizationModeCategory {      // : Instance
constexpr uintptr_t Enabled = 0xD0;        // bool
constexpr uintptr_t Title[] = {0xB0, 0x0}; // string, deref 1, then add
} // namespace VisualizationModeCategory

namespace VoiceChatService {                                  // : Instance
constexpr uintptr_t EnableDefaultVoice = 0x1F4;               // bool
constexpr uintptr_t UseNewAudioApi = 0x1F5;                   // bool
constexpr uintptr_t UseNewControlPaths = 0x1F6;               // bool
constexpr uintptr_t UseNewJoinFlow = 0x1F7;                   // bool
constexpr uintptr_t UseStreamSwitching = 0x1F8;               // bool
constexpr uintptr_t VoiceChatEnabledForUniverseOnRcc = 0x1FA; // bool
// DefaultDistanceAttenuation                 = ?;   // E1
// EnableVoiceVolumeControls                  = ?;   // E1
// UseAudioApi                                = ?;   // E1
// VoiceChatEnabledForPlaceOnRcc              = ?;   // E3
} // namespace VoiceChatService

namespace Weld {                            // : JointInstance
constexpr uintptr_t EnableSkinning = 0x188; // bool
} // namespace Weld

namespace WeldConstraint {          // : Instance
constexpr uintptr_t Enabled = 0xD8; // bool
constexpr uintptr_t State = 0x118;  // int
constexpr uintptr_t Active[] = {
    0xE8, 0x10, 0x8}; // bool, obscured, deref all but the last, then add
constexpr uintptr_t CFrame0[] = {0xE8,
                                 0x38}; // CoordinateFrame, deref 1, then add
constexpr uintptr_t CFrame1[] = {0xE8,
                                 0x68}; // CoordinateFrame, deref 1, then add
// Part0                                      = ?;   // E4
// Part0Internal                              = ?;   // E4
// Part1                                      = ?;   // E4
// Part1Internal                              = ?;   // E4
} // namespace WeldConstraint

namespace Wire { // : Instance
                 // Connected                                  = ?;   // E0
                 // SourceInstance                             = ?;   // E4
                 // SourceName                                 = ?;   // E1
                 // TargetInstance                             = ?;   // E4
                 // TargetName                                 = ?;   // E1
} // namespace Wire

namespace WireframeHandleAdornment {   // : HandleAdornment
constexpr uintptr_t Scale = 0x1A8;     // Vector3
constexpr uintptr_t Thickness = 0x1B4; // float
} // namespace WireframeHandleAdornment

namespace Workspace {                               // : WorldRoot
constexpr uintptr_t InsertPoint = 0x3B8;            // Vector3
constexpr uintptr_t TerrainWeldsFixed = 0x3F8;      // bool
constexpr uintptr_t DistributedGameTime = 0x4B8;    // double
constexpr uintptr_t AirTurbulenceIntensity = 0x4C0; // float
constexpr uintptr_t StreamingMinRadius = 0x538;     // int
constexpr uintptr_t StreamingTargetRadius = 0x53C;  // int
constexpr uintptr_t ThrottleLevel = 0x540;          // int
constexpr uintptr_t AllowThirdPartySales = 0x554;   // bool
constexpr uintptr_t ConvexDecompCompressed = 0x555; // bool
constexpr uintptr_t FallHeightEnabled = 0x556;      // bool
constexpr uintptr_t StreamingEnabled = 0x557;       // bool
constexpr uintptr_t StreamingEnabledAlias = 0x557;  // bool
constexpr uintptr_t AirDensity[] = {
    0x3F0, 0x218, 0x18}; // float, deref all but the last, then add
constexpr uintptr_t CollisionGroupData[] = {
    0x3F0, 0x3E0}; // BinaryString, deref 1, then add
constexpr uintptr_t ExplicitAutoJoints[] = {0x3F0,
                                            0x399}; // bool, deref 1, then add
constexpr uintptr_t FallenPartsDestroyHeight[] = {
    0x3F0, 0x208}; // float, deref 1, then add
constexpr uintptr_t GlobalWind[] = {
    0x3F0, 0x218, 0x3C}; // Vector3, deref all but the last, then add
constexpr uintptr_t Gravity[] = {0x3F0, 0x210}; // float, deref 1, then add
constexpr uintptr_t PhysicsStepTime[] = {0x3F0,
                                         0x200};    // float, deref 1, then add
constexpr uintptr_t WatermarkHash[] = {0x468, 0x0}; // string, deref 1, then add
// AuthorityMode                              = ?;   // E1
// AvatarUnificationMode                      = ?;   // E1
// ClientAnimatorThrottling                   = ?;   // E1
// CollisionGroups                            = ?;   // E1
// CurrentCamera                              = ?;   // E4
// DataModelPlaceVersion                      = ?;   // E9
// EnableSLIMAvatars                          = ?;   // E1
// FilteringEnabled                           = ?;   // E1
// FluidForces                                = ?;   // E1
// IKControlConstraintSupport                 = ?;   // E1
// ImprovedAnimationConstraint                = ?;   // E1
// ImprovedPhysicsReplication                 = ?;   // E1
// InterpolationThrottling                    = ?;   // E1
// LayeredClothingCacheOptimizations          = ?;   // E1
// LuauTypeCheckMode                          = ?;   // E1
// MeshPartHeadsAndAccessories                = ?;   // E1
// MeshStreamingAndImprovedLods               = ?;   // E1
// ModelStreamingBehavior                     = ?;   // E1
// NextGenerationReplication                  = ?;   // E1
// NextGenerationReplicationAlias             = ?;   // E1
// PathfindingUseImprovedSearch               = ?;   // E1
// PhysicsSteppingMethod                      = ?;   // E1
// PlayerCharacterDestroyBehavior             = ?;   // E1
// PlayerScriptsUseInputActionSystem          = ?;   // E1
// PlayerScriptsUseInputActionSystemAlias     = ?;   // E1
// PredictiveStreamingMode                    = ?;   // E1
// PrimalPhysicsSolver                        = ?;   // E1
// RejectCharacterDeletions                   = ?;   // E1
// RenderingCacheOptimizations                = ?;   // E1
// ReplicateInstanceDestroySetting            = ?;   // E1
// Retargeting                                = ?;   // E1
// SandboxedInstanceMode                      = ?;   // E1
// SignalBehavior                             = ?;   // E1
// SignalBehavior2                            = ?;   // E1
// SignalBehaviorAlias                        = ?;   // E1
// StreamOutBehavior                          = ?;   // E1
// StreamingIntegrityMode                     = ?;   // E1
// StreamingPauseMode                         = ?;   // E1
// Terrain                                    = ?;   // E4
// TouchEventsUseCollisionGroups              = ?;   // E1
// TouchesUseCollisionGroups                  = ?;   // E9
// UseFixedSimulation                         = ?;   // E1
// UseFixedSimulationAlias                    = ?;   // E1
// UseNewLuauTypeSolver                       = ?;   // E1
// ValidateEnabledProximityPrompt             = ?;   // E1
} // namespace Workspace

namespace WrapTarget {                                // : BaseWrap
constexpr uintptr_t CageOriginWorld = 0x68;           // CoordinateFrame
constexpr uintptr_t ImportOriginWorld = 0x68;         // CoordinateFrame
constexpr uintptr_t CageMeshId = 0xC8;                // ContentId
constexpr uintptr_t HSRAssetId = 0xF8;                // ContentId
constexpr uintptr_t HSRContent = 0xF8;                // Content
constexpr uintptr_t TemporaryCageMeshContent = 0x128; // Content
constexpr uintptr_t TemporaryCageMeshId = 0x128;      // ContentId
constexpr uintptr_t ImportInProcess = 0x1C0;          // bool
constexpr uintptr_t Stiffness = 0x2B0;                // float
// CageMeshContent                            = ?;   // E1
// CageOrigin                                 = ?;   // E1
// Color                                      = ?;   // E1
// DebugMode                                  = ?;   // E1
// HSRData                                    = ?;   // E1
// HSRMeshIdData                              = ?;   // E1
// ImportOrigin                               = ?;   // E1
} // namespace WrapTarget

namespace WrapTextureTransfer { // : Instance
// ReferenceCageMeshContent                   = ?;   // E1
// UVMaxBound                                 = ?;   // E3
// UVMinBound                                 = ?;   // E3
} // namespace WrapTextureTransfer

} // namespace Offsets
