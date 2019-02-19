#pragma once

// InjectMe
#include "ClientEmu.hpp"

namespace Rivet
{
	// Класс эмулятора клиента для клепа
	class RivetClientEmu : public ClientEmu
	{
		// Поток эмулятора клиента
		sf::Thread m_thread;

		// Функция потока эмулятора клиента
		void threadFunction();

		// Флаг активности эмулятора
		volatile bool m_active;

	protected:

		// Обрабатывает пакет сокета игрового сервера
		void HandleGamePacket(sf::Uint16 packetID, Buffer &buffer) override;

	public:

		// Конструктор эмулятора
		RivetClientEmu(const sf::IpAddress &address, sf::Uint16 port, const sf::String &username, const sf::String &password, sf::Uint32 accountID, sf::Uint16 charNum, sf::Uint16 posX, sf::Uint16 posY, IEncryption *encryption, IInnerClientEmu *innerClientEmu = nullptr);

		// Возвращает флаг активности эмулятора
		bool IsActive() const;
	};
}