#include "CTransformer.h"
#include "Init.h"

static pul::AudioProcessor* thisProcessor = nullptr;

void AudioProcessorInit(pul::AudioEngine& engine)
{
	std::cout << "Initializing ThirdPartyPlugin.dll ... :)\n";
	auto myProcessor = new pul::CTransformer(engine);
	thisProcessor = myProcessor;
}

void AudioProcessorShutdown(pul::AudioEngine& engine)
{
	engine.deregisterAudioProcessor(thisProcessor);
}