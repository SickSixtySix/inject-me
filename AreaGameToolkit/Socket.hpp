#pragma once

// InjectMe
#include "Buffer.hpp"
#include "IBufferHandler.hpp"
#include "IEncryption.hpp"
#include "ISocketHandler.hpp"
#include "IEncryption.hpp"

// SFML
#include <SFML/Config.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>

// C++
#include <queue>
#include <utility>

namespace InjectMe::Network
{
	// ����� ������
	class Socket : public Utils::IBufferHandler
	{
	protected:

		// ����������� �����
		sf::TcpSocket m_socket;

		// ����� ��������� ������������ ������
		sf::Thread m_socketThread;

		// ������� ������� ������� ������
		std::queue<std::pair<sf::Uint16, Utils::Buffer>> m_queue;
		sf::Mutex m_queueMutex;

		// ����� ��������� ������� ������� ������� ������
		sf::Thread m_queueThread;

		// ���������� ������� ������� ������
		ISocketHandler *m_handler = nullptr;

		// ��������� ���������� ��� ������� ������
		IEncryption *m_encryption = nullptr;

		// ���� ����������� ������� ������
		bool m_connected = false;

		// ������� ������ ��������� ������������ ������
		virtual void socketFunction();

		// ������� ������ ��������� ������� ������� ������� ������
		void queueFunction();

	public:

		// ����������� ������
		Socket(ISocketHandler *handler, IEncryption *encryption);

		// ������������ ����������� ������� ������
		virtual bool Connect();

		// ���������� ������ ����� ������ �����
		void Send(const char *data, size_t size);

		// ���������� ����� ����� ������ �����
		void SendPacket(sf::Uint16 packetID, Utils::Buffer &buffer);

		// �������� ����� � ������� ������� ������� ������
		void Enqueue(sf::Uint16 packetID, Utils::Buffer &buffer);

		// ��������� ������ �����
		void Disconnect();

		// ���������� ���� ����������� ������� ������
		bool IsConnected() const;

		// ���������� ������� ������ �������� �� ������
		void HandleRead(const Utils::Buffer &buffer, void *data, size_t offset, size_t length) final;

		// ���������� ������� ������ �������� � �����
		void HandleWrite(Utils::Buffer &buffer, char *data, size_t offset, size_t length) final;
	};
}