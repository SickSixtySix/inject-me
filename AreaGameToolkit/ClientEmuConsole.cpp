// InjectMe
#include "ClientEmuConsole.hpp"

using namespace InjectMe::Utils;
using namespace InjectMe::Network;

// C++
#include <iostream>

ClientEmuConsole::ClientEmuConsole(IInnerClientEmu *innerClientEmu) : InnerClientEmuDecorator(innerClientEmu) {}

void ClientEmuConsole::HandleAuthConnected()
{
	std::cout << "Auth Connection Established" << std::endl;
}

void ClientEmuConsole::HandleGameConnected()
{
	std::cout << "Game Connection Established" << std::endl;
}

void ClientEmuConsole::HandleAuthPacket(sf::Uint16 packetID, Buffer &buffer)
{
	if (packetID == 1007)
	{
		++m_charactersCount;
	}
	else if (packetID == 1006)
	{
		for (size_t i = 0; i < m_charactersCount; i++)
		{
			sf::Uint8 level;
			buffer.Read(10 + 4 + 59 * i + 25, level);

			sf::Uint64 experience;
			buffer.Read(10 + 4 + 59 * i + 26, experience);

			std::cout << "Level = " << static_cast<unsigned>(level) << "\tExperience = " << experience << std::endl;
		}
	}

	InnerClientEmuDecorator::HandleAuthPacket(packetID, buffer);
}

void ClientEmuConsole::HandleGamePacket(sf::Uint16 packetID, Buffer &buffer)
{
	if (packetID == 4036)
	{
		sf::Uint8 level;
		buffer.Read(12, level);

		sf::Uint64 experience;
		buffer.Read(13, experience);

		std::cout << "Level = " << static_cast<unsigned>(level) << "\tExperience = " << experience << std::endl;
	}

	InnerClientEmuDecorator::HandleGamePacket(packetID, buffer);
}