#include "PulEngine.h"
#include "AudioProcessor.h"
#include "PluginLoader.h"
#include <iostream>
#include <format>


namespace pul {

    std::vector<AudioProcessor*> AudioEngine::getAudioProcessors() const
    {
        return m_Processors;
    }

    void AudioEngine::registerAudioProcessor(AudioProcessor* processor)
    {
        if (processor) {
            processor->setHostEngine(this);
            m_Processors.push_back(processor);
        }
    }

    void AudioEngine::run()
    {
        

    }

    void AudioEngine::play()
    {
        std::cout << "Playing...\n";
        setVolume(3.5218f); //(3.52dB == 1.5x gain increase)

        //Simulating calling the prepareToPlay function of
        //all registered audio processor plugins,
        //immediately before playing starts.     
        for (const auto& proc : getAudioProcessors()) {
            proc->prepareToPlay();
        }

        //Simulating filling the buffers with audio samples
        //and sending these to the audio processors.
        //In this case creating and sending three buffers filled with
        //one full sine-wave cycle each.
        constexpr size_t NUMSAMPLES = 36;

        auto fullSinCycle = getSinSampleValues<float, NUMSAMPLES>();
        AudioBuffer<float> buffer1(NUMSAMPLES, fullSinCycle);
        AudioBuffer<float> buffer2(NUMSAMPLES, fullSinCycle);
        AudioBuffer<float> buffer3(NUMSAMPLES, fullSinCycle);
        std::array<AudioBuffer<float>, 3> buffers{
            std::move(buffer1), std::move(buffer2), std::move(buffer3)
        };

        //Calling the audio callback function (processBlock)
        //on all registered audio processor plugins in sequence.
        for (auto& buf : buffers) {
            for (const auto& proc : getAudioProcessors()) {
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

    void AudioEngine::setVolume(float newVolume)
    {
        ASSERT(-60.f <= newVolume && newVolume <= 15.f);
        m_Volume = newVolume;
        notify("Volume has been changed by host DAW...");
    }

    PUL_API std::string AudioEngine::getDllNameFromLua(const char* luaFileName)
    {
        m_Lua.exec_file(luaFileName);
        auto dllName = m_Lua.get_string("dllName");
        return dllName.okOrDefault("File not found.");
    }

    void AudioEngine::registerListener(Listener* listener)
    {
        if (listener)
        {
            m_Listeners.push_back(listener);
        }
    }

    void AudioEngine::deregisterListener(Listener* listener)
    {
        std::erase_if(m_Listeners, [=](Listener* l) {return l == listener; });
    }


    void AudioEngine::notify(std::string_view msg) const
    {
        for (auto* listener : m_Listeners) {
            listener->onNotified(*this, msg);
        }
    }

}