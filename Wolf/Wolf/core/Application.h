#pragma once
#ifndef __WOLF_APPLICATION__
#define __WOLF_APPLICATION__

#include "GraphicsContext.h"
#include "Layer.h"
#include "Time.h"
#include "Window.h"
#include <memory>

namespace Wolf {
class Application {

public:
    Application()
    {
        _clock = Clock();
        _layer_stack = LayerStack();
    }
    bool initialize(const Window::Configuration& config);
    void run();
    void on_event(const Unique<Event>& event);
    void on_update(const Time& time);
    void on_render();
    void add_layer(const Shared<Layer>& layer) { _layer_stack.add(layer); }
    void set_imgui_layer(const Shared<Layer>& layer)
    {
        _imgui_layer = layer;
        _layer_stack.add_overlay(layer);
    }
    bool remove_layer(const Shared<Layer>& layer) { return _layer_stack.remove(layer); }
    void add_overlay(const Shared<Layer>& layer) { _layer_stack.add_overlay(layer); }
    Unique<Window>& get_main_window() { return _main_window; }
    void quit();

    inline static Unique<Application>& get()
    {
        static Unique<Application> application;
        if (application)
            return application;

        application = std::make_unique<Application>();
        return application;
    }

    inline const Time& get_update_time() { return _update_time; }
    inline const Time& get_render_time() { return _render_time; }

private:
    static Application* _instance;
    Unique<Window> _main_window;
    LayerStack _layer_stack;
    Clock _clock;
    Time _render_time;
    Time _update_time;
    Shared<Layer> _imgui_layer;
    Shared<GraphicsContext> _graphics_context;
};
}
#endif
