#ifndef AUDIOPROCESSOR_H
#define AUDIOPROCESSOR_H

#include "PulEngine.h"
#include "AudioBuffer.h"




namespace pul {

    class PUL_API AudioProcessor
    {
    public:
        virtual void setHostEngine(AudioEngine* engine);
        virtual void prepareToPlay() = 0;
        virtual void processBlock(AudioBuffer<float>& buffer) = 0;
        virtual std::string_view getName() const { return "AudioProcessor base class..."; }

        virtual ~AudioProcessor() = default;
    private:
        AudioEngine* m_HostEngine;
    };

}

#endif //AUDIOPROCESSOR_H