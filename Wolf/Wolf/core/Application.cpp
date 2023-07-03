#include <iostream>
#include "Application.h"
#include <GLFW/glfw3.h>
#include "../rendering/RenderCommand.h"
#include "../imgui_layer/imgui_layer.h"


namespace Wolf
{

    bool Application::initialize(Window::Configuration config)
    {
        /* Initialize the library */
        if (!glfwInit())
        {
            std::cout << "Unable to initialize glfw lib" << std::endl;
            glfwTerminate();
            return false;
        }
        _main_window = std::make_unique<Window>();
        /* Creates main window */
        if (!_main_window->initialize(config))
        {
            glfwTerminate();
            return false;
        }
        _main_window->make_context_current();

        _graphics_context = GraphicsContext::create(_main_window);
        _graphics_context->init();
        return true;
    }

    void Application::on_event(Event* event)
    {
        // Updates from the overlays to the lowest
        auto layers = _layer_stack.get_layers();

        for (auto it = layers.rbegin(); it != layers.rend(); it++)
        {
            if (event->handled)
                return;
            (*it)->on_event(event);
        }

        EventDispatcher disptacher = EventDispatcher(event);
        disptacher.dispatch<WindowResizeEvent>(
            EventType::WindowResize,

            [this](WindowResizeEvent* event){
                this->_graphics_context->on_viewport_resize(event->width, event->height);
                return false;
            }
        );
    }

    void Application::on_update(const Time& delta)
    {
        // Updates from the lowest layer to the overlays
        for (auto layer : _layer_stack.get_layers())
            layer->on_update(delta);
    }

    void Application::on_render()
    {
        // Renders from the lowest layer to the overlays
        for (auto layer : _layer_stack.get_layers())
            layer->on_render();


        // ImGui rendering
        _imgui_layer->on_ui_render_start();
        for (auto layer : _layer_stack.get_layers())
        {
            if (layer != _imgui_layer)
                layer->on_ui_render_start();
        }
        for (auto layer : _layer_stack.get_layers())
        {
            if (layer != _imgui_layer)
                layer->on_ui_render_finish();
        }
        _imgui_layer->on_ui_render_finish();

    }

    void Application::quit()
    {
        _layer_stack.clear();
        glfwTerminate();
    }

    void Application::run()
    {
        _clock = Clock();
        _clock.start();

        Clock deltaClock, timingClock;
        deltaClock.start();
        while (!_main_window->should_close())
        {
            Time elapsed = deltaClock.elapsed();
            deltaClock.start();

            timingClock.start();
            on_update(elapsed);
            _update_time = timingClock.elapsed();

            timingClock.start();
            Rendering::RenderCommand::clear();
            on_render();
            _main_window->swap_buffers();            
            _render_time = timingClock.elapsed();
            /* Poll for and process events */
            _main_window->poll_events();
        }
    }
}