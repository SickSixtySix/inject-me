// InjectMe
#include "Memory.hpp"
#include "ClientEmuConsole.hpp"
#include "AsdaGlobalEncryption.hpp"

using namespace InjectMe::Utils;
using namespace InjectMe::Network;

// Rivet
#include "Rivet.hpp"
#include "RivetClientEmu.hpp"

using namespace Rivet;

// SFML
#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>

// C++
#include <iostream>

void StartRivet()
{
	// Инициализация памяти
	ChainInit();

	RivetClientEmu *clientEmu;
	for (;;)
	{
		clientEmu = new RivetClientEmu("35.169.192.251", 15001, "samprplover1", "jv^9m^bk", 0x0000BE50, 0x000D, 256, 256, AsdaGlobalEncryption::Instance(), new ClientEmuConsole());
		//clientEmu = new RivetClientEmu("35.169.192.251", 15001, "Samuel267", "due?_r6q", 0x0000BEF9, 0x000A, 256, 256, AsdaGlobalEncryption::Instance(), new ClientEmuConsole());
		clientEmu->StartClientEmu();

		sf::Clock clock; 
		while (clientEmu->IsActive() && clock.getElapsedTime() < sf::seconds(45)) 
			sf::sleep(sf::milliseconds(2));

		delete clientEmu;
	}
}