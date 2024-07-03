#ifndef MYPROCESSOR_H
#define MYPROCESSOR_H

#include "AudioProcessor.h"
#include "Gain.h"
#include "Observer.h"
#include "Daw.h"
#include <string>


#ifdef JUCE_DLL_BUILD
#define JUCE_DLL __declspec(dllexport) 
#else
#define JUCE_DLL __declspec(dllimport)
#endif



class JUCE_DLL MyProcessor : public AudioProcessor,
                             public Listener
{
public:
    MyProcessor(Daw& daw);
    ~MyProcessor();
    void prepareToPlay() override;
    void processBlock(AudioBuffer<float>& buffer) override;
private:
    Daw& m_Daw;
    Gain<float> m_Gain;
    float m_LevelDb {0.f};
    void onNotified(const Broadcaster&, std::string_view msg) override;
};

#endif //MYPROCESSOR_H
