#pragma once

// SFML
#include <SFML/System/Mutex.hpp>

// C
#include <stdio.h>

namespace InjectMe::Utils
{
	// Класс механизма журналирования
	class Logger
	{
		// Экземпляр механизма журналирования
		static Logger *s_instance;

		// Мьютекс экземпляра механизма журналирования
		static sf::Mutex s_instanceMutex;

		// Структура файла механизма журналирования
		FILE *_Stream;

		// Конструктор механизма журналирования
		Logger();

	public:

		// Получает экземпляр механизма журналирования 
		static Logger* GetInstance();

		// Аналог функции printf механизма журналирования 
		void printf(const char *_Format, ...);
	};
}