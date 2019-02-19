#pragma once

// AddonUtils
#include "Buffer.hpp"

// SFML
#include <SFML/Config.hpp>
#include <SFML/System/Mutex.hpp>

// C++
#include <unordered_map>

namespace Cheat::Hijack
{
	// ����� ���� "����� ���������"
	class Hijack
	{
		// ��������� ������ ����
		static Hijack *s_instance;

		// ������ ���������� ��� �����
		std::unordered_map<std::string, InjectMe::Utils::Buffer> m_characters;
		sf::Mutex m_charactersMutex;

		// ������������� �������� ��� �����
		sf::Uint32 m_accountID = 0x9933;

		// ����� ��������� ��� �����
		sf::Uint16 m_charNum = 0x0A;

		// ������� X ��������� ��� �����
		sf::Uint16 m_posX = 0x100;

		// ������� Y ��������� ��� �����
		sf::Uint16 m_posY = 0x100;

		// ���� ���������� ����
		bool m_enabled = false;

		// ����������� ������ ����
		Hijack();

	public:

		// ���������� ��������� ������ ����
		static Hijack* Instance();

		// ������������ ����� 4005
		void Handle4005(InjectMe::Utils::Buffer &buffer);

		// ������������ ����� 5058
		void Handle5058(InjectMe::Utils::Buffer &buffer);

		// ���������
		void ImGui();
	};
}