#pragma once

// InjectMe
#include "Buffer.hpp"

// SFML
#include <SFML/Config.hpp>

namespace InjectMe::Network
{
	// Предварительное объявление класса сокета
	class Socket;

	// Интерфейс обработчика событий сокета
	class ISocketHandler
	{
	public:

		// Обработчик события подключения сокета
		virtual void HandleConnected(Socket *socket) = 0;

		// Обработчик события принятия пакета сокетом
		virtual void HandlePacket(Socket *socket, sf::Uint16 packetID, Utils::Buffer &buffer) = 0;

		// Обработчик события принятия пакета сокетом из очереди
		virtual void HandleQueuePacket(Socket *socket, sf::Uint16 packetID, Utils::Buffer &buffer) = 0;

		// Обработчик события отключения сокета
		virtual void HandleDisconnected(Socket *socket) = 0;
	};
}