#ifndef AUDIOBUFFER_H
#define AUDIOBUFFER_H


#include "Helpers.h"
#include <concepts>
#include <algorithm>
#include <iostream>
#include <span>
#include <functional>


namespace pul {

    template<typename SampleType>
        requires std::is_trivial_v<SampleType>
    class AudioBuffer
    {
    public:
        AudioBuffer(size_t size) : m_BufSize{ size }, m_Buffer{ new SampleType[size] } {}

        AudioBuffer(size_t size, std::span<SampleType> rhs)
            : AudioBuffer(size)
        {
            ASSERT(size == rhs.size());
            std::memcpy(m_Buffer, rhs.data(), size * sizeof(SampleType));
        }

        AudioBuffer(const AudioBuffer& rhs) noexcept
            : m_BufSize{ rhs.m_BufSize }, m_Buffer(new SampleType[rhs.m_BufSize])
        {
            std::memcpy(m_Buffer, rhs.m_Buffer, m_BufSize * sizeof(SampleType));
        }

        AudioBuffer& operator=(const AudioBuffer& rhs) noexcept
        {
            ASSERT(&rhs != this && rhs.m_BufSize == m_BufSize && rhs.m_Buffer);
            if (!m_Buffer) {
                m_Buffer = new SampleType[m_BufSize];
            }
            std::memcpy(m_Buffer, rhs.m_Buffer, m_BufSize * sizeof(SampleType));
            return *this;
        }

        AudioBuffer(AudioBuffer&& rhs) noexcept
            : m_BufSize{ rhs.m_BufSize }
        {
            m_Buffer = rhs.m_Buffer;
            rhs.m_Buffer = nullptr;
        }

        AudioBuffer& operator= (AudioBuffer&& rhs) noexcept
        {
            delete[] m_Buffer;
            m_Buffer = rhs.m_Buffer;
            m_BufSize = rhs.m_BufSize;
            rhs.m_Buffer = nullptr;
            return *this;
        }

        ~AudioBuffer()
        {
            delete[] m_Buffer;
        } 

        using ProcessFunc = std::function<SampleType(SampleType)>;
        void process(const ProcessFunc& func)
        {
            for (size_t i = 0; i < m_BufSize; ++i) {
                m_Buffer[i] = func(m_Buffer[i]);
            }
        }

        void fillWith(SampleType value)
        {
            auto v = value;
            process([=](SampleType x) {return v; });
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
            return m_BufSize;
        }

        void copyFrom(AudioBuffer& other)
        {
            ASSERT(m_BufSize == other.m_BufSize && m_Buffer != other.m_Buffer);
            ASSERT(m_Buffer && other.m_Buffer);
            *this = other;
        }

        void addFrom(AudioBuffer& other)
        {
            ASSERT(m_BufSize == other.m_BufSize);
            for (size_t i = 0; i < m_BufSize; ++i) {
                m_Buffer[i] += other.m_Buffer[i];
            }
        }

        void print() const
        {
            for (size_t i = 0; i < m_BufSize; ++i) {
                std::cout << m_Buffer[i] << std::endl;
            }
        }

    private:
        size_t m_BufSize{ 5 };
        SampleType* m_Buffer;
    };

}

#endif //AUDIOBUFFER_H