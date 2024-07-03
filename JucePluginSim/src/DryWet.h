#ifndef DRYWET_H
#define DRYWET_H

#include "AudioBuffer.h"
#include <cstdint>
#include <cassert>

template<typename SampleType>
    requires std::is_trivial_v<SampleType>
class DryWet 
{
public:
    
    inline SampleType dryLevel() const noexcept { return m_DryLevel; }
    void setDryLevel(SampleType newLevel) noexcept { assert (0 <= newLevel && newLevel <= 100); m_DryLevel = newLevel; }
    void prepare(AudioBuffer<SampleType>* buffer)
    {
        m_Buffer = buffer;
        if (buffer->getNumSamples() != m_DryBuffer.getNumSamples()) {
            AudioBuffer<SampleType> new_DryBuffer {buffer->getNumSamples()};
            AudioBuffer<SampleType> new_WetBuffer {buffer->getNumSamples()};
            m_DryBuffer = std::move(new_DryBuffer);
            m_WetBuffer = std::move(new_WetBuffer);
        }
        assert (m_Buffer);
        
    }
    void process() 
    {
       m_DryBuffer.copyFrom(*m_Buffer);
       m_WetBuffer.copyFrom(*m_Buffer);
       m_WetBuffer.process([*this](SampleType sample){return 0.5f * (1.0 - (m_DryLevel / 100.f)) * sample;}); 
       m_DryBuffer.process([*this](SampleType sample){return (m_DryLevel / 100.f) * sample;}); 
       m_Buffer->copyFrom(m_DryBuffer);
       m_Buffer->addFrom(m_WetBuffer);
       
    }
    
private:
    uint8_t m_DryLevel{100};
    AudioBuffer<SampleType>* m_Buffer{nullptr};
    AudioBuffer<SampleType> m_DryBuffer {2};
    AudioBuffer<SampleType> m_WetBuffer {9};
};

#endif //DRYWET_H