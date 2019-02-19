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
	// ����� ����������� �������
	class TaskExecutor
	{
		// ������ ������� ������� ����������� �������
		std::vector<Task> m_taskList;
		sf::Mutex m_taskListMutex;

		// ����� ������� ����������� �������
		sf::Thread m_thread;

		// ������� ������  ������� ����������� �������
		void threadFunction();

	public:

		// ����������� ����������� �������
		TaskExecutor();

		// ��������� ������� ��� ������� ����������� �������
		void SheduleTask(const Task &task);
	};
}