#pragma once

#include "Daw.h"
#include "MyProcessor.h"
#include "YourProcessor.h"

extern "C" {
	void __declspec(dllexport) Init(pul::Daw& daw);
}



namespace pul::AudioPlugin {
	
}
