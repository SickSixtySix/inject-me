#pragma once

// InjectMe
#include "Task.hpp"

// SFML
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>

// C++
#include <vector>

namespace InjectMe::Utils
{
	// Класс исполнителя заданий
	class TaskExecutor
	{
		// Список заданий данного исполнителя заданий
		std::vector<Task> m_taskList;
		sf::Mutex m_taskListMutex;

		// Поток данного исполнителя заданий
		sf::Thread m_thread;

		// Функция потока  данного исполнителя заданий
		void threadFunction();

	public:

		// Конструктор исполнителя заданий
		TaskExecutor();

		// Планирует задание для данного исполнителя заданий
		void SheduleTask(const Task &task);
	};
}