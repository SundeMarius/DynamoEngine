#pragma once

#include "DynamoEngine/src/exceptions/exceptions.hpp"

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

class RegisteringEventError : public FatalException
{
public:
    RegisteringEventError(int eventId)
        : FatalException("Could not register event with id \"" + std::to_string(eventId) + "\"") {}
};

class UndefinedEventError : public WarningException
{
public:
    UndefinedEventError(int eventId)
        : WarningException("No event with id \"" + std::to_string(eventId) + "\"") {}
};
