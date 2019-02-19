#pragma once

// InjectMe
#include "ClientEmu.hpp"

namespace Rivet
{
	// ����� ��������� ������� ��� �����
	class RivetClientEmu : public ClientEmu
	{
		// ����� ��������� �������
		sf::Thread m_thread;

		// ������� ������ ��������� �������
		void threadFunction();

		// ���� ���������� ���������
		volatile bool m_active;

	protected:

		// ������������ ����� ������ �������� �������
		void HandleGamePacket(sf::Uint16 packetID, Buffer &buffer) override;

	public:

		// ����������� ���������
		RivetClientEmu(const sf::IpAddress &address, sf::Uint16 port, const sf::String &username, const sf::String &password, sf::Uint32 accountID, sf::Uint16 charNum, sf::Uint16 posX, sf::Uint16 posY, IEncryption *encryption, IInnerClientEmu *innerClientEmu = nullptr);

		// ���������� ���� ���������� ���������
		bool IsActive() const;
	};
}