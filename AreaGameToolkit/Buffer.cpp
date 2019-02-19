// InjectMe
#include "Buffer.hpp"

// SFML
#include <SFML/System/Lock.hpp>

// C++
#include <fstream>

using namespace InjectMe::Utils;

Buffer::Buffer(size_t length)
{
	ChainAlloc(length, &m_memory);
	m_assigned = false;
	m_removed = false;
}

Buffer::Buffer(char *buffer, size_t length)
{
	m_memory.lpAddress = buffer;
	m_memory.dwSize = length;
	m_assigned = true;
	m_removed = false;
}

Buffer::Buffer(const Buffer &buffer)
{
	// Выделение памяти и копирование данных
	ChainAlloc(buffer.m_memory.dwSize, &m_memory);
	memcpy_s(m_memory.lpAddress, m_memory.dwSize, buffer.m_memory.lpAddress, buffer.m_memory.dwSize);

	// Остальные поля
	m_offset = buffer.m_offset;
	m_handler = buffer.m_handler;
	m_assigned = false;
	m_removed = false;
}

Buffer::Buffer(Buffer &&buffer)
{
	m_memory = buffer.m_memory;
	m_offset = buffer.m_offset;
	m_handler = buffer.m_handler;
	m_assigned = false;
	m_removed = false;

	// Изменение флага перемещения копируемого буфера
	buffer.m_removed = true;
}

Buffer::Buffer(const std::string &file)
{
	// Открытие файла и определение его размера
	std::ifstream is(file);
	is.seekg(0, is.end);
	auto length = static_cast<size_t>(is.tellg());
	is.seekg(0, is.beg);

	// Выделение памяти и чтение данных из файла
	ChainAlloc(length, &m_memory);
	is.read(m_memory.lpAddress, m_memory.dwSize);
	is.close();

	// Остальные поля
	m_handler = nullptr;
	m_offset = 0;
	m_assigned = false;
	m_removed = false;
}

Buffer::~Buffer()
{
	// Возвращение области памяти в хранилище
	if (!m_assigned && !m_removed)
		ChainFree(m_memory);
}

const Buffer& Buffer::operator= (const Buffer &buffer)
{
	// Выделение памяти и копирование данных
	ChainAlloc(buffer.m_memory.dwSize, &m_memory);
	memcpy_s(m_memory.lpAddress, m_memory.dwSize, buffer.m_memory.lpAddress, buffer.m_memory.dwSize);

	// Остальные поля
	m_offset = buffer.m_offset;
	m_handler = buffer.m_handler;
	m_assigned = false;
	m_removed = false;

	return *this;
}

const Buffer& Buffer::operator= (Buffer &&buffer)
{
	m_memory = buffer.m_memory;
	m_offset = buffer.m_offset;
	m_handler = buffer.m_handler;
	m_assigned = false;
	m_removed = false;

	// Изменение флага перемещения копируемого буфера
	buffer.m_removed = true;

	return *this;
}

const MEMORY_BLOCK_CHAIN& Buffer::GetMemory() const
{
	return m_memory;
}

size_t Buffer::GetOffset() const
{
	return m_offset;
}

void Buffer::SetHandler(IBufferHandler *handler)
{
	m_handler = handler;
}

void Buffer::SetOffset(size_t offset)
{
	m_offset = offset;
}

void Buffer::Save(const std::string &file)
{
	std::ofstream(file).write(m_memory.lpAddress, m_offset);
}

void Buffer::Read(size_t offset, sf::String &value) const
{
	while (true)
	{
		auto byte = m_memory.lpAddress[offset + value.getSize()];
		if (byte != '\0')
			value += byte;
		else
			break;
	}

	if (m_handler != nullptr)
		m_handler->HandleRead(*this, const_cast<sf::Uint32*>(value.getData()), offset, value.getSize());
}

void Buffer::Read(sf::String &value)
{
	while (true)
	{
		auto byte = m_memory.lpAddress[m_offset + value.getSize()];
		if (byte != '\0')
			value += byte;
		else
			break;
	}

	if (m_handler != nullptr)
		m_handler->HandleRead(*this, const_cast<sf::Uint32*>(value.getData()), m_offset, value.getSize());
	m_offset += value.getSize() + 1;
}

void Buffer::Write(size_t offset, const sf::String &value)
{
	auto szValue = value.toAnsiString();
	memcpy_s(m_memory.lpAddress + offset, m_memory.dwSize - offset, szValue.c_str(), szValue.length() + 1);
	m_memory.lpAddress[offset + szValue.length() + 1] = '\0';
}

void Buffer::Write(const sf::String &value)
{
	auto szValue = value.toAnsiString();
	memcpy_s(m_memory.lpAddress + m_offset, m_memory.dwSize - m_offset, szValue.c_str(), szValue.length() + 1);
	m_memory.lpAddress[m_offset + szValue.length() + 1] = '\0';
	m_offset += szValue.length() + 1;
}