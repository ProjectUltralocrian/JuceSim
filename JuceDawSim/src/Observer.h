#ifndef OBSERVER_H
#define OBSERVER_H

#include <memory>
#include <string>

struct Listener;

struct Broadcaster
{
    virtual ~Broadcaster() = default;

	/**
    * @brief Interface for registering a pointer to a Listener instance, 
    *        which will receive notifications through the notify() method. 
             Must be implemented by subclass.
    * @param listener: Raw pointer to Listener object. Must have a lifetime at least as long as the Broadcaster,
    *        or be deregistered upon destruction.
    */
    virtual void registerListener(Listener* listener) = 0;

    /**
    * @brief Interface for degistering a previously registered Listener instance. Must be implemented by subclass.
    * @param listener: Raw pointer to the registered Listener object.
    */
    virtual void deregisterListener(Listener* listener) = 0;

    /**
    * @brief Interface for sending a notification to registered listeners. Must be implemented by subclass.
    * @param msg: Message to be sent in the notification.
    */
    virtual void notify(std::string_view msg) const = 0;
};

struct Listener
{
    virtual ~Listener() = default;

    /**
    * @brief Interface for callback function which will be called by registered listener. 
    *        Must be implemented by subclass.
    * @param broadcaster: A reference to the broadcaster sending the notification.
    * @param msg: received by listener from broadcaster in the notification.
    */
    virtual void onNotified(const Broadcaster& broadcaster, std::string_view msg) = 0;
};


#endif //OBSERVER_H