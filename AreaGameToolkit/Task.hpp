#pragma once

// SFML
#include <SFML/System/Thread.hpp>
#include <SFML/System/Clock.hpp>

namespace InjectMe::Utils
{
	namespace priv
	{
		// ������� ����� �������
		class Function;
	}

	// ����� �������
	class Task
	{
		// ���������� ������� ������� �������
		priv::Function *m_function;

		// ����� ����� �������� ������� �������
		sf::Time m_delay;

		// ���� ������� ������� ����� �������� ������� �������
		sf::Clock m_delayClock;

	public:
		
		// ����������� �������
		template<typename F> Task(F function, sf::Time delay = sf::seconds(0));

		// ����������� �������
		template<typename C> Task(void(C::*function)(), C *object, sf::Time delay = sf::seconds(0));

		// ��������� ������ �������. ���������� ������ � ������ ��� ����������
		bool UpdateTask();
	};

#include "Task.inl"
}