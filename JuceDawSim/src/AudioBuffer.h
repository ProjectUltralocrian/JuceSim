#ifndef AUDIOBUFFER_H
#define AUDIOBUFFER_H

#include <iosfwd>
#include <concepts>
#include <cassert>
#include <algorithm>
#include <cstring>
#include <iostream>

template<typename SampleType>
    requires std::is_trivial_v<SampleType>
class AudioBuffer
{
public:
    
    //AudioBuffer() : m_Buffer{ new SampleType[BUFSIZE] } {}
    AudioBuffer(size_t size) : BUFSIZE{size}, m_Buffer{ new SampleType[size] } {}
    AudioBuffer(const AudioBuffer& rhs) noexcept
        : BUFSIZE{rhs.BUFSIZE}, m_Buffer(new SampleType[rhs.BUFSIZE])
    {
        std::memcpy(m_Buffer, rhs.m_Buffer, BUFSIZE * sizeof(SampleType));
    }
    AudioBuffer& operator=(const AudioBuffer& rhs) noexcept
    {
        assert (&rhs != this && rhs.BUFSIZE == BUFSIZE && rhs.m_Buffer);
        if (!m_Buffer) {
            m_Buffer = new SampleType[BUFSIZE];
        }
        std::memcpy(m_Buffer, rhs.m_Buffer, BUFSIZE * sizeof(SampleType));
        return *this;
    }
    AudioBuffer(AudioBuffer&& rhs) noexcept
        : BUFSIZE{rhs.BUFSIZE}
    {
        m_Buffer = rhs.m_Buffer;
        rhs.m_Buffer = nullptr;
    }
    AudioBuffer& operator= (AudioBuffer&& rhs) noexcept
    {
        delete[] m_Buffer;
        m_Buffer = rhs.m_Buffer;
        BUFSIZE = rhs.BUFSIZE;
        rhs.m_Buffer = nullptr;
        return *this;
    }
    
    ~AudioBuffer() 
    {
        delete[] m_Buffer;
    }
    
    template<typename ProcessFunc>
    void process(ProcessFunc func)
    {
        for (size_t i = 0; i < BUFSIZE; ++i) {
            m_Buffer[i] = func(m_Buffer[i]);
        }
    }
    void fill_with(SampleType value)
    {
        auto v = value;
        process([=](SampleType x){return v;});
    }
    const SampleType* getReadPointer() const
    {
        return m_Buffer;
    }
    SampleType* getWritePointer()
    {
        return m_Buffer;
    }
    inline constexpr size_t getNumSamples() const noexcept
    {
        return BUFSIZE;
    }
    void copyFrom(AudioBuffer& other)
    {
        assert(BUFSIZE == other.BUFSIZE && m_Buffer != other.m_Buffer);
        assert(m_Buffer && other.m_Buffer);
        *this = other;
    }
    void addFrom(AudioBuffer& other)
    {
        assert(BUFSIZE == other.BUFSIZE);
        for (size_t i = 0; i < BUFSIZE; ++i) {
            m_Buffer[i] += other.m_Buffer[i];
        }
    }
    void print() const 
    {
        for (size_t i = 0; i < BUFSIZE; ++i) {
            std::cout << m_Buffer[i] << std::endl;
        }
    }
private:
    size_t BUFSIZE{5};
    SampleType* m_Buffer;
};


#endif //AUDIOBUFFER_H