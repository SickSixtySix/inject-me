// InjectMe
#include "AsdaGlobalPacketFactory.hpp"
#include "KickClientEmu.hpp"

using namespace InjectMe::Utils;
using namespace InjectMe::Network;

KickClientEmu::KickClientEmu(const sf::IpAddress &address, sf::Uint16 port, const sf::String &username, const sf::String &password, sf::Uint32 accountID, sf::Uint16 charNum, sf::Uint16 posX, sf::Uint16 posY, sf::Uint32 victimAccountID, sf::Uint16 victimCharNum, IEncryption *encryption, IInnerClientEmu *innerClientEmu) : ClientEmu(address, port, username, password, accountID, charNum, posX, posY, encryption, innerClientEmu), m_victimAccountID(victimAccountID), m_victimCharNum(victimCharNum) {}

void KickClientEmu::HandleGamePacket(sf::Uint16 packetID, Buffer &buffer)
{
	if (packetID == 6743)
	{
		ClientEmu::HandleGamePacket(packetID, buffer);

		auto packet5058 = AsdaGlobalPacketFactory::Instance()->MakePacket(5058);
		packet5058.Write(34, m_accountID);
		packet5058.Write(38, m_charNum);
		packet5058.Write(40, m_posX);
		packet5058.Write(42, m_posY);
		m_asdaGlobalData.PreparePacket(5058, packet5058);
		SendGamePacket(5058, packet5058);
	}
	else
	{
		ClientEmu::HandleGamePacket(packetID, buffer);
	}
}