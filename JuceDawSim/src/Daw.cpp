#include "Daw.h"
#include "AudioEngine.h"
#include <chrono>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

namespace pul {
	void Daw::run()
	{
        getAndRegisterPluginsFromLua("config.lua");

        EngineLogger::Init(Logger::LogLevel::Info);


        PUL_INFO("Starting DAW...");


        auto processors = getAudioProcessors();
        if (processors.size()) {
            PUL_INFO("Registered plugins:");
        }
        for (const auto& proc : processors) {
            PUL_INFO(std::format("  - {}", proc->getName()));
        }

        play();

        std::this_thread::sleep_for(1000ms);
	}
}

  