#include "Init.h"

static std::vector<pul::AudioProcessor*> thisProcessor{};


void AudioProcessorInit(pul::AudioEngine& engine)
{
	std::cout << "Initializing PluginSim.dll ... :)\n";
	auto myProcessor = new pul::MyProcessor(engine);
	auto yourProcessor = new pul::YourProcessor(engine);
	thisProcessor.push_back(myProcessor);
	thisProcessor.push_back(yourProcessor);
}

void AudioProcessorShutdown(pul::AudioEngine& engine)
{
	for (auto* proc : engine.getAudioProcessors()) {
		if (std::find(thisProcessor.begin(), thisProcessor.end(), proc) != thisProcessor.end()) {
			std::cout << "Deleting: " << proc->getName() << std::endl;
			delete proc;
		}
	}
}