// InjectMe
#include "Proxy.hpp"

using namespace InjectMe::Utils;
using namespace InjectMe::Network;

// SFML
#include <SFML/System/Lock.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>

void Proxy::ClientEnqueue(sf::Uint16 packetID, Buffer &buffer)
{
	m_clientSocket->Enqueue(packetID, buffer);
}

void Proxy::ServerEnqueue(sf::Uint16 packetID, Buffer &buffer)
{
	m_serverSocket->Enqueue(packetID, buffer);
}

void Proxy::HandleClientPacket(sf::Uint16 packetID, Buffer &buffer)
{
	m_serverSocket->Send(buffer.GetMemory().lpAddress, buffer.GetOffset());
}

void Proxy::HandleServerPacket(sf::Uint16 packetID, Buffer &buffer)
{
	m_clientSocket->Send(buffer.GetMemory().lpAddress, buffer.GetOffset());
}

Proxy::Proxy(const sf::IpAddress &serverAddress, sf::Uint16 serverPort, sf::Uint16 clientPort, IProxyHandler *handler, IEncryption *encryption)
{
	m_serverAddress = serverAddress;
	m_serverPort = serverPort;
	m_clientPort = clientPort;
	m_handler = handler;
	m_encryption = encryption;
	m_clientSocket = new ClientSocket(m_serverAddress, m_serverPort, this, m_encryption);
	if (!m_clientSocket->Connect())
		m_handler->HandleReady();
}

void Proxy::SendServerPacket(sf::Uint16 packetID, Buffer &buffer)
{
	m_serverSocket->SendPacket(packetID, buffer);
}

void Proxy::SendClientPacket(sf::Uint16 packetID, Buffer &buffer)
{
	m_clientSocket->SendPacket(packetID, buffer);
}

const sf::IpAddress& Proxy::GetServerAddress() const
{
	return m_serverAddress;
}

sf::Uint16 Proxy::GetServerPort() const
{
	return m_serverPort;
}

void Proxy::HandleConnected(Socket *socket)
{
	if (m_clientSocket == socket)
	{
		m_serverSocket = new ServerSocket(m_clientPort, this, m_encryption);
		if (!m_serverSocket->Connect())
			m_clientSocket->Disconnect();
		m_handler->HandleReady();
	}
}

void Proxy::HandlePacket(Socket *socket, sf::Uint16 packetID, Buffer &buffer)
{
	if (m_clientSocket == socket)
		HandleClientPacket(packetID, buffer);
	else if (m_serverSocket == socket)
		HandleServerPacket(packetID, buffer);
}

void Proxy::HandleQueuePacket(Socket *socket, sf::Uint16 packetID, Buffer &buffer)
{
	if (m_clientSocket == socket)
		HandleClientQueuePacket(packetID, buffer);
	else if (m_serverSocket == socket)
		HandleServerQueuePacket(packetID, buffer);
}

void Proxy::HandleDisconnected(Socket *socket)
{
	if (m_clientSocket == socket && m_serverSocket != nullptr)
		m_serverSocket->Disconnect();
	else if (m_serverSocket == socket && m_clientSocket != nullptr)
		m_clientSocket->Disconnect();
}