// InjectMe
#include "OuterClientEmuDecorator.hpp"

using namespace InjectMe::Utils;
using namespace InjectMe::Network;

OuterClientEmuDecorator::OuterClientEmuDecorator(IOuterClientEmu *outerClientEmu)
{
	m_outerClientEmu = outerClientEmu;
}

void OuterClientEmuDecorator::StartClientEmu()
{
	m_outerClientEmu->StartClientEmu();
}

void OuterClientEmuDecorator::SendAuthPacket(sf::Uint16 packetID, Buffer &buffer)
{
	m_outerClientEmu->SendAuthPacket(packetID, buffer);
}

void OuterClientEmuDecorator::SendGamePacket(sf::Uint16 packetID, Buffer &buffer)
{
	m_outerClientEmu->SendGamePacket(packetID, buffer);
}