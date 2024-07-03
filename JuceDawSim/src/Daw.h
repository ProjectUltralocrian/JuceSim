#ifndef DAW_H
#define DAW_H

#include <vector>
#include "AudioProcessor.h"
#include <memory>
#include "Observer.h"

using ProcVector = std::vector<std::unique_ptr<AudioProcessor>>;

class NotImplementedException : public std::logic_error
{
public:
    NotImplementedException() : std::logic_error("Function not yet implemented") { };
};

class Daw : public Broadcaster
{
public:
    Daw();
    void run();
    virtual void registerListener(Listener* listener) override;
    virtual void deregisterListener(Listener* listener) override;
    inline float getVolume() const { return m_Volume; }
    void setVolume(float newVolume);
private:
    void play();
    std::vector<Listener*> m_Listeners;   //this MUST precede declaration of m_Processors, otherwise the destruction will take place in the incorrect order...
    ProcVector m_Processors;
    float m_Volume {0.f};
    ProcVector getProcessors();
    void notify(std::string_view msg) const override;
    
};


#endif //DAW_H