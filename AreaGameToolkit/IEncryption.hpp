#pragma once

// InjectMe
#include "Buffer.hpp"

// SFML
#include <SFML/Config.hpp>

namespace InjectMe::Network
{
	// Интерфейс поставщика шифрования
	class IEncryption
	{
	public:

		// Выполняет шифрование переданного буфера
		virtual void Encrypt(Utils::Buffer &buffer) = 0;

		// Выполняет шифрование переданных данных
		virtual void Encrypt(void *data, sf::Uint8 key, size_t offset, size_t length) = 0;
	};
}