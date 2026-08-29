#pragma once
// Skech-style ImGui skin for SmiteDK GUI prototyping.
// UI layout only — feature wiring later (except local friend/enemy save).

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <ctime>
#include <fstream>
#include <functional>
#include <string>
#include <vector>

#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"
#include "utils.hpp"

namespace SkechStyle
{
	inline ImVec4 ColBg() { return ImVec4(0.07f, 0.07f, 0.078f, 1.0f); }
	inline ImVec4 ColOuter() { return ImVec4(0.24f, 0.24f, 0.26f, 1.0f); }
	inline ImVec4 ColSidebar() { return ImVec4(0.04f, 0.04f, 0.045f, 1.0f); }
	inline ImVec4 ColPanel() { return ImVec4(0.09f, 0.09f, 0.10f, 1.0f); }
	inline ImVec4 ColPanelHeader() { return ImVec4(0.105f, 0.105f, 0.115f, 1.0f); }
	inline ImVec4 ColNavActive() { return ImVec4(0.12f, 0.12f, 0.135f, 1.0f); }
	inline ImVec4 ColAccent() { return ImVec4(0.92f, 0.12f, 0.14f, 1.0f); }
	inline ImVec4 ColAccentSoft() { return ImVec4(0.55f, 0.09f, 0.11f, 1.0f); }
	inline ImVec4 ColEnemy() { return ImVec4(0.95f, 0.25f, 0.28f, 1.0f); }
	inline ImVec4 ColFriend() { return ImVec4(0.25f, 0.85f, 0.40f, 1.0f); }
	inline ImVec4 ColText() { return ImVec4(0.94f, 0.94f, 0.96f, 1.0f); }
	inline ImVec4 ColTextOn() { return ImVec4(1.0f, 1.0f, 1.0f, 1.0f); }
	inline ImVec4 ColTextDim() { return ImVec4(0.72f, 0.72f, 0.76f, 1.0f); }
	inline ImVec4 ColTrack() { return ImVec4(0.07f, 0.07f, 0.078f, 1.0f); }
	inline ImVec4 ColTrackOutline() { return ImVec4(0.34f, 0.34f, 0.37f, 1.0f); }
	inline ImVec4 ColBar() { return ImVec4(0.05f, 0.05f, 0.05f, 1.0f); }

	inline ImU32 U32(const ImVec4& c) { return ImGui::ColorConvertFloat4ToU32(c); }
	inline ImU32 U32A(const ImVec4& c, float a) { ImVec4 t = c; t.w = a; return ImGui::ColorConvertFloat4ToU32(t); }

	inline float Approach(float cur, float target, float speed)
	{
		const float dt = ImGui::GetIO().DeltaTime;
		const float t = ImMin(1.0f, speed * dt); // snappy, linear — cleaner hover
		return cur + (target - cur) * t;
	}
	inline ImVec4 Lerp4(const ImVec4& a, const ImVec4& b, float t)
	{
		t = ImClamp(t, 0.0f, 1.0f);
		return ImVec4(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t, a.w + (b.w - a.w) * t);
	}

	enum class Icon : int
	{
		Crosshair = 0, Person, Eye, Globe, Running, Sliders, Dice, Keyboard,
		Shield, Users, Palette, Box, Folder, Menu, Explorer, Theme, Admin, Count
	};

	inline void DrawIcon(ImDrawList* dl, Icon icon, ImVec2 c, float s, ImU32 col, float th = 1.65f)
	{
		const float r = s * 0.5f;
		switch (icon)
		{
		case Icon::Crosshair:
			dl->AddCircle(c, r * 0.72f, col, 24, th);
			dl->AddCircleFilled(c, r * 0.11f, col, 10);
			dl->AddLine(ImVec2(c.x - r, c.y), ImVec2(c.x - r * 0.28f, c.y), col, th);
			dl->AddLine(ImVec2(c.x + r * 0.28f, c.y), ImVec2(c.x + r, c.y), col, th);
			dl->AddLine(ImVec2(c.x, c.y - r), ImVec2(c.x, c.y - r * 0.28f), col, th);
			dl->AddLine(ImVec2(c.x, c.y + r * 0.28f), ImVec2(c.x, c.y + r), col, th);
			break;
		case Icon::Person:
			dl->AddCircle(ImVec2(c.x, c.y - r * 0.42f), r * 0.30f, col, 16, th);
			dl->PathClear();
			dl->PathArcTo(ImVec2(c.x, c.y + r * 0.95f), r * 0.78f, IM_PI * 1.12f, IM_PI * 1.88f, 16);
			dl->PathStroke(col, 0, th);
			break;
		case Icon::Eye:
			dl->PathClear();
			dl->PathArcTo(ImVec2(c.x, c.y + r * 0.15f), r * 1.05f, IM_PI * 1.15f, IM_PI * 1.85f, 14);
			dl->PathStroke(col, 0, th);
			dl->PathClear();
			dl->PathArcTo(ImVec2(c.x, c.y - r * 0.15f), r * 1.05f, IM_PI * 0.15f, IM_PI * 0.85f, 14);
			dl->PathStroke(col, 0, th);
			dl->AddCircle(c, r * 0.28f, col, 14, th);
			dl->AddCircleFilled(c, r * 0.12f, col, 10);
			break;
		case Icon::Globe:
			dl->AddCircle(c, r * 0.88f, col, 28, th);
			dl->AddEllipse(c, ImVec2(r * 0.38f, r * 0.88f), col, 0.0f, 24, th);
			dl->AddLine(ImVec2(c.x - r * 0.88f, c.y), ImVec2(c.x + r * 0.88f, c.y), col, th * 0.85f);
			break;
		case Icon::Running:
			dl->AddCircle(ImVec2(c.x + r * 0.2f, c.y - r * 0.55f), r * 0.2f, col, 12, th);
			dl->AddLine(ImVec2(c.x + r * 0.05f, c.y - r * 0.28f), ImVec2(c.x - r * 0.25f, c.y + r * 0.15f), col, th);
			dl->AddLine(ImVec2(c.x - r * 0.25f, c.y + r * 0.15f), ImVec2(c.x + r * 0.15f, c.y + r * 0.85f), col, th);
			dl->AddLine(ImVec2(c.x - r * 0.05f, c.y - r * 0.05f), ImVec2(c.x + r * 0.7f, c.y + r * 0.2f), col, th);
			dl->AddLine(ImVec2(c.x - r * 0.15f, c.y + r * 0.05f), ImVec2(c.x - r * 0.75f, c.y + r * 0.55f), col, th);
			break;
		case Icon::Sliders:
			for (int i = 0; i < 3; ++i)
			{
				const float y = c.y + r * (-0.48f + i * 0.48f);
				const float x = c.x + r * (i == 0 ? -0.25f : (i == 1 ? 0.35f : -0.4f));
				dl->AddLine(ImVec2(c.x - r * 0.85f, y), ImVec2(c.x + r * 0.85f, y), col, th);
				dl->AddCircleFilled(ImVec2(x, y), r * 0.2f, col, 10);
			}
			break;
		case Icon::Dice:
			dl->AddRect(ImVec2(c.x - r * 0.58f, c.y - r * 0.58f), ImVec2(c.x + r * 0.58f, c.y + r * 0.58f), col, 2.5f, 0, th);
			dl->AddCircleFilled(ImVec2(c.x - r * 0.22f, c.y - r * 0.22f), r * 0.10f, col, 8);
			dl->AddCircleFilled(ImVec2(c.x + r * 0.22f, c.y + r * 0.22f), r * 0.10f, col, 8);
			dl->AddCircleFilled(c, r * 0.10f, col, 8);
			break;
		case Icon::Keyboard:
			dl->AddRect(ImVec2(c.x - r * 0.92f, c.y - r * 0.55f), ImVec2(c.x + r * 0.92f, c.y + r * 0.55f), col, 3.0f, 0, th);
			for (int row = 0; row < 2; ++row)
				for (int colI = 0; colI < 4; ++colI)
				{
					const float x0 = c.x - r * 0.72f + colI * r * 0.4f;
					const float y0 = c.y - r * 0.28f + row * r * 0.32f;
					dl->AddRectFilled(ImVec2(x0, y0), ImVec2(x0 + r * 0.22f, y0 + r * 0.16f), col, 1.2f);
				}
			break;
		case Icon::Shield:
		{
			const ImVec2 pts[]{
				ImVec2(c.x, c.y - r * 0.9f), ImVec2(c.x + r * 0.78f, c.y - r * 0.45f),
				ImVec2(c.x + r * 0.65f, c.y + r * 0.35f), ImVec2(c.x, c.y + r * 0.9f),
				ImVec2(c.x - r * 0.65f, c.y + r * 0.35f), ImVec2(c.x - r * 0.78f, c.y - r * 0.45f)
			};
			dl->AddPolyline(pts, 6, col, ImDrawFlags_Closed, th);
			break;
		}
		case Icon::Users:
			dl->AddCircle(ImVec2(c.x - r * 0.28f, c.y - r * 0.35f), r * 0.26f, col, 14, th);
			dl->AddCircle(ImVec2(c.x + r * 0.42f, c.y - r * 0.22f), r * 0.22f, col, 14, th);
			dl->PathClear();
			dl->PathArcTo(ImVec2(c.x - r * 0.28f, c.y + r * 1.05f), r * 0.72f, IM_PI * 1.15f, IM_PI * 1.85f, 12);
			dl->PathStroke(col, 0, th);
			break;
		case Icon::Palette:
			dl->AddCircle(c, r * 0.85f, col, 24, th);
			dl->AddCircleFilled(ImVec2(c.x - r * 0.35f, c.y - r * 0.2f), r * 0.14f, col, 8);
			dl->AddCircleFilled(ImVec2(c.x + r * 0.28f, c.y - r * 0.32f), r * 0.14f, col, 8);
			dl->AddCircleFilled(ImVec2(c.x + r * 0.35f, c.y + r * 0.28f), r * 0.14f, col, 8);
			break;
		case Icon::Box:
			dl->AddRect(ImVec2(c.x - r * 0.65f, c.y - r * 0.35f), ImVec2(c.x + r * 0.65f, c.y + r * 0.7f), col, 2.5f, 0, th);
			dl->AddLine(ImVec2(c.x - r * 0.65f, c.y - r * 0.35f), ImVec2(c.x, c.y - r * 0.85f), col, th);
			dl->AddLine(ImVec2(c.x + r * 0.65f, c.y - r * 0.35f), ImVec2(c.x, c.y - r * 0.85f), col, th);
			break;
		case Icon::Folder:
			dl->AddRect(ImVec2(c.x - r * 0.85f, c.y - r * 0.25f), ImVec2(c.x + r * 0.85f, c.y + r * 0.7f), col, 2.5f, 0, th);
			dl->AddRect(ImVec2(c.x - r * 0.85f, c.y - r * 0.55f), ImVec2(c.x - r * 0.05f, c.y - r * 0.25f), col, 2.0f, 0, th);
			break;
		case Icon::Menu:
			dl->AddRect(ImVec2(c.x - r * 0.7f, c.y - r * 0.55f), ImVec2(c.x + r * 0.7f, c.y + r * 0.55f), col, 2.5f, 0, th);
			for (int i = 0; i < 3; ++i)
			{
				const float y = c.y - r * 0.28f + i * r * 0.28f;
				dl->AddLine(ImVec2(c.x - r * 0.42f, y), ImVec2(c.x + r * 0.42f, y), col, th);
			}
			break;
		case Icon::Explorer:
			dl->AddRect(ImVec2(c.x - r * 0.7f, c.y - r * 0.65f), ImVec2(c.x + r * 0.7f, c.y + r * 0.65f), col, 2.0f, 0, th);
			dl->AddLine(ImVec2(c.x - r * 0.7f, c.y - r * 0.15f), ImVec2(c.x + r * 0.7f, c.y - r * 0.15f), col, th);
			dl->AddLine(ImVec2(c.x - r * 0.15f, c.y - r * 0.15f), ImVec2(c.x - r * 0.15f, c.y + r * 0.65f), col, th);
			dl->AddLine(ImVec2(c.x - r * 0.55f, c.y + r * 0.15f), ImVec2(c.x + r * 0.45f, c.y + r * 0.15f), col, th * 0.85f);
			dl->AddLine(ImVec2(c.x - r * 0.55f, c.y + r * 0.4f), ImVec2(c.x + r * 0.2f, c.y + r * 0.4f), col, th * 0.85f);
			break;
		case Icon::Theme:
			dl->AddCircle(c, r * 0.72f, col, 24, th);
			dl->AddCircleFilled(ImVec2(c.x + r * 0.18f, c.y - r * 0.05f), r * 0.72f, IM_COL32(0, 0, 0, 0), 24);
			dl->PathClear();
			dl->PathArcTo(c, r * 0.72f, -IM_PI * 0.55f, IM_PI * 0.55f, 14);
			dl->PathLineTo(c);
			dl->PathFillConvex(col);
			break;
		case Icon::Admin:
			dl->AddCircle(ImVec2(c.x, c.y - r * 0.38f), r * 0.26f, col, 14, th);
			dl->PathClear();
			dl->PathArcTo(ImVec2(c.x, c.y + r * 0.95f), r * 0.7f, IM_PI * 1.15f, IM_PI * 1.85f, 12);
			dl->PathStroke(col, 0, th);
			dl->AddLine(ImVec2(c.x - r * 0.15f, c.y + r * 0.15f), ImVec2(c.x - r * 0.15f, c.y + r * 0.55f), col, th);
			dl->AddLine(ImVec2(c.x + r * 0.15f, c.y + r * 0.15f), ImVec2(c.x + r * 0.15f, c.y + r * 0.55f), col, th);
			break;
		default: break;
		}
	}

	inline void DrawGlowText(ImDrawList* dl, ImFont* font, float size, ImVec2 pos, ImU32 col, const char* text, float glow = 0.45f)
	{
		const ImU32 glowCol = (col & 0x00FFFFFF) | ((ImU32)(glow * 80.0f) << 24);
		for (int i = -1; i <= 1; ++i)
			for (int j = -1; j <= 1; ++j)
				if (i || j)
					dl->AddText(font, size, ImVec2(pos.x + (float)i, pos.y + (float)j), glowCol, text);
		dl->AddText(font, size, pos, col, text);
	}

	inline void DrawSoftGlowRect(ImDrawList* dl, ImVec2 a, ImVec2 b, ImU32 col, float rounding, int layers = 3)
	{
		for (int i = layers; i >= 1; --i)
		{
			const float exp = (float)i * 2.0f;
			const int alpha = ((col >> 24) * (layers - i + 1)) / ((layers * (layers + 1)) / 2);
			dl->AddRect(ImVec2(a.x - exp, a.y - exp), ImVec2(b.x + exp, b.y + exp),
				(col & 0x00FFFFFF) | ((ImU32)alpha << 24), rounding + exp * 0.35f, 0, 1.4f);
		}
	}

	inline void ApplyTheme()
	{
		ImGuiStyle& s = ImGui::GetStyle();
		s.WindowRounding = 8.0f;
		s.ChildRounding = 8.0f;
		s.FrameRounding = 5.0f;
		s.GrabRounding = 3.0f;
		s.PopupRounding = 6.0f;
		s.ScrollbarRounding = 6.0f;
		s.WindowBorderSize = 0.0f;
		s.ChildBorderSize = 0.0f;
		s.FrameBorderSize = 0.0f; // custom inset borders — avoids edge clipping
		s.WindowPadding = ImVec2(0, 0);
		s.FramePadding = ImVec2(10, 8);
		s.ItemSpacing = ImVec2(10, 10);
		s.ItemInnerSpacing = ImVec2(8, 6);
		s.ScrollbarSize = 8.0f;

		ImVec4* c = s.Colors;
		c[ImGuiCol_WindowBg] = ColBg();
		c[ImGuiCol_ChildBg] = ImVec4(0, 0, 0, 0);
		c[ImGuiCol_PopupBg] = ColPanel();
		c[ImGuiCol_Border] = ColTrackOutline();
		c[ImGuiCol_Text] = ColText();
		c[ImGuiCol_TextDisabled] = ColTextDim();
		c[ImGuiCol_FrameBg] = ColTrack();
		c[ImGuiCol_FrameBgHovered] = ImVec4(0.11f, 0.11f, 0.12f, 1.0f);
		c[ImGuiCol_FrameBgActive] = ImVec4(0.13f, 0.13f, 0.14f, 1.0f);
		c[ImGuiCol_CheckMark] = ColAccent();
		c[ImGuiCol_SliderGrab] = ColTrackOutline();
		c[ImGuiCol_SliderGrabActive] = ImVec4(0.55f, 0.55f, 0.58f, 1.0f);
		c[ImGuiCol_Button] = ColTrack();
		c[ImGuiCol_ButtonHovered] = ImVec4(0.14f, 0.14f, 0.16f, 1.0f);
		c[ImGuiCol_ButtonActive] = ColAccentSoft();
		c[ImGuiCol_Header] = ColNavActive();
		c[ImGuiCol_HeaderHovered] = ImVec4(0.16f, 0.12f, 0.12f, 1.0f);
		c[ImGuiCol_HeaderActive] = ColAccentSoft();
		c[ImGuiCol_Separator] = ImVec4(0.18f, 0.18f, 0.20f, 1.0f);
		c[ImGuiCol_ScrollbarBg] = ImVec4(0, 0, 0, 0);
		c[ImGuiCol_ScrollbarGrab] = ImVec4(0.28f, 0.28f, 0.30f, 1.0f);
	}

	inline bool Toggle(const char* id, bool* v)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems) return false;
		const ImGuiID iid = window->GetID(id);
		const float height = 18.0f, width = 36.0f;
		const ImVec2 pos = window->DC.CursorPos;
		const ImRect bb(pos, ImVec2(pos.x + width, pos.y + height));
		ImGui::ItemSize(bb);
		if (!ImGui::ItemAdd(bb, iid)) return false;
		bool hovered = false, held = false;
		bool pressed = ImGui::ButtonBehavior(bb, iid, &hovered, &held);
		if (pressed) *v = !*v;

		ImGuiStorage* storage = ImGui::GetStateStorage();
		float t = storage->GetFloat(iid + 1, *v ? 1.0f : 0.0f);
		t = Approach(t, *v ? 1.0f : 0.0f, 28.0f);
		storage->SetFloat(iid + 1, t);

		ImDrawList* dl = window->DrawList;
		dl->AddRectFilled(bb.Min, bb.Max, U32(Lerp4(ColTrack(), ColAccent(), t)), height * 0.5f);
		dl->AddRect(bb.Min, bb.Max, U32(ColTrackOutline()), height * 0.5f, 0, 1.0f);
		const float pad = 2.0f, knob = height - pad * 2.0f;
		const float kx = bb.Min.x + pad + t * (width - pad * 2.0f - knob);
		dl->AddCircleFilled(ImVec2(kx + knob * 0.5f, bb.Min.y + height * 0.5f), knob * 0.5f, IM_COL32(255, 255, 255, 255));
		return pressed;
	}

	// Right-aligned control — keep clear of panel clip edge
	inline float RightAlignX(float controlW)
	{
		return ImGui::GetWindowContentRegionMax().x - controlW - 10.0f;
	}

	inline void DrawInsetFrame(ImDrawList* dl, ImVec2 a, ImVec2 b, float rounding = 5.0f)
	{
		const float inset = 1.0f;
		dl->AddRectFilled(ImVec2(a.x + inset, a.y + inset), ImVec2(b.x - inset, b.y - inset), U32(ColTrack()), rounding);
		dl->AddRect(ImVec2(a.x + inset, a.y + inset), ImVec2(b.x - inset, b.y - inset), U32(ColTrackOutline()), rounding, 0, 1.15f);
	}

	inline void LabelOn(const char* label, bool on)
	{
		ImGui::AlignTextToFramePadding();
		ImGui::TextColored(on ? ColTextOn() : ColTextDim(), "%s", label);
	}

	// Custom checkbox — full rounded square, never clipped on the right
	inline bool CheckboxRow(const char* label, bool* v)
	{
		ImGui::PushID(label);
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		LabelOn(label, *v);

		const float box = 18.0f;
		const float round = 4.0f;
		ImGui::SameLine(RightAlignX(box));

		const ImGuiID id = window->GetID("##cb");
		const ImVec2 pos = window->DC.CursorPos;
		// Align with text baseline / frame
		const float yOff = (ImGui::GetFrameHeight() - box) * 0.5f;
		const ImVec2 a(pos.x, pos.y + yOff);
		const ImVec2 b(a.x + box, a.y + box);
		const ImRect bb(a, b);

		ImGui::ItemSize(ImVec2(box, ImGui::GetFrameHeight()));
		if (!ImGui::ItemAdd(bb, id))
		{
			ImGui::PopID();
			return false;
		}

		bool hovered = false, held = false;
		const bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);
		if (pressed) *v = !*v;

		ImDrawList* dl = window->DrawList;
		// Draw fully inside the rect so rounding isn't cut by clip
		const float pad = 1.0f;
		const ImVec2 ia(a.x + pad, a.y + pad);
		const ImVec2 ib(b.x - pad, b.y - pad);

		if (*v)
		{
			dl->AddRectFilled(ia, ib, U32(ColAccent()), round);
			// Checkmark
			const ImVec2 p1(ia.x + box * 0.22f, ia.y + box * 0.48f);
			const ImVec2 p2(ia.x + box * 0.40f, ia.y + box * 0.68f);
			const ImVec2 p3(ia.x + box * 0.72f, ia.y + box * 0.28f);
			dl->AddLine(p1, p2, IM_COL32(255, 255, 255, 255), 1.8f);
			dl->AddLine(p2, p3, IM_COL32(255, 255, 255, 255), 1.8f);
		}
		else
		{
			dl->AddRectFilled(ia, ib, U32(hovered ? ColNavActive() : ColTrack()), round);
			dl->AddRect(ia, ib, U32(ColTrackOutline()), round, 0, 1.25f);
		}

		ImGui::PopID();
		return pressed;
	}

	inline bool StyledSliderFloat(const char* id, float* v, float mn, float mx, const char* fmt)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems) return false;
		ImGui::PushID(id);
		const ImGuiID iid = window->GetID("##sl");
		const float w = ImGui::GetContentRegionAvail().x;
		const float h = 24.0f;
		const ImVec2 pos = window->DC.CursorPos;
		const ImRect bb(pos, ImVec2(pos.x + w, pos.y + h));
		ImGui::ItemSize(bb, 2.0f);
		if (!ImGui::ItemAdd(bb, iid)) { ImGui::PopID(); return false; }

		bool hovered = false, held = false;
		ImGui::ButtonBehavior(bb, iid, &hovered, &held);
		bool changed = false;
		if (held)
		{
			const float nt = ImClamp((ImGui::GetIO().MousePos.x - bb.Min.x) / ImMax(w, 1.0f), 0.0f, 1.0f);
			const float nv = mn + nt * (mx - mn);
			if (nv != *v) { *v = nv; changed = true; }
		}

		const float t = (*v - mn) / ImMax(mx - mn, 0.0001f);
		ImDrawList* dl = window->DrawList;
		DrawInsetFrame(dl, bb.Min, bb.Max, 5.0f);
		const float grabX = bb.Min.x + 6.0f + t * (w - 12.0f);
		dl->AddRectFilled(ImVec2(grabX - 2.0f, bb.Min.y + 5.0f), ImVec2(grabX + 2.0f, bb.Max.y - 5.0f), U32(ColAccent()), 2.0f);

		char buf[64];
		ImFormatString(buf, IM_ARRAYSIZE(buf), fmt, *v);
		const ImVec2 ts = ImGui::CalcTextSize(buf);
		dl->AddText(ImVec2(bb.Min.x + (w - ts.x) * 0.5f, bb.Min.y + (h - ts.y) * 0.5f), U32(ColText()), buf);
		ImGui::PopID();
		return changed;
	}

	inline bool StyledSliderInt(const char* id, int* v, int mn, int mx)
	{
		float f = (float)*v;
		const bool changed = StyledSliderFloat(id, &f, (float)mn, (float)mx, "%.0f");
		*v = (int)roundf(f);
		return changed;
	}

	inline bool SliderRowF(const char* label, float* v, float mn, float mx, const char* fmt = "%.1f")
	{
		ImGui::PushID(label);
		ImGui::TextColored(ColTextDim(), "%s", label);
		const bool changed = StyledSliderFloat("##sl", v, mn, mx, fmt);
		ImGui::PopID();
		return changed;
	}

	inline bool SliderRowI(const char* label, int* v, int mn, int mx)
	{
		ImGui::PushID(label);
		ImGui::TextColored(ColTextDim(), "%s", label);
		const bool changed = StyledSliderInt("##sli", v, mn, mx);
		ImGui::PopID();
		return changed;
	}

	inline bool ComboRow(const char* label, int* current, const char* const* items, int count)
	{
		ImGui::PushID(label);
		ImGui::TextColored(ColTextDim(), "%s", label);
		const float w = ImGui::GetContentRegionAvail().x - 4.0f;
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ColTrack());
		ImGui::SetNextItemWidth(w);
		const bool changed = ImGui::Combo("##cm", current, items, count);
		{
			ImDrawList* dl = ImGui::GetWindowDrawList();
			const ImVec2 a = ImGui::GetItemRectMin();
			const ImVec2 b = ImGui::GetItemRectMax();
			dl->AddRect(ImVec2(a.x + 1.0f, a.y + 1.0f), ImVec2(b.x - 1.0f, b.y - 1.0f), U32(ColTrackOutline()), 5.0f, 0, 1.15f);
		}
		ImGui::PopStyleColor();
		ImGui::PopID();
		return changed;
	}

	inline void BindPickerRow(const char* label, int* key)
	{
		ImGui::PushID(label);
		ImGui::AlignTextToFramePadding();
		ImGui::TextColored(ColTextDim(), "%s", label);
		ImGui::SameLine(RightAlignX(102.0f));
		ImGui::Hotkey(key, ImVec2(100.0f, 22.0f));
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Click to bind. Backspace clears.");
		ImGui::PopID();
	}

	inline void ColorRow(const char* label, float col[4])
	{
		ImGui::PushID(label);
		ImGui::AlignTextToFramePadding();
		ImGui::TextColored(ColTextDim(), "%s", label);
		ImGui::SameLine(RightAlignX(26.0f));
		ImGui::ColorEdit4("##col", col, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
		ImGui::PopID();
	}

	inline bool FullButton(const char* label)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ColTrack());
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.14f, 0.14f, 0.16f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ColAccentSoft());
		const float w = ImGui::GetContentRegionAvail().x - 4.0f;
		const bool pressed = ImGui::Button(label, ImVec2(w, 0.0f));
		{
			ImDrawList* dl = ImGui::GetWindowDrawList();
			const ImVec2 a = ImGui::GetItemRectMin();
			const ImVec2 b = ImGui::GetItemRectMax();
			dl->AddRect(ImVec2(a.x + 1.0f, a.y + 1.0f), ImVec2(b.x - 1.0f, b.y - 1.0f), U32(ColTrackOutline()), 5.0f, 0, 1.15f);
		}
		ImGui::PopStyleColor(3);
		return pressed;
	}

	// Feature panel with optional On toggle. Title-only panels pass enabled=nullptr.
	inline void BeginPanel(const char* title, bool* enabled, const ImVec2& size, Icon icon = Icon::Box)
	{
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ColPanel());
		ImGui::BeginChild(title, size, ImGuiChildFlags_None, ImGuiWindowFlags_NoScrollbar);

		ImDrawList* dl = ImGui::GetWindowDrawList();
		const ImVec2 p = ImGui::GetWindowPos();
		const float w = ImGui::GetWindowSize().x;
		const float h = ImGui::GetWindowSize().y;

		ImGuiStorage* storage = ImGui::GetStateStorage();
		const ImGuiID glowId = ImGui::GetID(title) + 9001;
		const bool hasToggle = (enabled != nullptr);
		const float target = (hasToggle && *enabled) ? 1.0f : 0.0f;
		float glow = storage->GetFloat(glowId, target);
		glow = Approach(glow, target, 22.0f);
		storage->SetFloat(glowId, glow);

		dl->AddRectFilled(p, ImVec2(p.x + w, p.y + h), U32(ColPanel()), 8.0f);
		dl->AddRect(ImVec2(p.x + 1.0f, p.y + 1.0f), ImVec2(p.x + w - 1.0f, p.y + h - 1.0f), U32(ColOuter()), 8.0f, 0, 1.1f);

		if (glow > 0.01f)
		{
			DrawSoftGlowRect(dl, p, ImVec2(p.x + w, p.y + h), U32A(ColAccent(), 0.30f * glow), 8.0f, 3);
			dl->AddRectFilled(p, ImVec2(p.x + w, p.y + 40.0f), U32A(ColAccentSoft(), 0.25f * glow), 8.0f, ImDrawFlags_RoundCornersTop);
		}
		else
		{
			dl->AddRectFilled(p, ImVec2(p.x + w, p.y + 40.0f), U32(ColPanelHeader()), 8.0f, ImDrawFlags_RoundCornersTop);
		}

		const bool titleAccent = !hasToggle || glow > 0.35f;
		const ImU32 iconCol = U32(titleAccent ? ColAccent() : ColTextDim());
		DrawIcon(dl, icon, ImVec2(p.x + 20.0f, p.y + 20.0f), 15.0f, iconCol, 1.7f);

		ImFont* font = ImGui::GetFont();
		const float titleSize = ImGui::GetFontSize() * 1.08f;
		const ImVec2 tpos(p.x + 38.0f, p.y + 11.0f);
		dl->AddText(font, titleSize, tpos, U32(titleAccent ? (hasToggle ? ColTextOn() : ColAccent()) : ColTextOn()), title);

		ImGui::SetCursorPos(ImVec2(38.0f, 11.0f));
		ImGui::Dummy(ImVec2(ImGui::CalcTextSize(title).x + 8.0f, ImGui::GetTextLineHeight() + 4.0f));

		if (hasToggle)
		{
			ImGui::SameLine();
			ImGui::SetCursorPos(ImVec2(w - 50.0f, 11.0f));
			Toggle("##panel_toggle", enabled);
		}

		ImGui::SetCursorPos(ImVec2(18.0f, 48.0f));
		ImGui::BeginChild((std::string(title) + "_body").c_str(), ImVec2(w - 40.0f, size.y - 62.0f),
			ImGuiChildFlags_None);
	}

	inline void EndPanel()
	{
		ImGui::EndChild();
		ImGui::EndChild();
		ImGui::PopStyleColor();
	}

	inline bool NavButton(const char* label, Icon icon, bool active, float width)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		const ImGuiID id = window->GetID(label);
		const float h = 38.0f;
		const ImVec2 pos = window->DC.CursorPos;
		const ImRect bb(pos, ImVec2(pos.x + width, pos.y + h));
		ImGui::ItemSize(bb, 3.0f);
		if (!ImGui::ItemAdd(bb, id)) return false;

		bool hovered = false, held = false;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);

		ImGuiStorage* storage = ImGui::GetStateStorage();
		float t = storage->GetFloat(id + 7, active ? 1.0f : 0.0f);
		t = Approach(t, active ? 1.0f : (hovered ? 0.55f : 0.0f), 32.0f);
		storage->SetFloat(id + 7, t);

		ImDrawList* dl = window->DrawList;
		if (t > 0.01f)
		{
			dl->AddRectFilled(bb.Min, bb.Max, U32A(ColNavActive(), 0.55f + t * 0.45f), 6.0f);
			if (active)
			{
				dl->AddRectFilled(ImVec2(bb.Min.x, bb.Min.y + 8.0f), ImVec2(bb.Min.x + 3.0f, bb.Max.y - 8.0f), U32(ColAccent()), 2.0f);
				dl->AddRectFilledMultiColor(bb.Min, bb.Max,
					U32A(ColAccent(), 0.08f * t), U32A(ColAccent(), 0.0f),
					U32A(ColAccent(), 0.0f), U32A(ColAccent(), 0.06f * t));
			}
		}

		DrawIcon(dl, icon, ImVec2(bb.Min.x + 22.0f, bb.Min.y + h * 0.5f), 16.0f, U32(Lerp4(ColTextDim(), ColAccent(), t)), 1.75f);
		dl->AddText(ImVec2(bb.Min.x + 42.0f, bb.Min.y + 10.0f), U32(Lerp4(ColTextDim(), ColTextOn(), t)), label);
		return pressed;
	}

	inline void DrawLogo(ImDrawList* dl, ImVec2 origin, void* tex = nullptr, ImVec2 texSize = ImVec2(0, 0))
	{
		if (tex)
		{
			const float h = 44.0f;
			const float w = (texSize.y > 1.0f) ? h * (texSize.x / texSize.y) : 148.0f;
			dl->AddImage(ImTextureRef((ImTextureID)(size_t)tex), ImVec2(origin.x + 10.0f, origin.y + 12.0f), ImVec2(origin.x + 10.0f + w, origin.y + 12.0f + h));
			return;
		}
		dl->AddText(ImGui::GetFont(), 22.0f, ImVec2(origin.x + 14.0f, origin.y + 18.0f), U32(ColTextOn()), "SMITE DK");
		dl->AddRectFilled(ImVec2(origin.x + 16.0f, origin.y + 46.0f), ImVec2(origin.x + 86.0f, origin.y + 49.0f), U32(ColAccent()), 1.0f);
	}

	inline void DrawPlaceholderAvatar(ImDrawList* dl, ImVec2 center, float size, ImU32 col)
	{
		const float r = size * 0.5f;
		dl->AddCircleFilled(center, r, IM_COL32(28, 28, 32, 255), 24);
		dl->AddCircle(center, r, U32(ColOuter()), 24, 1.2f);
		dl->AddCircle(ImVec2(center.x, center.y - r * 0.28f), r * 0.22f, col, 14, 1.5f);
		dl->PathClear();
		dl->PathArcTo(ImVec2(center.x, center.y + r * 0.85f), r * 0.55f, IM_PI * 1.15f, IM_PI * 1.85f, 12);
		dl->PathStroke(col, 0, 1.5f);
	}

	enum class Relation : int { None = 0, Friend = 1, Enemy = 2 };

	struct FriendEntry
	{
		char displayName[64];
		char userName[64];
		Relation relation = Relation::None;
	};

	inline const char* RelationsPath() { return "smitedk_relations.json"; }

	inline void SaveRelations(const FriendEntry* list, int count)
	{
		std::ofstream out(RelationsPath(), std::ios::trunc);
		if (!out.is_open()) return;
		out << "{\n  \"players\": [\n";
		for (int i = 0; i < count; ++i)
		{
			const char* rel = list[i].relation == Relation::Friend ? "friend"
				: (list[i].relation == Relation::Enemy ? "enemy" : "none");
			out << "    {\"user\":\"" << list[i].userName
				<< "\",\"display\":\"" << list[i].displayName
				<< "\",\"relation\":\"" << rel << "\"}";
			if (i + 1 < count) out << ",";
			out << "\n";
		}
		out << "  ]\n}\n";
	}

	inline void LoadRelations(FriendEntry* list, int count)
	{
		std::ifstream in(RelationsPath());
		if (!in.is_open()) return;
		std::string data((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
		for (int i = 0; i < count; ++i)
		{
			const std::string key = std::string("\"user\":\"") + list[i].userName + "\"";
			const size_t pos = data.find(key);
			if (pos == std::string::npos) continue;
			const size_t rpos = data.find("\"relation\":\"", pos);
			if (rpos == std::string::npos) continue;
			const size_t start = rpos + 12;
			const size_t end = data.find('"', start);
			if (end == std::string::npos) continue;
			const std::string rel = data.substr(start, end - start);
			if (rel == "friend") list[i].relation = Relation::Friend;
			else if (rel == "enemy") list[i].relation = Relation::Enemy;
			else list[i].relation = Relation::None;
		}
	}

	struct DemoState
	{
		bool menuVisible = true;
		int nav = 0;
		bool friendsWin = false;
		bool themeWin = false;
		bool adminWin = false;
		bool explorerWin = false;

		bool aimbotEnabled = false;
		bool aimbotFOVEnabled = false;
		bool aimbotPredictionEnabled = false;
		bool aimbotToggleLock = false;
		bool aimbotHoldSwitch = false;
		bool aimbotWallCheck = false;
		float aimbotFOVRadius = 100.0f;
		float aimbotStrenght = 0.35f;
		float aimbotPredictionX = 5.0f;
		float aimbotPredictionY = 5.0f;
		int aimbotLockPart = 0;
		ImVec4 aimbotFovColor{ 1, 0, 0, 1 };

		bool triggerbotEnabled = false;
		bool triggerbotIndicateClicking = false;
		bool triggerbotRightClick = false;
		bool triggerbotWallCheck = false;
		bool triggerbotFOVEnabled = false;
		bool triggerbotShowPredDot = false;
		bool triggerbotPredictionEnabled = false;
		float triggerbotDetectionRadius = 20.0f;
		float triggerbotDelayMs = 50.0f;
		int triggerbotTriggerPart = 0;
		ImVec4 triggerbotFovColor{ 1.0f, 0.55f, 0.1f, 1.0f };

		bool silentAimEnabled = false;
		int silentAimLockPart = 0;
		float silentAimFOVRadius = 100.0f;

		bool espEnabled = false;
		bool espFilled = false;
		bool espShowName = true;
		bool espShowHealth = true;
		bool espShowDistance = true;
		bool espIgnoreDeadPlrs = false;
		int espType = 0;
		int espDistance = 200;
		ImVec4 espColor{ 1, 0, 0, 1 };
		bool tracersEnabled = false;
		int tracerType = 0;
		ImVec4 tracerColor{ 1, 1, 1, 1 };

		char configFileName[64] = "";
		char configStatus[96] = "";
		static constexpr int MaxConfigs = 48;
		char configList[MaxConfigs][64]{};
		const char* configListPtrs[MaxConfigs]{};
		int configCount = 0;
		int configIdx = 0;
		bool requestRefreshConfigs = true;
		bool rbxWindowNeedsToBeSelected = true;
		int mainLoopDelay = 0;
		bool requestExit = false;
		bool requestForceReset = false;
		bool espPreviewOpened = false;

		float tpX = 0, tpY = 0, tpZ = 0;
		float orbitDistanceMultiplier = 1.0f;
		float orbitSpeedMultiplier = 1.0f;
		bool flyEnabled = false;
		int flyMode = 0;
		float flySpeed = 16.0f;
		bool behindPlayerEnabled = true;
		float behindPlayerDistance = 4.0f;
		float behindPlayerFOV = 250.0f;
		bool noclipEnabled = false;
		bool streamproofEnabled = false;
		bool walkSpeedEnabled = false;
		int walkSpeedSet = 16;
		bool jumpPowerEnabled = false;
		int jumpPowerSet = 50;

		int slot1 = 0, slot2 = 0, slot3 = 0;
		int gamblingBalance = 500;
		int slotBet = 10;
		int minesBet = 10;
		int gamblingLastYmd = 0;
		bool walletLoaded = false;
		bool autoSaveEnabled = false;
		std::function<void()> onSaveConfig;
		std::function<void()> onCreateConfig;
		std::function<void()> onLoadConfig;
		bool handleInsert = true;
		bool fillBackdrop = false;
		bool hostExtraWindows = false; // true = extra windows drawn by host
		void* logoTex = nullptr;
		ImVec2 logoSize{ 0, 0 };
		void* selectedAvatarTex = nullptr;
		ImVec2 selectedAvatarSize{ 0, 0 };
		float menuX = -1.0f;
		float menuY = -1.0f;
		bool slotSpinning = false;
		float slotSpinT = 0.0f;
		float slotSpinDur = 0.0f;
		int slotTarget1 = 0, slotTarget2 = 0, slotTarget3 = 0;
		float slotOffset[3]{ 0, 0, 0 };

		// Blackjack
		int bjBet = 10;
		int bjPlayer[8]{};
		int bjDealer[8]{};
		int bjPlayerCount = 0;
		int bjDealerCount = 0;
		int bjPhase = 0; // 0 idle, 1 playing, 2 stand/reveal, 3 done
		bool bjSettled = true;
		char bjMsg[64] = "Place a bet and Deal.";

		// Mines
		static constexpr int MinesN = 25;
		bool minesBomb[MinesN]{};
		bool minesRevealed[MinesN]{};
		bool minesActive = false;
		bool minesDead = false;
		bool minesCashed = false;
		int minesBombs = 5;
		int minesSafe = 0;
		float minesMult = 1.0f;

		bool keybindListVisible = false;
		char themeFileName[64] = "";

		bool highEndVisuals = true;
		bool sessionBoost = false;

		static constexpr int MaxLivePlayers = 64;
		struct LivePlayerEntry
		{
			char name[64];
			int64_t userId = 0;
			bool isFriend = false;
			bool isLocal = false;
			bool isSmite = false;
		};
		LivePlayerEntry livePlayers[MaxLivePlayers]{};
		int livePlayerCount = 0;
		int selectedLivePlayer = -1;

		enum class PlayerListAction : int
		{
			None = 0,
			Spectate,
			StopSpectate,
			Teleport,
			Behind,
			Orbit,
			StopOrbit,
			ToggleFriend,
			ToggleEnemy
		};
		PlayerListAction playerAction = PlayerListAction::None;
		char playerActionTarget[64]{};

		enum class TpAction : int { None = 0, SetFromLocal, Clear, Teleport };
		TpAction tpAction = TpAction::None;

		int flyKey = 0;
		int behindPlayerKey = 0;
		int walkSpeedKey = 0;
		int jumpPowerKey = 0;
		int aimbotKey = 2;
		int triggerbotKey = 0;
		int toggleGuiKey = 45;

		int adminPlayerIdx = 0;
		const char* adminPlayerNames[MaxLivePlayers + 1]{ "Select player" };
		int adminPlayerCount = 1;
		bool ownerBring = false, ownerFollow = false, ownerSpin = false;
		bool ownerFreeze = false, ownerFling = false, ownerJumpOnly = false;
		bool hideSmiteLogo = false;

		float contentFade = 1.0f;
		float backGlow = 0.0f;
		int lastNav = 0;
	};

	inline int TodayYmd()
	{
		time_t now = time(nullptr);
		tm t{};
		localtime_s(&t, &now);
		return (t.tm_year + 1900) * 10000 + (t.tm_mon + 1) * 100 + t.tm_mday;
	}

	inline int YmdDayDiff(int fromYmd, int toYmd)
	{
		auto unpack = [](int ymd, tm& out)
		{
			memset(&out, 0, sizeof(out));
			out.tm_year = ymd / 10000 - 1900;
			out.tm_mon = (ymd / 100) % 100 - 1;
			out.tm_mday = ymd % 100;
			out.tm_isdst = -1;
		};
		tm a{}, b{};
		unpack(fromYmd, a);
		unpack(toYmd, b);
		const time_t ta = mktime(&a);
		const time_t tb = mktime(&b);
		if (ta == (time_t)-1 || tb == (time_t)-1) return 1;
		const int days = (int)((tb - ta) / 86400);
		return days > 0 ? days : 1;
	}

	inline const char* WalletPath() { return "smitedk_wallet.json"; }

	inline void SaveWallet(const DemoState& st)
	{
		std::ofstream out(WalletPath(), std::ios::trunc);
		if (!out.is_open()) return;
		out << "{\n  \"balance\": " << st.gamblingBalance << ",\n  \"ymd\": " << st.gamblingLastYmd << "\n}\n";
	}

	inline void TickDailyWallet(DemoState& st)
	{
		const int today = TodayYmd();
		if (!st.walletLoaded)
		{
			st.walletLoaded = true;
			std::ifstream in(WalletPath());
			if (in.is_open())
			{
				std::string data((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
				const auto grab = [&](const char* key) -> int
				{
					const std::string k = std::string("\"") + key + "\":";
					const size_t p = data.find(k);
					if (p == std::string::npos) return 0;
					return atoi(data.c_str() + p + k.size());
				};
				st.gamblingBalance = grab("balance");
				st.gamblingLastYmd = grab("ymd");
			}
			if (st.gamblingLastYmd == 0)
			{
				st.gamblingBalance = 500;
				st.gamblingLastYmd = today;
				SaveWallet(st);
				return;
			}
		}
		if (today > st.gamblingLastYmd)
		{
			st.gamblingBalance += 500 * YmdDayDiff(st.gamblingLastYmd, today);
			st.gamblingLastYmd = today;
			SaveWallet(st);
		}
	}

	inline float CountActiveFeatures(const DemoState& st)
	{
		return (float)(st.aimbotEnabled + st.triggerbotEnabled + st.silentAimEnabled + st.espEnabled
			+ st.tracersEnabled + st.flyEnabled + st.walkSpeedEnabled + st.jumpPowerEnabled
			+ st.noclipEnabled + st.streamproofEnabled);
	}

	inline bool BottomBarButton(const char* id, Icon icon, const char* tip, bool active)
	{
		const float size = 36.0f;
		ImGui::PushID(id);
		const ImVec2 pos = ImGui::GetCursorScreenPos();
		const bool pressed = ImGui::InvisibleButton("##bb", ImVec2(size, size));
		const bool hovered = ImGui::IsItemHovered();
		ImDrawList* dl = ImGui::GetWindowDrawList();
		const ImVec2 a = pos;
		const ImVec2 b(pos.x + size, pos.y + size);
		const ImVec2 c((a.x + b.x) * 0.5f, (a.y + b.y) * 0.5f);

		ImGuiStorage* storage = ImGui::GetStateStorage();
		float t = storage->GetFloat(ImGui::GetID("anim"), active ? 1.0f : 0.0f);
		t = Approach(t, active ? 1.0f : (hovered ? 0.7f : 0.0f), 36.0f);
		storage->SetFloat(ImGui::GetID("anim"), t);

		dl->AddRectFilled(a, b, U32A(ColAccent(), 0.14f * t), 6.0f);
		dl->AddRect(ImVec2(a.x + 1, a.y + 1), ImVec2(b.x - 1, b.y - 1),
			U32(Lerp4(ColOuter(), ColAccent(), t)), 6.0f, 0, 1.25f);
		DrawIcon(dl, icon, c, size * 0.5f, U32(Lerp4(ColTextDim(), ColAccent(), ImMax(t, active ? 1.0f : 0.0f))), 1.8f);

		if (hovered)
			ImGui::SetTooltip("%s", tip);

		ImGui::PopID();
		return pressed;
	}

	inline int CardValue(int card) // 0-51
	{
		const int r = card % 13;
		if (r >= 9) return 10;
		return r + 1;
	}
	inline int HandTotal(const int* cards, int n)
	{
		int total = 0, aces = 0;
		for (int i = 0; i < n; ++i)
		{
			int v = CardValue(cards[i]);
			if (v == 1) { aces++; total += 11; }
			else total += v;
		}
		while (total > 21 && aces > 0) { total -= 10; --aces; }
		return total;
	}
	inline void DrawCardFace(ImDrawList* dl, ImVec2 a, float w, float h, int card, bool hidden)
	{
		dl->AddRectFilled(a, ImVec2(a.x + w, a.y + h), hidden ? IM_COL32(40, 20, 25, 255) : IM_COL32(245, 245, 248, 255), 4.0f);
		dl->AddRect(ImVec2(a.x + 1, a.y + 1), ImVec2(a.x + w - 1, a.y + h - 1), U32(ColOuter()), 4.0f, 0, 1.1f);
		if (hidden)
		{
			dl->AddText(ImVec2(a.x + w * 0.28f, a.y + h * 0.35f), U32(ColAccent()), "?");
			return;
		}
		static const char* ranks[]{ "A","2","3","4","5","6","7","8","9","10","J","Q","K" };
		static const char* suits[]{ "C","D","H","S" };
		const int r = card % 13, s = card / 13;
		const bool red = (s == 1 || s == 2);
		char buf[16];
		ImFormatString(buf, IM_ARRAYSIZE(buf), "%s%s", ranks[r], suits[s]);
		dl->AddText(ImVec2(a.x + 6.0f, a.y + 6.0f), red ? IM_COL32(200, 40, 50, 255) : IM_COL32(20, 20, 25, 255), buf);
	}

	inline void DrawFloatingWindow(const char* title, bool* open, const ImVec2& size, Icon icon, const std::function<void()>& body)
	{
		if (!*open) return;
		ImGui::SetNextWindowSize(size, ImGuiCond_Appearing);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ColPanel());
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(14, 14));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.0f);
		if (ImGui::Begin(title, open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings))
		{
			ImDrawList* dl = ImGui::GetWindowDrawList();
			const ImVec2 p = ImGui::GetCursorScreenPos();
			DrawIcon(dl, icon, ImVec2(p.x + 8.0f, p.y + 8.0f), 14.0f, U32(ColAccent()), 1.6f);
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 24.0f);
			ImGui::TextColored(ColAccent(), "%s", title);
			ImGui::Separator();
			body();
		}
		ImGui::End();
		ImGui::PopStyleVar(2);
		ImGui::PopStyleColor();
	}

	inline void DrawDemo(DemoState& st)
	{
		static const char* lockParts[]{ "Closest", "Head", "Torso", "Left Arm", "Right Arm", "Left Leg", "Right Leg" };
		static const char* triggerParts[]{ "Closest", "Head", "Torso", "Left Arm", "Right Arm" };
		static const char* espTypes[]{ "Square", "Skeleton", "Corners" };
		static const char* tracerTypes[]{ "Mouse", "Corner", "Top", "Bottom" };
		static const char* flyModes[]{ "Default", "CFrame", "Position", "Velocity", "Hybrid", "PlatformStand", "Anchored" };

		TickDailyWallet(st);

		if (st.handleInsert && ImGui::IsKeyPressed(ImGuiKey_Insert, false))
			st.menuVisible = !st.menuVisible;

		if (st.nav != st.lastNav) { st.contentFade = 0.0f; st.lastNav = st.nav; }
		if (st.highEndVisuals)
			st.contentFade = Approach(st.contentFade, 1.0f, 18.0f);
		else
			st.contentFade = 1.0f;
		if (st.highEndVisuals)
			st.backGlow = Approach(st.backGlow, ImClamp(CountActiveFeatures(st) * 0.18f, 0.0f, 0.55f), 14.0f);
		else
			st.backGlow = 0.0f;

		const ImGuiViewport* vp = ImGui::GetMainViewport();
		ImDrawList* bg = ImGui::GetBackgroundDrawList();
		(void)bg;
		if (st.fillBackdrop)
			bg->AddRectFilled(vp->WorkPos, ImVec2(vp->WorkPos.x + vp->WorkSize.x, vp->WorkPos.y + vp->WorkSize.y), IM_COL32(18, 18, 20, 255));

		// Bottom Extra bar — real ImGui window so clicks always work
		{
			const float barW = 340.0f;
			const float barH = 52.0f;
			ImGui::SetNextWindowPos(ImVec2(vp->WorkPos.x + (vp->WorkSize.x - barW) * 0.5f, vp->WorkPos.y + vp->WorkSize.y - 72.0f));
			ImGui::SetNextWindowSize(ImVec2(barW, barH));
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ColBar());
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 8.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(18, 8));
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.0f);
			ImGui::PushStyleColor(ImGuiCol_Border, ColOuter());
			ImGui::Begin("##BottomBar", nullptr,
				ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
				ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);
			ImGui::SetCursorPosY(8.0f);
			if (BottomBarButton("menu", Icon::Menu, "Menu", st.menuVisible)) st.menuVisible = !st.menuVisible;
			ImGui::SameLine(0, 18);
			if (BottomBarButton("explorer", Icon::Explorer, "Explorer", st.explorerWin)) st.explorerWin = !st.explorerWin;
			ImGui::SameLine(0, 18);
			if (BottomBarButton("friends", Icon::Users, "Players", st.friendsWin)) st.friendsWin = !st.friendsWin;
			ImGui::SameLine(0, 18);
			if (BottomBarButton("theme", Icon::Theme, "Theme Changer", st.themeWin)) st.themeWin = !st.themeWin;
			ImGui::SameLine(0, 18);
			if (BottomBarButton("admin", Icon::Admin, "Admin", st.adminWin)) st.adminWin = !st.adminWin;
			ImGui::End();
			ImGui::PopStyleColor(2);
			ImGui::PopStyleVar(3);
		}

		auto drawPlayerListBody = [&]()
		{
			ImGui::TextWrapped("Click a player for actions. Friend = green ESP / ignored by aim.");
			ImGui::Separator();
			const float listW = ImGui::GetContentRegionAvail().x * 0.46f;
			ImGui::BeginChild("##flist", ImVec2(listW, -1), ImGuiChildFlags_Borders);
			for (int i = 0; i < st.livePlayerCount; ++i)
			{
				const DemoState::LivePlayerEntry& f = st.livePlayers[i];
				ImGui::PushID(i);
				const bool selected = st.selectedLivePlayer == i;
				const float rowH = 54.0f;
				const float rowW = ImGui::GetContentRegionAvail().x;
				const ImVec2 rowPos = ImGui::GetCursorScreenPos();
				ImDrawList* rdl = ImGui::GetWindowDrawList();

				if (selected) rdl->AddRectFilled(rowPos, ImVec2(rowPos.x + rowW, rowPos.y + rowH), U32A(ColAccent(), 0.12f), 6.0f);
				rdl->AddRect(rowPos, ImVec2(rowPos.x + rowW, rowPos.y + rowH), U32(ColOuter()), 6.0f, 0, 1.0f);

				const ImU32 avCol = f.isLocal ? U32(ColAccent())
					: (f.isFriend ? U32(ColFriend()) : U32(ColTextDim()));
				if (selected && st.selectedAvatarTex)
				{
					const ImVec2 avMin(rowPos.x + 8.0f, rowPos.y + 8.0f);
					ImGui::GetWindowDrawList()->AddImage(ImTextureRef((ImTextureID)(size_t)st.selectedAvatarTex), avMin, ImVec2(avMin.x + 38.0f, avMin.y + 38.0f));
				}
				else
					DrawPlaceholderAvatar(rdl, ImVec2(rowPos.x + 26.0f, rowPos.y + rowH * 0.5f), 34.0f, avCol);
				rdl->AddText(ImVec2(rowPos.x + 52.0f, rowPos.y + 10.0f), U32(ColTextOn()), f.name);
				if (f.isLocal)
					rdl->AddText(ImVec2(rowPos.x + 52.0f, rowPos.y + 28.0f), U32(ColTextDim()), "(you)");
				else if (f.isSmite)
					rdl->AddText(ImVec2(rowPos.x + 52.0f, rowPos.y + 28.0f), U32(ColAccent()), "using DK");
				else if (f.isFriend)
					rdl->AddText(ImVec2(rowPos.x + 52.0f, rowPos.y + 28.0f), U32(ColFriend()), "friend");

				ImGui::SetCursorScreenPos(rowPos);
				if (ImGui::InvisibleButton("##row", ImVec2(rowW, rowH)))
					st.selectedLivePlayer = i;
				ImGui::SetCursorScreenPos(ImVec2(rowPos.x, rowPos.y + rowH + 8.0f));
				ImGui::Dummy(ImVec2(0, 0));
				ImGui::PopID();
			}
			if (st.livePlayerCount == 0)
				ImGui::TextColored(ColTextDim(), "No players in server.");
			ImGui::EndChild();

			ImGui::SameLine();
			ImGui::BeginChild("##fdetail", ImVec2(0, -1), ImGuiChildFlags_Borders);
			if (st.selectedLivePlayer >= 0 && st.selectedLivePlayer < st.livePlayerCount)
			{
				const DemoState::LivePlayerEntry& f = st.livePlayers[st.selectedLivePlayer];
				ImDrawList* ddl = ImGui::GetWindowDrawList();
				const ImVec2 cp = ImGui::GetCursorScreenPos();
				const ImU32 avCol = f.isFriend ? U32(ColFriend()) : U32(ColAccent());
				if (st.selectedAvatarTex)
				{
					ddl->AddImage(ImTextureRef((ImTextureID)(size_t)st.selectedAvatarTex), ImVec2(cp.x + 8.0f, cp.y + 8.0f), ImVec2(cp.x + 80.0f, cp.y + 80.0f));
				}
				else
					DrawPlaceholderAvatar(ddl, ImVec2(cp.x + 36.0f, cp.y + 36.0f), 64.0f, avCol);
				ddl->AddText(ImGui::GetFont(), 18.0f, ImVec2(cp.x + 92.0f, cp.y + 16.0f), U32(ColTextOn()), f.name);
				ddl->AddText(ImVec2(cp.x + 92.0f, cp.y + 40.0f), U32(ColTextDim()), f.isLocal ? "Local player" : "Roblox character");
				if (f.isSmite)
					ddl->AddText(ImVec2(cp.x + 92.0f, cp.y + 58.0f), U32(ColAccent()), "Using this");
				else if (f.isFriend)
					ddl->AddText(ImVec2(cp.x + 92.0f, cp.y + 58.0f), U32(ColFriend()), "Friend");

				ImGui::Dummy(ImVec2(0, 88));
				if (!f.isLocal)
				{
					ImGui::TextColored(ColAccent(), "Actions");
					if (FullButton("Orbit"))
					{
						st.playerAction = DemoState::PlayerListAction::Orbit;
						strncpy_s(st.playerActionTarget, f.name, _TRUNCATE);
					}
					if (FullButton("Spectate"))
					{
						st.playerAction = DemoState::PlayerListAction::Spectate;
						strncpy_s(st.playerActionTarget, f.name, _TRUNCATE);
					}
					if (FullButton("Stop spectating"))
						st.playerAction = DemoState::PlayerListAction::StopSpectate;
					if (FullButton("Stop orbit"))
						st.playerAction = DemoState::PlayerListAction::StopOrbit;
					if (FullButton("Teleport"))
					{
						st.playerAction = DemoState::PlayerListAction::Teleport;
						strncpy_s(st.playerActionTarget, f.name, _TRUNCATE);
					}
					if (FullButton("Behind"))
					{
						st.playerAction = DemoState::PlayerListAction::Behind;
						strncpy_s(st.playerActionTarget, f.name, _TRUNCATE);
					}
					ImGui::Spacing();
					if (FullButton(f.isFriend ? "Remove friend" : "Add friend"))
					{
						st.playerAction = DemoState::PlayerListAction::ToggleFriend;
						strncpy_s(st.playerActionTarget, f.name, _TRUNCATE);
					}
				}
				else
					ImGui::TextColored(ColTextDim(), "Select another player for actions.");
			}
			else
				ImGui::TextColored(ColTextDim(), "Select a player.");
			ImGui::EndChild();
		};

		if (!st.hostExtraWindows)
			DrawFloatingWindow("Players", &st.friendsWin, ImVec2(620, 420), Icon::Users, drawPlayerListBody);

		// Floating Extra windows from bottom bar (host draws explorer/admin/theme/players when attached)
		if (!st.hostExtraWindows)
		{
		DrawFloatingWindow("Theme Changer", &st.themeWin, ImVec2(320, 180), Icon::Theme, [&]()
		{
			ImGui::TextColored(ColTextDim(), "Theme name");
			ImGui::SetNextItemWidth(-1);
			ImGui::InputText("##theme", st.themeFileName, IM_ARRAYSIZE(st.themeFileName));
			FullButton("Set theme");
			FullButton("Reset theme");
		});
		DrawFloatingWindow("Admin", &st.adminWin, ImVec2(360, 420), Icon::Admin, [&]()
		{
			ImGui::Text("Role: default");
			ImGui::Text("Level: 1");
			ImGui::TextDisabled("Subscriptions: (preview)");
			ImGui::Separator();
			FullButton("Logout key (restart)");
			ImGui::Separator();
			ImGui::TextColored(ColAccent(), "[Stealth] Staff+");
			CheckboxRow("Hide DK logo from others", &st.hideSmiteLogo);
			ImGui::Separator();
			ImGui::TextColored(ColAccent(), "[Trolls] CoOwner+");
			ComboRow("Target player", &st.adminPlayerIdx, st.adminPlayerNames, st.adminPlayerCount);
			CheckboxRow("Bring to me", &st.ownerBring);
			CheckboxRow("Follow me", &st.ownerFollow);
			CheckboxRow("Spin", &st.ownerSpin);
			CheckboxRow("Freeze", &st.ownerFreeze);
			CheckboxRow("Fling", &st.ownerFling);
			CheckboxRow("Jump only", &st.ownerJumpOnly);
		});
		DrawFloatingWindow("Explorer", &st.explorerWin, ImVec2(420, 480), Icon::Explorer, [&]()
		{
			ImGui::TextColored(ColTextDim(), "Players");
			ImGui::BeginChild("##exscroll", ImVec2(0, 0), ImGuiChildFlags_Borders);
			for (int i = 0; i < st.livePlayerCount; ++i)
				ImGui::BulletText("%s%s", st.livePlayers[i].name, st.livePlayers[i].isLocal ? " (you)" : "");
			if (st.livePlayerCount == 0)
				ImGui::TextDisabled("No players detected.");
			ImGui::EndChild();
		});
		}

		if (!st.menuVisible)
			return;

		const float menuW = 1057.0f;
		const float menuH = 640.0f;
		if (st.menuX < 0.0f)
		{
			st.menuX = vp->WorkPos.x + (vp->WorkSize.x - menuW) * 0.5f;
			st.menuY = vp->WorkPos.y + (vp->WorkSize.y - menuH) * 0.32f;
		}
		ImGui::SetNextWindowPos(ImVec2(st.menuX, st.menuY), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(menuW, menuH));

		ImGui::Begin("##SmiteDKMenu", nullptr,
			ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus);

		ImDrawList* dl = ImGui::GetWindowDrawList();
		const ImVec2 wp = ImGui::GetWindowPos();
		const ImVec2 ws = ImGui::GetWindowSize();
		const float sidebarW = 200.0f;
		const float contentPad = 16.0f;

		dl->AddRectFilled(wp, ImVec2(wp.x + ws.x, wp.y + ws.y), U32(ColBg()), 8.0f);
		dl->AddRect(wp, ImVec2(wp.x + ws.x, wp.y + ws.y), U32(ColOuter()), 8.0f, 0, 1.35f);
		if (st.backGlow > 0.01f)
		{
			dl->AddRectFilledMultiColor(
				ImVec2(wp.x + sidebarW, wp.y), ImVec2(wp.x + ws.x, wp.y + ws.y),
				U32A(ColAccent(), 0.0f), U32A(ColAccent(), 0.04f * st.backGlow),
				U32A(ColAccent(), 0.09f * st.backGlow), U32A(ColAccent(), 0.03f * st.backGlow));
		}

		dl->AddRectFilled(wp, ImVec2(wp.x + sidebarW, wp.y + ws.y), U32(ColSidebar()), 8.0f, ImDrawFlags_RoundCornersLeft);
		DrawLogo(dl, wp, st.logoTex, st.logoSize);

		ImGui::SetCursorPos(ImVec2(0.0f, 0.0f));
		ImGui::InvisibleButton("##drag_top", ImVec2(ws.x, 40.0f));
		if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
		{
			st.menuX += ImGui::GetIO().MouseDelta.x;
			st.menuY += ImGui::GetIO().MouseDelta.y;
		}

		ImGui::SetCursorPos(ImVec2(10.0f, 72.0f));
		ImGui::BeginChild("##sidebar", ImVec2(sidebarW - 12.0f, ws.y - 84.0f), ImGuiChildFlags_None);

		auto section = [](const char* name)
		{
			ImGui::Dummy(ImVec2(0, 8));
			ImGui::TextColored(ColTextDim(), "  %s", name);
			ImGui::Dummy(ImVec2(0, 3));
		};

		const float navW = sidebarW - 24.0f;
		section("Combat");
		if (NavButton("Aiming", Icon::Crosshair, st.nav == 0, navW)) st.nav = 0;
		section("Visuals");
		if (NavButton("Visuals", Icon::Eye, st.nav == 1, navW)) st.nav = 1;
		section("Client");
		if (NavButton("Settings", Icon::Sliders, st.nav == 2, navW)) st.nav = 2;
		if (NavButton("Misc", Icon::Running, st.nav == 3, navW)) st.nav = 3;
		if (NavButton("Gambling", Icon::Dice, st.nav == 4, navW)) st.nav = 4;
		if (NavButton("Keybinds", Icon::Keyboard, st.nav == 5, navW)) st.nav = 5;

		ImGui::EndChild();

		const char* titles[]{ "Aim", "Visuals", "Settings", "Misc", "Gambling", "Keybinds" };
		ImGui::SetCursorPos(ImVec2(sidebarW + contentPad, 14.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, st.contentFade);
		ImGui::TextColored(ColTextDim(), "%s", titles[st.nav]);

		ImGui::SetCursorPos(ImVec2(sidebarW + contentPad, 40.0f));
		const float contentW = ws.x - sidebarW - contentPad * 2.0f;
		const float contentH = ws.y - 52.0f;
		ImGui::BeginChild("##content", ImVec2(contentW, contentH), ImGuiChildFlags_None);
		const float gap = 12.0f;

		if (st.nav == 0)
		{
			const float leftW = contentW * 0.38f;
			const float rightW = (contentW - leftW - gap * 2.0f) * 0.5f;
			const float tallH = contentH;
			const float shortH = contentH * 0.72f;

			ImGui::SetCursorPos(ImVec2(0, 0));
			BeginPanel("Aimbot", &st.aimbotEnabled, ImVec2(leftW, tallH), Icon::Crosshair);
			CheckboxRow("Toggle FOV", &st.aimbotFOVEnabled);
			CheckboxRow("Toggle prediction", &st.aimbotPredictionEnabled);
			CheckboxRow("Wall check", &st.aimbotWallCheck);
			ComboRow("Lock Parts", &st.aimbotLockPart, lockParts, IM_ARRAYSIZE(lockParts));
			SliderRowF("FOV radius", &st.aimbotFOVRadius, 1.0f, 400.0f);
			SliderRowF("Aimbot strength", &st.aimbotStrenght, 0.05f, 5.0f, "%.2f");
			SliderRowF("Prediction X", &st.aimbotPredictionX, 0.0f, 20.0f);
			SliderRowF("Prediction Y", &st.aimbotPredictionY, 0.0f, 20.0f);
			ColorRow("FOV color", (float*)&st.aimbotFovColor);
			BindPickerRow("Aimbot key", &st.aimbotKey);
			CheckboxRow("Toggle lock", &st.aimbotToggleLock);
			if (st.aimbotToggleLock)
				st.aimbotHoldSwitch = false;
			CheckboxRow("Hold lock (can swap)", &st.aimbotHoldSwitch);
			if (st.aimbotHoldSwitch)
				st.aimbotToggleLock = false;
			ImGui::TextColored(ColTextDim(), "Hold lock: keep holding to aim; closest in FOV can change.");
			EndPanel();

			ImGui::SetCursorPos(ImVec2(leftW + gap, 0));
			BeginPanel("Triggerbot", &st.triggerbotEnabled, ImVec2(rightW, shortH), Icon::Crosshair);
			CheckboxRow("Toggle FOV", &st.triggerbotFOVEnabled);
			CheckboxRow("Show prediction dot", &st.triggerbotShowPredDot);
			CheckboxRow("Toggle prediction", &st.triggerbotPredictionEnabled);
			CheckboxRow("Indicate clicking", &st.triggerbotIndicateClicking);
			CheckboxRow("Right click", &st.triggerbotRightClick);
			CheckboxRow("Wall check", &st.triggerbotWallCheck);
			ImGui::TextColored(ColTextDim(), "Prediction uses Aimbot X/Y values. Dot = where to aim to trigger.");
			ComboRow("Trigger parts", &st.triggerbotTriggerPart, triggerParts, IM_ARRAYSIZE(triggerParts));
			SliderRowF("Detection radius", &st.triggerbotDetectionRadius, 1.0f, 100.0f);
			SliderRowF("Delay (ms)", &st.triggerbotDelayMs, 0.0f, 500.0f, "%.0f");
			ColorRow("FOV color", (float*)&st.triggerbotFovColor);
			BindPickerRow("Triggerbot key", &st.triggerbotKey);
			EndPanel();

			ImGui::SetCursorPos(ImVec2(leftW + gap * 2.0f + rightW, 0));
			BeginPanel("Silent Aim", &st.silentAimEnabled, ImVec2(rightW, shortH), Icon::Crosshair);
			ComboRow("Lock Parts", &st.silentAimLockPart, lockParts, IM_ARRAYSIZE(lockParts));
			SliderRowF("FOV Radius", &st.silentAimFOVRadius, 1.0f, 1000.0f, "%.0f");
			EndPanel();
		}
		else if (st.nav == 1)
		{
			const float panelW = (contentW - gap) * 0.5f;
			ImGui::SetCursorPos(ImVec2(0, 0));
			BeginPanel("ESP", &st.espEnabled, ImVec2(panelW, contentH), Icon::Eye);
			ComboRow("ESP Type", &st.espType, espTypes, IM_ARRAYSIZE(espTypes));
			CheckboxRow("Filled ESP", &st.espFilled);
			CheckboxRow("Show name", &st.espShowName);
			CheckboxRow("Show health", &st.espShowHealth);
			CheckboxRow("Show distance", &st.espShowDistance);
			CheckboxRow("Ignore dead players", &st.espIgnoreDeadPlrs);
			SliderRowI("ESP distance", &st.espDistance, 0, 500);
			ColorRow("ESP color", (float*)&st.espColor);
			if (FullButton("Preview ESP"))
				st.espPreviewOpened = !st.espPreviewOpened;
			EndPanel();

			ImGui::SetCursorPos(ImVec2(panelW + gap, 0));
			BeginPanel("Tracers", &st.tracersEnabled, ImVec2(panelW, contentH * 0.55f), Icon::Globe);
			ComboRow("Tracer Type", &st.tracerType, tracerTypes, IM_ARRAYSIZE(tracerTypes));
			ColorRow("Tracer color", (float*)&st.tracerColor);
			EndPanel();
		}
		else if (st.nav == 2)
		{
			const float panelW = (contentW - gap) * 0.5f;
			ImGui::SetCursorPos(ImVec2(0, 0));
			BeginPanel("Configs", nullptr, ImVec2(panelW, contentH), Icon::Folder);
			CheckboxRow("Auto save", &st.autoSaveEnabled);
			if (st.autoSaveEnabled)
			{
				if (st.configFileName[0])
					ImGui::TextColored(ColFriend(), "Saving every ~1.5s into \"%s\".", st.configFileName);
				else
					ImGui::TextColored(ColAccent(), "Pick or Create a config first.");
			}
			else
				ImGui::TextColored(ColTextDim(), "Off by default — turn on only when you want live writes.");
			if (st.configCount > 0)
			{
				if (ComboRow("Config list", &st.configIdx, st.configListPtrs, st.configCount)
					&& st.configIdx >= 0 && st.configIdx < st.configCount)
				{
					strncpy_s(st.configFileName, st.configList[st.configIdx], _TRUNCATE);
				}
			}
			else
				ImGui::TextColored(ColTextDim(), "No configs yet — type a name and Create.");
			ImGui::TextColored(ColTextDim(), "Config name");
			ImGui::SetNextItemWidth(-1.0f);
			ImGui::InputText("##cfgname", st.configFileName, IM_ARRAYSIZE(st.configFileName));
			if (FullButton("Create config") && st.onCreateConfig) st.onCreateConfig();
			if (FullButton("Save config") && st.onSaveConfig) st.onSaveConfig();
			if (FullButton("Load config") && st.onLoadConfig)
			{
				st.autoSaveEnabled = false;
				st.onLoadConfig();
			}
			if (FullButton("Refresh list"))
				st.requestRefreshConfigs = true;
			if (st.configStatus[0])
				ImGui::TextColored(ColFriend(), "%s", st.configStatus);
			ImGui::Spacing();
			ImGui::TextWrapped("Type a name then Create for a new profile. Select one from the list to autosave/save into it.");
			ImGui::Spacing();
			ImGui::TextWrapped("Use the bottom Theme button to change themes.");
			EndPanel();

			ImGui::SetCursorPos(ImVec2(panelW + gap, 0));
			BeginPanel("General", nullptr, ImVec2(panelW, contentH * 0.7f), Icon::Sliders);
			CheckboxRow("Roblox window needs to be selected", &st.rbxWindowNeedsToBeSelected);
			SliderRowI("Main loop delay (ms)", &st.mainLoopDelay, 0, 50);
			BindPickerRow("Toggle GUI key", &st.toggleGuiKey);
			if (!st.highEndVisuals)
			{
				ImGui::Spacing();
				ImGui::TextColored(ColAccent(), "Low end");
				if (st.sessionBoost)
					ImGui::TextColored(ColFriend(), "Boost is on for this launch only.");
				else
					ImGui::TextWrapped("Click once to raise CPU priority so aim/ESP stay smoother. Turns off when you close.");
				if (!st.sessionBoost)
				{
					if (FullButton("Boost this session"))
						st.sessionBoost = true;
				}
				else
				{
					ImGui::BeginDisabled();
					FullButton("Boost active");
					ImGui::EndDisabled();
				}
			}
			ImGui::Spacing();
			ImGui::TextWrapped("If fly or noclip locks your character, force reset unlocks walking and collision.");
			if (FullButton("Force reset character"))
				st.requestForceReset = true;
			ImGui::Spacing();
			if (FullButton("Exit"))
				st.requestExit = true;
			EndPanel();
		}
		else if (st.nav == 3)
		{
			const float colW = (contentW - gap) * 0.5f;
			const float topH = contentH * 0.58f;
			const float botH = contentH - topH - gap;

			ImGui::SetCursorPos(ImVec2(0, 0));
			BeginPanel("Teleport", nullptr, ImVec2(colW, topH), Icon::Globe);
			ImGui::TextColored(ColTextDim(), "X");
			ImGui::SetNextItemWidth(-1); ImGui::InputFloat("##x", &st.tpX);
			ImGui::TextColored(ColTextDim(), "Y");
			ImGui::SetNextItemWidth(-1); ImGui::InputFloat("##y", &st.tpY);
			ImGui::TextColored(ColTextDim(), "Z");
			ImGui::SetNextItemWidth(-1); ImGui::InputFloat("##z", &st.tpZ);
			if (FullButton("Set coordinates"))
				st.tpAction = DemoState::TpAction::SetFromLocal;
			if (FullButton("Clear coordinates"))
				st.tpAction = DemoState::TpAction::Clear;
			if (FullButton("Teleport to coordinates"))
				st.tpAction = DemoState::TpAction::Teleport;
			ImGui::TextDisabled("Orbit and spectate are in the Players window.");
			EndPanel();

			ImGui::SetCursorPos(ImVec2(colW + gap, 0));
			BeginPanel("Movement / Stream", nullptr, ImVec2(colW, topH), Icon::Running);
			CheckboxRow("Toggle fly", &st.flyEnabled);
			BindPickerRow("Fly key", &st.flyKey);
			ComboRow("Fly mode", &st.flyMode, flyModes, IM_ARRAYSIZE(flyModes));
			SliderRowF("Fly speed", &st.flySpeed, 1.0f, 200.0f);
			CheckboxRow("Behind player", &st.behindPlayerEnabled);
			BindPickerRow("Behind key", &st.behindPlayerKey);
			SliderRowF("Behind distance", &st.behindPlayerDistance, 1.0f, 20.0f);
			SliderRowF("Behind FOV", &st.behindPlayerFOV, 50.0f, 500.0f, "%.0f");
			CheckboxRow("Toggle noclip", &st.noclipEnabled);
			SliderRowF("Orbit distance", &st.orbitDistanceMultiplier, 0.25f, 5.0f, "%.2fx");
			SliderRowF("Orbit speed", &st.orbitSpeedMultiplier, 0.1f, 5.0f, "%.2fx");
			CheckboxRow("Hide Stream", &st.streamproofEnabled);
			ImGui::TextWrapped("Hides the overlay from OBS and other capture software.");
			EndPanel();

			ImGui::SetCursorPos(ImVec2(0, topH + gap));
			BeginPanel("Humanoid", nullptr, ImVec2(contentW, botH), Icon::Person);
			CheckboxRow("WalkSpeed active", &st.walkSpeedEnabled);
			BindPickerRow("WalkSpeed key", &st.walkSpeedKey);
			SliderRowI("WalkSpeed", &st.walkSpeedSet, 0, 1000);
			CheckboxRow("JumpPower active", &st.jumpPowerEnabled);
			BindPickerRow("JumpPower key", &st.jumpPowerKey);
			SliderRowI("JumpPower", &st.jumpPowerSet, 0, 1000);
			ImGui::TextDisabled("Key toggles the active checkbox. Sliders apply while on.");
			EndPanel();
		}
		else if (st.nav == 4)
		{
			const float headerH = 56.0f;
			{
				ImDrawList* hdl = ImGui::GetWindowDrawList();
				const ImVec2 hp = ImGui::GetCursorScreenPos();
				hdl->AddRectFilled(hp, ImVec2(hp.x + contentW, hp.y + 48.0f), U32(ColPanel()), 8.0f);
				hdl->AddRect(ImVec2(hp.x + 1, hp.y + 1), ImVec2(hp.x + contentW - 1, hp.y + 47.0f), U32(ColOuter()), 8.0f, 0, 1.1f);
				char bank[64];
				ImFormatString(bank, IM_ARRAYSIZE(bank), "Balance   $%d", st.gamblingBalance);
				hdl->AddText(ImGui::GetFont(), 20.0f, ImVec2(hp.x + 16.0f, hp.y + 12.0f), U32(ColAccent()), bank);
				hdl->AddText(ImVec2(hp.x + 220.0f, hp.y + 16.0f), U32(ColTextDim()), "Starts at $500  ·  +$500 each day  ·  set a bet on each game");
				ImGui::Dummy(ImVec2(contentW, headerH));
			}
			const float bodyH = contentH - headerH;
			const float colW = (contentW - gap * 2.0f) / 3.0f;

			auto betRow = [](const char* id, int* bet, int balance)
			{
				ImGui::TextColored(ColTextDim(), "Bet amount");
				if (*bet < 1) *bet = 1;
				if (*bet > 500) *bet = 500;
				ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - 4.0f);
				ImGui::SliderInt(id, bet, 1, 500, "$%d");
				if (*bet > balance)
					ImGui::TextColored(ColEnemy(), "Not enough balance.");
			};

			// ---- Slots ----
			ImGui::SetCursorPos(ImVec2(0, headerH));
			BeginPanel("Slots", nullptr, ImVec2(colW, bodyH), Icon::Dice);

			if (st.slotSpinning)
			{
				st.slotSpinT += ImGui::GetIO().DeltaTime;
				for (int i = 0; i < 3; ++i)
				{
					const float delay = i * 0.18f;
					const float local = ImClamp((st.slotSpinT - delay) / ImMax(st.slotSpinDur - delay, 0.05f), 0.0f, 1.0f);
					const float ease = 1.0f - (1.0f - local) * (1.0f - local);
					st.slotOffset[i] = (1.0f - ease) * 18.0f + sinf(st.slotSpinT * (18.0f - i * 3.0f)) * (1.0f - ease) * 10.0f;
					if (local < 1.0f)
					{
						int& v = (i == 0 ? st.slot1 : (i == 1 ? st.slot2 : st.slot3));
						v = (v + 1 + (int)(ImGui::GetIO().DeltaTime * 40.0f)) % 10;
					}
					else
					{
						if (i == 0) st.slot1 = st.slotTarget1;
						if (i == 1) st.slot2 = st.slotTarget2;
						if (i == 2) st.slot3 = st.slotTarget3;
					}
				}
				if (st.slotSpinT >= st.slotSpinDur)
				{
					st.slotSpinning = false;
					st.slot1 = st.slotTarget1;
					st.slot2 = st.slotTarget2;
					st.slot3 = st.slotTarget3;
					st.slotOffset[0] = st.slotOffset[1] = st.slotOffset[2] = 0.0f;
					int payout = 0;
					if (st.slot1 == st.slot2 && st.slot2 == st.slot3)
						payout = st.slotBet * 10;
					else if (st.slot1 == st.slot2 || st.slot2 == st.slot3 || st.slot1 == st.slot3)
						payout = st.slotBet * 2;
					if (payout > 0)
					{
						st.gamblingBalance += payout;
						SaveWallet(st);
					}
				}
			}

			{
				ImDrawList* sdl = ImGui::GetWindowDrawList();
				const ImVec2 base = ImGui::GetCursorScreenPos();
				const float reelW = 54.0f, reelH = 72.0f, gapR = 10.0f;
				const float totalW = reelW * 3.0f + gapR * 2.0f;
				const float startX = base.x + (ImGui::GetContentRegionAvail().x - totalW) * 0.5f;
				const int vals[3]{ st.slot1, st.slot2, st.slot3 };
				for (int i = 0; i < 3; ++i)
				{
					const ImVec2 a(startX + i * (reelW + gapR), base.y);
					const ImVec2 b(a.x + reelW, a.y + reelH);
					DrawInsetFrame(sdl, a, b, 6.0f);
					char buf[8]; ImFormatString(buf, IM_ARRAYSIZE(buf), "%d", vals[i]);
					const ImVec2 ts = ImGui::CalcTextSize(buf);
					sdl->AddText(ImGui::GetFont(), 28.0f,
						ImVec2(a.x + (reelW - ts.x * 1.5f) * 0.5f, a.y + (reelH - 28.0f) * 0.5f + st.slotOffset[i]),
						U32(ColTextOn()), buf);
				}
				ImGui::Dummy(ImVec2(0, reelH + 12.0f));
			}

			betRow("##slotbet", &st.slotBet, st.gamblingBalance);
			const bool canSpin = !st.slotSpinning && st.gamblingBalance >= st.slotBet;
			if (canSpin && FullButton("Spin"))
			{
				st.gamblingBalance -= st.slotBet;
				SaveWallet(st);
				st.slotSpinning = true;
				st.slotSpinT = 0.0f;
				st.slotSpinDur = 1.35f;
				st.slotTarget1 = rand() % 10;
				st.slotTarget2 = rand() % 10;
				st.slotTarget3 = rand() % 10;
			}
			else if (st.slotSpinning)
			{
				ImGui::BeginDisabled();
				FullButton("Spinning...");
				ImGui::EndDisabled();
			}
			else
			{
				ImGui::BeginDisabled();
				FullButton("Spin");
				ImGui::EndDisabled();
			}
			if (!st.slotSpinning && st.slot1 == st.slot2 && st.slot2 == st.slot3)
				ImGui::TextColored(ColFriend(), "Jackpot!  10x");
			EndPanel();

			// ---- Blackjack ----
			ImGui::SetCursorPos(ImVec2(colW + gap, headerH));
			BeginPanel("Blackjack", nullptr, ImVec2(colW, bodyH), Icon::Box);
			betRow("##bjbet", &st.bjBet, st.gamblingBalance);
			ImGui::TextWrapped("%s", st.bjMsg);
			ImGui::Spacing();

			auto dealCard = []() { return rand() % 52; };
			if (st.bjPhase == 0 || st.bjPhase == 3)
			{
				if (st.gamblingBalance >= st.bjBet && FullButton("Deal"))
				{
					st.gamblingBalance -= st.bjBet;
					st.bjSettled = false;
					SaveWallet(st);
					st.bjPlayerCount = st.bjDealerCount = 0;
					st.bjPlayer[st.bjPlayerCount++] = dealCard();
					st.bjDealer[st.bjDealerCount++] = dealCard();
					st.bjPlayer[st.bjPlayerCount++] = dealCard();
					st.bjDealer[st.bjDealerCount++] = dealCard();
					st.bjPhase = 1;
					ImFormatString(st.bjMsg, IM_ARRAYSIZE(st.bjMsg), "Your move.");
					if (HandTotal(st.bjPlayer, st.bjPlayerCount) == 21)
					{
						st.bjPhase = 3;
						st.gamblingBalance += (int)(st.bjBet * 2.5f);
						st.bjSettled = true;
						SaveWallet(st);
						ImFormatString(st.bjMsg, IM_ARRAYSIZE(st.bjMsg), "Blackjack! +$%d", (int)(st.bjBet * 2.5f));
					}
				}
				else if (st.bjPhase == 0 || st.bjPhase == 3)
				{
					if (st.gamblingBalance < st.bjBet)
					{
						ImGui::BeginDisabled();
						FullButton("Deal");
						ImGui::EndDisabled();
					}
				}
			}
			else if (st.bjPhase == 1)
			{
				if (FullButton("Hit") && st.bjPlayerCount < 8)
				{
					st.bjPlayer[st.bjPlayerCount++] = dealCard();
					const int pt = HandTotal(st.bjPlayer, st.bjPlayerCount);
					if (pt > 21)
					{
						st.bjPhase = 3;
						st.bjSettled = true;
						ImFormatString(st.bjMsg, IM_ARRAYSIZE(st.bjMsg), "Bust (%d). Dealer wins.", pt);
					}
				}
				if (FullButton("Stand"))
				{
					while (HandTotal(st.bjDealer, st.bjDealerCount) < 17 && st.bjDealerCount < 8)
						st.bjDealer[st.bjDealerCount++] = dealCard();
					const int pt = HandTotal(st.bjPlayer, st.bjPlayerCount);
					const int dt = HandTotal(st.bjDealer, st.bjDealerCount);
					st.bjPhase = 3;
					if (dt > 21)
					{
						st.gamblingBalance += st.bjBet * 2;
						ImFormatString(st.bjMsg, IM_ARRAYSIZE(st.bjMsg), "Dealer bust. +$%d", st.bjBet * 2);
					}
					else if (pt > dt)
					{
						st.gamblingBalance += st.bjBet * 2;
						ImFormatString(st.bjMsg, IM_ARRAYSIZE(st.bjMsg), "You win! +$%d", st.bjBet * 2);
					}
					else if (pt < dt)
						ImFormatString(st.bjMsg, IM_ARRAYSIZE(st.bjMsg), "You lose. -$%d", st.bjBet);
					else
					{
						st.gamblingBalance += st.bjBet;
						ImFormatString(st.bjMsg, IM_ARRAYSIZE(st.bjMsg), "Push. Bet returned.");
					}
					st.bjSettled = true;
					SaveWallet(st);
				}
			}

			ImGui::Spacing();
			{
				char dealerLabel[48];
				if (st.bjPhase == 1)
					ImFormatString(dealerLabel, IM_ARRAYSIZE(dealerLabel), "Dealer  ?");
				else
					ImFormatString(dealerLabel, IM_ARRAYSIZE(dealerLabel), "Dealer  %d", HandTotal(st.bjDealer, st.bjDealerCount));
				ImGui::TextColored(ColAccent(), "%s", dealerLabel);
			}
			{
				ImDrawList* cdl = ImGui::GetWindowDrawList();
				ImVec2 cpos = ImGui::GetCursorScreenPos();
				for (int i = 0; i < st.bjDealerCount; ++i)
				{
					const bool hide = (i == 1 && st.bjPhase == 1);
					DrawCardFace(cdl, ImVec2(cpos.x + i * 38.0f, cpos.y), 48.0f, 64.0f, st.bjDealer[i], hide);
				}
				ImGui::Dummy(ImVec2(0, 72.0f));
			}
			ImGui::TextColored(ColAccent(), "You  %d", HandTotal(st.bjPlayer, st.bjPlayerCount));
			{
				ImDrawList* cdl = ImGui::GetWindowDrawList();
				ImVec2 cpos = ImGui::GetCursorScreenPos();
				for (int i = 0; i < st.bjPlayerCount; ++i)
					DrawCardFace(cdl, ImVec2(cpos.x + i * 38.0f, cpos.y), 48.0f, 64.0f, st.bjPlayer[i], false);
				ImGui::Dummy(ImVec2(0, 72.0f));
			}
			EndPanel();

			// ---- Mines ----
			ImGui::SetCursorPos(ImVec2(colW * 2.0f + gap * 2.0f, headerH));
			BeginPanel("Mines", nullptr, ImVec2(colW, bodyH), Icon::Box);
			betRow("##minesbet", &st.minesBet, st.gamblingBalance);
			ImGui::TextColored(ColTextDim(), "Bombs");
			ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - 4.0f);
			ImGui::SliderInt("##mbombs", &st.minesBombs, 1, 12);
			ImGui::Text("Safe: %d   Mult: %.2fx", st.minesSafe, st.minesMult);

			if (!st.minesActive)
			{
				if (st.gamblingBalance >= st.minesBet && FullButton("Start round"))
				{
					st.gamblingBalance -= st.minesBet;
					SaveWallet(st);
					for (int i = 0; i < DemoState::MinesN; ++i) { st.minesBomb[i] = false; st.minesRevealed[i] = false; }
					int placed = 0;
					while (placed < st.minesBombs)
					{
						const int idx = rand() % DemoState::MinesN;
						if (!st.minesBomb[idx]) { st.minesBomb[idx] = true; ++placed; }
					}
					st.minesActive = true;
					st.minesDead = false;
					st.minesCashed = false;
					st.minesSafe = 0;
					st.minesMult = 1.0f;
				}
				else if (st.gamblingBalance < st.minesBet)
				{
					ImGui::BeginDisabled();
					FullButton("Start round");
					ImGui::EndDisabled();
				}
			}
			else
			{
				if (!st.minesDead && !st.minesCashed && FullButton("Cash out"))
				{
					st.minesCashed = true;
					st.minesActive = false;
					const int win = (int)(st.minesBet * st.minesMult);
					st.gamblingBalance += win;
					SaveWallet(st);
					for (int i = 0; i < DemoState::MinesN; ++i) st.minesRevealed[i] = true;
				}
				if ((st.minesDead || st.minesCashed) && FullButton("New round"))
				{
					st.minesActive = false;
					st.minesDead = false;
					st.minesCashed = false;
				}
			}

			ImGui::Spacing();
			const float cell = 36.0f;
			const float gridGap = 4.0f;
			ImDrawList* mdl = ImGui::GetWindowDrawList();
			const ImVec2 g0 = ImGui::GetCursorScreenPos();
			for (int i = 0; i < DemoState::MinesN; ++i)
			{
				const int row = i / 5, col = i % 5;
				const ImVec2 a(g0.x + col * (cell + gridGap), g0.y + row * (cell + gridGap));
				const ImVec2 b(a.x + cell, a.y + cell);
				ImGui::SetCursorScreenPos(a);
				ImGui::PushID(i);
				const bool clicked = ImGui::InvisibleButton("##m", ImVec2(cell, cell));
				const bool hovered = ImGui::IsItemHovered();

				ImU32 fill = U32(ColTrack());
				if (st.minesRevealed[i])
					fill = st.minesBomb[i] ? U32(ColEnemy()) : U32A(ColFriend(), 0.55f);
				else if (hovered && st.minesActive && !st.minesDead)
					fill = U32(ColNavActive());

				mdl->AddRectFilled(ImVec2(a.x + 1, a.y + 1), ImVec2(b.x - 1, b.y - 1), fill, 4.0f);
				mdl->AddRect(ImVec2(a.x + 1, a.y + 1), ImVec2(b.x - 1, b.y - 1), U32(ColTrackOutline()), 4.0f, 0, 1.1f);

				if (st.minesRevealed[i])
				{
					const char* mark = st.minesBomb[i] ? "X" : "*";
					const ImVec2 ts = ImGui::CalcTextSize(mark);
					mdl->AddText(ImVec2(a.x + (cell - ts.x) * 0.5f, a.y + (cell - ts.y) * 0.5f), U32(ColTextOn()), mark);
				}

				if (clicked && st.minesActive && !st.minesDead && !st.minesCashed && !st.minesRevealed[i])
				{
					st.minesRevealed[i] = true;
					if (st.minesBomb[i])
					{
						st.minesDead = true;
						st.minesActive = false;
						for (int j = 0; j < DemoState::MinesN; ++j) st.minesRevealed[j] = true;
					}
					else
					{
						st.minesSafe++;
						st.minesMult *= 1.0f + (float)st.minesBombs * 0.08f;
					}
				}
				ImGui::PopID();
			}
			ImGui::SetCursorScreenPos(ImVec2(g0.x, g0.y + 5.0f * (cell + gridGap) + 8.0f));
			ImGui::Dummy(ImVec2(0, 0));
			if (st.minesDead) ImGui::TextColored(ColEnemy(), "Boom — you hit a mine.");
			if (st.minesCashed) ImGui::TextColored(ColFriend(), "Cashed out at %.2fx", st.minesMult);
			EndPanel();
		}
		else if (st.nav == 5)
		{
			ImGui::SetCursorPos(ImVec2(0, 0));
			BeginPanel("Keybinds", nullptr, ImVec2(contentW * 0.55f, contentH * 0.55f), Icon::Keyboard);
			CheckboxRow("Show floating keybind list", &st.keybindListVisible);
			ImGui::Spacing();
			ImGui::TextWrapped("Click a bind, then press a key. Backspace or Escape clears it.");
			ImGui::Separator();
			BindPickerRow("Aimbot", &st.aimbotKey);
			BindPickerRow("Triggerbot", &st.triggerbotKey);
			BindPickerRow("Fly", &st.flyKey);
			BindPickerRow("Behind player", &st.behindPlayerKey);
			BindPickerRow("WalkSpeed", &st.walkSpeedKey);
			BindPickerRow("JumpPower", &st.jumpPowerKey);
			BindPickerRow("Toggle GUI", &st.toggleGuiKey);
			EndPanel();
		}

		ImGui::EndChild();
		ImGui::PopStyleVar();
		ImGui::End();
	}
}
