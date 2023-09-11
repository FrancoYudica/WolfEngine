#ifndef __WOLF_TEST_CHARACTER_CONTROLLER__
#define __WOLF_TEST_CHARACTER_CONTROLLER__

#include "WEngine.h"
#include <imgui/imgui.h>
#include <vector>
#include "character.hpp"

using namespace Wolf;
using namespace Wolf::Rendering;

namespace Tests {

class CharacterControllerLayer : public Layer {
private:
    Wolf::Rendering::Camera _camera;
    Character _character;

public:
    void on_start()
    {
        Wolf::Unique<Window>& window = Application::get()->get_main_window();
        _camera = Wolf::Rendering::Camera(window->get_width(), window->get_height(), 1);

        RenderCommand::set_blending_mode(BlendMode::Transparent);
        RenderCommand::set_clear_color(0.1, 0.1, 0.1, 1.0);

        _character.change_state<CharacterIdleState>();
    }

    void on_event(const Unique<Event>& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowResizeEvent>(
            EventType::WindowResize,
            [this](const Unique<WindowResizeEvent>& resize_event) {
                _camera.on_viewport_resize(resize_event->width, resize_event->height);
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
        _character.on_update(delta);

        // Updates camera translation
        glm::vec3 offset = _character.position - _camera.get_position();
        _camera.set_position(_camera.get_position() + offset * (0.30f * delta));
    }

    void on_ui_render_start()
    {
        ImGui::Begin("Animation");

        ImGui::End();
    }

    void on_render()
    {

        // Renders objects
        Renderer2D::begin_scene(_camera);
        Renderer2D::new_frame();

        float size = 0.5f;
        Renderer2D::submit_quad(
            _character.position + glm::vec3(0, size, 0),
            glm::vec3(_character.velocity.x > 0 ? size : -size, size, size),
            glm::vec4(1),
            _character.animation->get_texture(),
            _character.animation->get_bounds());

        Renderer2D::submit_quad(
            glm::vec3(0.0f, -10.0f, 0.0f),
            glm::vec3(3, 10, 3),
            glm::vec4(.2f));

        Renderer2D::end_frame();
    }
};
}
#endif