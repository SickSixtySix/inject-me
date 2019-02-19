#pragma once

// InjectMe
#include "ClientSocket.hpp"
#include "AsdaGlobalData.hpp"
#include "IInnerClientEmu.hpp"
#include "IOuterClientEmu.hpp"
#include "ISocketHandler.hpp"

// SFML
#include <SFML/Config.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/System/String.hpp>

namespace InjectMe::Network
{
	class ClientEmu : public ISocketHandler, public IInnerClientEmu, public IOuterClientEmu
	{
		// ���������� ��������� ��������� �������
		IInnerClientEmu *m_innerClientEmu;

	protected:

#pragma region ������ ��� �����������

		// ����� ������� ����������� ��� ����������� ������� ���������
		sf::IpAddress m_address;

		// ���� ������� ����������� ��� ����������� ������� ���������
		sf::Uint16 m_port;

#pragma endregion

#pragma region ������ �������

		// ����� �������� ������� ���������
		sf::String m_username;

		// ������ �������� ������� ���������
		sf::String m_password;

		// ������������� �������� ������� ���������
		sf::Uint32 m_accountID;

		// ����� ��������� �������� ������� ���������
		sf::Uint16 m_charNum;

		// ������� X ��������� �������� ������� ���������
		sf::Uint16 m_posX;

		// ������� Y ��������� �������� ������� ���������
		sf::Uint16 m_posY;

		// ������������� ������ ������� ���������
		sf::Uint32 m_sessionID;

		// ������� ������� 1001 ������� ���������
		size_t m_packet1001Counter = 0;

		// ������� ������� 1013 ������� ���������
		size_t m_packet1013Counter = 0;

#pragma endregion

#pragma region ������ ���������

		// ��������� ���������� ������� ���������
		IEncryption *m_encryption;

		// ����� ��� ����������� � ������� ����������� ������� ���������
		ClientSocket *m_authSocket;

		// ����� ��� ����������� � �������� ������� ������� ���������
		ClientSocket *m_gameSocket;

		// �������� ������� ���������
		Hook::AsdaGlobal::AsdaGlobalData m_asdaGlobalData;

#pragma endregion

#pragma region ������� ��������� (���������� IClientEmu)

		// ������������ ������� ����������� ������ ������� �����������
		void HandleAuthConnected() override;

		// ������������ ������� ����������� ������ �������� �������
		void HandleGameConnected() override;

		// ������������ ����� ������ ������� �����������
		void HandleAuthPacket(sf::Uint16 packetID, Utils::Buffer &buffer) override;

		// ������������ ����� ������ �������� �������
		void HandleGamePacket(sf::Uint16 packetID, Utils::Buffer &buffer) override;

		// ������������ ����� �� ������� ������� ������ ������� �����������
		void HandleAuthQueuePacket(sf::Uint16 packetID, Utils::Buffer &buffer) override;

		// ������������ ����� �� ������� ������� ������ �������� �������
		void HandleGameQueuePacket(sf::Uint16 packetID, Utils::Buffer &buffer) override;

		// ������������ ������� ���������� ������ ������� �����������
		void HandleAuthDisconnected() override;

		// ������������ ������� ���������� ������ �������� �������
		void HandleGameDisconnected() override;

#pragma endregion

#pragma region �������� �������

		// ���������� ����� 1003
		void send1003();

#pragma endregion

#pragma region ���������� ��������

		// ��������� ����� � ������� ������� ������ ������� �����������
		void AuthEnqueue(sf::Uint16 packetID, Utils::Buffer &buffer);

		// ��������� ����� � ������� ������� ������ �������� �������
		void GameEnqueue(sf::Uint16 packetID, Utils::Buffer &buffer);

#pragma endregion

	public:

		// ����������� ���������
		ClientEmu(const sf::IpAddress &address, sf::Uint16 port, const sf::String &username, const sf::String &password, sf::Uint32 accountID, sf::Uint16 charNum, sf::Uint16 posX, sf::Uint16 posY, IEncryption *encryption, IInnerClientEmu *innerClientEmu = nullptr);

		// ��������� ������ ��������
		void StartClientEmu() override;

#pragma region �������� ������� (���������� IClientEmu)

		// ���������� ����� ����� ����� ������� �����������
		void SendAuthPacket(sf::Uint16 packetID, Utils::Buffer &buffer) override;

		// ���������� ����� ����� ����� �������� �������
		void SendGamePacket(sf::Uint16 packetID, Utils::Buffer &buffer) override;

#pragma endregion

#pragma region ���������� ISocketHandler

		// ���������� ������� ����������� ������
		void HandleConnected(Socket *socket) final;

		// ���������� ������� �������� ������ �������
		void HandlePacket(Socket *socket, sf::Uint16 packetID, Utils::Buffer &buffer) final;

		// ���������� ������� �������� ������ ������� �� �������
		void HandleQueuePacket(Socket *socket, sf::Uint16 packetID, Utils::Buffer &buffer) final;

		// ���������� ������� ���������� ������
		void HandleDisconnected(Socket *socket) final;

#pragma endregion
	};
}