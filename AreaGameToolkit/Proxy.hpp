#pragma once

// InjectMe
#include "Buffer.hpp"
#include "IProxyHandler.hpp"
#include "ISocketHandler.hpp"
#include "ClientSocket.hpp"
#include "ServerSocket.hpp"

// SFML
#include <SFML/Config.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>

// C++
#include <queue>

namespace InjectMe::Network
{
	// ����� ������
	class Proxy : public ISocketHandler
	{
	protected:

		// ����� ������� ��� ����������� ������� ������
		sf::IpAddress m_serverAddress;

		// ���� ������� ��� ����������� ������� ������
		sf::Uint16 m_serverPort;

		// ���� ������� ��� ����������� ������� ������
		sf::Uint16 m_clientPort;

		// ���������� ������� ������� ������
		IProxyHandler *m_handler = nullptr;

		// ��������� ���������� ������� ������
		IEncryption *m_encryption;

		// ���������� ����� ������� ������
		ClientSocket *m_clientSocket = nullptr;

		// ��������� ����� ������� ������
		ServerSocket *m_serverSocket = nullptr;

		// ������������ ����� ����������� ������
		virtual void HandleClientPacket(sf::Uint16 packetID, Utils::Buffer &buffer);

		// ������������ ����� ���������� ������
		virtual void HandleServerPacket(sf::Uint16 packetID, Utils::Buffer &buffer);

		// ������������ ����� �� ������� ������� ����������� ������
		virtual void HandleClientQueuePacket(sf::Uint16 packetID, Utils::Buffer &buffer) {};

		// ������������ ����� �� ������� ������� ���������� ������
		virtual void HandleServerQueuePacket(sf::Uint16 packetID, Utils::Buffer &buffer) {};

		// ��������� ����� � ������� ������� ����������� ������
		void ClientEnqueue(sf::Uint16 packetID, Utils::Buffer &buffer);

		// ��������� ����� � ������� ������� ���������� ������
		void ServerEnqueue(sf::Uint16 packetID, Utils::Buffer &buffer);

	public:

		// ����������� ������� ������
		Proxy(const sf::IpAddress &serverAddress, sf::Uint16 serverPort, sf::Uint16 clientPort, IProxyHandler *handler, IEncryption *encryption);

		// ���������� ����� ����� ���������� �����
		virtual void SendClientPacket(sf::Uint16 packetID, Utils::Buffer &buffer);

		// ���������� ����� ����� ��������� �����
		virtual void SendServerPacket(sf::Uint16 packetID, Utils::Buffer &buffer);

		// ���������� ����� ������� ��� ����������� ������� ������
		const sf::IpAddress& GetServerAddress() const;

		// ���������� ���� ������� ��� ����������� ������� ������
		sf::Uint16 GetServerPort() const;

		// ���������� ������� ����������� ������
		void HandleConnected(Socket *socket) override;

		// ���������� ������� �������� ������ �������
		void HandlePacket(Socket *socket, sf::Uint16 packetID, Utils::Buffer &buffer) override;

		// ���������� ������� �������� ������ ������� �� �������
		void HandleQueuePacket(Socket *socket, sf::Uint16 packetID, Utils::Buffer &buffer) override;

		// ���������� ������� ���������� ������
		void HandleDisconnected(Socket *socket) override;
	};
}