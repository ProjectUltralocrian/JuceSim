#include "CTransformer.h"


struct pul::CTransformer::ProcessorImpl
{
	const char* getName() const;
	void prepareToPlay();
	void processBlock(pul::AudioBuffer<float>* buffer);
};

const char* pul::CTransformer::ProcessorImpl::getName() const
{
	return "Third Party Plugin";
}


void pul::CTransformer::ProcessorImpl::prepareToPlay()
{
	PUL_INFO("Preparing to play in Thirdparty plugin...");
}

void pul::CTransformer::ProcessorImpl::processBlock(pul::AudioBuffer<float>* buffer)
{
	buffer->process([](float f) { return 5 * f; });
}
