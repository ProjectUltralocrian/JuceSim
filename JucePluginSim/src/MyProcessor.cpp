#include "MyProcessor.h"
#include <iostream>


namespace pul {

    MyProcessor::MyProcessor(Daw& daw)
        : m_Daw{ daw }
    {
        m_Daw.registerListener(this);
    }

    MyProcessor::~MyProcessor()
    {
        m_Daw.deregisterListener(this);
    }

    void MyProcessor::onNotified(const Broadcaster& broadcaster, std::string_view msg)
    {
        std::cout << msg << std::endl;
        if (const auto* daw = dynamic_cast<const Daw*>(&broadcaster)) {
            m_LevelDb = daw->getVolume();
            std::cout << "DAW volume: " << daw->getVolume() << std::endl;
            m_Gain.changeLevelByDb(m_LevelDb);
            std::cout << "m_Gain level: " << m_Gain.level() << std::endl;
        }
        else {
            std::cout << "Not daw...\n";
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