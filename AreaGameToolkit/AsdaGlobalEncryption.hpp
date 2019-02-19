#pragma once

// InjectMe
#include "Buffer.hpp"
#include "IEncryption.hpp"

// SFML
#include <SFML/Config.hpp>

namespace InjectMe::Network
{
	// Поставщик шифрования для Asda Global
	class AsdaGlobalEncryption : public IEncryption
	{
		// Экземпляр класса
		static AsdaGlobalEncryption *s_instance;

		// Конструктор класса
		AsdaGlobalEncryption();

	public:

		// Возвращает экземпляр класса
		static AsdaGlobalEncryption* Instance();

		// Выполняет шифрование переданного буфера
		void Encrypt(Utils::Buffer &buffer) final;

		// Выполняет шифрование предоставленного буфера
		void Encrypt(void *data, sf::Uint8 key, size_t offset, size_t length) final;
	};
}