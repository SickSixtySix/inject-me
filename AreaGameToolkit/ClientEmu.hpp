#pragma once

// InjectMe
#include "ClientSocket.hpp"
#include "AsdaGlobalData.hpp"
#include "IInnerClientEmu.hpp"
#include "IOuterClientEmu.hpp"
#include "ISocketHandler.hpp"

// SFML
#include <SFML/Config.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/System/String.hpp>

namespace InjectMe::Network
{
	class ClientEmu : public ISocketHandler, public IInnerClientEmu, public IOuterClientEmu
	{
		// Внутренний декоратор эмулятора клиента
		IInnerClientEmu *m_innerClientEmu;

	protected:

#pragma region Данные для подключения

		// Адрес сервера авторизации для подключения данного эмулятора
		sf::IpAddress m_address;

		// Порт сервера авторизации для подключения данного эмулятора
		sf::Uint16 m_port;

#pragma endregion

#pragma region Данные клиента

		// Логин аккаунта данного эмулятора
		sf::String m_username;

		// Пароль аккаунта данного эмулятора
		sf::String m_password;

		// Идентификатор аккаунта данного эмулятора
		sf::Uint32 m_accountID;

		// Номер персонажа аккаунта данного эмулятора
		sf::Uint16 m_charNum;

		// Позиция X персонажа аккаунта данного эмулятора
		sf::Uint16 m_posX;

		// Позиция Y персонажа аккаунта данного эмулятора
		sf::Uint16 m_posY;

		// Идентификатор сессии данного эмулятора
		sf::Uint32 m_sessionID;

		// Счетчик пакетов 1001 данного эмулятора
		size_t m_packet1001Counter = 0;

		// Счетчик пакетов 1013 данного эмулятора
		size_t m_packet1013Counter = 0;

#pragma endregion

#pragma region Данные эмулятора

		// Поставщик шифрования данного эмулятора
		IEncryption *m_encryption;

		// Сокет для подключения к серверу авторизации данного эмулятора
		ClientSocket *m_authSocket;

		// Сокет для подключения к игровому серверу данного эмулятора
		ClientSocket *m_gameSocket;

		// Контекст данного эмулятора
		Hook::AsdaGlobal::AsdaGlobalData m_asdaGlobalData;

#pragma endregion

#pragma region События эмулятора (реализация IClientEmu)

		// Обрабатывает событие подключения сокета сервера авторизации
		void HandleAuthConnected() override;

		// Обрабатывает событие подключения сокета игрового сервера
		void HandleGameConnected() override;

		// Обрабатывает пакет сокета сервера авторизации
		void HandleAuthPacket(sf::Uint16 packetID, Utils::Buffer &buffer) override;

		// Обрабатывает пакет сокета игрового сервера
		void HandleGamePacket(sf::Uint16 packetID, Utils::Buffer &buffer) override;

		// Обрабатывает пакет из очереди пакетов сокета сервера авторизации
		void HandleAuthQueuePacket(sf::Uint16 packetID, Utils::Buffer &buffer) override;

		// Обрабатывает пакет из очереди пакетов сокета игрового сервера
		void HandleGameQueuePacket(sf::Uint16 packetID, Utils::Buffer &buffer) override;

		// Обрабатывает событие отключения сокета сервера авторизации
		void HandleAuthDisconnected() override;

		// Обрабатывает событие отключения сокета игрового сервера
		void HandleGameDisconnected() override;

#pragma endregion

#pragma region Отправка пакетов

		// Отправляет пакет 1003
		void send1003();

#pragma endregion

#pragma region Управление пакетами

		// Добавляет пакет в очередь пакетов сокета сервера авторизации
		void AuthEnqueue(sf::Uint16 packetID, Utils::Buffer &buffer);

		// Добавляет пакет в очередь пакетов сокета игрового сервера
		void GameEnqueue(sf::Uint16 packetID, Utils::Buffer &buffer);

#pragma endregion

	public:

		// Конструктор эмулятора
		ClientEmu(const sf::IpAddress &address, sf::Uint16 port, const sf::String &username, const sf::String &password, sf::Uint32 accountID, sf::Uint16 charNum, sf::Uint16 posX, sf::Uint16 posY, IEncryption *encryption, IInnerClientEmu *innerClientEmu = nullptr);

		// Запускает данный эмулятор
		void StartClientEmu() override;

#pragma region Отправка пакетов (реализация IClientEmu)

		// Отправляет пакет через сокет сервера авторизации
		void SendAuthPacket(sf::Uint16 packetID, Utils::Buffer &buffer) override;

		// Отправляет пакет через сокет игрового сервера
		void SendGamePacket(sf::Uint16 packetID, Utils::Buffer &buffer) override;

#pragma endregion

#pragma region Реализация ISocketHandler

		// Обработчик события подключения сокета
		void HandleConnected(Socket *socket) final;

		// Обработчик события принятия пакета сокетом
		void HandlePacket(Socket *socket, sf::Uint16 packetID, Utils::Buffer &buffer) final;

		// Обработчик события принятия пакета сокетом из очереди
		void HandleQueuePacket(Socket *socket, sf::Uint16 packetID, Utils::Buffer &buffer) final;

		// Обработчик события отключения сокета
		void HandleDisconnected(Socket *socket) final;

#pragma endregion
	};
}