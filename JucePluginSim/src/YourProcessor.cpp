#include "YourProcessor.h"
#include <iostream>


YourProcessor::YourProcessor(Daw& daw)
    : m_Daw{daw}
{
    
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
    std::cout << "Processing YourProcessor...\n";
    m_DryWet.prepare(&buffer);
    m_DryWet.process();
    
    buffer.getWritePointer()[2] = -42.42;
}