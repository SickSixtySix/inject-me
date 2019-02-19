#pragma once

// InjectMe
#include "Buffer.hpp"

// SFML
#include <SFML/Config.hpp>

namespace InjectMe::Network
{
	// ������� ��������� ��������� �������
	class IOuterClientEmu
	{
	public:

		// ��������� ������ ��������
		virtual void StartClientEmu() = 0;

#pragma region �������� �������

		// ���������� ����� ����� ����� ������� �����������
		virtual void SendAuthPacket(sf::Uint16 packetID, Utils::Buffer &buffer) = 0;

		// ���������� ����� ����� ����� �������� �������
		virtual void SendGamePacket(sf::Uint16 packetID, Utils::Buffer &buffer) = 0;

#pragma endregion
	};
}