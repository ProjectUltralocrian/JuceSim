#include "AudioEngine.h"
#include "Daw.h"

#include <iostream>

namespace pul {
	void Daw::run()
	{
        auto dllFileName = getDllNameFromLua("config.lua");


        size_t newsize = strlen(dllFileName.c_str()) + 1;
        wchar_t* wcstring = new wchar_t[newsize];
        size_t convertedChars = 0;
        mbstowcs_s(&convertedChars, wcstring, newsize, dllFileName.c_str(), _TRUNCATE);
        PluginLoader loader(wcstring, this);
        delete[]wcstring;
        

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

  