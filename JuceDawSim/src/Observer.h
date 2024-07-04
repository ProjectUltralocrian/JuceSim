#ifndef OBSERVER_H
#define OBSERVER_H

#include <memory>
#include <string>

struct Listener;

struct Broadcaster
{
    virtual void registerListener(Listener* listener) = 0;
    virtual void deregisterListener(Listener* listener) = 0;
    virtual void notify(std::string_view msg) const = 0;
};

struct Listener
{
    virtual ~Listener() = default;
    virtual void onNotified(const Broadcaster&, std::string_view msg) = 0;
};



#endif //OBSERVER_H