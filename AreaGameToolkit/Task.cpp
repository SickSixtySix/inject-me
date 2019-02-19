// InjectMe
#include "Task.hpp"

using namespace InjectMe::Utils;

bool Task::UpdateTask()
{
	if (m_delayClock.getElapsedTime() < m_delay)
		return false;

	m_function->Invoke();
	return true;
}