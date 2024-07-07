#include "YourProcessor.h"
#include <iostream>


namespace pul {

    YourProcessor::YourProcessor(Daw& daw)
        : m_Daw{ daw } 
    {
        m_Daw.registerAudioProcessor(this);
    }


    void YourProcessor::prepareToPlay()
    {
        std::cout << "Preparing YourProcessor...\n";

        //simulating retrieving audio parameters (e.g. from GUI)
        //and setting the state of the plugin prior to processing.
        m_DryLevel = 50;
        m_DryWet.setDryLevel(m_DryLevel);
    }

    void YourProcessor::processBlock(AudioBuffer<float>& buffer)
    {
        std::cout << "YourProcessor: Processing...\n";
        m_DryWet.prepare(&buffer);
        m_DryWet.process();

        //Demonstrating how to process the buffer by accessing it via a writepointer
        //and simply iterating through them - inverting the phase.
        /*auto samples = buffer.getWritePointer();
        for (size_t i = 0; i < buffer.getNumSamples(); ++i) {
            samples[i] *= -1;
        }*/

        //The same can be done with the process() method...
        buffer.process([](float f) {return -f; });

    }

}