#pragma once

#include <cstdint>
#include <string>

#include "offsets/offsets_structured_latest.hpp"

namespace Offsets
{
	inline std::string clientVersion{ ::ClientVersion };

	inline uintptr_t Adornee{ offsets::Highlight::Adornee };
	inline uintptr_t Anchored{ offsets::Primitive::PrimitiveFlags };
	inline uintptr_t AnchoredMask{ offsets::PrimitiveFlags::AnchoredMask };
	inline uintptr_t AnimationId{ offsets::Animation::AnimationId };
	inline uintptr_t BeamBrightness{ offsets::Beam::Brightness };
	inline uintptr_t BeamColor{ offsets::Beam::Color };
	inline uintptr_t BeamLightEmission{ offsets::Beam::LightEmission };
	inline uintptr_t BeamLightInfuence{ offsets::Beam::LightInfluence };
	inline uintptr_t CFrame{ offsets::Primitive::CFrame };
	inline uintptr_t Camera{ offsets::Workspace::Camera };
	inline uintptr_t CameraMaxZoomDistance{ offsets::Player::MaxZoomDistance };
	inline uintptr_t CameraMinZoomDistance{ offsets::Player::MinZoomDistance };
	inline uintptr_t CameraMode{ offsets::Player::CameraMode };
	inline uintptr_t CameraPos{ offsets::Camera::Position };
	inline uintptr_t CameraRotation{ offsets::Camera::Rotation };
	inline uintptr_t CameraSubject{ offsets::Camera::Subject };
	inline uintptr_t CameraType{ offsets::Camera::Type };
	inline uintptr_t CanCollide{ offsets::Primitive::PrimitiveFlags };
	inline uintptr_t CanCollideMask{ offsets::PrimitiveFlags::CanCollideMask };
	inline uintptr_t CanTouchMask{ offsets::PrimitiveFlags::CanTouchMask };
	inline uintptr_t Children{ offsets::Instance::Children };
	inline uintptr_t ChildrenEnd{ offsets::Instance::ChildrenSize };
	inline uintptr_t ClassDescriptor{ offsets::Instance::ClassDescriptor };
	inline uintptr_t ClassDescriptorToClassName{ offsets::Instance::ClassDescriptorToClassName };
	inline uintptr_t ClockTime{ offsets::Lighting::ClockTime };
	inline uintptr_t CreatorId{ offsets::DataModel::CreatorId };
	inline uintptr_t DataModelDeleterPointer{ offsets::FakeDataModel::DataModelDeleterPointer };
	inline uintptr_t DataModelToRenderView1{ offsets::DataModel::ToRenderView1 };
	inline uintptr_t DataModelToRenderView2{ offsets::DataModel::ToRenderView2 };
	inline uintptr_t DataModelToRenderView3{ offsets::DataModel::ToRenderView3 };
	inline uintptr_t Deleter{ offsets::Instance::Deleter };
	inline uintptr_t Dimensions{ offsets::VisualEngine::Dimensions };
	inline uintptr_t DisplayName{ offsets::Player::DisplayName };
	inline uintptr_t EvaluateStateMachine{ offsets::Humanoid::EvaluateStateMachine };
	inline uintptr_t FOV{ offsets::Camera::FOV };
	inline uintptr_t FakeDataModelPointer{ offsets::FakeDataModel::Pointer };
	inline uintptr_t FakeDataModelToDataModel{ offsets::FakeDataModel::ToRealDataModel };
	inline uintptr_t FogColor{ offsets::Lighting::FogColor };
	inline uintptr_t FogEnd{ offsets::Lighting::FogEnd };
	inline uintptr_t FogStart{ offsets::Lighting::FogStart };
	inline uintptr_t FramePositionOffsetX{ offsets::GuiObject::PositionOffsetX };
	inline uintptr_t FramePositionOffsetY{ offsets::GuiObject::PositionOffsetY };
	inline uintptr_t FramePositionX{ offsets::GuiObject::PositionX };
	inline uintptr_t FramePositionY{ offsets::GuiObject::PositionY };
	inline uintptr_t FrameRotation{ offsets::GuiObject::Rotation };
	inline uintptr_t FrameSizeOffsetX{ offsets::GuiObject::SizeOffsetX };
	inline uintptr_t FrameSizeOffsetY{ offsets::GuiObject::SizeOffsetY };
	inline uintptr_t FrameSizeX{ offsets::GuiObject::SizeX };
	inline uintptr_t FrameSizeY{ offsets::GuiObject::SizeY };
	inline uintptr_t GameId{ offsets::DataModel::GameId };
	inline uintptr_t GameLoaded{ offsets::DataModel::GameLoaded };
	inline uintptr_t Gravity{ offsets::World::Gravity };
	inline uintptr_t Health{ offsets::Humanoid::Health };
	inline uintptr_t HealthDisplayDistance{ offsets::Humanoid::HealthDisplayDistance };
	inline uintptr_t HipHeight{ offsets::Humanoid::HipHeight };
	inline uintptr_t HumanoidState{ offsets::Humanoid::HumanoidState };
	inline uintptr_t HumanoidStateId{ offsets::Humanoid::HumanoidStateId };
	inline uintptr_t InputObject{ offsets::InputObject::InputObject };
	inline uintptr_t JobEnd{ offsets::TaskScheduler::JobEnd };
	inline uintptr_t JobId{ offsets::DataModel::JobId };
	inline uintptr_t JobStart{ offsets::TaskScheduler::JobStart };
	inline uintptr_t Job_Name{ offsets::TaskScheduler::JobName };
	inline uintptr_t JobsPointer{ offsets::TaskScheduler::JobsPointer };
	inline uintptr_t JumpPower{ offsets::Humanoid::JumpPower };
	inline uintptr_t LocalPlayer{ offsets::Players::LocalPlayer };
	inline uintptr_t LocalScriptByteCode{ offsets::LocalScript::ByteCode };
	inline uintptr_t LocalScriptHash{ offsets::LocalScript::Hash };
	inline uintptr_t MaterialType{ offsets::Primitive::Material };
	inline uintptr_t MaxHealth{ offsets::Humanoid::MaxHealth };
	inline uintptr_t MaxSlopeAngle{ offsets::Humanoid::MaxSlopeAngle };
	inline uintptr_t MeshPartColor3{ offsets::BasePart::BrickColor };
	inline uintptr_t MeshPartTexture{ offsets::MeshPart::TextureId };
	inline uintptr_t ModelInstance{ offsets::Player::ModelInstance };
	inline uintptr_t ModuleScriptByteCode{ offsets::ModuleScript::ByteCode };
	inline uintptr_t ModuleScriptHash{ offsets::ModuleScript::Hash };
	inline uintptr_t MoonTextureId{ offsets::Sky::MoonTextureId };
	inline uintptr_t MousePosition{ 0xD4 };
	inline uintptr_t MouseSensitivity{ offsets::Pointers::Sensitivity };
	inline uintptr_t MoveDirection{ offsets::Humanoid::MoveDirection };
	inline uintptr_t Name{ offsets::Instance::Name };
	inline uintptr_t NameDisplayDistance{ offsets::Humanoid::NameDisplayDistance };
	inline uintptr_t NameSize{ offsets::Instance::NameSize };
	inline uintptr_t OutdoorAmbient{ offsets::Lighting::OutDoorAmbient };
	inline uintptr_t Parent{ offsets::Instance::Parent };
	inline uintptr_t PartSize{ offsets::Primitive::Size };
	inline uintptr_t Ping{ offsets::Ping::Value };
	inline uintptr_t PlaceId{ offsets::DataModel::PlaceId };
	inline uintptr_t PlayerConfigurerPointer{ offsets::Pointers::PlayerConfigurer };
	inline uintptr_t PlayerMouse{ offsets::LocalPlayer::PlayerMouse };
	inline uintptr_t Position{ offsets::Primitive::Position };
	inline uintptr_t Primitive{ offsets::BasePart::Primitive };
	inline uintptr_t PrimitiveValidateValue{ offsets::Primitive::ValidateValue };
	inline uintptr_t PrimitivesPointer1{ offsets::Workspace::World };
	inline uintptr_t PrimitivesPointer2{ offsets::World::PrimitiveList };
	inline uintptr_t RenderJobToDataModel{ offsets::RenderJob::DataModel };
	inline uintptr_t RenderJobToFakeDataModel{ offsets::RenderJob::FakeDataModel };
	inline uintptr_t RenderJobToRenderView{ offsets::RenderJob::ToRenderView };
	inline uintptr_t RigType{ offsets::Humanoid::RigType };
	inline uintptr_t Rotation{ offsets::Primitive::Rotation };
	inline uintptr_t ScriptContext{ offsets::DataModel::ScriptContext };
	inline uintptr_t Sit{ offsets::Humanoid::Sit };
	inline uintptr_t SkyboxBk{ offsets::Sky::SkyboxBk };
	inline uintptr_t SkyboxDn{ offsets::Sky::SkyboxDn };
	inline uintptr_t SkyboxFt{ offsets::Sky::SkyboxFt };
	inline uintptr_t SkyboxLf{ offsets::Sky::SkyboxLf };
	inline uintptr_t SkyboxRt{ offsets::Sky::SkyboxRt };
	inline uintptr_t SkyboxUp{ offsets::Sky::SkyboxUp };
	inline uintptr_t StarCount{ offsets::Sky::StarCount };
	inline uintptr_t StringLength{ offsets::Instance::NameSize };
	inline uintptr_t SunTextureId{ offsets::Sky::SunTextureId };
	inline uintptr_t TaskSchedulerPointer{ offsets::Pointers::TaskScheduler };
	inline uintptr_t Team{ offsets::Player::Team };
	inline uintptr_t TeamColor{ offsets::Team::TeamColor };
	inline uintptr_t TextLabelText{ offsets::TextLabel::Text };
	inline uintptr_t Tool_Grip_Position{ offsets::Tool::GripPosition };
	inline uintptr_t Transparency{ offsets::BasePart::Transparency };
	inline uintptr_t UserId{ offsets::Player::UserId };
	inline uintptr_t Value{ offsets::Value::Value };
	inline uintptr_t Velocity{ offsets::Primitive::Velocity };
	inline uintptr_t ViewportSize{ offsets::Camera::ViewportSize };
	inline uintptr_t VisualEnginePointer{ offsets::VisualEngine::Pointer };
	inline uintptr_t VisualEngineToDataModel1{ offsets::VisualEngine::FakeDataModel };
	inline uintptr_t VisualEngineToDataModel2{ offsets::VisualEngine::DataModel };
	inline uintptr_t WalkSpeed{ offsets::Humanoid::WalkSpeed };
	inline uintptr_t WalkSpeedCheck{ offsets::Humanoid::WalkSpeedCheck };
	inline uintptr_t Workspace{ offsets::DataModel::Workspace };
	inline uintptr_t WorkspaceToWorld{ offsets::Workspace::World };
	inline uintptr_t viewmatrix{ offsets::VisualEngine::ViewMatrix };

	inline bool fetchOffsets()
	{
		return true;
	}
}
