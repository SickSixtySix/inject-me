#pragma once

// InjectMe
#include "Buffer.hpp"

namespace InjectMe::Hook::AsdaGlobal
{
	// Класс данных клиента
	class AsdaGlobalData
	{
		// Флаг выделения памяти
		bool m_allocated = false;

		// Адрес источника данных #1
		unsigned long m_address1 = 0;

		// Адрес источника данных #2
		unsigned long m_address2 = 0;

		// Адрес источника данных #3
		unsigned long m_address3 = 0;

		// Адрес источника данных #4
		unsigned long m_address4 = 0;

	public:

		// Конструктор данных клиента
		AsdaGlobalData();

		// Конструктор данных клиента (через адресы)
		AsdaGlobalData(unsigned long address1, unsigned long address2, unsigned long address3, unsigned long address4);

		// Деструктор данных клиента
		~AsdaGlobalData();

		// Сбрасывает данные клиента
		void ResetData();

		// Переключает данные клиента
		void SwitchData();

		// Возвращает адрес источника данных #1
		unsigned long GetAddress1() const;

		// Возвращает адрес источника данных #2
		unsigned long GetAddress2() const;

		// Возвращает адрес источника данных #3
		unsigned long GetAddress3() const;

		// Возвращает адрес источника данных #4
		unsigned long GetAddress4() const;

		// Подготавливает пакет
		void PreparePacket(sf::Uint16 packetID, Utils::Buffer &buffer);
	};
}

//0x0180EC24, 0x034DDF94, 0x0180E964, 0x0180EC24
//packetOptions[1000] = { false, true, true, 0 };
//packetOptions[1003] = { true, true, true, 254 };
//packetOptions[1005] = { true, true, true, 6 };
//packetOptions[1012] = { true, true, true, 5 };
//packetOptions[1016] = { true, true, true, 9 };
//packetOptions[4001] = { true, true, true, 16 };
//packetOptions[4006] = { false, true, true, 31 };
//packetOptions[5006] = { true, true, true, 17 };
//packetOptions[5012] = { true, true, true, 12 };
//packetOptions[5041] = { true, true, true, 11 };
//packetOptions[5043] = { true, true, true, 8 };
//packetOptions[5056] = { true, true, true, 0 };
//packetOptions[5058] = { true, true, true, 16 };
//packetOptions[5084] = { false, false, false, -1 };
//packetOptions[5256] = { true, true, false, 11 };
//packetOptions[6084] = { true, true, true, 5 };
//packetOptions[6666] = { false, false, false, -1 };
//packetOptions[8215] = { false, true, true, 17 };
//packetOptions[8226] = { false, true, true, 8 };
//packetOptions[9915] = { false, false, false, 0 };
//packetOptions[20000] = { true, true, false, 27 };