#ifndef DAW_H
#define DAW_H

#include "PulEngine.h"
#include "Observer.h"

#pragma comment(lib, "AudioEngine.lib")
#include <memory>


namespace pul {

    class Daw : public AudioEngine,
                public Broadcaster
    {
    public:
        void run() override;

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
        /**
         * @brief m_Listeners MUST precede declaration of m_Processors,
         *        otherwise the destruction will take place in the incorrect order...
         */
        std::vector<Listener*> m_Listeners;   
          
        /**
         * @brief 
         */
        float m_Volume{ 0.f };

        /**
         * @brief Implementing the notify function of the Broadcaster interface.
         *        Sends a notification to all registered listeners.
         * @param msg: The message to be sent along with a reference to the broadcaster.
         */
        void notify(std::string_view msg) const override;

        /**
         * @brief Simulating the play functionality of a daw (e.g. loading audio buffers and sending
         *        them to registered processors for processing.
         */
        void play();
    };
}

#endif //DAW_H