#pragma once
#include "AudioEngine.h"
#include <memory>

namespace pul {
class CTransformer : public AudioProcessor
    {
    public:
        CTransformer(AudioEngine& engine);
        ~CTransformer();
        std::string_view getName() const override;
        void prepareToPlay() override;
        void processBlock(AudioBuffer<float>& buffer) override;
    private:
        struct ProcessorImpl;
        std::unique_ptr<ProcessorImpl> m_Impl;
        AudioEngine& m_Engine;

    };
}