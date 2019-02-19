// InjectMe
#include "ClientSocket.hpp"

using namespace InjectMe::Network;

ClientSocket::ClientSocket(const sf::IpAddress &address, sf::Uint16 port, ISocketHandler *handler, IEncryption *encryption) : Socket(handler, encryption), m_address(address), m_port(port) {}

bool ClientSocket::Connect()
{
	if (m_socket.connect(m_address, m_port) != sf::Socket::Status::Done)
		return false;

	return Socket::Connect();
}