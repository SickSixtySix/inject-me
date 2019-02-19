// InjectMe
#include "AsdaGlobalData.hpp"
#include "AsdaGlobalHash.hpp"
#include "AsdaGlobalPost.hpp"
#include "AsdaGlobalSync.hpp"

using namespace InjectMe::Utils;
using namespace InjectMe::Hook::AsdaGlobal;

AsdaGlobalData::AsdaGlobalData()
{
	m_address1 = reinterpret_cast<long>(new long[1000]);
	m_address2 = reinterpret_cast<long>(new long[1000]);
	m_address3 = reinterpret_cast<long>(new long[1000]);
	m_address4 = reinterpret_cast<long>(new long[1000]);
	m_allocated = true;
}

AsdaGlobalData::AsdaGlobalData(unsigned long address1, unsigned long address2, unsigned long address3, unsigned long address4)
{
	m_address1 = address1;
	m_address2 = address2;
	m_address3 = address3;
	m_address4 = address4;
	m_allocated = false;
}

AsdaGlobalData::~AsdaGlobalData()
{
	if (m_allocated)
	{
		delete[] reinterpret_cast<long*>(m_address1); m_address1 = 0;
		delete[] reinterpret_cast<long*>(m_address2); m_address2 = 0;
		delete[] reinterpret_cast<long*>(m_address3); m_address3 = 0;
		delete[] reinterpret_cast<long*>(m_address4); m_address4 = 0;
		m_allocated = false;
	}
}

void AsdaGlobalData::ResetData()
{
	if (!m_allocated)
		return;

	for (size_t i = 0; i < 1000; i++)
	{
		(reinterpret_cast<unsigned long*>(m_address1))[i] = 0;
		(reinterpret_cast<unsigned long*>(m_address2))[i] = 0;
		(reinterpret_cast<unsigned long*>(m_address3))[i] = 1;
		(reinterpret_cast<unsigned long*>(m_address4))[i] = 0;
	}
}

void AsdaGlobalData::SwitchData()
{
	if (!m_allocated)
		return;

	for (size_t i = 0; i < 1000; i++)
	{
		(reinterpret_cast<unsigned long*>(m_address3))[i] = 3 - (reinterpret_cast<unsigned long*>(m_address3))[i];
		(reinterpret_cast<unsigned long*>(m_address4))[i] = 0;
	}
}

unsigned long AsdaGlobalData::GetAddress1() const
{
	return m_address1;
}

unsigned long AsdaGlobalData::GetAddress2() const
{
	return m_address2;
}

unsigned long AsdaGlobalData::GetAddress3() const
{
	return m_address3;
}

unsigned long AsdaGlobalData::GetAddress4() const
{
	return m_address4;
}

void AsdaGlobalData::PreparePacket(sf::Uint16 packetID, Buffer &buffer)
{
	sf::Int16 *opt = nullptr;

	if (packetID == 1000)
	{
#include "1000"
		opt = opt1000;
	}
	else if (packetID == 1003)
	{
#include "1003"
		opt = opt1003;
	}
	else if (packetID == 1005)
	{
#include "1005"
		opt = opt1005;
	}
	else if (packetID == 1012)
	{
#include "1012"
		opt = opt1012;
	}
	else if (packetID == 1016)
	{
#include "1016"
		opt = opt1016;
	}
	else if (packetID == 4001)
	{
#include "4001"
		opt = opt4001;
	}
	else if (packetID == 5041)
	{
#include "5041"
		opt = opt5041;
	}
	else if (packetID == 5043)
	{
#include "5043"
		opt = opt5043;
	}
	else if (packetID == 5056)
	{
#include "5056"
		opt = opt5056;
	}
	else if (packetID == 5058)
	{
#include "5058"
		opt = opt5058;
	}
	else if (packetID == 9915)
	{
#include "9915"
		opt = opt9915;
	}
	else if (packetID == 20000)
	{
#include "20000"
		opt = opt20000;
	}

	if (!opt)
	{
		static sf::Int16 optDefault[] = { 1, 1, 1, -1 };
		opt = optDefault;
	}

	unsigned long len = opt[3];

	if (len < 0)
		len = static_cast<sf::Uint16>(buffer.GetOffset());

	if (opt[0])
		AsdaGlobalSync(buffer.GetMemory().lpAddress, 10, *this);

	if (opt[1])
		if (opt[0])
			AsdaGlobalHash(buffer.GetMemory().lpAddress, 18, len, 34);
		else
			AsdaGlobalHash(buffer.GetMemory().lpAddress, 10, len, 26);

	if (opt[2])
	{
		AsdaGlobalPost(buffer.GetMemory().lpAddress, &len, opt[0], opt[1], *this);
		buffer.SetOffset(len);
	}
}