//#include "AudioEngine.h"
#include "Daw.h"

#include <iostream>

namespace pul {
	void Daw::run()
	{
        getAndRegisterPluginsFromLua("config.lua");

        std::cout << "Starting DAW... :) \n";

        auto processors = getAudioProcessors();
        if (processors.size()) {
            std::cout << "Registered plugins: \n";
        }
        for (const auto& proc : processors) {
            std::cout << "  - " << proc->getName() << std::endl;
        }

        play();
	}
}

  