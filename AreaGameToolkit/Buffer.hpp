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
	// ����� ������
	class Buffer
	{
		// ������� ������ ������� ������
		MEMORY_BLOCK_CHAIN m_memory;

		// �������� ������ ������� ������
		size_t m_offset = 0;

		// ���������� ������� ������� ������
		IBufferHandler *m_handler = nullptr;

		// ���� ������������ ������� ������
		bool m_assigned;

		// ���� ����������� ������� ������
		bool m_removed;

	public:

		// ����������� ������
		Buffer(size_t length = 4096);

		// ����������� ������ � �������������
		Buffer(char *buffer, size_t length);

		// ���������� ����������� ������
		Buffer(const Buffer &buffer);

		// ������������ ����������� ������
		Buffer(Buffer &&buffer);

		// ����������� �� ����� ����������� ������
		Buffer(const std::string &file);

		// ���������� ������
		~Buffer();

		// �������� ���������� ������������� ������ � ������ ������
		const Buffer& operator= (const Buffer &buffer);

		// ���������� ���������� ������������� ������ � ������ ������
		const Buffer& operator= (Buffer &&buffer);

		// ���������� ������� ������ ������� ������
		const MEMORY_BLOCK_CHAIN& GetMemory() const;

		// ���������� �������� � ������ ������� ������
		size_t GetOffset() const;

		// ������������� ���������� ��� ������� ������
		void SetHandler(IBufferHandler *handler);

		// ������������� �������� ��� ������� ������
		void SetOffset(size_t offset);

		// ��������� ����� � ����
		void Save(const std::string &file);

		// ��������� ������ �� ������
		template<typename T>
		void Read(size_t offset, T &value) const
		{
			value = *reinterpret_cast<T*>(m_memory.lpAddress + offset);
			if (m_handler != nullptr)
				m_handler->HandleRead(*this, &value, offset, sizeof(T));
		}

		// ��������� ������ �� ������ �� ������� ���������
		template<typename T>
		void Read(T &value)
		{
			value = *reinterpret_cast<T*>(m_memory.lpAddress + m_offset);
			if (m_handler != nullptr)
				m_handler->HandleRead(*this, &value, m_offset, sizeof(T));
			m_offset += sizeof(T);
		}

		// ��������� ������ �� ������ � ������
		template<typename T, size_t size>
		void Read(size_t offset, T(&value)[size]) const
		{
			memcpy_s(value, sizeof(T) * size, m_memory.lpAddress + offset, sizeof(T) * size);
			if (m_handler != nullptr)
				m_handler->HandleRead(*this, &value, offset, sizeof(T) * size);
		}

		// ��������� ������ �� ������ � ������ �� ������� ���������
		template<typename T, size_t size>
		void Read(T(&value)[size])
		{
			memcpy_s(value, sizeof(T) * size, m_memory.lpAddress + m_offset, sizeof(T) * size);
			if (m_handler != nullptr)
				m_handler->HandleRead(*this, &value, m_offset, sizeof(T) * size);
			m_offset += sizeof(T) * size;
		}

		// ��������� ������ �� ������ � ������� ������
		template<typename T>
		void Read(size_t offset, T *value, size_t size) const
		{
			memcpy_s(value, sizeof(T) * size, m_memory.lpAddress + offset, sizeof(T) * size);
			if (m_handler != nullptr)
				m_handler->HandleRead(*this, &value, offset, sizeof(T) * size);
		}

		// ��������� ������ �� ������ � ������� ������ �� ������� ���������
		template<typename T>
		void Read(T *value, size_t size)
		{
			memcpy_s(value, sizeof(T) * size, m_memory.lpAddress + m_offset, sizeof(T) * size);
			if (m_handler != nullptr)
				m_handler->HandleRead(*this, &value, m_offset, sizeof(T) * size);
			m_offset += sizeof(T) * size;
		}

		// ��������� ������ ������ �� ������
		void Read(size_t offset, sf::String &value) const;

		// ��������� ������ ������ �� ������ �� ������� ���������
		void Read(sf::String &value);

		// ��������� ������ � �����
		template<typename T>
		void Write(size_t offset, const T &value)
		{
			*reinterpret_cast<T*>(m_memory.lpAddress + offset) = value;
			if (m_handler != nullptr)
				m_handler->HandleWrite(*this, m_memory.lpAddress, offset, sizeof(T));
		}

		// ��������� ������ � ����� �� ������� ���������
		template<typename T>
		void Write(const T &value)
		{
			*reinterpret_cast<T*>(m_memory.lpAddress + m_offset) = value;
			if (m_handler != nullptr)
				m_handler->HandleWrite(*this, m_memory.lpAddress, m_offset, sizeof(T));
			m_offset += sizeof(T);
		}

		// ��������� ������ ������� � �����
		template<typename T, size_t size>
		void Write(size_t offset, const T(&value)[size])
		{
			memcpy_s(m_memory.lpAddress + offset, m_memory.dwSize - offset, value, sizeof(T) * size);
			if (m_handler != nullptr)
				m_handler->HandleWrite(*this, m_memory.lpAddress, offset, sizeof(T));
		}

		// ��������� ������ ������� � ����� �� ������� erfpfntkz
		template<typename T, size_t size>
		void Write(const T(&value)[size])
		{
			memcpy_s(m_memory.lpAddress + m_offset, m_memory.dwSize - m_offset, value, sizeof(T) * size);
			if (m_handler != nullptr)
				m_handler->HandleWrite(*this, m_memory.lpAddress, m_offset, sizeof(T) * size);
			m_offset += sizeof(T) * size;
		}

		// ��������� ������ ������� ������ � �����
		template<typename T>
		void Write(size_t offset, const T *value, size_t size)
		{
			memcpy_s(m_memory.lpAddress + offset, m_memory.dwSize - offset, value, sizeof(T) * size);
			if (m_handler != nullptr)
				m_handler->HandleWrite(*this, m_memory.lpAddress, offset, sizeof(T) * size);
		}

		// ��������� ������ ������� ������ � ����� �� ������� ���������
		template<typename T>
		void Write(const T *value, size_t size)
		{
			memcpy_s(m_memory.lpAddress + m_offset, m_memory.dwSize - m_offset, value, sizeof(T) * size);
			if (m_handler != nullptr)
				m_handler->HandleWrite(*this, m_memory.lpAddress, m_offset, sizeof(T) * size);
			m_offset += sizeof(T) * size;
		}

		// ��������� ������ ������ � �����
		void Write(size_t offset, const sf::String &value);

		// ��������� ������ ������ � ����� �� ������� ���������
		void Write(const sf::String &value);
	};
}