// InjectMe
#include "Buffer.hpp"
#include "TextureFactory.hpp"

using namespace InjectMe::Utils;
using namespace InjectMe::UI;

// Addon
#include "DailyBonus.hpp"

// ImGui
#include "ImGui/imgui.h"
#include "ImGui/imgui_user.h"

namespace Addon::UI::DailyBonus
{
	struct
	{
		sf::Uint8 dayNumber;			// Номер дня

		struct
		{
			sf::String packageName;		// Имя пакета
			sf::String btzFileName;		// Имя файла .btz
			sf::String texFileName;		// Имя файла .tex
			sf::Uint16 texX, texY;		// Координаты текстуры
			sf::Uint16 texW, texH;		// Размеры текстуры
			sf::Uint8 texIndex;			// Номер текстуры
			sf::Uint8 itemsCount;		// Количество предметов
			sf::String itemNames[10];	// Имена предметов
		} DailyBonusDayInfo[28];		// Дни

		void ReadDailyBonusInfo(Buffer &buffer)
		{
			buffer.SetOffset(10);

			buffer.Read(dayNumber);

			for (int i = 0; i < 28; i++)
			{
				buffer.Read(DailyBonusDayInfo[i].packageName);
				DailyBonusDayInfo[i].btzFileName = "juidata\\sIcon\\Texture.btz";
				buffer.Read(DailyBonusDayInfo[i].texFileName);
				buffer.Read(DailyBonusDayInfo[i].texIndex);
				buffer.Read(DailyBonusDayInfo[i].itemsCount);

				for (int j = 0; j < DailyBonusDayInfo[i].itemsCount; j++)
				{
					buffer.Read(DailyBonusDayInfo[i].itemNames[j]);
				}
			}
		}
	} DailyBonusInfo;

	// Флаг активности окна ежедневного бонуса
	bool isDailyBonusWindowActive = false;

	bool IsDailyBonusActive()
	{
		return isDailyBonusWindowActive;
	}

	void OpenDailyBonus(Buffer &buffer)
	{
		if (isDailyBonusWindowActive == true)
		{
			return;
		}

		DailyBonusInfo.ReadDailyBonusInfo(buffer);
		isDailyBonusWindowActive = true;
	}

	void CloseDailyBonus()
	{
		isDailyBonusWindowActive = false;
	}

	void DailyBonus()
	{
		//ImGui::ShowDemoWindow();

		if (isDailyBonusWindowActive == false)
		{
			return;
		}

		char title[256];
		sprintf_s(title, "Daily Bonus (day %u)", DailyBonusInfo.dayNumber);

		ImGui::SetNextWindowPosCenter(ImGuiCond_Appearing);
		if (ImGui::BeginAsda(
			title,
			&isDailyBonusWindowActive,
			TextureFactory::Instance()->MakeTexture("juidata\\Image\\Texture.btz", "mes_present.tex"),
			ImVec2(64, 64),
			ImVec4(2, 2, 60, 60)) == true)
		{
			for (int i = 0; i < 7 * 4; i++)
			{
				int tilesInRowCount = 8, tileSizeX = 64, tileSizeY = 64;

				if (DailyBonusInfo.DailyBonusDayInfo[i].texFileName == "s_item_s_02")
				{
					tilesInRowCount <<= 1;
					tileSizeX >>= 1;
					tileSizeY >>= 1;
				}

				ImGui::Image(
					TextureFactory::Instance()->MakeTexture(
						DailyBonusInfo.DailyBonusDayInfo[i].btzFileName,
						DailyBonusInfo.DailyBonusDayInfo[i].texFileName + ".tex", false
					),
					ImVec2(
						96, 96
					),
					ImVec2(
					(DailyBonusInfo.DailyBonusDayInfo[i].texIndex % tilesInRowCount) * tileSizeX / 512.f,
						(DailyBonusInfo.DailyBonusDayInfo[i].texIndex / tilesInRowCount) * tileSizeY / 512.f
					),
					ImVec2(
					(DailyBonusInfo.DailyBonusDayInfo[i].texIndex % tilesInRowCount + 1) * tileSizeX / 512.f,
						(DailyBonusInfo.DailyBonusDayInfo[i].texIndex / tilesInRowCount + 1) * tileSizeY / 512.f
					),
					i < DailyBonusInfo.dayNumber - 1 ? ImColor(0.29f, 0.29f, 0.29f) :
					i == DailyBonusInfo.dayNumber - 1 ? ImColor(1.f, 1.f, 1.f) : ImColor(0.55f, 0.55f, 0.55f)
				);

				if (ImGui::IsItemHovered() == true)
				{
					ImGui::BeginAsdaTooltip();

					auto aTitle = DailyBonusInfo.DailyBonusDayInfo[i].packageName.toAnsiString();
					ImGui::Text(aTitle.c_str());
					ImGui::Separator();

					for (size_t j = 0; j < DailyBonusInfo.DailyBonusDayInfo[i].itemsCount; j++)
					{
						auto aName = DailyBonusInfo.DailyBonusDayInfo[i].itemNames[j].toAnsiString();
						ImGui::Text("%u. %s", j + 1, aName.c_str());
					}

					ImGui::EndAsdaTooltip();
				}

				if ((i + 1) % 7 != 0)
				{
					ImGui::SameLine();
				}

				if (ImGui::IsWindowFocused())
				{
					const int key_index = ImGui::GetIO().KeyMap[ImGuiKey_Escape];
					bool pressed = (key_index >= 0) ? ImGui::IsKeyPressed(key_index) : false;
					if (pressed)
						CloseDailyBonus();
				}
			}
		}

		ImGui::EndAsda();
	}
}