#ifndef MYPROCESSOR_H
#define MYPROCESSOR_H


#include "PulEngine.h"
#include "AudioProcessor.h"
#include "Gain.h"
#include "Observer.h"
#include <string>

namespace pul {

    class MyProcessor : public AudioProcessor,
                                public Listener
    {
    public:
        MyProcessor(AudioEngine& daw);
        std::string_view getName() const override { return "My Gain Processor..."; }
        ~MyProcessor();
        void prepareToPlay() override;
        void processBlock(AudioBuffer<float>& buffer) override;
    private:
        AudioEngine& m_Engine;
        Gain<float> m_Gain;
        float m_LevelDb{ 0.f };
        void onNotified(const Broadcaster&, std::string_view msg) override;
    };

}
#endif //MYPROCESSOR_H
