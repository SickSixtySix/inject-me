#pragma once

// InjectMe
#include "IBufferHandler.hpp"
#include "Memory.hpp"

// SFML
#include <SFML\System\Mutex.hpp>
#include <SFML\System\String.hpp>

// C++
#include <forward_list>
#include <string>

namespace InjectMe::Utils
{
	// Класс буфера
	class Buffer
	{
		// Область памяти данного буфера
		MEMORY_BLOCK_CHAIN m_memory;

		// Смещение внутри данного буфера
		size_t m_offset = 0;

		// Обработчик событий данного буфера
		IBufferHandler *m_handler = nullptr;

		// Флаг присваивания данного буфера
		bool m_assigned;

		// Флаг перемещения данного буфера
		bool m_removed;

	public:

		// Конструктор буфера
		Buffer(size_t length = 4096);

		// Конструктор буфера с присваиванием
		Buffer(char *buffer, size_t length);

		// Копирующий конструктор буфера
		Buffer(const Buffer &buffer);

		// Перемещающий конструктор буфера
		Buffer(Buffer &&buffer);

		// Загружающий из файла конструктор буфера
		Buffer(const std::string &file);

		// Деструктор буфера
		~Buffer();

		// Копирует содержимое передаваемого буфера в данный буфера
		const Buffer& operator= (const Buffer &buffer);

		// Перемещает содержимое передаваемого буфера в данный буфера
		const Buffer& operator= (Buffer &&buffer);

		// Возвращает область памяти данного буфера
		const MEMORY_BLOCK_CHAIN& GetMemory() const;

		// Возвращает смещение в внутри данного буфера
		size_t GetOffset() const;

		// Устанавливает обработчик для данного буфера
		void SetHandler(IBufferHandler *handler);

		// Устанавливает смещение для данного буфера
		void SetOffset(size_t offset);

		// Сохраняет буфер в файл
		void Save(const std::string &file);

		// Выполняет чтение из буфера
		template<typename T>
		void Read(size_t offset, T &value) const
		{
			value = *reinterpret_cast<T*>(m_memory.lpAddress + offset);
			if (m_handler != nullptr)
				m_handler->HandleRead(*this, &value, offset, sizeof(T));
		}

		// Выполняет чтение из буфера со сдвигом указателя
		template<typename T>
		void Read(T &value)
		{
			value = *reinterpret_cast<T*>(m_memory.lpAddress + m_offset);
			if (m_handler != nullptr)
				m_handler->HandleRead(*this, &value, m_offset, sizeof(T));
			m_offset += sizeof(T);
		}

		// Выполняет чтение из буфера в массив
		template<typename T, size_t size>
		void Read(size_t offset, T(&value)[size]) const
		{
			memcpy_s(value, sizeof(T) * size, m_memory.lpAddress + offset, sizeof(T) * size);
			if (m_handler != nullptr)
				m_handler->HandleRead(*this, &value, offset, sizeof(T) * size);
		}

		// Выполняет чтение из буфера в массив со сдвигом указателя
		template<typename T, size_t size>
		void Read(T(&value)[size])
		{
			memcpy_s(value, sizeof(T) * size, m_memory.lpAddress + m_offset, sizeof(T) * size);
			if (m_handler != nullptr)
				m_handler->HandleRead(*this, &value, m_offset, sizeof(T) * size);
			m_offset += sizeof(T) * size;
		}

		// Выполняет чтение из буфера в область памяти
		template<typename T>
		void Read(size_t offset, T *value, size_t size) const
		{
			memcpy_s(value, sizeof(T) * size, m_memory.lpAddress + offset, sizeof(T) * size);
			if (m_handler != nullptr)
				m_handler->HandleRead(*this, &value, offset, sizeof(T) * size);
		}

		// Выполняет чтение из буфера в область памяти со сдвигом указателя
		template<typename T>
		void Read(T *value, size_t size)
		{
			memcpy_s(value, sizeof(T) * size, m_memory.lpAddress + m_offset, sizeof(T) * size);
			if (m_handler != nullptr)
				m_handler->HandleRead(*this, &value, m_offset, sizeof(T) * size);
			m_offset += sizeof(T) * size;
		}

		// Выполняет чтение строки из буфера
		void Read(size_t offset, sf::String &value) const;

		// Выполняет чтение строки из буфера со сдвигом указателя
		void Read(sf::String &value);

		// Выполняет запись в буфер
		template<typename T>
		void Write(size_t offset, const T &value)
		{
			*reinterpret_cast<T*>(m_memory.lpAddress + offset) = value;
			if (m_handler != nullptr)
				m_handler->HandleWrite(*this, m_memory.lpAddress, offset, sizeof(T));
		}

		// Выполняет запись в буфер со сдвигом указателя
		template<typename T>
		void Write(const T &value)
		{
			*reinterpret_cast<T*>(m_memory.lpAddress + m_offset) = value;
			if (m_handler != nullptr)
				m_handler->HandleWrite(*this, m_memory.lpAddress, m_offset, sizeof(T));
			m_offset += sizeof(T);
		}

		// Выполняет запись массива в буфер
		template<typename T, size_t size>
		void Write(size_t offset, const T(&value)[size])
		{
			memcpy_s(m_memory.lpAddress + offset, m_memory.dwSize - offset, value, sizeof(T) * size);
			if (m_handler != nullptr)
				m_handler->HandleWrite(*this, m_memory.lpAddress, offset, sizeof(T));
		}

		// Выполняет запись массива в буфер со сдвигом erfpfntkz
		template<typename T, size_t size>
		void Write(const T(&value)[size])
		{
			memcpy_s(m_memory.lpAddress + m_offset, m_memory.dwSize - m_offset, value, sizeof(T) * size);
			if (m_handler != nullptr)
				m_handler->HandleWrite(*this, m_memory.lpAddress, m_offset, sizeof(T) * size);
			m_offset += sizeof(T) * size;
		}

		// Выполняет запись области памяти в буфер
		template<typename T>
		void Write(size_t offset, const T *value, size_t size)
		{
			memcpy_s(m_memory.lpAddress + offset, m_memory.dwSize - offset, value, sizeof(T) * size);
			if (m_handler != nullptr)
				m_handler->HandleWrite(*this, m_memory.lpAddress, offset, sizeof(T) * size);
		}

		// Выполняет запись области памяти в буфер со сдвигом указателя
		template<typename T>
		void Write(const T *value, size_t size)
		{
			memcpy_s(m_memory.lpAddress + m_offset, m_memory.dwSize - m_offset, value, sizeof(T) * size);
			if (m_handler != nullptr)
				m_handler->HandleWrite(*this, m_memory.lpAddress, m_offset, sizeof(T) * size);
			m_offset += sizeof(T) * size;
		}

		// Выполняет запись строки в буфер
		void Write(size_t offset, const sf::String &value);

		// Выполняет запись строки в буфер со сдвигом указателя
		void Write(const sf::String &value);
	};
}