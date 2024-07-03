#ifndef AUDIOPROCESSOR_H
#define AUDIOPROCESSOR_H

#include "AudioBuffer.h"

class AudioProcessor 
{
public:
    virtual void prepareToPlay() = 0;
    virtual void processBlock(AudioBuffer<float>& buffer) = 0;
    virtual ~AudioProcessor() = default;
};



#endif //AUDIOPROCESSOR_H