#pragma once

// WinAPI
#include <Windows.h>

namespace InjectMe::Utils
{
// Максимальное количество хранилищ блоков памяти
#define MEMORY_STORAGE_COUNT	4

// Количество блоков памяти по горизонтали (в памяти блоки расположены линейно)
#define MEMORY_BLOCK_COUNT_X	64

// Количество блоков памяти по вертикали (в памяти блоки расположены линейно)
#define MEMORY_BLOCK_COUNT_Y	64

// Размер блока памяти
#define MEMORY_BLOCK_SIZE		1024

	// Информационная структура блока памяти
	typedef struct _MEMORY_BLOCK_INFO
	{
		// Идентификатор цепочки блоков памяти
		DWORD dwChainID;

		// Флаг свободности блока памяти
		BOOL bFree;
	} MEMORY_BLOCK_INFO, *PMEMORY_BLOCK_INFO, *LPMEMORY_BLOCK_INFO;

	// Структура блока памяти
	typedef struct _MEMORY_BLOCK
	{
		// Адрес блока памяти
		LPVOID lpAddress;

		// Размер блока памяти
		SIZE_T dwSize;
	} MEMORY_BLOCK;

	// Структура цепочки блоков памяти
	typedef struct _MEMORY_BLOCK_CHAIN
	{
		// Индекс хранилища блоков памяти цепочки
		DWORD dwStorage;

		// Индекс первого блока памяти цепочки
		DWORD dwStartBlock;

		// Количество блоков памяти цепочки
		DWORD dwBlockCount;

		// Адрес блоков памяти цепочки
		PCHAR lpAddress;

		// Размер цепочки блоков памяти
		DWORD dwSize;
	} MEMORY_BLOCK_CHAIN, *PMEMORY_BLOCK_CHAIN;

	// Информационная структура хранилища блоков памяти
	typedef struct _MEMORY_STORAGE_INFO
	{
		// Критическая секция хранилища блоков памяти
		CRITICAL_SECTION criticalSection;

		// Счетчик идентификаторов цепочек блоков памяти
		DWORD dwChainIDCounter;

		// Адрес информации блоков памяти хранилища
		LPMEMORY_BLOCK_INFO lpBlockInfo;

		// Адрес блоков памяти хранилища
		LPVOID lpBlockAddress;
	} MEMORY_STORAGE_INFO, *PMEMORY_STORAGE_INFO, *LPMEMORY_STORAGE_INFO;

	typedef struct _MEMORY_STORAGE_PROFILE
	{
		// Адрес информации блоков памяти хранилища
		LPMEMORY_BLOCK_INFO lpBlockInfo;

		// Количество блоков памяти хранилища
		DWORD dwBlockCount;
	} MEMORY_STORAGE_PROFILE, *PMEMORY_STORAGE_PROFILE, *LPMEMORY_STORAGE_PROFILE;

	typedef struct _MEMORY_PROFILE
	{
		// Профили хранилищ блоков памяти
		LPMEMORY_STORAGE_PROFILE lpStorageProfile;

		// Количество хранилищ блоков памяти
		DWORD dwStorageCount;
	} MEMORY_PROFILE, *PMEMORY_PROFILE, *LPMEMORY_PROFILE;

	// Инициализирует память
	VOID ChainInit();

	// Выделяет цепочку блоков памяти из хранилища
	BOOL ChainAlloc(SIZE_T dwSize, PMEMORY_BLOCK_CHAIN pMemoryBlockChain);

	// Перераспределяет цепочку блоков памяти из хранилища
	BOOL ChainReAlloc(SIZE_T dwSize, PMEMORY_BLOCK_CHAIN pMemoryBlockChain);

	// Возвращает цепочку блоков памяти в хранилище
	VOID ChainFree(MEMORY_BLOCK_CHAIN memoryBlockChain);

	// Выполняет профилирование памяти
	VOID ChainProfile(PMEMORY_PROFILE pMemoryProfile);
}