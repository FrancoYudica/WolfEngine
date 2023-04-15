#pragma once
#ifndef WOLF_WINDOW_H
#define WOLF_WINDOW_H
#include "Event.h"
#include <vector>
#include <iostream>

namespace Wolf
{

    struct WindowUserData
    {
        void* window_ptr;
    };

    class Window
    {

    public:
        struct Configuration
        {
            uint32_t width = 600;
            uint32_t height = 600;
            const char* title = "App";
            bool fullscreen = false;
        };

    public:
        Window() = default;
        bool initialize(Window::Configuration config);
        void* get_native_ptr() const { return _window_ptr; }
        bool should_close();
        void make_context_current();
        void swap_buffers();
        void poll_events();

    private:
        WindowUserData _user_data;
        void* _window_ptr;
    };
}
#endif