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
	// Класс чита "Кража персонажа"
	class Hijack
	{
		// Экземпляр класса чита
		static Hijack *s_instance;

		// Список персонажей для кражи
		std::unordered_map<std::string, InjectMe::Utils::Buffer> m_characters;
		sf::Mutex m_charactersMutex;

		// Идентификатор аккаунта для кражи
		sf::Uint32 m_accountID = 0x9933;

		// Номер персонажа для кражи
		sf::Uint16 m_charNum = 0x0A;

		// Позиция X персонажа для кражи
		sf::Uint16 m_posX = 0x100;

		// Позиция Y персонажа для кражи
		sf::Uint16 m_posY = 0x100;

		// Флаг активности чита
		bool m_enabled = false;

		// Конструктор класса чита
		Hijack();

	public:

		// Возвращает экземпляр класса чита
		static Hijack* Instance();

		// Обрабатывает пакет 4005
		void Handle4005(InjectMe::Utils::Buffer &buffer);

		// Обрабатывает пакет 5058
		void Handle5058(InjectMe::Utils::Buffer &buffer);

		// Интерфейс
		void ImGui();
	};
}