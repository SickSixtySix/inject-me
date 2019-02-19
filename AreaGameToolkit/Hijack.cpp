// AddonCheat
#include "AsdaGlobalData.hpp"
#include "AsdaGlobalEncryption.hpp"
#include "AsdaGlobalHook.hpp"
#include "ClientEmu.hpp"
#include "KickClientEmu.hpp"
#include "Hijack.hpp"
#include "Proxy.hpp"

using namespace InjectMe::Utils;
using namespace InjectMe::Network;
using namespace InjectMe::Hook::AsdaGlobal;
using namespace Cheat::Hijack;

// ImGui
#include "ImGui/imgui.h"
#include "ImGui/imgui_user.h"

// SFML
#include <SFML/System/Lock.hpp>
#include <SFML/System/Mutex.hpp>

#include <Windows.h>

// C++
#include <string>
#include <unordered_map>

Hijack *Hijack::s_instance = nullptr;

Hijack::Hijack()
{
	if (!(GetFileAttributes("Characters") & FILE_ATTRIBUTE_DIRECTORY))
		if (!CreateDirectory("Characters", NULL))
			return;

	WIN32_FIND_DATA ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	hFind = FindFirstFile("Characters\\*", &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
		return;
	do
		if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			m_characters[ffd.cFileName] = Buffer("Characters\\" + std::string(ffd.cFileName));
	while (FindNextFile(hFind, &ffd) != 0);

	FindClose(hFind);
}

Hijack* Hijack::Instance()
{
	if (s_instance == nullptr)
		s_instance = new Hijack();

	return s_instance;
}

void Hijack::Handle4005(Buffer &buffer)
{
	// Считывание имени персонажа и сохранение его в файл
	char name[20];
	buffer.Read(27, name);
	buffer.Save("Characters\\" + std::string(name));
	
	// Добавление персонажа в список
	sf::Lock lock(m_charactersMutex);
	m_characters[name] = buffer;
}

void Hijack::Handle5058(Buffer &buffer)
{
	if (!m_enabled)
		return;
	
	// Замена идентификатора аккаунта в адресном пространстве клиента
	SetAccountID(m_accountID);
	
	// Модификация пакета
	buffer.Write(34, m_accountID);
	buffer.Write(38, m_charNum);
	buffer.Write(40, m_posX);
	buffer.Write(42, m_posY);
}

extern Proxy *currentProxy;

void Hijack::ImGui()
{
	ImGui::InputUint32("AccountID", &m_accountID);
	ImGui::InputUint16("CharNum", &m_charNum);
	ImGui::InputUint16("PosX", &m_posX);
	ImGui::InputUint16("PosY", &m_posY);
	
	static std::string selected = "Select...";
	if (ImGui::BeginCombo("Characters", selected.c_str()))
	{
		sf::Lock lock(m_charactersMutex);
		for (auto &pair : m_characters)
		{
			if (ImGui::Selectable(pair.first.c_str(), selected == pair.first))
			{
				pair.second.Read(23, m_accountID);
				pair.second.Read(47, m_charNum);
				pair.second.Read(12, m_posX);
				pair.second.Read(14, m_posY);
				selected = pair.first;
			}
		}
		ImGui::EndCombo();
	}
	
	if (ImGui::Button("Hijack##hijack_button"))
		m_enabled = true;
	if (ImGui::Button("Kick##kick_button"))
		(new KickClientEmu(currentProxy->GetServerAddress(), currentProxy->GetServerPort(), "Samuel267", "due?_r6q", 0x0000BEF9, 0x000A, m_posX, m_posY, m_accountID, m_charNum, AsdaGlobalEncryption::Instance()))->StartClientEmu();
}