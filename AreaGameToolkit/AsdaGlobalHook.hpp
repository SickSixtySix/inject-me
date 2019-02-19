#pragma once

// SFML
#include <SFML\Config.hpp>

namespace InjectMe::Hook::AsdaGlobal
{
	// Возвращает идентификатор аккаунта Asda Global
	sf::Uint32 GetAccountID();

	// Возвращает идентификатор сессии Asda Global
	sf::Uint16 GetSessionID();

	// Возвращает идентификатор гильдии Asda Global
	sf::Uint16 GetGuildID();

	// Возвращает (?) Asda Global
	sf::Uint32 GetUnknown1();

	// Возвращает позицию X персонажа Asda Global
	sf::Uint16 GetPositionX();

	// Возвращает позицию Y персонажа Asda Global
	sf::Uint16 GetPositionY();

	// Возвращает (?) Asda Global
	sf::Uint16 GetUnknown4();

	// Возвращает номер персонажа Asda Global
	sf::Uint8 GetCharNum();

	// Возвращает идентификатор карты персонажа Asda Global
	sf::Uint8 GetMapID();

	// Устанавливает идентификатор аккаунта Asda Global
	void SetAccountID(sf::Uint32 accountID);

	// Устанавливает идентификатор карты аккаунта Asda Global
	void SetMapID(sf::Uint8 mapID);
}