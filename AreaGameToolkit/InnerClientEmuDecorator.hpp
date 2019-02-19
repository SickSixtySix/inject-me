#pragma once

// InjectMe
#include "IInnerClientEmu.hpp"

namespace InjectMe::Network
{
	// ����� ����������� ���������� ��������� �������
	class InnerClientEmuDecorator : public IInnerClientEmu
	{
		// ���������� ��������� ��������� �������
		IInnerClientEmu *m_innerClientEmu;

	protected:

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

	public:

		// ����������� ���������� ��������� �������
		InnerClientEmuDecorator(IInnerClientEmu *innerClientEmu = nullptr);
	};
}