#pragma once

namespace InjectMe::Network
{
	// ���������� ������� ������
	class IProxyHandler
	{
	public:

		// ���������� ������� ���������� ������
		virtual void HandleReady() = 0;
	};
}