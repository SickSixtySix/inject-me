#pragma once

// SFML
#include <SFML\Config.hpp>

namespace InjectMe::Hook::AsdaGlobal
{
	// ���������� ������������� �������� Asda Global
	sf::Uint32 GetAccountID();

	// ���������� ������������� ������ Asda Global
	sf::Uint16 GetSessionID();

	// ���������� ������������� ������� Asda Global
	sf::Uint16 GetGuildID();

	// ���������� (?) Asda Global
	sf::Uint32 GetUnknown1();

	// ���������� ������� X ��������� Asda Global
	sf::Uint16 GetPositionX();

	// ���������� ������� Y ��������� Asda Global
	sf::Uint16 GetPositionY();

	// ���������� (?) Asda Global
	sf::Uint16 GetUnknown4();

	// ���������� ����� ��������� Asda Global
	sf::Uint8 GetCharNum();

	// ���������� ������������� ����� ��������� Asda Global
	sf::Uint8 GetMapID();

	// ������������� ������������� �������� Asda Global
	void SetAccountID(sf::Uint32 accountID);

	// ������������� ������������� ����� �������� Asda Global
	void SetMapID(sf::Uint8 mapID);
}