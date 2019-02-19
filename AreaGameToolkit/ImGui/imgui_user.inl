// InjectMe
#include "../TextureFactory.hpp"

using namespace InjectMe::UI;

// ImGui
#include "imgui.h"
#include "imgui_user.h"

bool ImGui::BeginAsda(const char* name, bool* p_open, ImTextureID user_texture_id, const ImVec2& texture_size, const ImVec4& uv, ImGuiWindowFlags flags)
{
	ImTextureID n_01 = TextureFactory::Instance()->MakeTexture("juidata\\Image\\Texture.btz", "n_01.tex");
	ImTextureID ne_wheeltaget1 = TextureFactory::Instance()->MakeTexture("juidata\\Image\\Texture.btz", "ne_wheeltaget1.tex");
	auto doesCanDrawAsda = n_01 != NULL && ne_wheeltaget1 != NULL;
	//auto doesCanDrawAsda = false;

	flags |= ImGuiWindowFlags_NoCollapse;
	flags |= ImGuiWindowFlags_NoSavedSettings;

	if (doesCanDrawAsda)
	{
		flags |= ImGuiWindowFlags_NoTitleBar;
		flags |= ImGuiWindowFlags_NoResize;
		flags |= ImGuiWindowFlags_NoScrollbar;
		flags |= ImGuiWindowFlags_AlwaysAutoResize;
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
		if (ImGui::GetIO().Fonts->Fonts.size() > 5)
			ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[5]);
		ImGui::SetNextWindowBgAlpha(0);
	}

	auto result = ImGui::Begin(name, p_open, flags);

	if (doesCanDrawAsda)
		PopClipRect();

	if (doesCanDrawAsda && result)
	{
		// Позиция и размер окна
		auto pos = GetWindowPos(); auto size = GetWindowSize();

		if (user_texture_id != NULL)
		{
			// Первая строка
			AddImage(n_01, ImVec2(512, 512), pos, pos + ImVec2(48, 37), ImVec4(362, 471, 48, 37));
			AddImage(n_01, ImVec2(512, 512), pos + ImVec2(48, 0), pos + ImVec2(size.x - 86, 37), ImVec4(414, 471, 4, 37));
			AddImage(n_01, ImVec2(512, 512), pos + ImVec2(size.x - 86, 0), pos + ImVec2(size.x, 37), ImVec4(422, 471, 86, 37));

			// Вторая строка
			AddImage(n_01, ImVec2(512, 512), pos + ImVec2(0, 37), pos + ImVec2(20, size.y - 20), ImVec4(456, 439, 20, 4));
			AddImage(n_01, ImVec2(512, 512), pos + ImVec2(20, 37), pos + ImVec2(size.x - 20, size.y - 20), ImVec4(488, 439, 4, 4));
			AddImage(n_01, ImVec2(512, 512), pos + ImVec2(size.x - 20, 37), pos + ImVec2(size.x, size.y - 20), ImVec4(488, 439, 20, 4));

			// Третья строка
			AddImage(n_01, ImVec2(512, 512), pos + ImVec2(0, size.y - 20), pos + ImVec2(20, size.y), ImVec4(456, 447, 20, 20));
			AddImage(n_01, ImVec2(512, 512), pos + ImVec2(20, size.y - 20), pos + ImVec2(size.x - 20, size.y), ImVec4(480, 447, 4, 20));
			AddImage(n_01, ImVec2(512, 512), pos + ImVec2(size.x - 20, size.y - 20), pos + ImVec2(size.x, size.y), ImVec4(488, 447, 20, 20));

			// Фон заголовка окна
			AddImage(ne_wheeltaget1, ImVec2(256, 256), pos + ImVec2(0, 0), pos + ImVec2(185, 37), ImVec4(100, 218, 156, 37));

			// Иконка окна
			GetWindowDrawList()->AddImageRounded(user_texture_id, pos + ImVec2(3, 3), pos + ImVec2(37, 37), ImVec2(uv.x, uv.y) / texture_size, ImVec2(uv.x + uv.z, uv.y + uv.w) / texture_size, 0xFFFFFFFF, (37 - 3) / 2);

			// Заголовок окна
			GetWindowDrawList()->AddText(pos + ImVec2(37 + 3, 37 / 2 - CalcTextSize(name).y / 2), 0xFFFFFFFF, name);
		}
		else
		{
			// Первая строка
			AddImage(n_01, ImVec2(512, 512), pos, pos + ImVec2(53, 24), ImVec4(373, 341, 53, 24));
			AddImage(n_01, ImVec2(512, 512), pos + ImVec2(53, 0), pos + ImVec2(size.x - 53, 24), ImVec4(430, 341, 5, 24));
			AddImage(n_01, ImVec2(512, 512), pos + ImVec2(size.x - 53, 0), pos + ImVec2(size.x, 24), ImVec4(439, 341, 53, 24));

			// Вторая строка
			AddImage(n_01, ImVec2(512, 512), pos + ImVec2(0, 24), pos + ImVec2(20, size.y - 20), ImVec4(456, 439, 20, 4));
			AddImage(n_01, ImVec2(512, 512), pos + ImVec2(20, 24), pos + ImVec2(size.x - 20, size.y - 20), ImVec4(488, 439, 4, 4));
			AddImage(n_01, ImVec2(512, 512), pos + ImVec2(size.x - 20, 24), pos + ImVec2(size.x, size.y - 20), ImVec4(488, 439, 20, 4));

			// Третья строка
			AddImage(n_01, ImVec2(512, 512), pos + ImVec2(0, size.y - 20), pos + ImVec2(20, size.y), ImVec4(456, 447, 20, 20));
			AddImage(n_01, ImVec2(512, 512), pos + ImVec2(20, size.y - 20), pos + ImVec2(size.x - 20, size.y), ImVec4(480, 447, 4, 20));
			AddImage(n_01, ImVec2(512, 512), pos + ImVec2(size.x - 20, size.y - 20), pos + ImVec2(size.x, size.y), ImVec4(488, 447, 20, 20));

			// Заголовок окна
			auto titleSize = CalcTextSize(name);
			GetWindowDrawList()->AddText(pos + ImVec2(size.x - titleSize.x, 24 - titleSize.y) / 2, 0xFFFFFFFF, name);
		}

		// Кнопка закрытия
		if (p_open != NULL)
		{
			auto id = GetCurrentWindow()->GetID("#CLOSE");
			const ImRect bb(
				pos + ImVec2(size.x - 17 - 5, 5 + 0),
				pos + ImVec2(size.x - 0 - 5, 5 + 17));
			bool is_clipped = !ItemAdd(bb, id);
			bool hovered, held;
			bool pressed = ButtonBehavior(bb, id, &hovered, &held);

			if (!is_clipped)
			{
				if (held)
					AddImage(n_01, ImVec2(512, 512), pos + ImVec2(size.x - 17 - 5, 5), pos + ImVec2(size.x - 5, 5 + 17), ImVec4(125, 241, 17, 17));
				else if (hovered)
					AddImage(n_01, ImVec2(512, 512), pos + ImVec2(size.x - 17 - 5, 5), pos + ImVec2(size.x - 5, 5 + 17), ImVec4(103, 241, 17, 17));
				else
					AddImage(n_01, ImVec2(512, 512), pos + ImVec2(size.x - 17 - 5, 5), pos + ImVec2(size.x - 5, 5 + 17), ImVec4(81, 241, 17, 17));
			}

			if (pressed)
				*p_open = false;
		}
	}

	if (doesCanDrawAsda)
	{
		ImGui::PopStyleVar(3);
		if (ImGui::GetIO().Fonts->Fonts.size() > 3)
			ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[3]);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5 + 37);
	}

	return result;
}

void ImGui::EndAsda()
{
	if (ImGui::GetIO().Fonts->Fonts.size() > 3)
		ImGui::PopFont();
	
	ImGui::End();

	if (ImGui::GetIO().Fonts->Fonts.size() > 5)
		ImGui::PopFont();
}

bool ImGui::BeginAsdaChild(const char* str_id, const ImVec2& size_arg, bool border, ImGuiWindowFlags extra_flags)
{
	ImTextureID n_01 = TextureFactory::Instance()->MakeTexture("juidata\\Image\\Texture.btz", "n_01.tex");
	auto doesCanDrawAsda = n_01 != NULL;
	//auto doesCanDrawAsda = false;

	if (doesCanDrawAsda)
	{
		extra_flags |= ImGuiWindowFlags_AlwaysUseWindowPadding;
		ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0);
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(2, 2));
		ImGui::SetNextWindowBgAlpha(0);
	}

	ImGuiWindow* window = GetCurrentWindow();
	auto result = BeginChildEx(str_id, window->GetID(str_id), size_arg, border, extra_flags);

	if (doesCanDrawAsda)
		PopClipRect();

	if (doesCanDrawAsda && result)
	{
		// Позиция и размер окна
		auto pos = GetWindowPos(); auto size = GetWindowSize();

		// Первая строка
		AddImage(n_01, ImVec2(512, 512), pos, pos + ImVec2(11, 5), ImVec4(405, 427, 11, 5));
		AddImage(n_01, ImVec2(512, 512), pos + ImVec2(11, 0), pos + ImVec2(size.x - 11, 5), ImVec4(420, 427, 4, 5));
		AddImage(n_01, ImVec2(512, 512), pos + ImVec2(size.x - 11, 0), pos + ImVec2(size.x, 5), ImVec4(428, 427, 11, 5));

		// Вторая строка
		AddImage(n_01, ImVec2(512, 512), pos + ImVec2(0, 5), pos + ImVec2(11, size.y - 11), ImVec4(405, 436, 11, 4));
		AddImage(n_01, ImVec2(512, 512), pos + ImVec2(11, 5), pos + ImVec2(size.x - 11, size.y - 11), ImVec4(420, 436, 4, 4));
		AddImage(n_01, ImVec2(512, 512), pos + ImVec2(size.x - 11, 5), pos + ImVec2(size.x, size.y - 11), ImVec4(428, 436, 11, 4));

		// Третья строка
		AddImage(n_01, ImVec2(512, 512), pos + ImVec2(0, size.y - 11), pos + ImVec2(11, size.y), ImVec4(405, 444, 11, 11));
		AddImage(n_01, ImVec2(512, 512), pos + ImVec2(11, size.y - 11), pos + ImVec2(size.x - 11, size.y), ImVec4(420, 444, 4, 11));
		AddImage(n_01, ImVec2(512, 512), pos + ImVec2(size.x - 11, size.y - 11), pos + ImVec2(size.x, size.y), ImVec4(428, 444, 11, 11));
	}

	if (doesCanDrawAsda)
	{
		ImGui::PopStyleVar(3);
	}

	return result;

	
}

bool ImGui::AsdaWhiteButtonEx(const char* label, const ImVec2& size_arg, int flags)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = CalcTextSize(label, NULL, true);

	ImVec2 pos = window->DC.CursorPos;
	if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrentLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
		pos.y += window->DC.CurrentLineTextBaseOffset - style.FramePadding.y;
	ImVec2 size = CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	const ImRect bb(pos, pos + size);
	ItemSize(bb, style.FramePadding.y);
	if (!ItemAdd(bb, id))
		return false;

	if (window->DC.ItemFlags & ImGuiItemFlags_ButtonRepeat)
		flags |= ImGuiButtonFlags_Repeat;
	bool hovered, held;
	bool pressed = ButtonBehavior(bb, id, &hovered, &held, flags);
	if (pressed)
		MarkItemValueChanged(id);

	// Текстуры Asda 2 / Asda Story
	ImTextureID ne_skillbar1 = TextureFactory::Instance()->MakeTexture("juidata//Image//Texture.btz", "ne_skillbar1.tex");
	ImTextureID ne_skillbar3 = TextureFactory::Instance()->MakeTexture("juidata//Image//Texture.btz", "ne_skillbar3.tex");
	bool canDrawAsda = ne_skillbar1 != NULL && ne_skillbar3 != NULL;

	// Render
	if (!canDrawAsda)
	{
		const ImU32 col = GetColorU32((hovered && held) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
		RenderNavHighlight(bb, id);
		RenderFrame(bb.Min, bb.Max, col, true, style.FrameRounding);
		RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, style.ButtonTextAlign, &bb);
	}
	else
	{
		// Задний фон
		window->DrawList->AddImage(ne_skillbar1, bb.Min, bb.Min + ImVec2(4, 28), ImVec2(26, 228) / ImVec2(256, 256), ImVec2(26, 228) / 256 + ImVec2(4, 28) / 256);
		window->DrawList->AddImage(ne_skillbar1, bb.Min + ImVec2(4, 0), bb.Max - ImVec2(4, 0), ImVec2(34, 228) / ImVec2(256, 256), ImVec2(34, 228) / 256 + ImVec2(4, 28) / 256);
		window->DrawList->AddImage(ne_skillbar1, bb.Max - ImVec2(4, 28), bb.Max, ImVec2(42, 228) / ImVec2(256, 256), ImVec2(42, 228) / 256 + ImVec2(4, 28) / 256);

		// Смещение переднего фона
		float foreOffset = held ? 1.f : 0.f;

		// Передний фон
		window->DrawList->AddImage(ne_skillbar3, bb.Min + ImVec2(3 + 0, 3 + 0 + foreOffset), bb.Min + ImVec2(3 + 4, 3 + 22 + foreOffset), ImVec2(155 + 0, 86) / ImVec2(256, 256), ImVec2(155 + 0, 86) / 256 + ImVec2(4, 22) / 256);
		window->DrawList->AddImage(ne_skillbar3, bb.Min + ImVec2(3 + 4, 3 + 0 + foreOffset), bb.Max - ImVec2(3 + 4, 3 + 0 - foreOffset), ImVec2(155 + 4, 86) / ImVec2(256, 256), ImVec2(155 + 4, 86) / 256 + ImVec2(4, 22) / 256);
		window->DrawList->AddImage(ne_skillbar3, bb.Max - ImVec2(3 + 4, 22 + 3 - foreOffset), bb.Max - ImVec2(3 + 0, 0 + 3 - foreOffset), ImVec2(255 - 4, 86) / ImVec2(256, 256), ImVec2(255 - 4, 86) / 256 + ImVec2(4, 22) / 256);

		// Текст
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.05f, 0.05f, 0.05f, 1.0f));
		RenderTextClipped(bb.Min + ImVec2(3, 3), bb.Max - ImVec2(3, 3), label, NULL, &label_size, ImVec2(0.5f, 0.5f), &bb);
		ImGui::PopStyleColor();

		// Осветление
		if (hovered && !held)
			RenderFrame(bb.Min + ImVec2(3, 3), bb.Max - ImVec2(3, 3), ImColor(255, 255, 255, 45), false);

		// Иконка
		window->DrawList->AddImage(ne_skillbar1, bb.Min + ImVec2(5, 6), bb.Min + ImVec2(5 + 16, 6 + 16), ImVec2(31, 159) / 256, ImVec2(31, 159) / 256 + ImVec2(16, 16) / 256);
	}

	// Automatically close popups
	//if (pressed && !(flags & ImGuiButtonFlags_DontClosePopups) && (window->Flags & ImGuiWindowFlags_Popup))
	//    CloseCurrentPopup();

	return pressed;
}

bool ImGui::AsdaWhiteButton(const char* label, const ImVec2& size_arg)
{
	return AsdaWhiteButtonEx(label, size_arg, 0);
}

bool ImGui::AsdaOrangeButtonEx(const char* label, const ImVec2& size_arg, int flags)
{
	ImTextureID ne_skillbar1 = TextureFactory::Instance()->MakeTexture("juidata//Image//Texture.btz", "ne_skillbar1.tex");
	ImTextureID ne_skillbar3 = TextureFactory::Instance()->MakeTexture("juidata//Image//Texture.btz", "ne_skillbar3.tex");
	bool doesCanDrawAsda = ne_skillbar1 != NULL && ne_skillbar3 != NULL;

	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = CalcTextSize(label, NULL, true);

	ImVec2 pos = window->DC.CursorPos;
	if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrentLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
		pos.y += window->DC.CurrentLineTextBaseOffset - style.FramePadding.y;
	ImVec2 size = CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	const ImRect bb(pos, pos + size);
	ItemSize(bb, style.FramePadding.y);
	if (!ItemAdd(bb, id))
		return false;

	if (window->DC.ItemFlags & ImGuiItemFlags_ButtonRepeat)
		flags |= ImGuiButtonFlags_Repeat;
	bool hovered, held;
	bool pressed = ButtonBehavior(bb, id, &hovered, &held, flags);
	if (pressed)
		MarkItemValueChanged(id);

	// Render
	if (!doesCanDrawAsda)
	{
		const ImU32 col = GetColorU32((hovered && held) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
		RenderNavHighlight(bb, id);
		RenderFrame(bb.Min, bb.Max, col, true, style.FrameRounding);
		RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, style.ButtonTextAlign, &bb);
	}
	else
	{
		// Задний фон
		window->DrawList->AddImage(ne_skillbar1, bb.Min, bb.Min + ImVec2(4, 28), ImVec2(26, 228) / ImVec2(256, 256), ImVec2(26, 228) / 256 + ImVec2(4, 28) / 256);
		window->DrawList->AddImage(ne_skillbar1, bb.Min + ImVec2(4, 0), bb.Max - ImVec2(4, 0), ImVec2(34, 228) / ImVec2(256, 256), ImVec2(34, 228) / 256 + ImVec2(4, 28) / 256);
		window->DrawList->AddImage(ne_skillbar1, bb.Max - ImVec2(4, 28), bb.Max, ImVec2(42, 228) / ImVec2(256, 256), ImVec2(42, 228) / 256 + ImVec2(4, 28) / 256);

		// Смещение переднего фона
		float foreOffset = held ? 1.0f : 0.0f;

		// Передний фон
		window->DrawList->AddImage(ne_skillbar3, bb.Min + ImVec2(3 + 0, 3 + 0 + foreOffset), bb.Min + ImVec2(3 + 4, 3 + 22 + foreOffset), ImVec2(155 + 0, 60) / ImVec2(256, 256), ImVec2(155 + 0, 60) / 256 + ImVec2(4, 22) / 256);
		window->DrawList->AddImage(ne_skillbar3, bb.Min + ImVec2(3 + 4, 3 + 0 + foreOffset), bb.Max - ImVec2(3 + 4, 3 + 0 - foreOffset), ImVec2(155 + 4, 60) / ImVec2(256, 256), ImVec2(155 + 4, 60) / 256 + ImVec2(4, 22) / 256);
		window->DrawList->AddImage(ne_skillbar3, bb.Max - ImVec2(3 + 4, 22 + 3 - foreOffset), bb.Max - ImVec2(3 + 0, 0 + 3 - foreOffset), ImVec2(255 - 4, 60) / ImVec2(256, 256), ImVec2(255 - 4, 60) / 256 + ImVec2(4, 22) / 256);

		// Текст
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.85f, 0.85f, 0.85f, 1.0f));
		RenderTextClipped(bb.Min + ImVec2(3, 3), bb.Max - ImVec2(3, 3), label, NULL, &label_size, ImVec2(0.5f, 0.5f), &bb);
		ImGui::PopStyleColor();

		// Осветление
		if (hovered && !held)
			RenderFrame(bb.Min + ImVec2(3, 3), bb.Max - ImVec2(3, 3), ImColor(255, 255, 255, 45), false);

		// Иконка
		window->DrawList->AddImage(ne_skillbar1, bb.Min + ImVec2(5, 6), bb.Min + ImVec2(5 + 16, 6 + 16), ImVec2(31, 179) / 256, ImVec2(31, 179) / 256 + ImVec2(16, 16) / 256);
	}

	// Automatically close popups
	//if (pressed && !(flags & ImGuiButtonFlags_DontClosePopups) && (window->Flags & ImGuiWindowFlags_Popup))
	//    CloseCurrentPopup();

	return pressed;
}

bool ImGui::AsdaOrangeButton(const char* label, const ImVec2& size_arg)
{
	return AsdaOrangeButtonEx(label, size_arg, 0);
}

void ImGui::Image(ImTextureID user_texture_id, const ImVec2& texture_size, const ImVec4& uv, bool flipHorizontally, const ImVec4& tint_col, const ImVec4& border_col)
{
	auto u0 = uv.x / texture_size.x;
	auto v0 = uv.y / texture_size.y;
	auto u1 = u0 + uv.z / texture_size.x;
	auto v1 = v0 + uv.w / texture_size.y;
	Image(
		user_texture_id, ImVec2(uv.z, uv.w),
		ImVec2(flipHorizontally ? u1 : u0, v0),
		ImVec2(flipHorizontally ? u0 : u1, v1),
		tint_col, border_col);
}

bool ImGui::InputUint32(const char* label, sf::Uint32* v, sf::Uint32 step, sf::Uint32 step_fast, ImGuiInputTextFlags extra_flags)
{
	auto iV = static_cast<int>(*v);
	auto result = InputInt(label, &iV, step, step_fast, extra_flags);
	*v = static_cast<sf::Uint32>(iV);
	return result;
}

bool ImGui::InputUint16(const char* label, sf::Uint16* v, sf::Uint16 step, sf::Uint16 step_fast, ImGuiInputTextFlags extra_flags)
{
	auto iV = static_cast<int>(*v);
	auto result = InputInt(label, &iV, step, step_fast, extra_flags);
	*v = static_cast<sf::Uint16>(iV);
	return result;
}

void ImGui::BeginAsdaTooltip()
{
	ImTextureID n_01 = TextureFactory::Instance()->MakeTexture("juidata\\Image\\Texture.btz", "n_01.tex");
	auto doesCanDrawAsda = n_01 != NULL;
	//auto doesCanDrawAsda = false;

	if (doesCanDrawAsda)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(4, 4));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
		if (ImGui::GetIO().Fonts->Fonts.size() > 3)
			ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[3]);
		ImGui::SetNextWindowBgAlpha(0);
	}

	BeginTooltipEx(0, false);

	if (doesCanDrawAsda)
		PopClipRect();

	if (doesCanDrawAsda)
	{
		// Позиция и размер окна
		auto pos = GetWindowPos(); auto size = GetWindowSize();

		// Первая строка
		AddImage(n_01, ImVec2(512, 512), pos, pos + ImVec2(4, 4), ImVec4(86, 415, 4, 4));
		AddImage(n_01, ImVec2(512, 512), pos + ImVec2(4, 0), pos + ImVec2(size.x - 4, 4), ImVec4(94, 415, 4, 4));
		AddImage(n_01, ImVec2(512, 512), pos + ImVec2(size.x - 4, 0), pos + ImVec2(size.x, 4), ImVec4(102, 415, 4, 4));

		// Вторая строка
		AddImage(n_01, ImVec2(512, 512), pos + ImVec2(0, 4), pos + ImVec2(4, size.y - 4), ImVec4(86, 423, 4, 4));
		AddImage(n_01, ImVec2(512, 512), pos + ImVec2(4, 4), pos + ImVec2(size.x - 4, size.y - 4), ImVec4(94, 423, 4, 4));
		AddImage(n_01, ImVec2(512, 512), pos + ImVec2(size.x - 4, 4), pos + ImVec2(size.x, size.y - 4), ImVec4(102, 423, 4, 4));

		// Третья строка
		AddImage(n_01, ImVec2(512, 512), pos + ImVec2(0, size.y - 4), pos + ImVec2(4, size.y), ImVec4(86, 431, 4, 4));
		AddImage(n_01, ImVec2(512, 512), pos + ImVec2(4, size.y - 4), pos + ImVec2(size.x - 4, size.y), ImVec4(94, 431, 4, 4));
		AddImage(n_01, ImVec2(512, 512), pos + ImVec2(size.x - 4, size.y - 4), pos + ImVec2(size.x, size.y), ImVec4(102, 431, 4, 4));
	}

	if (doesCanDrawAsda)
	{
		ImGui::PopStyleVar(3);
	}
}

void ImGui::EndAsdaTooltip()
{
	IM_ASSERT(GetCurrentWindowRead()->Flags & ImGuiWindowFlags_Tooltip);   // Mismatched BeginTooltip()/EndTooltip() calls
	End();

	if (ImGui::GetIO().Fonts->Fonts.size() > 3)
		ImGui::PopFont();
}

bool ImGui::BeginAsdaPopupModal(const char* name, bool* p_open, ImGuiWindowFlags flags)
{
	ImTextureID ne_wheelcharacter1 = TextureFactory::Instance()->MakeTexture("juidata\\Image\\Texture.btz", "ne_wheelcharacter1.tex");
	auto doesCanDrawAsda = ne_wheelcharacter1 != NULL;
	//auto doesCanDrawAsda = false;

	if (doesCanDrawAsda)
	{
		flags |= ImGuiWindowFlags_NoTitleBar;
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
		ImGui::PushStyleColor(ImGuiCol_ModalWindowDarkening, ImVec4(0, 0, 0, 0));
		if (ImGui::GetIO().Fonts->Fonts.size() > 3)
			ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[3]);
		ImGui::SetNextWindowBgAlpha(0);
	}

	auto result = ImGui::BeginPopupModal(name, p_open, flags);

	if (doesCanDrawAsda)
		PopClipRect();

	if (doesCanDrawAsda && result)
	{
		// Позиция и размер окна
		auto pos = GetWindowPos(); auto size = GetWindowSize();

		// Первая строка
		AddImage(ne_wheelcharacter1, ImVec2(256, 256), pos, pos + ImVec2(26, 38), ImVec4(192, 129, 26, 38));
		AddImage(ne_wheelcharacter1, ImVec2(256, 256), pos + ImVec2(26, 0), pos + ImVec2(size.x - 26, 38), ImVec4(222, 129, 4, 38));
		AddImage(ne_wheelcharacter1, ImVec2(256, 256), pos + ImVec2(size.x - 26, 0), pos + ImVec2(size.x, 38), ImVec4(230, 129, 26, 38));

		// Вторая строка
		AddImage(ne_wheelcharacter1, ImVec2(256, 256), pos + ImVec2(0, 38), pos + ImVec2(26, size.y - 26), ImVec4(192, 222, 26, 4));
		AddImage(ne_wheelcharacter1, ImVec2(256, 256), pos + ImVec2(26, 38), pos + ImVec2(size.x - 26, size.y - 26), ImVec4(222, 222, 4, 4));
		AddImage(ne_wheelcharacter1, ImVec2(256, 256), pos + ImVec2(size.x - 26, 38), pos + ImVec2(size.x, size.y - 26), ImVec4(230, 222, 26, 4));

		// Третья строка
		AddImage(ne_wheelcharacter1, ImVec2(256, 256), pos + ImVec2(0, size.y - 26), pos + ImVec2(26, size.y), ImVec4(192, 230, 26, 26));
		AddImage(ne_wheelcharacter1, ImVec2(256, 256), pos + ImVec2(26, size.y - 26), pos + ImVec2(size.x - 26, size.y), ImVec4(222, 230, 4, 26));
		AddImage(ne_wheelcharacter1, ImVec2(256, 256), pos + ImVec2(size.x - 26, size.y - 26), pos + ImVec2(size.x, size.y), ImVec4(230, 230, 26, 26));

		// Икона восклицательного знака
		AddImage(ne_wheelcharacter1, ImVec2(256, 256), pos + ImVec2(5, 5), pos + ImVec2(5 + 39, 5 + 39), ImVec4(217, 179, 39, 39));
	}

	if (doesCanDrawAsda)
	{
		ImGui::PopStyleVar(3);
		ImGui::PopStyleColor(1);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5 + 38);
	}

	return result;
}

void ImGui::EndAsdaPopup()
{
	ImGuiContext& g = *GImGui; (void)g;
	IM_ASSERT(g.CurrentWindow->Flags & ImGuiWindowFlags_Popup);  // Mismatched BeginPopup()/EndPopup() calls
	IM_ASSERT(g.CurrentPopupStack.Size > 0);

	// Make all menus and popups wrap around for now, may need to expose that policy.
	NavMoveRequestTryWrapping(g.CurrentWindow, ImGuiNavMoveFlags_LoopY);

	End();

	if (ImGui::GetIO().Fonts->Fonts.size() > 3)
		ImGui::PopFont();
}

void ImGui::AddImage(ImTextureID user_texture_id, const ImVec2& texture_size, const ImVec2& a, const ImVec2& b, const ImVec4& uv, ImU32 col)
{
	auto u0 = uv.x / texture_size.x;
	auto v0 = uv.y / texture_size.y;
	auto u1 = u0 + uv.z / texture_size.x;
	auto v1 = v0 + uv.w / texture_size.y;
	ImGui::GetWindowDrawList()->AddImage(user_texture_id, a, b, ImVec2(u0, v0), ImVec2(u1, v1), col);
}

bool ImGui::IsKeyDown(ImGuiKey_ key_index)
{
	const int user_key_index = ImGui::GetIO().KeyMap[key_index];
	if (user_key_index < 0) return false;
	IM_ASSERT(user_key_index >= 0 && user_key_index < IM_ARRAYSIZE(GImGui->IO.KeysDown));
	return GImGui->IO.KeysDown[user_key_index];
}