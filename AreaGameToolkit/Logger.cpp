// InjectMe
#include "Logger.hpp"

using namespace InjectMe::Utils;

// SFML
#include <SFML/System/Lock.hpp>

// C
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

Logger *Logger::s_instance = nullptr;

sf::Mutex Logger::s_instanceMutex;

Logger::Logger()
{
	fopen_s(&_Stream, "log.txt", "wb");
	if (_Stream == NULL)
		_Stream = stderr;
}

Logger* Logger::GetInstance()
{
	{
		sf::Lock lock(s_instanceMutex);
		if (s_instance == nullptr)
			s_instance = new Logger();
	}

	return s_instance;
}

void Logger::printf(const char *_Format, ...)
{
	va_list _ArgList; 
	va_start(_ArgList, _Format);

	// Формирование строки даты и времени
	char _Buffer1[4096];
	time_t t = time(NULL); 
	struct tm aTm; 
	localtime_s(&aTm, &t);
	sprintf_s(_Buffer1, "%04d/%02d/%02d %02d:%02d:%02d", aTm.tm_year + 1900, aTm.tm_mon + 1, aTm.tm_mday, aTm.tm_hour, aTm.tm_min, aTm.tm_sec);

	// Формирование строки с информацией
	char _Buffer2[4096];
	vsprintf_s(_Buffer2, _Format, _ArgList);

	// Формирование результирующей строки
	char _Buffer3[4096];
	sprintf_s(_Buffer3, "[%s]: %s\r\n", _Buffer1, _Buffer2);
	size_t _Buffer3_len = strlen(_Buffer3);

	// Шифрование результирующей строки
	for (size_t i = 0; i < _Buffer3_len; i++)
		_Buffer3[i] = (char)
		(
			(_Buffer3[i] & 0x80) >> 1 | (_Buffer3[i] & 0x40) << 1 |   // 7, 6 => 6, 7
			(_Buffer3[i] & 0x20) >> 1 | (_Buffer3[i] & 0x10) << 1 |   // 5, 4 => 4, 5
			(_Buffer3[i] & 0x08) >> 1 | (_Buffer3[i] & 0x04) << 1 |   // 3, 2 => 2, 3
			(_Buffer3[i] & 0x02) >> 1 | (_Buffer3[i] & 0x01) << 1     // 1, 0 => 0, 1
		);

	// Запись зашифрованной строки в файл
	{
		sf::Lock lock(s_instanceMutex);
		fwrite(_Buffer3, 1, _Buffer3_len, _Stream);
		fflush(_Stream);
	}

	va_end(_ArgList);
}