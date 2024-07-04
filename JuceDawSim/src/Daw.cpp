#include "Daw.h"
#include "YourProcessor.h"
#include "AudioBuffer.h"
#include "MyProcessor.h"
#include "Helpers.h"
#include <iostream>
#include <memory>
#include <array>
#include <format>
#include <stdexcept>


namespace pul {

    Daw::Daw()
    {
        m_Processors = getProcessors();
    }

    void Daw::run()
    {
        std::cout << "Simulating host DAW\n";

        play();
    }

    void Daw::play()
    {
        std::cout << "Playing...\n";
        setVolume(3.5218f); //(1.5x gain increase)
        //Simulating calling the prepareToPlay function of
        //all registered audio processor plugins,
        //immediately before playing starts.     

        for (const auto& proc : m_Processors) {
            proc->prepareToPlay();
        }

        //std::cout << "New volume: " << getVolume() << std::endl;

        //Simulating filling the buffers with audio samples
        //and sending these to the audio processors.
        
        constexpr size_t NUMSAMPLES = 36;
        
        auto fullSinCycle = getSinSampleValues<float, NUMSAMPLES>();
        for (auto c : fullSinCycle) {
            std::cout << std::format("SIN {:.4f}\n", c);
        }
        AudioBuffer<float> buffer1(NUMSAMPLES, fullSinCycle);
        AudioBuffer<float> buffer2(NUMSAMPLES, fullSinCycle);
        AudioBuffer<float> buffer3(NUMSAMPLES, fullSinCycle);
        std::array<AudioBuffer<float>, 3> buffers{
            std::move(buffer1), std::move(buffer2), std::move(buffer3)
        };

        //Calling the audio callback function (processBlock)
        //on all registered audio processor plugins in sequence.
        for (auto& buf : buffers) {
            for (const auto& proc : m_Processors) {
                proc->processBlock(buf);
            }
        }


        //Simulating audio output (printing out the processed samples)
        for (auto& buf : buffers) {
            auto p = buf.getReadPointer();
            for (size_t i = 0; i < buf.getNumSamples(); ++i) {
                std::cout << std::format("SAMPLE {}: {:.4f}\n", i, p[i]);
            }
        }
    }

    ProcVector Daw::getProcessors()
    {
        ProcVector output;
        output.emplace_back(std::make_unique<MyProcessor>(*this));
        //output.emplace_back(std::make_unique<YourProcessor>(*this));
        return output;
    }

    void Daw::setVolume(float newVolume)
    {
        assert(-60.f <= newVolume && newVolume <= 15.f);
        m_Volume = newVolume;
        notify("Volume has been changed by host DAW...");
    }

    void Daw::registerListener(Listener* listener)
    {
        if (listener)
        {
            m_Listeners.push_back(listener);
            std::cout << "Registered listener: " << listener << std::endl;
            std::cout << "Listeners: " << m_Listeners[0] << std::endl;
        }
    }


    void Daw::deregisterListener(Listener* listener)
    {
        //throw NotImplementedException{};
        std::cout << "Number of listeners: " << m_Listeners.size() << std::endl;
        std::erase_if(m_Listeners, [=](Listener* l) {return l == listener; });
        std::cout << "Number of listeners: " << m_Listeners.size() << std::endl;
    }

    void Daw::notify(std::string_view msg) const
    {
        for (auto* listener : m_Listeners) {
            listener->onNotified(*this, msg);
        }
    }

}