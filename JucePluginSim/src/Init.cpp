#include "Init.h"

void AudioProcessorInit(pul::AudioEngine& engine)
{
	std::cout << "Initializing PluginSim.dll ... :)\n";
	auto myProcessor = new pul::MyProcessor(engine);
	auto yourProcessor = new pul::YourProcessor(engine);
}

void AudioProcessorShutdown(pul::AudioEngine& engine)
{
	for (auto* proc : engine.getAudioProcessors()) {
		std::cout << "Deleting: " << proc->getName() << std::endl;
		delete proc;
	}
}