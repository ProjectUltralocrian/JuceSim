#pragma once


#include "MyProcessor.h"
#include "YourProcessor.h"
#include "AudioEngine.h"

extern "C" {
	void __declspec(dllexport) AudioProcessorInit(pul::AudioEngine& daw);
	void __declspec(dllexport) AudioProcessorFinalise(pul::AudioEngine& daw);
}
