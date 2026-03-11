#pragma once
#define PI			3.14159265358979323846
#include <DirectXMath.h>
#define RAD2DEG(x) DirectX::XMConvertToDegrees(x)
#define DEG2RAD(x) DirectX::XMConvertToRadians(x)
#define M_PI 3.14159265358979323846f
namespace render2 {
	enum e_textflags {
		none = 0,
		outline = 1 << 0,
		centered_x = 1 << 1,
		centered_y = 1 << 2,
		dropShadow = 1 << 3,
	};
	enum e_cornerflags {
		Default = 15,
		corner_left_top = 1 << 0,
		corner_right_top = 1 << 1,
		corner_left_bot = 1 << 2,
		corner_right_bot = 1 << 3,
		corner_top = ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersTopRight,   // 0x3
		corner_bot = ImDrawFlags_RoundCornersBottomLeft | ImDrawFlags_RoundCornersBottomRight,   // 0xC
		corner_left = ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersBottomLeft,    // 0x5
		corner_right = ImDrawFlags_RoundCornersTopRight | ImDrawFlags_RoundCornersBottomRight,  // 0xA
	};
}
class ImGuiRendering {
public:
	
	ImFont* smallest_pixel;
	ImFont* esp_name;
	ImFont* esp_weapon;
	void BeginScene();
	void EndScene();
	void arc(float x, float y, float radius, float min_angle, float max_angle, ImColor col, float thickness) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		DrawList->PathArcTo(ImVec2(x, y), radius, DEG2RAD(min_angle), DEG2RAD(max_angle), 32);
		DrawList->PathStroke(ImColor(col), false, thickness);
	}
	void two_sided_arc(float x, float y, float radius, float scale, ImColor col, float thickness) {
		arc(x, y, radius, -270, -90 - 90 * (scale * 2), col, thickness);
		arc(x, y, radius, -90 + 90 * (scale * 2), 90, col, thickness);
	}
	void PolyLine(const ImVec2* points, const int points_count, ImColor clr, bool closed, float thickness, ImColor fill) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		DrawList->AddConvexPolyFilled(points, points_count, fill);
		DrawList->AddPolyline(points, points_count, clr, closed, thickness);
	}
	void never_arrows(float x, float y, float radius, float min_angle, float max_angle, ImColor col, float thickness) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		DrawList->PathArcTo(ImVec2(x, y), radius, DEG2RAD(min_angle), DEG2RAD(max_angle), 32);
		DrawList->PathStroke(ImColor(col), false, thickness);
	}
	void DrawLine(ImVec2 pos, ImVec2 Size, ImColor clr, float thickness, bool outline = false) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		if (outline)
			DrawList->AddLine(ImVec2(pos.x, pos.y), ImVec2(Size.x, Size.y), ImColor(0, 0, 0), thickness * 2);
		DrawList->AddLine(ImVec2(pos.x, pos.y), ImVec2(Size.x, Size.y), clr, thickness);
	}

	void DrawCircle(ImVec2 pos, float r, float s, ImColor color) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		DrawList->AddCircle(ImVec2(pos.x, pos.y), r, color, 64, s);
	}
	void DrawFilledCircle(ImVec2 pos, float r, ImColor color) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		DrawList->AddCircleFilled(ImVec2(pos.x, pos.y), r + 1, ImColor(0, 0, 0, 255), 64);
		DrawList->AddCircleFilled(ImVec2(pos.x, pos.y), r, color, 64);
	}

	std::string string_To_UTF8(const std::string& str) {
		int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
		wchar_t* pwBuf = new wchar_t[nwLen + 1];
		ZeroMemory(pwBuf, nwLen * 2 + 2);
		::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);
		int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
		char* pBuf = new char[nLen + 1];
		ZeroMemory(pBuf, nLen + 1);
		::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
		std::string retStr(pBuf);
		delete[]pwBuf;
		delete[]pBuf;
		pwBuf = NULL;
		pBuf = NULL;
		return retStr;
	}
	void DrawString(ImVec2 coord, ImColor color, int flags, ImFont* font, float size_text, const char* message, ...) {
		std::string utf_8_1 = std::string(message);
		std::string utf_8_2 = string_To_UTF8(utf_8_1);
		auto size = font->CalcTextSizeA(size_text, FLT_MAX, 0, utf_8_2.c_str(), NULL);
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		auto coord_out = ImVec2{ coord.x, coord.y };
		ImColor outline_clr = ImColor(0, 0, 0, 255);
		int width = 0, height = 0;
		if (!(flags & render2::centered_x)) size.x = 0;
		if (!(flags & render2::centered_y)) size.y = 0;
		ImVec2 pos = ImVec2(coord.x - (size.x / 2), coord.y - (size.y / 2));
		if (flags & render2::outline) {
			DrawList->AddText(font, size_text, ImVec2(pos.x, pos.y + 1), outline_clr, utf_8_2.c_str());
			DrawList->AddText(font, size_text, ImVec2(pos.x + 1, pos.y), outline_clr, utf_8_2.c_str());
			DrawList->AddText(font, size_text, ImVec2(pos.x, pos.y - 1), outline_clr, utf_8_2.c_str());
			DrawList->AddText(font, size_text, ImVec2(pos.x - 1, pos.y), outline_clr, utf_8_2.c_str());
		}
		if (flags & render2::dropShadow) {
			DrawList->AddText(font, size_text, ImVec2(pos.x, pos.y + 1), outline_clr, utf_8_2.c_str());
		}
		DrawList->AddText(font, size_text, pos, color, utf_8_2.c_str());
	}
	void DrawTexture(ImVec2 pos, int flags, ImVec2 size, ImColor color, ImTextureID texture) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		auto coord = ImVec2(pos.x, pos.y);
		ImVec2 Size_ = ImVec2(size.x, size.y);
		if (!(flags & render2::centered_x)) Size_.x = 0;

		ImVec2 pos_ = ImVec2(coord.x - (Size_.x / 2), coord.y);

		DrawList->AddImage(texture, pos_, pos_ + size, ImVec2(0, 0), ImVec2(0, 0), color);

	}
	void DrawEspBox(Vector2 leftUpCorn, Vector2 rightDownCorn, ImColor clr, float width) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		ImVec2 min = ImVec2(leftUpCorn.x, leftUpCorn.y);
		ImVec2 max = ImVec2(min.x + rightDownCorn.x, min.y + rightDownCorn.y);
		DrawList->AddRect(min, max, clr, 0.0F, -1, width);
	}
	void DrawRoundBox(Vector2 leftUpCorn, Vector2 rightDownCorn, ImColor clr, float width) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		ImVec2 min = ImVec2(leftUpCorn.x, leftUpCorn.y);
		ImVec2 max = ImVec2(min.x + rightDownCorn.x, min.y + rightDownCorn.y);
		DrawList->AddRect(min, max, clr, 5.0F, -1, width);
	}
	void DrawCornerBox(const ImVec2& leftUpCorn, const ImVec2& rightUpCorn, const ImVec2& leftDownCorn, const ImVec2& rightDownCorn, ImColor clr, float width) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		DrawList->AddLine(leftUpCorn, leftUpCorn - ImVec2((leftUpCorn.x - rightUpCorn.x) / 4, 0), clr, width);
		DrawList->AddLine(leftUpCorn, leftUpCorn - ImVec2(0, (leftUpCorn.x - rightUpCorn.x) / 4), clr, width);
		DrawList->AddLine(rightUpCorn, rightUpCorn + ImVec2((leftUpCorn.x - rightUpCorn.x) / 4, 0), clr, width);
		DrawList->AddLine(rightUpCorn, rightUpCorn - ImVec2(0, (leftUpCorn.x - rightUpCorn.x) / 4), clr, width);
		DrawList->AddLine(leftDownCorn, leftDownCorn - ImVec2((leftUpCorn.x - rightUpCorn.x) / 4, 0), clr, width);
		DrawList->AddLine(leftDownCorn, leftDownCorn + ImVec2(0, (leftUpCorn.x - rightUpCorn.x) / 4), clr, width);
		DrawList->AddLine(rightDownCorn, rightDownCorn + ImVec2((leftUpCorn.x - rightUpCorn.x) / 4, 0), clr, width);
		DrawList->AddLine(rightDownCorn, rightDownCorn + ImVec2(0, (leftUpCorn.x - rightUpCorn.x) / 4), clr, width);
	}

	void DrawLineGradient(ImVec2 pos, ImVec2 size, ImColor clr1, ImColor cl2, float thickness, bool flip) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		if (!flip)
			DrawList->AddRectFilledMultiColor(ImVec2(pos.x, pos.y), ImVec2(pos.x + size.x, pos.y + size.x), clr1, cl2, cl2, clr1);
		else
			DrawList->AddRectFilledMultiColor(ImVec2(pos.x, pos.y), ImVec2(pos.x + size.x, pos.y + size.x), clr1, clr1, cl2, cl2);
	}
	void Rect(ImVec2 pos, ImVec2 Size, ImColor clr, float rounding, ImDrawFlags flags) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		DrawList->AddRect(ImVec2(pos.x, pos.y), ImVec2(pos.x + Size.x, pos.y + Size.y), clr, rounding, flags);
	}
	void Rect2(float x, float y, float w, float h, ImColor clr, float rounding, ImDrawFlags flags) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		DrawList->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), clr, rounding, flags);
	}
	void Rect3(float x, float y, float w, float h, ImColor clr, float rounding, ImDrawFlags flags, float thickness) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		DrawList->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), clr, rounding, flags, thickness);
	}
	void FilledRect(ImVec2 pos, ImVec2 Size, ImColor clr, float rounding = 0.f, ImDrawFlags flags = 0.f) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		DrawList->AddRectFilled(ImVec2(pos.x, pos.y), ImVec2(pos.x + Size.x, pos.y + Size.y), clr, rounding, flags);
	}
	void FilledRect3(float x, float y, float w, float h, ImColor clr, float rounding, ImDrawFlags flags) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		DrawList->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), clr, rounding, flags);
	}
	void FilledRectGradient(ImVec2 pos, ImVec2 Size, ImColor clr, ImColor clr2, ImColor clr3, ImColor clr4) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		DrawList->AddRectFilledMultiColor(ImVec2(pos.x, pos.y), ImVec2(pos.x + Size.x, pos.y + Size.y), clr, clr2, clr3, clr4);
	}
	void FilledRect2(ImVec2 pos, ImVec2 Size, ImColor clr, float rounding, ImDrawFlags flags) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		DrawList->AddRectFilled(ImVec2(pos.x, pos.y), ImVec2(Size.x, Size.y), clr, rounding, flags);
	}
	void Triangle(float x1, float y1, float x2, float y2, float x3, float y3, ImColor clr, float thickness) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		DrawList->AddTriangle(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), clr, thickness);
	}
	void TriangleFilled(float x1, float y1, float x2, float y2, float x3, float y3, ImColor clr) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		DrawList->AddTriangleFilled(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), clr);
	}
	void AddTriangleCsGo(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		DrawList->PathLineTo(p1);
		DrawList->PathLineTo(p2);
		DrawList->PathLineTo(p3);
		DrawList->PathLineTo(p4);
		DrawList->PathFillConvex(col);
	}
	void QuadFilled(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, ImColor clr) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		DrawList->AddQuadFilled(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), ImVec2(x4, y4), clr);
	}
	ImColor PercentColor(float Num, float alpha = 1.0f)
	{
		float red, green, blue;
		if (Num < 0.5)
		{
			red = Num * 2.f * 255.f;
			green = 255.f;
			blue = 0.f;
		}
		else
		{
			red = 255.f;
			green = (2.f - 2.f * Num) * 255.f;
			blue = 0.f;
		}

		return ImColor(red / 255, green / 255, blue / 255, alpha);
	}
	ImColor PercentColor2(float Num, float alpha = 1.0f)
	{
		float red, green, blue;
		if (Num < 0.5)
		{
			red = Num * 2.f * 255.f;
			green = 255.f;
			blue = 0.f;
		}
		else
		{
			red = 255.f;
			green = (2.f - 2.f * Num) * 255.f;
			blue = 0.f;
		}

		return ImColor(red / 255, green / 255, blue / 255, alpha);
	}

	void Progbar(Vector2 start, Vector2 end, float a, float b, ImColor alpha, float rounding, bool Vertical = false)
	{
		if (!Vertical)
		{
			FilledRect({ start.x, start.y }, { end.x, end.y + 1 }, ImColor(0.f, 0.f, 0.f, 255.f), rounding, ImDrawFlags_RoundCornersAll);
			if ((a / b) > 3) a = b;
			FilledRect({ start.x + 1, start.y + 1 }, { end.x * (a / b) - 1, end.y - 1 }, alpha, rounding, ImDrawFlags_RoundCornersAll);
		}
		else if (Vertical)
		{
			FilledRect({ start.x, start.y }, { end.x, end.y + 1 }, ImColor(0.f, 0.f, 0.f, 255.f), rounding, ImDrawFlags_RoundCornersAll);
			if ((a / b) > 3) a = b;
			FilledRect({ start.x + 1, start.y + (end.y + (-end.y * (a / b)))+1}, {end.x - 2, end.y * (a / b) - 1}, alpha, rounding, ImDrawFlags_RoundCornersAll);
		}
	}
	void ProgressBar(const Vector2 start, Vector2 end, float value, float z, ImColor alpha, float rounding)
	{
		FilledRect({ start.x, start.y }, { end.x , end.y }, ImColor(0.f, 0.f, 0.f, 255.f), rounding, ImDrawFlags_RoundCornersAll);
		float f = end.x;
		end.x = (start.x + (z * value));
		if (end.x > f) end.x = f - 2;
		//	rectangle_filled({ start.x + 1, start.y + 1 }, { (end.x - start.x) * (z / value), 4 }, fgcolor);
		FilledRect({ start.x + 1, start.y + 1 }, { end.x * (z / value), end.y - 2 }, alpha, rounding, ImDrawFlags_RoundCornersAll);

	}
#ifndef IM_DRAWLIST_ARCFAST_TABLE_SIZE
#define IM_DRAWLIST_ARCFAST_TABLE_SIZE                          48 // Number of samples in lookup table.
#endif
#define IM_DRAWLIST_ARCFAST_SAMPLE_MAX                          IM_DRAWLIST_ARCFAST_TABLE_SIZE // Sample index _PathArcToFastEx() for 360 angle.
	void AddRadialGradient(const ImVec2& center, float radius, ImU32 col_in, ImU32 col_out) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		if (((col_in | col_out) & IM_COL32_A_MASK) == 0 || radius < 0.5f) return;
		DrawList->PathArcToFast(center, radius, 0, IM_DRAWLIST_ARCFAST_SAMPLE_MAX);
		const int count = DrawList->_Path.Size - 1;
		unsigned int vtx_base = DrawList->_VtxCurrentIdx;
		DrawList->PrimReserve(count * 3, count + 1);
		const ImVec2 uv = DrawList->_Data->TexUvWhitePixel;
		DrawList->PrimWriteVtx(center, uv, col_in);
		for (int n = 0; n < count; n++) DrawList->PrimWriteVtx(DrawList->_Path[n], uv, col_out);
		for (int n = 0; n < count; n++) {
			DrawList->PrimWriteIdx((ImDrawIdx)(vtx_base));
			DrawList->PrimWriteIdx((ImDrawIdx)(vtx_base + 1 + n));
			DrawList->PrimWriteIdx((ImDrawIdx)(vtx_base + 1 + ((n + 1) % count)));
		}
		DrawList->_Path.Size = 0;
	}

	void CircleFilled(ImVec2 pos, float radius, ImColor col, int segments) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		DrawList->AddCircleFilled(ImVec2(pos.x, pos.y), radius, col, segments);
	}
};
inline ImGuiRendering* g_Render;
