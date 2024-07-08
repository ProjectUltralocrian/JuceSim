#ifndef YOURPROCESSOR_H
#define YOURPROCESSOR_H

#include "AudioEngine.h"
#include "Gain.h"
#include "DryWet.h"

namespace pul {
    class YourProcessor : public AudioProcessor
    {
    public:
        YourProcessor(AudioEngine& engine);
        std::string_view getName() const override { return "YourProcessor: DryWet..."; }
        void prepareToPlay() override;
        void processBlock(AudioBuffer<float>& buffer) override;
    private:
        AudioEngine& m_Engine;
        DryWet<float> m_DryWet;
        uint8_t m_DryLevel{ 100 };
    };
}

#endif //YOURPROCESSOR_H
