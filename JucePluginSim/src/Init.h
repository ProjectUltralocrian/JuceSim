#pragma once

#include "Daw.h"
#include "MyProcessor.h"
#include "YourProcessor.h"

extern "C" {
	void __declspec(dllexport) AudioProcessorInit(pul::Daw& daw);
	void __declspec(dllexport) AudioProcessorFinalise(pul::Daw& daw);
}
