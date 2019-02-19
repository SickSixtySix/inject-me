// InjectMe
#include "AsdaGlobalHook.hpp"

namespace InjectMe::Hook::AsdaGlobal
{
	sf::Uint8 mapID = 3;

	sf::Uint32 GetAccountID()
	{
		return *reinterpret_cast<sf::Uint32*>(0x01B70AB8 + 0x0000008C);
	}

	sf::Uint16 GetSessionID()
	{
		return *reinterpret_cast<sf::Uint16*>(*reinterpret_cast<sf::Uint32*>(0x0181A688 + 0x0025B398) + 0x00030FD0);
	}

	//0x0180EC24
	sf::Uint16 GetGuildID()
	{
		return *reinterpret_cast<sf::Uint16*>(0x03431B88);
	}

	sf::Uint32 GetUnknown1()
	{
		return *reinterpret_cast<sf::Uint32*>(0x034DDF94);
	}

	sf::Uint16 GetPositionX()
	{
		return *reinterpret_cast<sf::Uint16*>(0x01B0088D);
	}

	sf::Uint16 GetPositionY()
	{
		return *reinterpret_cast<sf::Uint16*>(0x01B0088F);
	}

	sf::Uint16 GetUnknown4()
	{
		return *reinterpret_cast<sf::Uint16*>(0x01816C94);
	}

	sf::Uint8 GetCharNum()
	{
		return *reinterpret_cast<sf::Uint8*>(0x01815C00);
	}

	sf::Uint8 GetMapID()
	{
		return mapID;
	}

	void SetAccountID(sf::Uint32 accountID)
	{
		*reinterpret_cast<sf::Uint32*>(0x01B70AB8 + 0x0000008C) = accountID;
		*reinterpret_cast<sf::Uint32*>(*reinterpret_cast<sf::Uint32*>(0x0181A688 + 0x0025B398) + 0x00000440) = accountID;
	}

	void SetMapID(sf::Uint8 mapID)
	{
		InjectMe::Hook::AsdaGlobal::mapID = mapID;
	}
}