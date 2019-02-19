#pragma once

// SFML
#include <SFML/System/Mutex.hpp>

// C
#include <stdio.h>

namespace InjectMe::Utils
{
	// ����� ��������� ��������������
	class Logger
	{
		// ��������� ��������� ��������������
		static Logger *s_instance;

		// ������� ���������� ��������� ��������������
		static sf::Mutex s_instanceMutex;

		// ��������� ����� ��������� ��������������
		FILE *_Stream;

		// ����������� ��������� ��������������
		Logger();

	public:

		// �������� ��������� ��������� �������������� 
		static Logger* GetInstance();

		// ������ ������� printf ��������� �������������� 
		void printf(const char *_Format, ...);
	};
}