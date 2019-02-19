#pragma once

// InjectMe
#include "Buffer.hpp"
#include "IEncryption.hpp"

// SFML
#include <SFML/Config.hpp>

namespace InjectMe::Network
{
	// ��������� ���������� ��� Asda 2
	class Asda2Encryption : public IEncryption
	{
		// ��������� ������
		static Asda2Encryption *s_instance;

	public:

		// ���������� ��������� ������
		static Asda2Encryption* Instance();

		// ��������� ���������� ����������� ������
		void Encrypt(Utils::Buffer &buffer) final;

		// ��������� ���������� ���������������� ������
		void Encrypt(void *data, sf::Uint8 key, size_t offset, size_t length) final;
	};
}