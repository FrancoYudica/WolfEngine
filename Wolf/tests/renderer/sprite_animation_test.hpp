#ifndef __WOLF_TEST_SPRITE_ANIMATION_LAYER_
#define __WOLF_TEST_SPRITE_ANIMATION_LAYER_

#include "WEngine.h"
#include <imgui/imgui.h>
#include <vector>

using namespace Wolf;
using namespace Wolf::Rendering;

namespace Tests {
namespace Renderer {

    struct AnimationData {
        Path::FilePath path;
        uint32_t width;
        uint32_t height;
    };

    class SpriteAnimationLayer : public Layer {
    private:
        Wolf::Rendering::Camera _camera;
        std::vector<Animation::SpriteSheetAnimation> _animations;

    public:
        void on_start()
        {
            Wolf::Unique<Window>& window = Application::get()->get_main_window();
            _camera = Wolf::Rendering::Camera(window->get_width(), window->get_height(), 1);

            Path::FilePath assets_path = Path::get_engine_assets_folder();
            assets_path /= "tests/animated_character";

            std::array<AnimationData, 9> anim_data = {
                AnimationData { assets_path / "Player Death 64x64.png", 64, 64 },
                AnimationData { assets_path / "Player Hurt 48x48.png", 48, 48 },
                AnimationData { assets_path / "Player Punch 64x64.png", 64, 64 },
                AnimationData { assets_path / "Player push idle 48x48.png", 48, 48 },
                AnimationData { assets_path / "Player sword atk 64x64.png", 64, 64 },
                AnimationData { assets_path / "Player Sword Idle 48x48.png", 48, 48 },
                AnimationData { assets_path / "Player Sword Run 48x48.png", 48, 48 },
                AnimationData { assets_path / "Player Sword Stab 96x48.png", 96, 48 },
                AnimationData { assets_path / "PlayerWalk 48x48.png", 48, 48 }
            };

            TextureConfig texture_config;
            texture_config.mag_filter = TextureTypes::Filter::NEAREST;

            for (const AnimationData& data : anim_data) {

                bool load_success = true;
                auto bitmap = Wolf::Assets::load_bitmap(data.path, load_success);
                int frames_count = bitmap->width / data.width;
                Shared<Texture> sheet = Rendering::Texture::from_bitmap(bitmap, texture_config);
                // Animation setup
                Animation::SpriteSheetAnimation animation;
                animation.set_sheet(sheet);
                animation.set_frame_duration(0.1f);
                animation.set_frames_count(frames_count);
                _animations.push_back(animation);
            }
            RenderCommand::set_blending_mode(BlendMode::Transparent);
            RenderCommand::set_clear_color(0.1, 0.1, 0.1, 1.0);
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

            for (auto& animation : _animations)
                animation.on_update(delta);

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
                for (auto& animation : _animations) {
                    animation.set_animation_mode(repeat ? Animation::AnimationMode::Repeat : Animation::AnimationMode::Once);
                    animation.restart();
                }
            }

            if (!repeat) {

                if (ImGui::Button("Restart")) {
                    for (auto& animation : _animations) {
                        animation.restart();
                    }
                }
            }

            static float frame_duration = 0.1f;
            if (ImGui::InputFloat("Frame duration", &frame_duration)) {
                for (auto& animation : _animations) {
                    animation.set_frame_duration(frame_duration);
                    animation.restart();
                }
            }
            ImGui::End();
        }

        void on_render()
        {

            // Renders objects
            Rendering::Renderer2D::begin_scene(_camera);
            Rendering::Renderer2D::new_frame();

            int i = 0;
            for (auto& animation : _animations) {
                Rendering::Renderer2D::submit_quad(
                    glm::vec3(i++, 0, 0),
                    glm::vec3(0.5f),
                    glm::vec4(1),
                    animation.get_texture(),
                    animation.get_bounds());
            }
            Rendering::Renderer2D::end_frame();
        }
    };
}
}
#endif