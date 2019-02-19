// InjectMe
#include "AsdaGlobalD3D9HookHandler.hpp"
#include "AsdaGlobalHook.hpp"
#include "Proxy.hpp"

using namespace InjectMe::Network;
using namespace InjectMe::Hook::D3D9;
using namespace InjectMe::Hook::AsdaGlobal;

// Cheat
#include "Hijack.hpp"
#include "Sniffer.hpp"
#include "Teleport.hpp"

using namespace Cheat::Hijack;
using namespace Cheat::Sniffer;
using namespace Cheat::Teleport;

// ImGui
#include "ImGui/imgui.h"
#include "ImGui/imgui_user.h"

extern Proxy *currentProxy;

AsdaGlobalD3D9HookHandler *AsdaGlobalD3D9HookHandler::s_instance = nullptr;

AsdaGlobalD3D9HookHandler::AsdaGlobalD3D9HookHandler() {}

AsdaGlobalD3D9HookHandler* AsdaGlobalD3D9HookHandler::Instance()
{
	if (s_instance == nullptr)
		s_instance = new AsdaGlobalD3D9HookHandler();

	return s_instance;
}


bool AsdaGlobalD3D9HookHandler::CanHandleNewFrame(unsigned long ebpValue)
{
	// TODO: Значения регистра EBP

	return true;
}

void AsdaGlobalD3D9HookHandler::HandleNewFrame()
{
	if (currentProxy == nullptr)
		return;

	// Сниффер
	Sniffer::Instance()->ImGui();

	// Читы
	if (ImGui::Begin("Cheats"))
	{
		// Телепортация
		if (ImGui::CollapsingHeader("Teleport"))
		{
			static sf::Uint16 mapID = 3;
			ImGui::InputUint16("MapID", &mapID);

			static sf::Uint16 posX = 256;
			ImGui::InputUint16("PosX", &posX);

			static sf::Uint16 posY = 256;
			ImGui::InputUint16("PosY", &posY);

			if (ImGui::Button("Teleport()"))
				Teleport(currentProxy, mapID, posX, posY);

			if (ImGui::Button("Mail Manager"))
				Teleport(currentProxy, 3, 150, 354);
		}

		// Кража
		if (ImGui::CollapsingHeader("Hijack"))
			Hijack::Instance()->ImGui();

		ImGui::Text("%u %u", GetPositionX(), GetPositionY());
	}
	ImGui::End();
}