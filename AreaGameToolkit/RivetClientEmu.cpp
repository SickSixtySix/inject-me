// InjectMe
#include "AsdaGlobalPacketFactory.hpp"

using namespace InjectMe::Utils;
using namespace InjectMe::Network;

// Rivet
#include "RivetClientEmu.hpp"

using namespace Rivet;

// SFML
#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>

void RivetClientEmu::threadFunction()
{
	sf::Clock clock;

	auto packet5043 = AsdaGlobalPacketFactory::Instance()->MakePacket(5043);
	packet5043.Write(35, m_accountID);
	SendGamePacket(5043, packet5043);
	while (m_gameSocket->IsConnected() && clock.getElapsedTime() < sf::seconds(30))
	{
		auto packet5041 = AsdaGlobalPacketFactory::Instance()->MakePacket(5041);
		packet5041.Write(34, m_accountID);
		SendGamePacket(5041, packet5041);
		sf::sleep(sf::milliseconds(5));
	}

	m_gameSocket->Disconnect();
	m_active = false;
}

void RivetClientEmu::HandleGamePacket(sf::Uint16 packetID, Buffer &buffer)
{
	if (packetID == 6743)
	{
		ClientEmu::HandleGamePacket(packetID, buffer);
		m_thread.launch();
		return;
	}

	ClientEmu::HandleGamePacket(packetID, buffer);
}

RivetClientEmu::RivetClientEmu(const sf::IpAddress &address, sf::Uint16 port, const sf::String &username, const sf::String &password, sf::Uint32 accountID, sf::Uint16 charNum, sf::Uint16 posX, sf::Uint16 posY, IEncryption *encryption, IInnerClientEmu *innerClientEmu) : ClientEmu(address, port, username, password, accountID, charNum, posX, posY, encryption, innerClientEmu), m_thread(&RivetClientEmu::threadFunction, this)
{
	m_active = true;
}

bool RivetClientEmu::IsActive() const
{
	return m_active;
}