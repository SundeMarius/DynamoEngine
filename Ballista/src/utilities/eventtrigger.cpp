#include "eventtrigger.hpp"

void EventTrigger::RegisterEvent(int eventId)
{
    Uint32 event = SDL_RegisterEvents(1);
    if (event == UINT32_MAX)
        throw RegisteringEventError(eventId);
    registeredEvents.emplace(eventId, event);
}

void EventTrigger::TriggerEvent(int eventId) const
{
    try
    {
        SDL_Event event;
        event.type = registeredEvents.at(eventId);
        SDL_PushEvent(&event);
    }
    catch (const std::out_of_range &e)
    {
        throw UndefinedEventError(eventId);
    }
}

Uint32 EventTrigger::GetEventType(int eventId) const
{
    try
    {
        return registeredEvents.at(eventId);
    }
    catch (const std::out_of_range &e)
    {
        throw UndefinedEventError(eventId);
    }
}
