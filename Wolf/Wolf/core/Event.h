#pragma once
#ifndef __WOLF_EVENT__
#define __WOLF_EVENT__
#include "codes.h"
#include "wolf_types.h"
#include <iostream>
#include <memory>

namespace Wolf {
enum EventType {
    MouseMove,
    MouseScroll,
    WindowClose,
    WindowResize,
    ButtonDown,
    ButtonUp,
    KeyUp,
    KeyDown
};

enum EventCategory {
    CategoryInput = 1,
    CategoryApplication = 2,
    CategoryKeyboard = 4,
    CategoryMouseMove = 8,
    CategoryMouseButton = 16
};

class Event {
public:
    bool handled = false;
    EventType type;
    uint32_t category;
    Event(EventType type, uint32_t category)
        : type(type)
        , category(category)
    {
    }
    virtual ~Event() = default;
    virtual void display()
    {
        std::cout << "Event(" << type << ")" << std::endl;
    }
};

class MouseMoveEvent : public Event {
public:
    const double x, y;
    MouseMoveEvent() = default;
    MouseMoveEvent(double xPos, double yPos)
        : Event(
            EventType::MouseMove,
            EventCategory::CategoryInput | EventCategory::CategoryMouseMove)
        , x(xPos)
        , y(yPos)
    {
    }
};

class MouseScrollEvent : public Event {
public:
    const double x_offset, y_offset;
    MouseScrollEvent(double x, double y)
        : Event(
            EventType::MouseScroll,
            EventCategory::CategoryInput | EventCategory::CategoryMouseButton)
        , x_offset(x)
        , y_offset(y)
    {
    }
};

class WindowResizeEvent : public Event {
public:
    const int width, height;
    WindowResizeEvent() = default;
    WindowResizeEvent(int w, int h)
        : Event(
            EventType::WindowResize,
            EventCategory::CategoryApplication)
        , width(w)
        , height(h)
    {
    }
};

class WindowClosedEvent : public Event {
public:
    void* window_ptr;
    WindowClosedEvent() = default;
    WindowClosedEvent(void* window)
        : Event(
            EventType::WindowClose,
            EventCategory::CategoryApplication)
        , window_ptr(window)
    {
    }
};

class ButtonDownEvent : public Event {
public:
    const MouseButton button;
    ButtonDownEvent() = default;
    ButtonDownEvent(MouseButton button, int mods)
        : Event(
            EventType::ButtonDown,
            EventCategory::CategoryInput | EventCategory::CategoryMouseButton)
        , button(button)
        , _mods(mods)
    {
    }
    bool is_mod(ActionModifier mod) { return mod & _mods; }

private:
    const int _mods;
};

class ButtonUpEvent : public Event {
public:
    const MouseButton button;
    ButtonUpEvent() = default;
    ButtonUpEvent(MouseButton button, int mods)
        : Event(
            EventType::ButtonUp,
            EventCategory::CategoryInput | EventCategory::CategoryMouseButton)
        , button(button)
        , _mods(mods)
    {
    }
    bool is_mod(ActionModifier mod) { return mod & _mods; }

private:
    const int _mods;
};

class KeyDownEvent : public Event {
public:
    const KeyCode key;
    KeyDownEvent() = default;
    KeyDownEvent(KeyCode key, int mods)
        : Event(
            EventType::KeyDown,
            EventCategory::CategoryInput | EventCategory::CategoryKeyboard)
        , key(key)
        , _mods(mods)
    {
    }
    inline bool is_mod(ActionModifier mod) { return mod & _mods; }

private:
    const int _mods;
};

class KeyUpEvent : public Event {
public:
    const KeyCode key;
    KeyUpEvent() = default;
    KeyUpEvent(KeyCode key, int mods)
        : Event(
            EventType::KeyUp,
            EventCategory::CategoryInput | EventCategory::CategoryKeyboard)
        , key(key)
        , _mods(mods)
    {
    }
    inline bool is_mod(ActionModifier mod) { return mod & _mods; }

private:
    const int _mods;
};

typedef bool EventProcessor(Event e);
class EventDispatcher {
public:
    EventDispatcher(const Unique<Event>& event)
        : _event(event)
    {
    }
    template <typename EventTypeName, typename F>
    bool dispatch(EventType type, const F& func)
    {
        if (_event->handled)
            return true;

        if (type == _event->type) {
            // Creates a unique pointer of the provided type
            EventTypeName* tmp = dynamic_cast<EventTypeName*>(_event.get());
            Unique<EventTypeName> new_unique;
            new_unique.reset(tmp);

            // Calls function
            _event->handled = func(new_unique);

            // Memory shouldn't be deleted here, it's done where it's created
            new_unique.release();
        }
        return _event->handled;
    }

private:
    const Unique<Event>& _event;
};
}
#endif