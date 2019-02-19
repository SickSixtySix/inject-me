#pragma once

// InjectMe
#include "Proxy.hpp"

// SFML
#include <SFML/System/Mutex.hpp>

// C++
#include <set>
#include <unordered_map>
#include <vector>

namespace Cheat::Sniffer
{
	// Класс сниффера
	class Sniffer
	{
	public:

		// Структура данных пакета
		struct Packet
		{
			// Прокси на пути данного пакета
			InjectMe::Network::Proxy *proxy;

			// Направление данного пакета
			sf::Uint32 direction;

			// Идентификатор данного пакета
			sf::Uint16 packetID;

			// Буфер данного пакета
			InjectMe::Utils::Buffer buffer;
		};

		// Структура данных передачи
		struct Transfer
		{
			// Передаваемый пакет
			Packet packet;

			// Текущее количество передач
			size_t current;

			// Необходимое количество передач
			size_t total;

			// Флаг приостановки операции
			bool suspend;
		};

	private:

		// Экземляр класса чита
		static Sniffer *s_sniffer;

		// Полная история
		std::vector<Packet> m_history;
		sf::Mutex m_historyMutex;

		// Все передачи
		std::vector<Transfer*> m_transfers;

		// Список всех прокси
		std::set<InjectMe::Network::Proxy*> m_proxies;

		// Список всех идентификатор пакетов
		std::set<sf::Uint16> m_packetIDs;

		// Фильтр по прокси
		InjectMe::Network::Proxy *m_filterProxy = nullptr;

		// Фильтр по пакетам
		sf::Uint16 m_filterPacket = 0;

		// Редактор памяти
		struct MemoryEditorImpl;
		MemoryEditorImpl *m_editor;

		// Номер редактируемого пакета
		int m_editPacket = -1;

		// Конструктор класса чита
		Sniffer();

	public:

		// Возвращает экземпляр класса
		static Sniffer* Instance();

		void LogFromClientToServer(InjectMe::Network::Proxy *proxy, sf::Uint16 packetID, const InjectMe::Utils::Buffer &buffer);

		void LogFromServerToClient(InjectMe::Network::Proxy *proxy, sf::Uint16 packetID, const InjectMe::Utils::Buffer &buffer);

		void LogFromProxyToServer(InjectMe::Network::Proxy *proxy, sf::Uint16 packetID, const InjectMe::Utils::Buffer &buffer);

		void LogFromProxyToClient(InjectMe::Network::Proxy *proxy, sf::Uint16 packetID, const InjectMe::Utils::Buffer &buffer);

		// Интерфейс
		void ImGui();
	};
}