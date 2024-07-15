#include "MyProcessor.h"
#include <iostream>
#include <format>

namespace pul {

    MyProcessor::MyProcessor(AudioEngine& daw)
        : m_Engine{ daw }
    {
        m_Engine.registerAudioProcessor(this);
        m_Engine.registerListener(this);
    }

    MyProcessor::~MyProcessor()
    {
        m_Engine.deregisterListener(this);
    }

    void MyProcessor::onNotified(const Broadcaster& broadcaster, std::string_view msg)
    {
        std::cout << msg << std::endl;
        if (const auto* daw = dynamic_cast<const AudioEngine*>(&broadcaster)) {
            m_LevelDb = daw->getVolume();
            PUL_INFO(std::format("DAW volume: {}", daw->getVolume()));
            m_Gain.changeLevelByDb(m_LevelDb);
            std::cout << "m_Gain level: " << m_Gain.level() << std::endl;
        }
        else {
            ASSERT(false);
            //std::cout << "Not daw...\n";
        }
    }

    void MyProcessor::prepareToPlay()
    {
        std::cout << "Preparing MyProcessor...\n";
        m_LevelDb = -6.0205f;  //(-6.02dB == 0.5x gain decrease..)
        m_Gain.changeLevelByDb(m_LevelDb);
    }

    void MyProcessor::processBlock(AudioBuffer<float>& buffer)
    {
        std::cout << "MyProcessor: Processing...\n";
        m_Gain.prepare(&buffer);
        m_Gain.process();
    }

}