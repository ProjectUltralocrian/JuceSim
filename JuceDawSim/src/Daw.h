#ifndef DAW_H
#define DAW_H

#include "AudioEngine.h"

namespace pul {

    class Daw : public AudioEngine
    {
        void run() override;
    };
}

#endif //DAW_H