#ifndef YOURPROCESSOR_H
#define YOURPROCESSOR_H

#include "AudioProcessor.h"
#include "Gain.h"
#include "DryWet.h"
#include "Daw.h"

#ifdef JUCE_DLL_BUILD
#define JUCE_DLL __declspec(dllexport) 
#else
#define JUCE_DLL __declspec(dllimport)
#endif

class JUCE_DLL YourProcessor : public AudioProcessor 
{
public:
    YourProcessor(Daw& daw);
    void prepareToPlay() override;
    void processBlock(AudioBuffer<float>& buffer) override;
private:
    Daw& m_Daw;
    DryWet<float> m_DryWet;
    uint8_t m_DryLevel{100};
};

#endif //YOURPROCESSOR_H
