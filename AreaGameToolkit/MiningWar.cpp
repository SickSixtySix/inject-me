// InjectMe
#include "Asda2Hook.hpp"
#include "Asda2Proxy.hpp"
#include "TextureFactory.hpp"
#include "Translator.hpp"

using namespace InjectMe::Utils;
using namespace InjectMe::Network;
using namespace InjectMe::UI;
using namespace InjectMe::Hook::Asda2;

// Addon
#include "MiningWar.hpp"

// ImGui
#include "ImGui/imgui.h"
#include "ImGui/imgui_user.h"

// SFML
#include <SFML/System/Clock.hpp>

extern Asda2Proxy *asda2Proxy;

namespace Addon::UI::MiningWar
{
	// Вход
	bool joinFired = false;				// Флаг события Join
	sf::Int16 joinMinesOwner = -1;		// Фракция-владелец шахты духа
	sf::Uint8 joinBattleStartTimeD;		// День
	sf::Uint8 joinBattle1StartTimeH;	// Часы (первая битва)
	sf::Uint8 joinBattle1StartTimeM;	// Минуты (первая битва)
	sf::Uint8 joinBattle2StartTimeH;	// Часы (вторая битва)
	sf::Uint8 joinBattle2StartTimeM;	// Минуты (вторая битва)
	void HandleJoinResponse(Buffer &buffer)
	{
		// TODO: Разобраться со структурой пакета
		joinFired = true;
		buffer.Read(joinMinesOwner);
		buffer.Read(joinBattleStartTimeD);
		buffer.Read(joinBattle1StartTimeH);
		buffer.Read(joinBattle1StartTimeM);
		buffer.Read(joinBattle2StartTimeH);
		buffer.Read(joinBattle2StartTimeM);
	}

	void Join()
	{
		if (joinFired)
		{
			if (!ImGui::IsPopupOpen("mining_war_join"))
				ImGui::OpenPopup("mining_war_join");
			joinFired = false;
		}

		ImGui::SetNextWindowSize(ImVec2(360, 0), ImGuiCond_Appearing);
		if (ImGui::BeginAsdaPopupModal("mining_war_join"))
		{
			char sD[128];
			switch (joinBattleStartTimeD)
			{
			case 0: sprintf_s(sD, Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::MONDAY).c_str()); break;
			case 1: sprintf_s(sD, Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::TUESDAY).c_str()); break;
			case 2: sprintf_s(sD, Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::WEDNESDAY).c_str()); break;
			case 3: sprintf_s(sD, Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::THURSDAY).c_str()); break;
			case 4: sprintf_s(sD, Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::FRIDAY).c_str()); break;
			case 5: sprintf_s(sD, Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::SATURDAY).c_str()); break;
			case 6: sprintf_s(sD, Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::SUNDAY).c_str()); break;
			}

			char sTime[256];
			sprintf_s(sTime, Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::NEXT_WAR_TIME_VALUE).c_str(),
				sD,
				joinBattle1StartTimeH,
				joinBattle1StartTimeM,
				joinBattle2StartTimeH,
				joinBattle2StartTimeM);

			std::string textLines[] =
			{
				Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::NEXT_WAR_TIME),
				sTime,
				joinMinesOwner == -1 ? Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::DOESNT_BELONG_TO_ANY_FACTION) :
				joinMinesOwner == 0 ? Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::BELONGS_TO_LIGHT) :
				joinMinesOwner == 1 ? Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::BELONGS_TO_DARK) :
				joinMinesOwner == 2 ? Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::BELONGS_TO_CHAOS) : "<null>"
			};

			for (int i = 0; i < sizeof(textLines) / sizeof(textLines[0]); i++)
			{
				ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2 - ImGui::CalcTextSize(textLines[i].c_str()).x / 2);
				ImGui::Text(textLines[i].c_str());
			}

			auto middleX = round(ImGui::GetWindowWidth() / 2);

			ImGui::SetCursorPosX(middleX - 7 - 106);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20);
			if (ImGui::AsdaWhiteButton(Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::OK).c_str(), ImVec2(106, 28)))
			{
				Buffer outBuffer;
				outBuffer.SetOffset(10);
				asda2Proxy->SendClientPacket(PacketID::MiningWarJoinRequestOK, outBuffer);
				ImGui::CloseCurrentPopup();
			}

			ImGui::SameLine(middleX + 7);
			if (ImGui::AsdaOrangeButton(Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::CANCEL).c_str(), ImVec2(106, 28)))
				ImGui::CloseCurrentPopup();

			ImGui::EndAsdaPopup();
		}
	}

	// Обновление фазы: добыча или битва
	bool miningUpdateFired = false; // Флаг события MiningUpdate
	bool battleUpdateFired = false;	// Флаг события BattleUpdate

	void Phase()
	{
		ImTextureID n_chapter = TextureFactory::Instance()->MakeTexture("juidata\\Image\\Texture.btz", "n_chapter.tex");
		const float y0 = 219;

		if (miningUpdateFired)
		{
			const float x0 = ImGui::GetIO().DisplaySize.x - 134 / 2 - 126 / 2;
			ImGui::AddImage(n_chapter, ImVec2(512, 512), ImVec2(x0, y0), ImVec2(x0 + 126, y0 + 23), ImVec4(386, 207, 126, 23));
		}
		else if (battleUpdateFired)
		{
			const float x0 = ImGui::GetIO().DisplaySize.x - 134 / 2 - 123 / 2;
			ImGui::AddImage(n_chapter, ImVec2(512, 512), ImVec2(x0, y0), ImVec2(x0 + 123, y0 + 23), ImVec4(389, 179, 123, 23));
		}
	}

	// Обновление фазы добычи
	sf::Uint16 miningUpdateBonus;	// Бонус
	sf::Uint32 miningUpdateCount;	// Количество оппонентов в регионе
	void HandleMiningUpdate(Buffer &buffer)
	{
		miningUpdateFired = true;
		battleUpdateFired = false;
		buffer.Read(miningUpdateBonus);
		buffer.Read(miningUpdateCount);
	}

	void Mining()
	{
		if (!miningUpdateFired)
			return;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(3, 2));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0.25f));
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0.25f));
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 136 - 110, 3), ImGuiCond_Appearing);
		if (ImGui::Begin("mining_war_mining", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize))
		{
			if (ImGui::GetIO().Fonts->Fonts.size() > 2)
				ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);

			ImTextureID campwar_markimage = TextureFactory::Instance()->MakeTexture("juidata\\Image\\Texture.btz", "campwar_markimage.tex");
			ImTextureID ne_ap_roulette = TextureFactory::Instance()->MakeTexture("juidata\\Image\\Texture.btz", "ne_ap_roulette.tex");

			ImGui::BeginChild("##domain_1", ImVec2(104, 16), false, ImGuiWindowFlags_NoScrollbar);
			ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - 93 / 2);
			ImGui::SetCursorPosY(ImGui::GetWindowSize().y / 2 - 17 / 2);
			ImGui::Image(ne_ap_roulette, ImVec2(512, 512), ImVec4(419, 111, 93, 17));
			ImGui::EndChild();

			ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2 - 64 / 2);
			ImGui::Image(campwar_markimage, ImVec2(128, 128), ImVec4(0, 0, 64, 64));

			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0.5f));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1, 1, 1, 0.5f));
			ImGui::BeginChild("##domain_2", ImVec2(104, 18), true, ImGuiWindowFlags_NoScrollbar);
			ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - 82 / 2);
			ImGui::SetCursorPosY(ImGui::GetWindowSize().y / 2 - 14 / 2);
			ImGui::Image(ne_ap_roulette, ImVec2(512, 512), ImVec4(425, 218, 82, 14));
			ImGui::EndChild();
			ImGui::PopStyleColor(2);

			char sBonus[256];
			sprintf_s(sBonus, "%.1f%%", miningUpdateBonus / 10.f);
			ImGui::BeginChild("##domain_3", ImVec2(104, 16));
			ImGui::SetCursorPosX(104 / 2 - ImGui::CalcTextSize(sBonus).x / 2);
			ImGui::Text("%s", sBonus);
			ImGui::EndChild();

			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0.5f));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1, 1, 1, 0.5f));
			ImGui::BeginChild("##domain_4", ImVec2(104, 18), true, ImGuiWindowFlags_NoScrollbar);
			ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - 95 / 2);
			ImGui::SetCursorPosY(ImGui::GetWindowSize().y / 2 - 17 / 2);
			ImGui::Image(ne_ap_roulette, ImVec2(512, 512), ImVec4(417, 236, 95, 17));
			ImGui::EndChild();
			ImGui::PopStyleColor(2);

			char sOpponents[256];
			sprintf_s(sOpponents, "%u %s", miningUpdateCount, Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::N_PLAYERS).c_str());
			ImGui::BeginChild("##domain_5", ImVec2(104, 16));
			ImGui::SetCursorPosX(104 / 2 - ImGui::CalcTextSize(sOpponents).x / 2);
			ImGui::Text("%s", sOpponents);
			ImGui::EndChild();

			if (ImGui::GetIO().Fonts->Fonts.size() > 2)
				ImGui::PopFont();
		}

		ImGui::End();

		ImGui::PopStyleVar(3);
		ImGui::PopStyleColor(2);
	}

	// Обновление фазы битвы
	sf::Uint32 battleUpdateCurHealth;	// Текущее здоровье главного кристалла
	sf::Uint32 battleUpdateMaxHealth;	// Максимальное здоровье главного кристалла
	void HandleBattleUpdate(Buffer &buffer)
	{
		battleUpdateFired = true;
		miningUpdateFired = false;
		buffer.Read(battleUpdateCurHealth);
		buffer.Read(battleUpdateMaxHealth);
	}

	void Battle()
	{
		if (!battleUpdateFired)
			return;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(3, 2));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0.25f));
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0.25f));
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 136 - 90, 3), ImGuiCond_Appearing);
		if (ImGui::Begin("mining_war_battle", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImTextureID n_chapter = TextureFactory::Instance()->MakeTexture("juidata\\Image\\Texture.btz", "n_chapter.tex");

			ImGui::BeginChild("##domain_1", ImVec2(84, 18));
			ImGui::SetCursorPosX(84 / 2 - 55 / 2);
			ImGui::SetCursorPosY(18 / 2 - 13 / 2);
			ImGui::Image(n_chapter, ImVec2(512, 512), ImVec4(6, 458, 55, 13));
			ImGui::EndChild();

			const auto middleX = round(ImGui::GetWindowSize().x / 2);
			const auto cursorY = ImGui::GetCursorPosY();
			const auto percentage = battleUpdateCurHealth / (float)battleUpdateMaxHealth;
			ImGui::SetCursorPosX(middleX - 34);
			ImGui::SetCursorPosY(cursorY + (1 - percentage) * 128);
			ImGui::Image(n_chapter, ImVec2(512, 512), ImVec4(478, 358 + (1 - percentage) * 128, 34, percentage * 128));
			ImGui::SameLine(middleX);
			ImGui::Image(n_chapter, ImVec2(512, 512), ImVec4(478, 358 + (1 - percentage) * 128, 34, percentage * 128), true);
		}

		ImGui::End();

		ImGui::PopStyleVar(3);
		ImGui::PopStyleColor(2);
	}

	// Начало битвы
	bool battleStartedFired = false;	// Флаг события BattleStarted
	void HandleBattleStarted(Buffer &buffer)
	{
		battleStartedFired = true;
	}

	float		battleStartedAlpha;	// Величина альфа-канала надписи
	sf::Clock	battleStartedClock;	// Отсчет времени для изменения величины альфа-канала
	void BattleStarted()
	{
		if (battleStartedFired)
		{
			battleStartedFired = false;
			battleStartedAlpha = 1;
			battleStartedClock.restart();
		}
		else if (battleStartedAlpha > 0)
		{
			ImTextureID n_chapter = TextureFactory::Instance()->MakeTexture("juidata\\Image\\Texture.btz", "n_chapter.tex");

			auto middleX = round(ImGui::GetWindowSize().x / 2);
			auto middleY = round(ImGui::GetWindowSize().y / 2);
			ImGui::SetCursorPosX(middleX - 200);
			ImGui::SetCursorPosY(middleY - 100);
			ImGui::Image(n_chapter, ImVec2(512, 512), ImVec4(4, 481, 351, 28), false, ImVec4(1, 1, 1, battleStartedAlpha));
			ImGui::SetCursorPosX(middleX - 270);
			ImGui::Image(n_chapter, ImVec2(512, 512), ImVec4(157, 302, 198, 18), false, ImVec4(1, 1, 1, battleStartedAlpha));
			ImGui::SameLine(middleX - 270 + 198);
			ImGui::Image(n_chapter, ImVec2(512, 512), ImVec4(139, 333, 142, 18), false, ImVec4(1, 1, 1, battleStartedAlpha));

			battleStartedAlpha -= battleStartedClock.getElapsedTime().asSeconds() * 0.2f;
			battleStartedClock.restart();
		}
	}

	// Конец битвы
	bool battleStoppedFired = false;	// Флаг события BattleStopped
	sf::Uint16 battleStoppedWinner;		// Фракция победителя
	sf::Uint16 battleStoppedPlayer;		// Фракция игрока
	sf::Uint16 battleStoppedReward;		// Тип награды
	sf::Uint32 battleStoppedAmount;		// Величина награды
	void HandleBattleStopped(Buffer &buffer)
	{
		battleStoppedFired = true;
		buffer.Read(battleStoppedWinner);
		buffer.Read(battleStoppedPlayer);
		buffer.Read(battleStoppedReward);
		buffer.Read(battleStoppedAmount);
	}

	void BattleStopped()
	{
		if (!battleStoppedFired)
			return;

		auto lightFaction = Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::LIGHT).c_str();
		auto darkFaction = Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::DARK).c_str();
		ImGui::SetNextWindowPosCenter(ImGuiCond_Appearing);
		if (ImGui::BeginAsda(battleStoppedWinner == 0 ? lightFaction : darkFaction))
		{
			ImTextureID campwar_markimage = TextureFactory::Instance()->MakeTexture("juidata\\Image\\Texture.btz", "campwar_markimage.tex");
			ImTextureID n_chapter = TextureFactory::Instance()->MakeTexture("juidata\\Image\\Texture.btz", "n_chapter.tex");

			const auto middleX = round(ImGui::GetWindowWidth() / 2);

			ImGui::SetCursorPosX(middleX - 64 / 2);
			ImGui::Image(campwar_markimage, ImVec2(128, 128), ImVec4(static_cast<float>((battleStoppedWinner % 2) * 64), static_cast<float>((battleStoppedWinner / 2) * 64), 64, 64));

			const char *sFraction = battleStoppedWinner == 0 ? lightFaction : darkFaction;
			ImGui::SetCursorPosX(middleX - 350 / 2);
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.22f, 0.22f, 0.22f, 1));
			ImGui::BeginChild("##domain_1", ImVec2(350, 28));
			ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - ImGui::CalcTextSize(sFraction).x / 2);
			ImGui::SetCursorPosY(ImGui::GetWindowSize().y / 2 - ImGui::CalcTextSize(sFraction).y / 2);
			ImGui::Text("%s", sFraction);
			ImGui::EndChild();
			ImGui::PopStyleColor();

			const char *sResult = battleStoppedWinner == battleStoppedPlayer ? 
				Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::YOU_HAVE_WON).c_str() : 
				Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::YOU_HAVE_LOSE).c_str();
			ImGui::SetCursorPosX(middleX - 350 / 2);
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.22f, 0.19f, 0.16f, 1));
			ImGui::BeginChild("##domain_2", ImVec2(350, 28));
			ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - ImGui::CalcTextSize(sResult).x / 2);
			ImGui::SetCursorPosY(ImGui::GetWindowSize().y / 2 - ImGui::CalcTextSize(sResult).y / 2);
			ImGui::Text("%s", sResult);
			ImGui::EndChild();
			ImGui::PopStyleColor();

			ImGui::SetCursorPosX(middleX - 205 / 2);
			ImGui::Image(n_chapter, ImVec2(512, 512), ImVec4(299, 3, 205, 20));
			ImGui::SetCursorPosX(middleX - 184 / 2);
			ImGui::Image(n_chapter, ImVec2(512, 512), ImVec4(306, 27, 184, 19));

			ImGui::BeginAsdaChild("##domain_3", ImVec2(385, 60), true);
			const char *text_3 = Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::ADDITIONAL_REWARD).c_str();
			ImGui::SetCursorPosX(2);
			ImGui::SetCursorPosY(2);
			ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0);
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0);
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.22f, 0.22f, 0.22f, 1));
			ImGui::BeginChild("##domain_4", ImVec2(381, 23), true, ImGuiWindowFlags_NoScrollbar);
			ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - ImGui::CalcTextSize(text_3).x / 2);
			ImGui::SetCursorPosY(ImGui::GetWindowSize().y / 2 - ImGui::CalcTextSize(text_3).y / 2);
			ImGui::Text("%s", text_3);
			ImGui::EndChild();
			ImGui::PopStyleVar(2);
			ImGui::PopStyleColor();
			ImGui::SetCursorPosX(14);
			ImGui::SetCursorPosY(29);
			ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1);
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0);
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.22f, 0.19f, 0.16f, 1));
			const char *sReward = battleStoppedReward == 0 ? Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::HONOR_POINT).c_str() : "<null>";
			ImGui::BeginChild("##domain_5", ImVec2(106, 22), true, ImGuiWindowFlags_NoScrollbar);
			ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - ImGui::CalcTextSize(sReward).x / 2);
			ImGui::SetCursorPosY(ImGui::GetWindowSize().y / 2 - ImGui::CalcTextSize(sReward).y / 2);
			ImGui::Text("%s", sReward);
			ImGui::End();
			ImGui::SetCursorPosX(123);
			ImGui::SetCursorPosY(29);
			char sAmount[256];
			sprintf_s(sAmount, "%u", battleStoppedAmount);
			ImGui::BeginChild("##domain_6", ImVec2(250, 22), true, ImGuiWindowFlags_NoScrollbar);
			ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - ImGui::CalcTextSize(sAmount).x / 2);
			ImGui::SetCursorPosY(ImGui::GetWindowSize().y / 2 - ImGui::CalcTextSize(sAmount).y / 2);
			ImGui::Text("%s", sAmount);
			ImGui::End();
			ImGui::PopStyleVar(2);
			ImGui::PopStyleColor();
			ImGui::EndChild();

			ImGui::SetCursorPosX(middleX - 100 / 2);
			if (ImGui::AsdaOrangeButton(Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::OK).c_str(), ImVec2(100, 28)))
				battleStoppedFired = false;
		}
		ImGui::EndAsda();
	}

	// Обновление времени начала битвы
	bool battleStartTimeUpdateFired = false;	// Флаг события BattleStartTimeUpdate
	sf::Uint8 battleStartTimeUpdateD;			// День
	sf::Uint8 battle1StartTimeUpdateH;			// Часы (первая битва)
	sf::Uint8 battle1StartTimeUpdateM;			// Минуты (первая битва)
	sf::Uint8 battle2StartTimeUpdateH;			// Часы (вторая битва)
	sf::Uint8 battle2StartTimeUpdateM;			// Минуты (вторая битва)
	void HandleBattleStartTimeUpdate(Buffer &buffer)
	{
		battleStartTimeUpdateFired = true;
		buffer.Read(battleStartTimeUpdateD);
		buffer.Read(battle1StartTimeUpdateH);
		buffer.Read(battle1StartTimeUpdateM);
		buffer.Read(battle2StartTimeUpdateH);
		buffer.Read(battle2StartTimeUpdateM);
	}

	void BattleStartTime()
	{
		if (!battleStartTimeUpdateFired)
			return;

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.75f, 0.75f, 0.75f, 1));
		ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(0.75f, 0.75f, 0.75f, 1));
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 1));
		if (ImGui::Begin("##mining_war_battle_start_time", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove))
		{
			ImGui::SetWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - ImGui::GetWindowSize().x, ImGui::GetIO().DisplaySize.y / 2 - ImGui::GetWindowSize().y / 2));

			if (ImGui::GetIO().Fonts->Fonts.size() > 2)
				ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);

			ImTextureID n_01 = TextureFactory::Instance()->MakeTexture("juidata\\Image\\Texture.btz", "n_01.tex");

			auto middleX = round(ImGui::GetWindowSize().x / 2);

			const char *text_1 = Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::NEXT_BATTLE_TIME).c_str();
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 1));
			ImGui::BeginChild("##domain_1", ImVec2(126, 15));
			ImGui::SetCursorPosX(3);
			ImGui::SetCursorPosY(ImGui::GetWindowHeight() / 2 - 8 / 2);
			ImGui::Image(n_01, ImVec2(512, 512), ImVec4(444, 459, 8, 8));
			ImGui::SameLine(ImGui::GetWindowWidth() - 3 - 8);
			ImGui::Image(n_01, ImVec2(512, 512), ImVec4(444, 459, 8, 8));
			ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - ImGui::CalcTextSize(text_1).x / 2);
			ImGui::SetCursorPosY(ImGui::GetWindowSize().y / 2 - ImGui::CalcTextSize(text_1).y / 2);
			ImGui::Text("%s", text_1);
			ImGui::EndChild();
			ImGui::PopStyleColor();
			ImGui::Separator();

			char sD[128];
			switch (battleStartTimeUpdateD)
			{
			case 0: sprintf_s(sD, Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::MONDAY).c_str()); break;
			case 1: sprintf_s(sD, Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::TUESDAY).c_str()); break;
			case 2: sprintf_s(sD, Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::WEDNESDAY).c_str()); break;
			case 3: sprintf_s(sD, Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::THURSDAY).c_str()); break;
			case 4: sprintf_s(sD, Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::FRIDAY).c_str()); break;
			case 5: sprintf_s(sD, Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::SATURDAY).c_str()); break;
			case 6: sprintf_s(sD, Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::SUNDAY).c_str()); break;
			}

			char sTime[256];
			sprintf_s(sTime, Translator::GetInstance()->GetEntry(GetAsda2TranslatorLocale(), EntryType::NEXT_WAR_TIME_VALUE).c_str(),
				sD,
				battle1StartTimeUpdateH,
				battle1StartTimeUpdateM,
				battle2StartTimeUpdateH,
				battle2StartTimeUpdateM);

			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.01f, 0.01f, 0.01f, 1));
			ImGui::BeginChild("##domain_2", ImVec2(126, 15));
			ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - ImGui::CalcTextSize(sTime).x / 2);
			ImGui::SetCursorPosY(ImGui::GetWindowSize().y / 2 - ImGui::CalcTextSize(sTime).y / 2);
			ImGui::Text("%s", sTime);
			ImGui::EndChild();
			ImGui::PopStyleColor(1);

			if (ImGui::GetIO().Fonts->Fonts.size() > 2)
				ImGui::PopFont();
		}

		ImGui::End();
		ImGui::PopStyleVar(4);
		ImGui::PopStyleColor(3);
	}

	// Начало оверлея
	void BeginOverlay()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
		ImGui::SetNextWindowBgAlpha(0);
		ImGui::Begin("mining_war_overlay", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoInputs);
		ImGui::PopStyleVar(3);
	}

	// Конец оверлея
	void EndOverlay()
	{
		ImGui::End();
	}

	// Отладка
	void Debug()
	{
		if (ImGui::Begin("Mining War"))
		{
			if (ImGui::CollapsingHeader("Battle Join"))
			{
				static int iOwner = 0;
				ImGui::RadioButton("None", &iOwner, -1);
				ImGui::RadioButton("Light", &iOwner, 0);
				ImGui::RadioButton("Dark", &iOwner, 1);
				ImGui::RadioButton("Chaos", &iOwner, 2);

				static int iD = 0;
				ImGui::RadioButton("Monday", &iD, 0);
				ImGui::RadioButton("Tuesday", &iD, 1);
				ImGui::RadioButton("Wednesday", &iD, 2);
				ImGui::RadioButton("Thursday", &iD, 3);
				ImGui::RadioButton("Friday", &iD, 4);
				ImGui::RadioButton("Saturday", &iD, 5);
				ImGui::RadioButton("Sunday", &iD, 6);

				static int iH1 = 0;
				ImGui::InputInt("H1", &iH1);

				static int iM1 = 0;
				ImGui::InputInt("M1", &iM1);

				static int iH2 = 0;
				ImGui::InputInt("H2", &iH2);

				static int iM2 = 0;
				ImGui::InputInt("M2", &iM2);

				if (ImGui::Button("Join Response"))
				{
					Buffer outBuffer;
					outBuffer.SetOffset(10);
					outBuffer.Write(static_cast<sf::Int16>(iOwner));
					outBuffer.Write(static_cast<sf::Uint8>(iD));
					outBuffer.Write(static_cast<sf::Uint8>(iH1));
					outBuffer.Write(static_cast<sf::Uint8>(iM1));
					outBuffer.Write(static_cast<sf::Uint8>(iH2));
					outBuffer.Write(static_cast<sf::Uint8>(iM2));
					outBuffer.SetOffset(10);
					MiningWar::HandleJoinResponse(outBuffer);
				}
			}

			if (ImGui::CollapsingHeader("Mining Update"))
			{
				static int iBonus = 5;
				ImGui::InputInt("Bonus", &iBonus);

				static int iCount = 0;
				ImGui::InputInt("Count", &iCount);

				if (ImGui::Button("Send Mining Update"))
				{
					Buffer outBuffer;
					outBuffer.SetOffset(10);
					outBuffer.Write(static_cast<sf::Uint16>(iBonus));
					outBuffer.Write(static_cast<sf::Uint32>(iCount));
					outBuffer.SetOffset(10);
					MiningWar::HandleMiningUpdate(outBuffer);
				}
			}

			if (ImGui::CollapsingHeader("Battle Update"))
			{
				static int iCurHealth = 100;
				ImGui::InputInt("CurHealth", &iCurHealth);

				static int iMaxHealth = 100;
				ImGui::InputInt("MaxHealth", &iMaxHealth);

				if (ImGui::Button("Send Battle Update"))
				{
					Buffer outBuffer;
					outBuffer.SetOffset(10);
					outBuffer.Write(static_cast<sf::Uint32>(iCurHealth));
					outBuffer.Write(static_cast<sf::Uint32>(iMaxHealth));
					outBuffer.SetOffset(10);
					MiningWar::HandleBattleUpdate(outBuffer);
				}
			}

			if (ImGui::Button("Send Battle Started"))
			{
				Buffer outBuffer;
				outBuffer.SetOffset(10);
				MiningWar::HandleBattleStarted(outBuffer);
			}

			if (ImGui::CollapsingHeader("Battle Stopped"))
			{
				static int iWinner = 0;
				ImGui::RadioButton("Winner Light", &iWinner, 0);
				ImGui::RadioButton("Winner Dark", &iWinner, 1);

				static int iPlayer = 0;
				ImGui::RadioButton("Player Light", &iPlayer, 0);
				ImGui::RadioButton("Player Dark", &iPlayer, 1);

				static int iReward = 0;
				ImGui::RadioButton("Honor Point", &iReward, 0);

				static int iAmount = 0;
				ImGui::InputInt("Amount", &iAmount);

				if (ImGui::Button("Send HandleMiningWarFinished"))
				{
					Buffer outBuffer;
					outBuffer.SetOffset(10);
					outBuffer.Write(static_cast<sf::Uint16>(iWinner));
					outBuffer.Write(static_cast<sf::Uint16>(iPlayer));
					outBuffer.Write(static_cast<sf::Uint16>(iReward));
					outBuffer.Write(static_cast<sf::Uint32>(iAmount));
					outBuffer.SetOffset(10);
					MiningWar::HandleBattleStopped(outBuffer);
				}
			}

			if (ImGui::CollapsingHeader("Battle Start Time Update"))
			{
				static int iD = 0;
				ImGui::RadioButton("Monday", &iD, 0);
				ImGui::RadioButton("Tuesday", &iD, 1);
				ImGui::RadioButton("Wednesday", &iD, 2);
				ImGui::RadioButton("Thursday", &iD, 3);
				ImGui::RadioButton("Friday", &iD, 4);
				ImGui::RadioButton("Saturday", &iD, 5);
				ImGui::RadioButton("Sunday", &iD, 6);

				static int iH1 = 0;
				ImGui::InputInt("H1", &iH1);

				static int iM1 = 0;
				ImGui::InputInt("M1", &iM1);

				static int iH2 = 0;
				ImGui::InputInt("H2", &iH2);

				static int iM2 = 0;
				ImGui::InputInt("M2", &iM2);

				if (ImGui::Button("Send Battle Start Time Update"))
				{
					Buffer outBuffer;
					outBuffer.SetOffset(10);
					outBuffer.Write(static_cast<sf::Uint8>(iD));
					outBuffer.Write(static_cast<sf::Uint8>(iH1));
					outBuffer.Write(static_cast<sf::Uint8>(iM1));
					outBuffer.Write(static_cast<sf::Uint8>(iH2));
					outBuffer.Write(static_cast<sf::Uint8>(iM2));
					outBuffer.SetOffset(10);
					MiningWar::HandleBattleStartTimeUpdate(outBuffer);
				}
			}
		}
		ImGui::End();
	}

	// Интерфейс
	void MiningWar()
	{
		// Оверлей
		BeginOverlay();
		MiningWar::Phase();			// Фаза: добыча или битва
		MiningWar::BattleStarted();	// Начало битвы
		MiningWar::Join();			// Вход
		EndOverlay();

		// Окна
		MiningWar::Mining();			// Фаза добычи
		MiningWar::Battle();			// Фаза битвы
		MiningWar::BattleStopped();		// Конец битвы
		MiningWar::BattleStartTime();	// Время начало битвы

		Debug();						// Отладка
	}
}