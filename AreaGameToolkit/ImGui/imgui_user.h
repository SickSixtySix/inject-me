#pragma once

// SFML
#include <SFML/Config.hpp>

namespace ImGui
{
	// Windows
	IMGUI_API bool          BeginAsda(const char* name, bool* p_open = NULL, ImTextureID user_texture_id = NULL, const ImVec2& texture_size = ImVec2(1, 1), const ImVec4& uv = ImVec4(0, 0, 1, 1), ImGuiWindowFlags flags = 0);
	IMGUI_API void          EndAsda();
	IMGUI_API bool          BeginAsdaChild(const char* str_id, const ImVec2& size = ImVec2(0, 0), bool border = false, ImGuiWindowFlags flags = 0);

	// Widgets
	IMGUI_API bool          AsdaWhiteButtonEx(const char* label, const ImVec2& size_arg = ImVec2(0, 0), int flags = 0);
	IMGUI_API bool          AsdaWhiteButton(const char* label, const ImVec2& size = ImVec2(0, 0));
	IMGUI_API bool          AsdaOrangeButtonEx(const char* label, const ImVec2& size_arg = ImVec2(0, 0), int flags = 0);
	IMGUI_API bool          AsdaOrangeButton(const char* label, const ImVec2& size = ImVec2(0, 0));
	IMGUI_API void          Image(ImTextureID user_texture_id, const ImVec2& texture_size, const ImVec4& uv, bool flipHorizontally = false, const ImVec4& tint_col = ImVec4(1, 1, 1, 1), const ImVec4& border_col = ImVec4(0, 0, 0, 0));

	// Widgets: Input with Keyboard
	IMGUI_API bool          InputUint32(const char* label, sf::Uint32* v, sf::Uint32 step = 1, sf::Uint32 step_fast = 100, ImGuiInputTextFlags extra_flags = 0);
	IMGUI_API bool          InputUint16(const char* label, sf::Uint16* v, sf::Uint16 step = 1, sf::Uint16 step_fast = 100, ImGuiInputTextFlags extra_flags = 0);

	// Tooltips
	IMGUI_API void          BeginAsdaTooltip();
	IMGUI_API void          EndAsdaTooltip();

	// Popups
	IMGUI_API bool          BeginAsdaPopupModal(const char* name, bool* p_open = NULL, ImGuiWindowFlags flags = 0);
	IMGUI_API void          EndAsdaPopup();

	// Draw list
	void AddImage(ImTextureID user_texture_id, const ImVec2& texture_size, const ImVec2& a, const ImVec2& b, const ImVec4& uv = ImVec4(0, 0, 1, 1), ImU32 col = 0xFFFFFFFF);

	// Inputs
	IMGUI_API bool          IsKeyDown(ImGuiKey_ key_index);                                      // is key being held. == io.KeysDown[user_key_index]. note that imgui doesn't know the semantic of each entry of io.KeysDown[]. Use your own indices/enums according to how your backend/engine stored them into io.KeysDown[]!
}