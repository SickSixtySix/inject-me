// Toolkit
#include "Logger.hpp"

// Rivet
#include "Rivet.hpp" 

using namespace InjectMe::Utils;

int main()
{
	Logger::GetInstance()->printf("main()");

	StartRivet();

	return 0;
}