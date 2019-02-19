#pragma once

namespace InjectMe::Hook::WSA
{
	// Структура данных для обработчика перехвата WSAConnect()
	struct WSAConnectData
	{
		// Первый байт IP адреса
		unsigned char b1;

		// Второй байт IP адреса
		unsigned char b2;

		// Третий байт IP адреса
		unsigned char b3;

		// Четвертый байт IP адреса
		unsigned char b4;

		// Порт назначения
		unsigned short DestinationPort;

		// Исходный порт
		unsigned short SourcePort;
	};
}