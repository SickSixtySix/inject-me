#pragma once

namespace InjectMe::Utils
{
	// Предварительное объявление класса буфера
	class Buffer;

	// Интерфейс обработчика событий буфера
	class IBufferHandler
	{
	public:

		// Обработчик события чтения значения из буфера
		virtual void HandleRead(const Buffer &buffer, void *data, size_t offset, size_t length) = 0;

		// Обработчик события записи значения в буфер
		virtual void HandleWrite(Buffer &buffer, char *data, size_t offset, size_t length) = 0;
	};
}