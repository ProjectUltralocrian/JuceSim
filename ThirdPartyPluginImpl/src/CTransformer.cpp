#include "CTransformer.h"

struct pul::CTransformer::ProcessorImpl
{
	const char* getName() const;
	void prepareToPlay();
	void processBlock(pul::AudioBuffer<float>* buffer);
};


pul::CTransformer::CTransformer(AudioEngine& engine)
	: m_Engine{ engine }, m_Impl{ std::make_unique<ProcessorImpl> () }
{
	m_Engine.registerAudioProcessor(this);
}

pul::CTransformer::~CTransformer() = default;

std::string_view pul::CTransformer::getName() const
{
	return m_Impl->getName();
}

void pul::CTransformer::prepareToPlay()
{
	m_Impl->prepareToPlay();
}

void pul::CTransformer::processBlock(AudioBuffer<float>& buffer)
{
	m_Impl->processBlock(&buffer);
}
