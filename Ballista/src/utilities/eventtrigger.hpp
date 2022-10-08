#pragma once

#include <SDL2/SDL.h>

#include <unordered_map>
#include <stdexcept>
#include <string>

class EventTrigger
{
public:
    void RegisterEvent(int eventId);
    void TriggerEvent(int eventId) const;
    Uint32 GetEventType(int eventId) const;

private:
    std::unordered_map<int, Uint32> registeredEvents{};
};

class RegisteringEventError : std::runtime_error
{
public:
    RegisteringEventError(int eventId)
        : std::runtime_error("Could not register event with id \"" + std::to_string(eventId) + "\"") {}
};

class UndefinedEventError : std::out_of_range
{
public:
    UndefinedEventError(int eventId)
        : std::out_of_range("No event with id \"" + std::to_string(eventId) + "\"") {}
};
