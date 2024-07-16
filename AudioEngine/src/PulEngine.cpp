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

    PUL_API void AudioEngine::deregisterAudioProcessor(AudioProcessor* processor)
    {
        for (auto* proc : getAudioProcessors()) {
            if (processor == proc) {
                std::cout << "Deleting: " << proc->getName() << std::endl;
                delete proc;
            }
        }
    }

    void AudioEngine::run() 
    {      
        play();
    }

    void AudioEngine::play()
    {
        PUL_INFO("Playing...");
        
        setVolume(3.5218f); //(3.52dB == 1.5x gain increase)

        //Simulating getting config value from Lua file.
        auto newVolume = m_Lua.get_number("volume");
        if (newVolume)
            setVolume(static_cast<float>(newVolume.unwrap()));


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
                PUL_INFO(std::format("SAMPLE {}: {:.4f}", i, p[i]));
            }
        }
    }

    void AudioEngine::setVolume(float newVolume)
    {
        ASSERT(-60.f <= newVolume && newVolume <= 15.f);
        m_Volume = newVolume;
        notify("Volume has been changed by host DAW...");
    }

    void AudioEngine::getAndRegisterPluginsFromLua(const char* luaFileName)
    {
        auto dllFileNames = getDllNamesFromLua(luaFileName, "plugins");
        if (dllFileNames) {
            for (const auto& dll : dllFileNames.value()) {
                size_t newsize = strlen(dll.c_str()) + 1;
                wchar_t* wcstring = new wchar_t[newsize];
                size_t convertedChars = 0;
                mbstowcs_s(&convertedChars, wcstring, newsize, dll.c_str(), _TRUNCATE);
                auto loader = new PluginLoader(wcstring, this);
                m_Loaders.push_back(loader);
                delete[]wcstring;
            }
        }
        else {
            PUL_INFO("No plugin dll filenames found in config.lua...");
        }
    }

    std::optional<std::vector<std::string>> AudioEngine::getDllNamesFromLua(const char* luaFileName, const char* varName)
    {
        if (!m_Lua.exec_file(luaFileName)) {
            std::cerr << luaFileName << " could not be found or opened...\n";
            return std::nullopt;
        } 
        auto dllNames = m_Lua.get_all_values_in_table(varName);
        
        if (dllNames)
            return dllNames.unwrap();
        else
            return std::nullopt;
    }

    
    AudioEngine::~AudioEngine()
    {
        for (auto loader : m_Loaders) {
            delete loader;
        }
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