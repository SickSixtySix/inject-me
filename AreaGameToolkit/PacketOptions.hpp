#pragma once

// AddonNetEmu
#include "AddonNetEmu.hpp"

// SFML
#include <SFML/Config.hpp>

// Структура данных для хранения опций пакета
struct ADDONNETEMU_API PacketOptions
{
	// Флаг записи синхронизационных данных пакета
	bool Sync;

	// Флаг записи дайджеста данных пакета
	bool Hash;

	// Флаг записи временной метки пакета
	bool Post;

	// Реальный размер пакета
	long RealSize;
};