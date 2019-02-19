#pragma once

// InjectMe
#include "Buffer.hpp"

// SFML
#include <SFML/Config.hpp>

namespace InjectMe::Network
{
	// ��������������� ���������� ������ ����������� ���������� ��������� �������
	class InnerClientEmuDecorator;

	// ��������������� ���������� ������ ��������� �������
	class ClientEmu;

	// ���������� ��������� ��������� �������
	class IInnerClientEmu
	{
	protected:

#pragma region ������� ���������

		// ������������ ������� ����������� ������ ������� �����������
		virtual void HandleAuthConnected() = 0;

		// ������������ ������� ����������� ������ �������� �������
		virtual void HandleGameConnected() = 0;

		// ������������ ����� ������ ������� �����������
		virtual void HandleAuthPacket(sf::Uint16 packetID, Utils::Buffer &buffer) = 0;

		// ������������ ����� ������ �������� �������
		virtual void HandleGamePacket(sf::Uint16 packetID, Utils::Buffer &buffer) = 0;

		// ������������ ����� �� ������� ������� ������ ������� �����������
		virtual void HandleAuthQueuePacket(sf::Uint16 packetID, Utils::Buffer &buffer) = 0;

		// ������������ ����� �� ������� ������� ������ �������� �������
		virtual void HandleGameQueuePacket(sf::Uint16 packetID, Utils::Buffer &buffer) = 0;

		// ������������ ������� ���������� ������ ������� �����������
		virtual void HandleAuthDisconnected() = 0;

		// ������������ ������� ���������� ������ �������� �������
		virtual void HandleGameDisconnected() = 0;

#pragma endregion

		// ���������� ������ ���������� ��������� ������� ������������� ������� ������
		friend class InnerClientEmuDecorator;

		// ���������� ������ ��������� ������� ������������� ������� ������
		friend class ClientEmu;
	};
}