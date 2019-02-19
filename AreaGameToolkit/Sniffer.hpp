#pragma once

// InjectMe
#include "Proxy.hpp"

// SFML
#include <SFML/System/Mutex.hpp>

// C++
#include <set>
#include <unordered_map>
#include <vector>

namespace Cheat::Sniffer
{
	// ����� ��������
	class Sniffer
	{
	public:

		// ��������� ������ ������
		struct Packet
		{
			// ������ �� ���� ������� ������
			InjectMe::Network::Proxy *proxy;

			// ����������� ������� ������
			sf::Uint32 direction;

			// ������������� ������� ������
			sf::Uint16 packetID;

			// ����� ������� ������
			InjectMe::Utils::Buffer buffer;
		};

		// ��������� ������ ��������
		struct Transfer
		{
			// ������������ �����
			Packet packet;

			// ������� ���������� �������
			size_t current;

			// ����������� ���������� �������
			size_t total;

			// ���� ������������ ��������
			bool suspend;
		};

	private:

		// �������� ������ ����
		static Sniffer *s_sniffer;

		// ������ �������
		std::vector<Packet> m_history;
		sf::Mutex m_historyMutex;

		// ��� ��������
		std::vector<Transfer*> m_transfers;

		// ������ ���� ������
		std::set<InjectMe::Network::Proxy*> m_proxies;

		// ������ ���� ������������� �������
		std::set<sf::Uint16> m_packetIDs;

		// ������ �� ������
		InjectMe::Network::Proxy *m_filterProxy = nullptr;

		// ������ �� �������
		sf::Uint16 m_filterPacket = 0;

		// �������� ������
		struct MemoryEditorImpl;
		MemoryEditorImpl *m_editor;

		// ����� �������������� ������
		int m_editPacket = -1;

		// ����������� ������ ����
		Sniffer();

	public:

		// ���������� ��������� ������
		static Sniffer* Instance();

		void LogFromClientToServer(InjectMe::Network::Proxy *proxy, sf::Uint16 packetID, const InjectMe::Utils::Buffer &buffer);

		void LogFromServerToClient(InjectMe::Network::Proxy *proxy, sf::Uint16 packetID, const InjectMe::Utils::Buffer &buffer);

		void LogFromProxyToServer(InjectMe::Network::Proxy *proxy, sf::Uint16 packetID, const InjectMe::Utils::Buffer &buffer);

		void LogFromProxyToClient(InjectMe::Network::Proxy *proxy, sf::Uint16 packetID, const InjectMe::Utils::Buffer &buffer);

		// ���������
		void ImGui();
	};
}