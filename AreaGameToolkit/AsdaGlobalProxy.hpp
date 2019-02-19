#pragma once

// InjectMe
#include "AsdaGlobalData.hpp"
#include "Proxy.hpp"
#include "TaskExecutor.hpp"

// SFML
#include <SFML/Config.hpp>
#include <SFML/Network/IpAddress.hpp>

namespace InjectMe::Network
{
	class AsdaGlobalProxy : public Proxy, private Utils::TaskExecutor
	{
#pragma region ������ �������

		// ����� �������� ������� ������
		sf::String m_username;

		// ������ �������� ������� ������
		sf::String m_password;

		// ������������� �������� ������� ������
		sf::Uint32 m_accountID;

		// ����� ��������� �������� ������� ������
		sf::Uint16 m_charNum;

		// ������� X ��������� �������� ������� ������
		sf::Uint16 m_posX;

		// ������� Y ��������� �������� ������� ������
		sf::Uint16 m_posY;

		// ������������ ����� ��������� �������� ������� ������
		sf::Uint8 m_mapID = 3;

		// ������� ������� 1001 ������� ������
		size_t m_packet1001Counter = 0;

		// ������� ������� 1013 ������� ������
		size_t m_packet1013Counter = 0;

		// �������� ������� ������� ������
		Hook::AsdaGlobal::AsdaGlobalData m_asdaGlobalData;

#pragma endregion

#pragma region �������� �������

		// ���������� ����� 1003
		void send1003();

#pragma endregion

#pragma region ������� �������

		// ������� ��������������� ������� �������
		void ReconnectTask();

#pragma endregion

	public:

		// ����������� ������
		AsdaGlobalProxy(const sf::IpAddress &serverAddress, sf::Uint16 serverPort, sf::Uint16 clientPort, const sf::String &username, const sf::String &password, sf::Uint32 accountID, sf::Uint16 charNum, sf::Uint16 posX, sf::Uint16 posY, IProxyHandler *handler, IEncryption *encryption);

		// ������������ ����� �� ���������� ������� ������� ������
		void HandleClientQueuePacket(sf::Uint16 packetID, Utils::Buffer &buffer) final;

		// ������������ ����� �� ��������� ������� ������� ������
		void HandleServerQueuePacket(sf::Uint16 packetID, Utils::Buffer &buffer) final;

		// ������������ ���������� ����� � �������� �������
		void HandleClientPacket(sf::Uint16 packetID, Utils::Buffer &buffer) final;

		// ������������ ��������� ����� � �������� �������
		void HandleServerPacket(sf::Uint16 packetID, Utils::Buffer &buffer) final;

		// ���������� ������� ����������� ������
		void HandleConnected(Socket *socket) final;
	};
}