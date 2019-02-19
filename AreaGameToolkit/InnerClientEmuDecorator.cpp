// InjectMe
#include "InnerClientEmuDecorator.hpp"

using namespace InjectMe::Utils;
using namespace InjectMe::Network;

void InnerClientEmuDecorator::HandleAuthConnected()
{
	if (m_innerClientEmu)
		m_innerClientEmu->HandleAuthConnected();
}

void InnerClientEmuDecorator::HandleGameConnected()
{
	if (m_innerClientEmu)
		m_innerClientEmu->HandleGameConnected();
}

void InnerClientEmuDecorator::HandleAuthPacket(sf::Uint16 packetID, Buffer &buffer)
{
	if (m_innerClientEmu)
		m_innerClientEmu->HandleAuthPacket(packetID, buffer);
}

void InnerClientEmuDecorator::HandleGamePacket(sf::Uint16 packetID, Buffer &buffer)
{
	if (m_innerClientEmu)
		m_innerClientEmu->HandleGamePacket(packetID, buffer);
}

void InnerClientEmuDecorator::HandleAuthQueuePacket(sf::Uint16 packetID, Buffer &buffer)
{
	if (m_innerClientEmu)
		m_innerClientEmu->HandleAuthQueuePacket(packetID, buffer);
}

void InnerClientEmuDecorator::HandleGameQueuePacket(sf::Uint16 packetID, Buffer &buffer)
{
	if (m_innerClientEmu)
		m_innerClientEmu->HandleGameQueuePacket(packetID, buffer);
}

void InnerClientEmuDecorator::HandleAuthDisconnected()
{
	if (m_innerClientEmu)
		m_innerClientEmu->HandleAuthDisconnected();
}

void InnerClientEmuDecorator::HandleGameDisconnected()
{
	if (m_innerClientEmu)
		m_innerClientEmu->HandleGameDisconnected();
}

InnerClientEmuDecorator::InnerClientEmuDecorator(IInnerClientEmu *innerClientEmu)
{
	m_innerClientEmu = innerClientEmu;
}