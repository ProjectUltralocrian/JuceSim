#ifndef YOURPROCESSOR_H
#define YOURPROCESSOR_H

#include "PulEngine.h"
#include "AudioProcessor.h"
#include "Gain.h"
#include "DryWet.h"
#include "Daw.h"

namespace pul {
    class YourProcessor : public AudioProcessor
    {
    public:
        YourProcessor(Daw& daw);
        std::string_view getName() const override { return "YourProcessor: DryWet..."; }
        void prepareToPlay() override;
        void processBlock(AudioBuffer<float>& buffer) override;
    private:
        Daw& m_Daw;
        DryWet<float> m_DryWet;
        uint8_t m_DryLevel{ 100 };
    };
}

#endif //YOURPROCESSOR_H
