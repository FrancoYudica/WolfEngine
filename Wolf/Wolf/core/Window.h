#pragma once
#ifndef __WOLF_WINDOW__
#define __WOLF_WINDOW__
#include "Event.h"
#include <iostream>
#include <vector>

namespace Wolf {

struct WindowUserData {
    void* window_ptr;
};

class Window {

public:
    struct Configuration {
        uint32_t width = 700;
        uint32_t height = 700;
        const char* title = "App";
        bool fullscreen = false;
    };

public:
    Window() = default;
    bool initialize(const Window::Configuration& config);
    inline void* get_native_ptr() const { return _window_ptr; }
    bool should_close();
    void make_context_current();
    void swap_buffers();
    void poll_events();
    uint32_t get_width() const;
    uint32_t get_height() const;

private:
    WindowUserData _user_data;
    void* _window_ptr;
};
}
#endif