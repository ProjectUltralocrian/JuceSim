#include "PulEngine.h"
#include "AudioProcessor.h"
#include <iostream>


void pul::AudioEngine::run()
{
	std::cout << "Starting PulAudioEngine...\n";
}

std::vector<pul::AudioProcessor*> pul::AudioEngine::getAudioProcessors() const
{
	return m_Processors;
}

void pul::AudioEngine::registerAudioProcessor(AudioProcessor* processor)
{
	std::cout << "processor registered: " << processor->getName() << std::endl;
	std::cout << "Address of registered: " << processor << std::endl;
	if (processor) {
		processor->setHostEngine(this);
		m_Processors.push_back(processor);
	}
	
}

