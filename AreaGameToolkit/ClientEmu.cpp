// InjectMe
#include "AsdaGlobalPacketFactory.hpp"
#include "ClientEmu.hpp"

using namespace InjectMe::Utils;
using namespace InjectMe::Network;

void ClientEmu::HandleAuthConnected()
{
	if (m_innerClientEmu)
		m_innerClientEmu->HandleAuthConnected();

	send1003();
}

void ClientEmu::HandleGameConnected()
{
	if (m_innerClientEmu)
		m_innerClientEmu->HandleGameConnected();

	m_asdaGlobalData.SwitchData();

	auto packet20000 = AsdaGlobalPacketFactory::Instance()->MakePacket(20000);
	packet20000.Write(50, m_accountID);
	SendGamePacket(20000, packet20000);
}

void ClientEmu::HandleAuthPacket(sf::Uint16 packetID, Buffer &buffer)
{
	if (m_innerClientEmu)
		m_innerClientEmu->HandleAuthPacket(packetID, buffer);

	if (packetID == 1004)
	{
		sf::Uint16 status;
		buffer.Read(10, status);

		if (status != 1)
			send1003();
		else
		{
			auto packet1012 = AsdaGlobalPacketFactory::Instance()->MakePacket(1012);
			packet1012.Write(34, m_accountID);
			sf::Uint8 serverID = 0x00;
			packet1012.Write(38, serverID);
			SendAuthPacket(1012, packet1012);
			auto packet1000 = AsdaGlobalPacketFactory::Instance()->MakePacket(1000); SendAuthPacket(1000, packet1000);
		}
	}
	else if (packetID == 1013)
	{
		if (++m_packet1013Counter == 2)
		{
			auto packet1005 = AsdaGlobalPacketFactory::Instance()->MakePacket(1005);
			packet1005.Write(34, m_accountID);
			sf::Uint16 channelID = 0x00;
			packet1005.Write(38, channelID);
			SendAuthPacket(1005, packet1005);
		}
	}
	else if (packetID == 1025)
	{
		auto packet1016 = AsdaGlobalPacketFactory::Instance()->MakePacket(1016);
		packet1016.Write(35, m_accountID);
		packet1016.Write(39, m_charNum);
		sf::Uint16 channelID = 0x00;
		packet1016.Write(42, channelID);
		SendAuthPacket(1016, packet1016);
		auto packet1000 = AsdaGlobalPacketFactory::Instance()->MakePacket(1000); SendAuthPacket(1000, packet1000);
	}
	else if (packetID == 1027)
		buffer.Read(11, m_sessionID);
	else if (packetID == 1021)
	{
		char address[20];
		buffer.Read(14, address);
		sf::Uint16 port;
		buffer.Read(34, port);

		m_gameSocket = new ClientSocket(sf::IpAddress(address), port, this, m_encryption);
		m_gameSocket->Connect();
	}
}

void ClientEmu::HandleGamePacket(sf::Uint16 packetID, Buffer &buffer)
{
	if (m_innerClientEmu)
		m_innerClientEmu->HandleGamePacket(packetID, buffer);

	if (packetID == 1001)
	{
		if (++m_packet1001Counter == 2)
		{
			auto packet4001 = AsdaGlobalPacketFactory::Instance()->MakePacket(4001);
			packet4001.Write(34, m_accountID);
			//packet4001.Write(40, static_cast<sf::Uint8>(m_charNum));
			packet4001.Write(40, static_cast<sf::Uint16>(0x0A));
			packet4001.Write(46, m_sessionID);
			SendGamePacket(4001, packet4001);
		}
	}
	else if (packetID == 6004)
	{
		auto packet5056 = AsdaGlobalPacketFactory::Instance()->MakePacket(5056); SendAuthPacket(5056, packet5056);
		auto packet1000 = AsdaGlobalPacketFactory::Instance()->MakePacket(1000); SendAuthPacket(1000, packet1000);
		m_authSocket->Disconnect();

		packet1000 = AsdaGlobalPacketFactory::Instance()->MakePacket(1000); SendGamePacket(1000, packet1000);
		packet1000 = AsdaGlobalPacketFactory::Instance()->MakePacket(1000); SendGamePacket(1000, packet1000);
	}
	else if (packetID == 6743)
	{
		auto packet9915 = AsdaGlobalPacketFactory::Instance()->MakePacket(9915); SendGamePacket(9915, packet9915);

		//auto packet5058 = AsdaGlobalPacketFactory::Instance()->MakePacket(5058);
		//packet5058.Write(34, m_accountID);
		//packet5058.Write(38, m_charNum);
		//packet5058.Write(40, m_posX);
		//packet5058.Write(42, m_posY);
		//SendGamePacket(5058, packet5058);
	}
}

void ClientEmu::HandleAuthQueuePacket(sf::Uint16 packetID, Buffer &buffer)
{
	if (m_innerClientEmu)
		m_innerClientEmu->HandleAuthQueuePacket(packetID, buffer);
}

void ClientEmu::HandleGameQueuePacket(sf::Uint16 packetID, Buffer &buffer)
{
	if (m_innerClientEmu)
		m_innerClientEmu->HandleGameQueuePacket(packetID, buffer);
}

void ClientEmu::HandleAuthDisconnected()
{
	if (m_innerClientEmu)
		m_innerClientEmu->HandleAuthDisconnected();
}

void ClientEmu::HandleGameDisconnected()
{
	if (m_innerClientEmu)
		m_innerClientEmu->HandleGameDisconnected();
}

void ClientEmu::send1003()
{
	auto packet = AsdaGlobalPacketFactory::Instance()->MakePacket(1003);
	packet.Write(54, m_username);
	packet.Write(104, m_password);
	SendAuthPacket(1003, packet);
}

void ClientEmu::AuthEnqueue(sf::Uint16 packetID, Buffer &buffer)
{
	m_authSocket->Enqueue(packetID, buffer);
}

void ClientEmu::GameEnqueue(sf::Uint16 packetID, Buffer &buffer)
{
	m_gameSocket->Enqueue(packetID, buffer);
}

ClientEmu::ClientEmu(const sf::IpAddress &address, sf::Uint16 port, const sf::String &username, const sf::String &password, sf::Uint32 accountID, sf::Uint16 charNum, sf::Uint16 posX, sf::Uint16 posY, IEncryption *encryption, IInnerClientEmu *innerClientEmu) : m_address(address), m_port(port), m_username(username), m_password(password), m_accountID(accountID), m_charNum(charNum), m_posX(posX), m_posY(posY), m_encryption(encryption), m_innerClientEmu(innerClientEmu)
{
	m_asdaGlobalData.ResetData();
}

void ClientEmu::StartClientEmu()
{
	m_authSocket = new ClientSocket(m_address, m_port, this, m_encryption);
	m_authSocket->Connect();
}

void ClientEmu::SendAuthPacket(sf::Uint16 packetID, Buffer &buffer)
{
	m_asdaGlobalData.PreparePacket(packetID, buffer);
	m_authSocket->SendPacket(packetID, buffer);
}

void ClientEmu::SendGamePacket(sf::Uint16 packetID, Buffer &buffer)
{
	m_asdaGlobalData.PreparePacket(packetID, buffer);
	m_gameSocket->SendPacket(packetID, buffer);
}

void ClientEmu::HandleConnected(Socket *socket)
{
	if (m_authSocket == socket)
		HandleAuthConnected();
	else if (m_gameSocket == socket)
		HandleGameConnected();
}

void ClientEmu::HandlePacket(Socket *socket, sf::Uint16 packetID, Buffer &buffer)
{
	buffer.SetHandler(nullptr);
	m_encryption->Encrypt(buffer);

	if (m_authSocket == socket)
		HandleAuthPacket(packetID, buffer);
	else if (m_gameSocket == socket)
		HandleGamePacket(packetID, buffer);
}

void ClientEmu::HandleQueuePacket(Socket *socket, sf::Uint16 packetID, Buffer &buffer)
{
	if (m_authSocket == socket)
		HandleAuthQueuePacket(packetID, buffer);
	else if (m_gameSocket == socket)
		HandleGameQueuePacket(packetID, buffer);
}

void ClientEmu::HandleDisconnected(Socket *socket)
{
	if (m_authSocket == socket)
		HandleAuthDisconnected();
	else if (m_gameSocket == socket)
		HandleGameDisconnected();
}