#pragma once

// InjectMe
#include "Buffer.hpp"
#include "IEncryption.hpp"

// SFML
#include <SFML/Config.hpp>

namespace InjectMe::Network
{
	// Поставщик шифрования для Asda 2
	class Asda2Encryption : public IEncryption
	{
		// Экземпляр класса
		static Asda2Encryption *s_instance;

	public:

		// Возвращает экземпляр класса
		static Asda2Encryption* Instance();

		// Выполняет шифрование переданного буфера
		void Encrypt(Utils::Buffer &buffer) final;

		// Выполняет шифрование предоставленного буфера
		void Encrypt(void *data, sf::Uint8 key, size_t offset, size_t length) final;
	};
}