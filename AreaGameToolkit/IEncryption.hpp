#pragma once

// InjectMe
#include "Buffer.hpp"

// SFML
#include <SFML/Config.hpp>

namespace InjectMe::Network
{
	// ��������� ���������� ����������
	class IEncryption
	{
	public:

		// ��������� ���������� ����������� ������
		virtual void Encrypt(Utils::Buffer &buffer) = 0;

		// ��������� ���������� ���������� ������
		virtual void Encrypt(void *data, sf::Uint8 key, size_t offset, size_t length) = 0;
	};
}