#ifndef DAW_H
#define DAW_H

#include <vector>
#include "AudioProcessor.h"
#include <memory>
#include "Observer.h"



namespace pul {

    using ProcVector = std::vector<std::unique_ptr<AudioProcessor>>;

    class Daw : public Broadcaster
    {
    public:
        Daw();
        void run();

        /**
        * @brief Registers a pointer to a Listener instance,
        *        which will receive notifications through the notify() method.
        * @param listener: Raw pointer to Listener object. Must have a lifetime at least as long as the Broadcaster,
        *        or be deregistered upon destruction.
        */
        virtual void registerListener(Listener* listener) override;

        virtual void deregisterListener(Listener* listener) override;
        inline float getVolume() const { return m_Volume; }
        void setVolume(float newVolume);

    private:
        // m_Listeners MUST precede declaration of m_Processors, 
        // otherwise the destruction will take place in the incorrect order...
        std::vector<Listener*> m_Listeners;   
        
        // m_Processors is destructed before m_Listeners. 
        // The processors are called in sequence, which will in turn 
        // deregister the registered processors as listeners, before m_Listeners is destroyed.
        ProcVector m_Processors; 
                
        float m_Volume{ 0.f };
        ProcVector getProcessors();
        void notify(std::string_view msg) const override;
        void play();
    };
}

#endif //DAW_H