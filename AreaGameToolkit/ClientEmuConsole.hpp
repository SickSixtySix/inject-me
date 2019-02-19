#pragma once

// InjectMe
#include "InnerClientEmuDecorator.hpp"

namespace InjectMe::Network
{
	// ����� ����������� ���������� ��������� �������
	class ClientEmuConsole : public InnerClientEmuDecorator
	{
		// ���������� ����������
		size_t m_charactersCount = 0;

	public:

		// ����������� ����������� ���������� ��������� �������
		ClientEmuConsole(IInnerClientEmu *innerClientEmu = nullptr);

#pragma region ������� ��������� (���������� IClientEmu)

		// ������������ ������� ����������� ������ ������� �����������
		void HandleAuthConnected() override;

		// ������������ ������� ����������� ������ �������� �������
		void HandleGameConnected() override;

		// ������������ ����� ������ ������� �����������
		void HandleAuthPacket(sf::Uint16 packetID, Utils::Buffer &buffer) override;

		// ������������ ����� ������ �������� �������
		void HandleGamePacket(sf::Uint16 packetID, Utils::Buffer &buffer) override;

#pragma endregion
	};
}