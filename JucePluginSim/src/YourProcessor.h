#ifndef YOURPROCESSOR_H
#define YOURPROCESSOR_H

#include "JucePlugin.h"
#include "AudioProcessor.h"
#include "Gain.h"
#include "DryWet.h"
#include "Daw.h"


namespace pul {

    class JUCE_DLL YourProcessor : public AudioProcessor
    {
    public:
        YourProcessor(Daw& daw);
        void prepareToPlay() override;
        void processBlock(AudioBuffer<float>& buffer) override;
    private:
        Daw& m_Daw;
        DryWet<float> m_DryWet;
        uint8_t m_DryLevel{ 100 };
    };

}

#endif //YOURPROCESSOR_H
