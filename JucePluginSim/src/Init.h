#pragma once

#include "PulEngine.h"
#include "MyProcessor.h"
#include "YourProcessor.h"

extern "C" {
	void __declspec(dllexport) AudioProcessorInit(pul::AudioEngine& daw);
	void __declspec(dllexport) AudioProcessorFinalise(pul::AudioEngine& daw);
}
