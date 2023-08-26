#ifndef __WOLF_TEST_BATCH_LAYER__
#define __WOLF_TEST_BATCH_LAYER__

#include "WEngine.h"
#include <imgui/imgui.h>
#include <unordered_map>
#include <vector>

namespace Tests {
namespace Renderer {
    using namespace Wolf;
    class BatchLayer : public Layer {
    private:
        Wolf::Rendering::Camera _camera;
        Wolf::Rendering::Camera _debug_camera;
        Shared<Wolf::Rendering::Texture> _texture;
        std::vector<glm::vec3> _points;

    public:
        void on_start()
        {
            Rendering::Renderer2D::init();

            Wolf::Unique<Window>& window = Application::get()->get_main_window();
            _camera = Wolf::Rendering::Camera(window->get_width(), window->get_height(), 1);
            _debug_camera = Wolf::Rendering::Camera(window->get_width(), window->get_height(), 1);
            _points.reserve(1000);

            for (uint32_t i = 0; i < 1000; i++) {
                float x = Wolf::Numerical::Random::range_f(-2, 2);
                float y = Wolf::Numerical::Random::range_f(-2, 2);
                _points.emplace_back(glm::vec3(x, y, 0));
            }

            std::cout << "Layer started" << std::endl;
        }

        void on_event(const Unique<Event>& event)
        {
            EventDispatcher dispatcher(event);
            dispatcher.dispatch<WindowResizeEvent>(
                EventType::WindowResize,
                [this](const Unique<WindowResizeEvent>& resize_event) {
                    _camera.on_viewport_resize(resize_event->width, resize_event->height);
                    _debug_camera.on_viewport_resize(resize_event->width, resize_event->height);
                    return false;
                });

            dispatcher.dispatch<MouseScrollEvent>(
                EventType::MouseScroll,
                [this](const Unique<MouseScrollEvent>& scroll) {
                    float zoom_ratio = 0.25f;

                    float zoom = _camera.get_zoom();
                    float offset = _camera.get_zoom() * zoom_ratio * scroll->y_offset;
                    _camera.set_zoom(zoom + offset);
                    return false;
                });
        }

        void on_update(const Time& delta)
        {

            // Updates camera translation
            float speed = 2.0f * delta.seconds() / _camera.get_zoom();
            glm::vec3 direction(0);
            direction += (float)Wolf::Input::is_key_down(KeyCode::KEY_W) * glm::vec3(0, 1, 0);
            direction += (float)Wolf::Input::is_key_down(KeyCode::KEY_S) * glm::vec3(0, -1, 0);
            direction += (float)Wolf::Input::is_key_down(KeyCode::KEY_D) * glm::vec3(1, 0, 0);
            direction += (float)Wolf::Input::is_key_down(KeyCode::KEY_A) * glm::vec3(-1, 0, 0);

            _camera.set_position(_camera.get_position() + direction * speed);
        }

        void on_render()
        {

            // Renders objects
            Rendering::Renderer2D::begin_scene(_camera);
            Rendering::Renderer2D::new_frame();

            auto size = glm::vec3(0.01f);
            auto color = glm::vec4(1.0f);

            for (glm::vec3& point : _points) {
                Rendering::Renderer2D::submit_circle(point, 0.05f, color);
            }

            for (uint32_t i = 0; i < _points.size() - 1; i++) {
                Rendering::Renderer2D::submit_line(_points[i], _points[i + 1], glm::vec4(1, 1, 1, 1), 0.0005);
            }
            Rendering::Renderer2D::end_frame();

            // Debug rendering
            Rendering::Renderer2D::begin_scene(_debug_camera);
            Rendering::Renderer2D::new_frame();

            float radius = 0.2;
            glm::vec3 center = { 0.5, 0.5, 0 };
            for (uint32_t i = 0; i < 100; i++) {
                float angle = 2 * 3.14159265358979 * static_cast<float>(i) / 100;
                Rendering::Renderer2D::submit_line_interpolated(center, center + glm::vec3(std::cos(angle), std::sin(angle), 0), glm::vec4(1, 0, 1, 1), 0.005);
            }

            Rendering::Renderer2D::end_frame();
        }
    };
}
}
#endif