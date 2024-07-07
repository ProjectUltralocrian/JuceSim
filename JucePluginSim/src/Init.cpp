#include "Init.h"

void Init(pul::Daw& daw)
{
	std::cout << "Initializing stuff....\n";
	std::cout << "Address of daw: " << &daw << std::endl;
	
	auto myProcessor = new pul::MyProcessor(daw);
	std::cout << "Address of myProcessor: " << myProcessor << std::endl;
	auto yourProcessor = new pul::YourProcessor(daw);
}
