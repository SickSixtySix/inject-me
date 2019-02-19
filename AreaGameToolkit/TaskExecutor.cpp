// InjectMe
#include "TaskExecutor.hpp"

using namespace InjectMe::Utils;

// SFML
#include <SFML/System/Lock.hpp>
#include <SFML/System/Sleep.hpp>

void TaskExecutor::threadFunction()
{
	for (;;)
	{
		{
			sf::Lock lock(m_taskListMutex);
			for (auto it = m_taskList.begin(); it != m_taskList.end(); it++)
				if (it->UpdateTask())
					m_taskList.erase(it--);
		}

		// Минимальная общая задержка - 2мс
		sf::sleep(sf::milliseconds(2));
	}
}

TaskExecutor::TaskExecutor() : m_thread(&TaskExecutor::threadFunction, this)
{
	m_thread.launch();
}

void TaskExecutor::SheduleTask(const Task &task)
{
	sf::Lock lock(m_taskListMutex);
	m_taskList.push_back(task);
}