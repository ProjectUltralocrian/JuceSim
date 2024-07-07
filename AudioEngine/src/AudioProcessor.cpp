#include "AudioProcessor.h"

void pul::AudioProcessor::setHostEngine(pul::AudioEngine* engine)
{
	ASSERT(engine != nullptr);
	m_HostEngine = engine;
}
