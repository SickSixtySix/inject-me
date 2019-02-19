#pragma once

namespace InjectMe::Network
{
	// Обработчик событий прокси
	class IProxyHandler
	{
	public:

		// Обработчик события готовности прокси
		virtual void HandleReady() = 0;
	};
}