#include "Init.h"

void AudioProcessorInit(pul::Daw& daw)
{
	std::cout << "Initializing PluginSim.dll ...\n";
	auto myProcessor = new pul::MyProcessor(daw);
	auto yourProcessor = new pul::YourProcessor(daw);
}

void AudioProcessorFinalise(pul::Daw& daw)
{
	for (auto& proc : daw.getAudioProcessors()) {
		std::cout << "Deleting: " << proc->getName() << std::endl;
		delete proc;
	}
}