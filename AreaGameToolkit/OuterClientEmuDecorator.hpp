#pragma once

// InjectMe
#include "IOuterClientEmu.hpp"

namespace InjectMe::Network
{
	// ����� �������� ���������� ��������� �������
	class OuterClientEmuDecorator : public IOuterClientEmu
	{
		// ����������� ��������� ������� ��� ��� ���������
		IOuterClientEmu *m_outerClientEmu = nullptr;

	public:

		// ����������� �������� ����������
		OuterClientEmuDecorator(IOuterClientEmu *clientEmu);

		// ��������� ������ ��������
		void StartClientEmu() override;

#pragma region �������� ������� (���������� IClientEmu)

		// ���������� ����� ����� ����� ������� �����������
		void SendAuthPacket(sf::Uint16 packetID, Utils::Buffer &buffer) override;

		// ���������� ����� ����� ����� �������� �������
		void SendGamePacket(sf::Uint16 packetID, Utils::Buffer &buffer) override;

#pragma endregion
	};
}