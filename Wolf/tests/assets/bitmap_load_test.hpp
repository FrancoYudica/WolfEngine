#ifndef __WOLF_TEST_TEXTURE_LOAD__
#define __WOLF_TEST_TEXTURE_LOAD__

#include "WEngine.h"
#include <imgui/imgui.h>
#include <unordered_map>
#include <vector>

namespace Tests {
namespace Assets {
    using namespace Wolf;
    class BitmapLoadTestLayer : public Layer {
    private:
        Wolf::Rendering::Camera _camera;

        Shared<Wolf::Rendering::Texture> texture_png;
        Shared<Wolf::Rendering::Texture> texture_jpg;

    public:
        void on_start()
        {

            // Camera initialization
            Wolf::Unique<Window>& window = Application::get()->get_main_window();
            _camera = Wolf::Rendering::Camera(window->get_width(), window->get_height(), 1);

            // Loads bitmap from disk
            bool success;
            auto bitmap_png = Wolf::Assets::load_bitmap("test_png.png", success);
            auto bitmap_jpg = Wolf::Assets::load_bitmap("test_jpg.jpg", success);
            Rendering::TextureConfig config;
            config.internal_pixel_format = Rendering::TextureTypes::PixelInternalFormat::RGBA_8;
            config.pixel_format = Rendering::TextureTypes::PixelFormat::RGBA;
            config.pixel_type = Rendering::TextureTypes::PixelType::UNSIGNED_BYTE;
            config.mag_filter = Rendering::TextureTypes::Filter::NEAREST;
            texture_png = Rendering::Texture::from_bitmap(bitmap_png, config);
            texture_jpg = Rendering::Texture::from_bitmap(bitmap_jpg, config);
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
        }

        void on_ui_render_start()
        {
            ImGui::Begin("Test");
            ImGui::End();
        }

        void on_update(const Time& delta)
        {
        }
        void on_render()
        {

            // Renders objects
            Rendering::Renderer2D::begin_scene(_camera);
            Rendering::Renderer2D::new_frame();
            glm::vec3 size = glm::vec3(0.5f);
            Rendering::Renderer2D::submit_quad(
                -size,
                size,
                { 1.0, 1.0, 1.0, 1.0 },
                texture_png);
            Rendering::Renderer2D::submit_quad(
                size,
                size,
                { 1.0, 1.0, 1.0, 1.0 },
                texture_jpg);

            Rendering::Renderer2D::end_frame();
        }
    };
}
}
#endif