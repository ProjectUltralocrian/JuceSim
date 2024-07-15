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
	throw NotImplementedException();
}

void pul::CTransformer::ProcessorImpl::processBlock(pul::AudioBuffer<float>* buffer)
{
	throw NotImplementedException();
}

/*

{
	
	void prepareToPlay();
	void processBlock(pul::AudioBuffer<float>* buffer);
};
*/