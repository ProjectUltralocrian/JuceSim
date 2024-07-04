#ifndef GAIN_H
#define GAIN_H

#include <cmath>
#include "AudioBuffer.h"

namespace pul {

    template<typename SampleType>
        requires std::is_trivial_v<SampleType>
    class Gain
    {
    public:
        static constexpr SampleType gainToDecibel(SampleType gain)
        {
            return 20 * log10(gain);
        }
        
        static constexpr SampleType decibelToGain(SampleType db)
        {
            return pow(10.f, db / 20.f);
        }

        inline SampleType level() const noexcept { return m_Level; }
        
        inline void setLevel(SampleType newLevel) noexcept { m_Level = newLevel; }
        
        inline void changeLevelBy(SampleType by) noexcept { m_Level *= by; }
        
        inline void changeLevelByDb(SampleType db) noexcept { m_Level *= (decibelToGain(db)); };
        
        void prepare(AudioBuffer<SampleType>* buffer)
        {
            m_Buffer = buffer;
        }

        void process()
        {
            m_Buffer->process([*this](SampleType sample) {return m_Level * sample; });
        }

    private:
        float m_Level{ 1.0f };
        AudioBuffer<SampleType>* m_Buffer{ nullptr };
    };

}

#endif //GAIN_H