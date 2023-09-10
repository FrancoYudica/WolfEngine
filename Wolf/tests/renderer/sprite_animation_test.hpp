#ifndef __WOLF_TEST_SPRITE_ANIMATION_LAYER_
#define __WOLF_TEST_SPRITE_ANIMATION_LAYER_

#include "WEngine.h"
#include <imgui/imgui.h>
#include <vector>

using namespace Wolf;
using namespace Wolf::Rendering;

namespace Tests {
namespace Renderer {
    class SpriteAnimationLayer : public Layer {
    private:
        Wolf::Rendering::Camera _camera;
        Shared<Rendering::Texture> _sprite_sheet;
        Animation::SpriteSheetAnimation _animation;

    public:
        void on_start()
        {
            Wolf::Unique<Window>& window = Application::get()->get_main_window();
            _camera = Wolf::Rendering::Camera(window->get_width(), window->get_height(), 1);

            bool load_success = true;
            auto bitmap = Wolf::Assets::load_bitmap("./Chest.png", load_success);

            RenderCommand::set_blending_mode(BlendMode::Transparent);
            RenderCommand::set_clear_color(0.1, 0.1, 0.1, 1.0);

            TextureConfig texture_config;
            texture_config.mag_filter = TextureTypes::Filter::NEAREST;
            _sprite_sheet = Rendering::Texture::from_bitmap(bitmap, texture_config);

            // Animation setup
            _animation.set_sheet(_sprite_sheet);
            _animation.set_frame_duration(0.1f);
            _animation.set_frames_count(8);
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

            _animation.on_update(delta);

            // Updates camera translation
            float speed = 2.0f * delta.seconds() / _camera.get_zoom();
            glm::vec3 direction(0);
            direction += (float)Wolf::Input::is_key_down(KeyCode::KEY_W) * glm::vec3(0, 1, 0);
            direction += (float)Wolf::Input::is_key_down(KeyCode::KEY_S) * glm::vec3(0, -1, 0);
            direction += (float)Wolf::Input::is_key_down(KeyCode::KEY_D) * glm::vec3(1, 0, 0);
            direction += (float)Wolf::Input::is_key_down(KeyCode::KEY_A) * glm::vec3(-1, 0, 0);

            _camera.set_position(_camera.get_position() + direction * speed);
        }

        void on_ui_render_start()
        {
            ImGui::Begin("Animation");

            static bool repeat = true;
            if (ImGui::Checkbox("Repeat", &repeat)) {
                _animation.set_animation_mode(repeat ? Animation::AnimationMode::Repeat : Animation::AnimationMode::Once);
                _animation.restart();
            }

            if (!repeat) {

                if (ImGui::Button("Restart")) {
                    _animation.restart();
                }

                if (_animation.ended())
                    ImGui::Text("Animation ended");
            }

            static float frame_duration = 0.1f;
            if (ImGui::InputFloat("Frame duration", &frame_duration)) {
                _animation.set_frame_duration(frame_duration);
                _animation.restart();
            }

            ImGui::End();
        }

        void on_render()
        {

            // Renders objects
            Rendering::Renderer2D::begin_scene(_camera);
            Rendering::Renderer2D::new_frame();

            Rendering::Renderer2D::submit_quad(
                glm::vec3(0),
                glm::vec3(1),
                glm::vec4(1),
                _animation.get_texture(),
                _animation.get_bounds());
            Rendering::Renderer2D::end_frame();
        }
    };
}
}
#endif