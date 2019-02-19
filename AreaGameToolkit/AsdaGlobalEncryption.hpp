#pragma once

// InjectMe
#include "Buffer.hpp"
#include "IEncryption.hpp"

// SFML
#include <SFML/Config.hpp>

namespace InjectMe::Network
{
	// ��������� ���������� ��� Asda Global
	class AsdaGlobalEncryption : public IEncryption
	{
		// ��������� ������
		static AsdaGlobalEncryption *s_instance;

		// ����������� ������
		AsdaGlobalEncryption();

	public:

		// ���������� ��������� ������
		static AsdaGlobalEncryption* Instance();

		// ��������� ���������� ����������� ������
		void Encrypt(Utils::Buffer &buffer) final;

		// ��������� ���������� ���������������� ������
		void Encrypt(void *data, sf::Uint8 key, size_t offset, size_t length) final;
	};
}