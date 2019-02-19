#pragma once

// InjectMe
#include "ClientEmu.hpp"

namespace InjectMe::Network
{
	class KickClientEmu : public ClientEmu
	{
#pragma region ������ �������

		// ������������� �������� ������� ���������
		sf::Uint32 m_victimAccountID;

		// ����� ��������� �������� ������� ���������
		sf::Uint16 m_victimCharNum;

#pragma endregion

	public:

		// ����������� ���������
		KickClientEmu(const sf::IpAddress &address, sf::Uint16 port, const sf::String &username, const sf::String &password, sf::Uint32 accountID, sf::Uint16 charNum, sf::Uint16 posX, sf::Uint16 posY, sf::Uint32 victimAccountID, sf::Uint16 victimCharNum, IEncryption *encryption, IInnerClientEmu *innerClientEmu = nullptr);

#pragma region ������� ��������� (���������� IClientEmu)

		// ������������ ����� ������ �������� �������
		void HandleGamePacket(sf::Uint16 packetID, Utils::Buffer &buffer) override;

#pragma endregion
	};
}