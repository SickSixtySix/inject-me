// InjectMe
#include "AsdaGlobalHook.hpp"
#include "AsdaGlobalPacketFactory.hpp"
#include "AsdaGlobalProxy.hpp"

using namespace InjectMe::Utils;
using namespace InjectMe::Network;
using namespace InjectMe::Hook::AsdaGlobal;

// Cheat
#include "Hijack.hpp"
#include "Sniffer.hpp"
#include "Teleport.hpp"

using namespace Cheat::Hijack;
using namespace Cheat::Sniffer;
using namespace Cheat::Teleport;

// ImGui
#include "ImGui/imgui.h"

// WinAPI
#include <Windows.h>

Proxy *currentProxy = nullptr;

void AsdaGlobalProxy::send1003()
{
	auto packet = AsdaGlobalPacketFactory::Instance()->MakePacket(1003);
	packet.Write(54, m_username);
	packet.Write(104, m_password);
	SendClientPacket(1003, packet);
}

void AsdaGlobalProxy::ReconnectTask()
{
	Teleport(this, GetMapID(), m_posX, m_posY);
}

AsdaGlobalProxy::AsdaGlobalProxy(const sf::IpAddress &serverAddress, sf::Uint16 serverPort, sf::Uint16 clientPort, const sf::String &username, const sf::String &password, sf::Uint32 accountID, sf::Uint16 charNum, sf::Uint16 posX, sf::Uint16 posY, IProxyHandler *handler, IEncryption *encryption)
	: Proxy(serverAddress, serverPort, clientPort, handler, encryption), m_username(username), m_password(password), m_accountID(accountID), m_charNum(charNum), m_posX(posX), m_posY(posY), m_asdaGlobalData(0x0180EC24, 0x034DDF94, 0x0180E964, 0x0180EC24)
{
	currentProxy = this;
}

void AsdaGlobalProxy::HandleClientQueuePacket(sf::Uint16 packetID, Buffer &buffer)
{
	buffer.SetHandler(nullptr);
	m_encryption->Encrypt(buffer);

	// TODO: Обработка очереди пакетов клиентского сокета
}

void AsdaGlobalProxy::HandleServerQueuePacket(sf::Uint16 packetID, Buffer &buffer)
{
	// TODO: Обработка очереди пакетов серверного сокета
}

void AsdaGlobalProxy::HandleClientPacket(sf::Uint16 packetID, Buffer &buffer)
{
	auto copy = buffer;
	copy.SetHandler(nullptr);
	m_encryption->Encrypt(copy);
	Sniffer::Instance()->LogFromServerToClient(this, packetID, copy); 

	// Немедленная обработка
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
			SendClientPacket(1012, packet1012);
			auto packet1000 = AsdaGlobalPacketFactory::Instance()->MakePacket(1000); SendClientPacket(1000, packet1000);
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
			SendClientPacket(1005, packet1005);
		}
	}
	else if (packetID == 4005)
		Hijack::Instance()->Handle4005(copy);

	// Отправка в очередь
	switch (packetID)
	{
	case 0: break;
		// TODO
	}

	// Сброс
	switch (packetID)
	{
	case 0: break;
	default:
		Proxy::HandleClientPacket(packetID, buffer);
	}
}

void AsdaGlobalProxy::HandleServerPacket(sf::Uint16 packetID, Buffer &buffer)
{
	auto copy = buffer;
	copy.SetHandler(nullptr);
	m_encryption->Encrypt(copy);
	Sniffer::Instance()->LogFromClientToServer(this, packetID, copy);

	if (packetID == 4006)
	{
		float posX, posY;
		buffer.Read(43, posX);
		buffer.Read(47, posY);
		m_posX = static_cast<sf::Uint16>((posX - 50) / 100);
		m_posY = static_cast<sf::Uint16>((posY - 50) / 100);
	}
	else if (packetID == 5058)
	{
		Hijack::Instance()->Handle5058(copy);
		m_asdaGlobalData.PreparePacket(packetID, copy);
		SendClientPacket(packetID, copy);
		return;
	}
	else if (packetID == 20000)
		SheduleTask(Task(&AsdaGlobalProxy::ReconnectTask, this, sf::seconds(2 * 60)));

	// Отправка в очередь
	switch (packetID)
	{
	case 0: break;
	}

	// Сброс
	switch (packetID)
	{
	case 0:
	case 1012:
		break;
	default:
		Proxy::HandleServerPacket(packetID, buffer);
	}
}

void AsdaGlobalProxy::HandleConnected(Socket *socket)
{
	if (m_serverSocket == socket)
		send1003();

	Proxy::HandleConnected(socket);
}