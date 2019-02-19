#pragma once

// InjectMe
#include "AsdaGlobalData.hpp"
#include "Proxy.hpp"
#include "TaskExecutor.hpp"

// SFML
#include <SFML/Config.hpp>
#include <SFML/Network/IpAddress.hpp>

namespace InjectMe::Network
{
	class AsdaGlobalProxy : public Proxy, private Utils::TaskExecutor
	{
#pragma region Данные клиента

		// Логин аккаунта данного прокси
		sf::String m_username;

		// Пароль аккаунта данного прокси
		sf::String m_password;

		// Идентификатор аккаунта данного прокси
		sf::Uint32 m_accountID;

		// Номер персонажа аккаунта данного прокси
		sf::Uint16 m_charNum;

		// Позиция X персонажа аккаунта данного прокси
		sf::Uint16 m_posX;

		// Позиция Y персонажа аккаунта данного прокси
		sf::Uint16 m_posY;

		// Идентфикатор карты персонажа аккаунта данного прокси
		sf::Uint8 m_mapID = 3;

		// Счетчик пакетов 1001 данного прокси
		size_t m_packet1001Counter = 0;

		// Счетчик пакетов 1013 данного прокси
		size_t m_packet1013Counter = 0;

		// Контекст клиента данного прокси
		Hook::AsdaGlobal::AsdaGlobalData m_asdaGlobalData;

#pragma endregion

#pragma region Отправка пакетов

		// Отправляет пакет 1003
		void send1003();

#pragma endregion

#pragma region Задания клиента

		// Задание переподключения данного клиента
		void ReconnectTask();

#pragma endregion

	public:

		// Конструктор прокси
		AsdaGlobalProxy(const sf::IpAddress &serverAddress, sf::Uint16 serverPort, sf::Uint16 clientPort, const sf::String &username, const sf::String &password, sf::Uint32 accountID, sf::Uint16 charNum, sf::Uint16 posX, sf::Uint16 posY, IProxyHandler *handler, IEncryption *encryption);

		// Обрабатывает пакет из клиентской очереди данного прокси
		void HandleClientQueuePacket(sf::Uint16 packetID, Utils::Buffer &buffer) final;

		// Обрабатывает пакет из серверной очереди данного прокси
		void HandleServerQueuePacket(sf::Uint16 packetID, Utils::Buffer &buffer) final;

		// Обрабатывает клиентский пакет в реальном времени
		void HandleClientPacket(sf::Uint16 packetID, Utils::Buffer &buffer) final;

		// Обрабатывает серверный пакет в реальном времени
		void HandleServerPacket(sf::Uint16 packetID, Utils::Buffer &buffer) final;

		// Обработчик события подключения сокета
		void HandleConnected(Socket *socket) final;
	};
}