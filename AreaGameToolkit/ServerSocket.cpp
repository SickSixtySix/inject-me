// InjectMe
#include "ServerSocket.hpp"

using namespace InjectMe::Network;

bool ServerSocket::Connect()
{
	if (listener.listen(m_port) != sf::Socket::Status::Done)
		return false;

	return Socket::Connect();
}

void ServerSocket::socketFunction()
{
	if (listener.accept(m_socket) != sf::Socket::Status::Done)
		// TODO: Обработка ошибки
		return;

	listener.close();
	Socket::socketFunction();
}

ServerSocket::ServerSocket(sf::Uint16 port, ISocketHandler *handler, IEncryption *encryption) : Socket(handler, encryption), m_port(port) {}