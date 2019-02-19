#pragma once

// SFML
#include <SFML/System/Thread.hpp>
#include <SFML/System/Clock.hpp>

namespace InjectMe::Utils
{
	namespace priv
	{
		// Базовый класс функции
		class Function;
	}

	// Класс задания
	class Task
	{
		// Вызываемая функция данного задания
		priv::Function *m_function;

		// Время перед запуском данного задания
		sf::Time m_delay;

		// Часы отсчета времени перед запуском данного задания
		sf::Clock m_delayClock;

	public:
		
		// Конструктор задания
		template<typename F> Task(F function, sf::Time delay = sf::seconds(0));

		// Конструктор задания
		template<typename C> Task(void(C::*function)(), C *object, sf::Time delay = sf::seconds(0));

		// Обновляет данное задание. Возвращает истину в случае его выполнения
		bool UpdateTask();
	};

#include "Task.inl"
}