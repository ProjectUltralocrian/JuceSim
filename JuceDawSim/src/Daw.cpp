#include "AudioEngine.h"
#include "Daw.h"
#include <chrono>
#include <iostream>
#include <thread>


using namespace std::chrono_literals;

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

        std::this_thread::sleep_for(1000ms);
	}
}

  