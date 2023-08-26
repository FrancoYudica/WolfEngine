#ifndef __WOLF_TEXTURE_TEST__
#define __WOLF_TEXTURE_TEST__
#include "WEngine.h"
#include <imgui/imgui.h>

namespace Tests {
namespace Renderer {
    using namespace Wolf;
    class TextureTestLayer : public Wolf::Layer {
    public:
        Shared<Wolf::Rendering::Texture> texture_rgba_unsigned_byte;
        Shared<Wolf::Rendering::Texture> texture_rgba_float;

        Shared<Wolf::Rendering::Texture> texture_rgb_unsigned_byte;
        Shared<Wolf::Rendering::Texture> texture_rgb_float;

        Shared<Wolf::Rendering::Texture> texture_r_unsigned_byte;
        Shared<Wolf::Rendering::Texture> texture_r_float;

        Shared<Wolf::Rendering::Material> material;

        virtual void on_start() override
        {

            {
                Shared<Rendering::BitMap<glm::vec4>> bitmap = std::make_shared<Rendering::BitMap<glm::vec4>>(3, 3);
                Rendering::TextureConfig texture_config;
                texture_config.mag_filter = Rendering::TextureTypes::Filter::NEAREST;
                texture_config.wrap_mode = Rendering::TextureTypes::WrapMode::CLAMP_TO_EDGE;
                texture_config.pixel_format = Rendering::TextureTypes::PixelFormat::RGBA;
                texture_config.internal_pixel_format = Rendering::TextureTypes::PixelInternalFormat::RGBA_8;
                texture_config.pixel_type = Rendering::TextureTypes::PixelType::FLOAT;

                bitmap->set_pixel({ 0, 0 }, glm::vec4 { 1, 0, 0, 1 });
                bitmap->set_pixel({ 1, 0 }, glm::vec4 { 0, 1, 0, 1 });
                bitmap->set_pixel({ 2, 0 }, glm::vec4 { 0, 0, 1, 1 });
                bitmap->set_pixel({ 0, 1 }, glm::vec4 { 1, 1, 0, 1 });
                bitmap->set_pixel({ 1, 1 }, glm::vec4 { 0, 1, 1, 1 });
                bitmap->set_pixel({ 2, 1 }, glm::vec4 { 1, 1, 1, 1 });
                bitmap->set_pixel({ 0, 2 }, glm::vec4 { 1, 1, 1, 1 });
                bitmap->set_pixel({ 1, 2 }, glm::vec4 { 1, 1, 1, 1 });
                bitmap->set_pixel({ 2, 2 }, glm::vec4 { 1, 1, 1, 1 });
                texture_rgba_float = Wolf::Rendering::Texture::from_bitmap(bitmap, texture_config);
            }
            {
                Shared<Rendering::BitMap<glm::vec3>> bitmap = std::make_shared<Rendering::BitMap<glm::vec3>>(3, 3);
                Rendering::TextureConfig texture_config;
                texture_config.mag_filter = Rendering::TextureTypes::Filter::NEAREST;
                texture_config.wrap_mode = Rendering::TextureTypes::WrapMode::CLAMP_TO_EDGE;
                texture_config.pixel_format = Rendering::TextureTypes::PixelFormat::RGB;
                texture_config.internal_pixel_format = Rendering::TextureTypes::PixelInternalFormat::RGB_8;
                texture_config.pixel_type = Rendering::TextureTypes::PixelType::FLOAT;

                bitmap->set_pixel({ 0, 0 }, glm::vec3 { 1, 0, 0 });
                bitmap->set_pixel({ 1, 0 }, glm::vec3 { 0, 1, 0 });
                bitmap->set_pixel({ 2, 0 }, glm::vec3 { 0, 0, 1 });
                bitmap->set_pixel({ 0, 1 }, glm::vec3 { 1, 1, 0 });
                bitmap->set_pixel({ 1, 1 }, glm::vec3 { 0, 1, 1 });
                bitmap->set_pixel({ 2, 1 }, glm::vec3 { 1, 1, 1 });
                bitmap->set_pixel({ 0, 2 }, glm::vec3 { 1, 1, 1 });
                bitmap->set_pixel({ 1, 2 }, glm::vec3 { 1, 1, 1 });
                bitmap->set_pixel({ 2, 2 }, glm::vec3 { 1, 1, 1 });

                texture_rgb_float = Wolf::Rendering::Texture::from_bitmap(bitmap, texture_config);
            }
            {
                // Creates simple bitmap
                Shared<Wolf::Rendering::BitMap<glm::u8vec4>> bitmap = std::make_shared<Wolf::Rendering::BitMap<glm::u8vec4>>(3, 3);
                Rendering::TextureConfig texture_config;
                texture_config.mag_filter = Rendering::TextureTypes::Filter::NEAREST;
                texture_config.wrap_mode = Rendering::TextureTypes::WrapMode::CLAMP_TO_EDGE;
                texture_config.pixel_format = Rendering::TextureTypes::PixelFormat::RGBA;
                texture_config.internal_pixel_format = Rendering::TextureTypes::PixelInternalFormat::RGBA_8;
                texture_config.pixel_type = Rendering::TextureTypes::PixelType::UNSIGNED_BYTE;

                bitmap->set_pixel({ 0, 0 }, glm::u8vec4 { 255, 0, 0, 255 });
                bitmap->set_pixel({ 1, 0 }, glm::u8vec4 { 0, 255, 0, 255 });
                bitmap->set_pixel({ 2, 0 }, glm::u8vec4 { 0, 0, 255, 255 });
                bitmap->set_pixel({ 0, 1 }, glm::u8vec4 { 255, 255, 0, 255 });
                bitmap->set_pixel({ 1, 1 }, glm::u8vec4 { 0, 255, 255, 255 });
                bitmap->set_pixel({ 2, 1 }, glm::u8vec4 { 255, 255, 255, 255 });
                bitmap->set_pixel({ 0, 2 }, glm::u8vec4(255));
                bitmap->set_pixel({ 1, 2 }, glm::u8vec4(255));
                bitmap->set_pixel({ 2, 2 }, glm::u8vec4(255));

                texture_rgba_unsigned_byte = Wolf::Rendering::Texture::from_bitmap(bitmap, texture_config);
            }
            {
                // Creates simple bitmap
                auto bitmap = std::make_shared<Wolf::Rendering::BitMap<glm::u8vec3>>(3, 3);
                Rendering::TextureConfig texture_config;
                texture_config.mag_filter = Rendering::TextureTypes::Filter::NEAREST;
                texture_config.wrap_mode = Rendering::TextureTypes::WrapMode::REPEAT;
                texture_config.pixel_format = Rendering::TextureTypes::PixelFormat::RGB;
                texture_config.internal_pixel_format = Rendering::TextureTypes::PixelInternalFormat::RGB_8;
                texture_config.pixel_type = Rendering::TextureTypes::PixelType::UNSIGNED_BYTE;

                bitmap->set_pixel({ 0, 0 }, glm::u8vec3 { 255, 0, 0 });
                bitmap->set_pixel({ 1, 0 }, glm::u8vec3 { 0, 255, 0 });
                bitmap->set_pixel({ 2, 0 }, glm::u8vec3 { 0, 0, 255 });
                bitmap->set_pixel({ 0, 1 }, glm::u8vec3 { 255, 255, 0 });
                bitmap->set_pixel({ 1, 1 }, glm::u8vec3 { 0, 255, 255 });
                bitmap->set_pixel({ 2, 1 }, glm::u8vec3 { 255, 255, 255 });
                bitmap->set_pixel({ 0, 2 }, glm::u8vec3(255));
                bitmap->set_pixel({ 1, 2 }, glm::u8vec3(255));
                bitmap->set_pixel({ 2, 2 }, glm::u8vec3(255));
                texture_rgb_unsigned_byte = Wolf::Rendering::Texture::from_bitmap(bitmap, texture_config);
            }
            {
                Shared<Rendering::BitMap<uint8_t>> bitmap = std::make_shared<Rendering::BitMap<uint8_t>>(3, 3);
                Rendering::TextureConfig texture_config;
                texture_config.mag_filter = Rendering::TextureTypes::Filter::NEAREST;
                texture_config.wrap_mode = Rendering::TextureTypes::WrapMode::CLAMP_TO_EDGE;
                texture_config.pixel_format = Rendering::TextureTypes::PixelFormat::R;
                texture_config.internal_pixel_format = Rendering::TextureTypes::PixelInternalFormat::R_8;
                texture_config.pixel_type = Rendering::TextureTypes::PixelType::UNSIGNED_BYTE;

                bitmap->set_pixel({ 0, 0 }, static_cast<uint8_t>(0.1f * 255.0f));
                bitmap->set_pixel({ 1, 0 }, static_cast<uint8_t>(0.2f * 255.0f));
                bitmap->set_pixel({ 2, 0 }, static_cast<uint8_t>(0.3f * 255.0f));
                bitmap->set_pixel({ 0, 1 }, static_cast<uint8_t>(0.4f * 255.0f));
                bitmap->set_pixel({ 1, 1 }, static_cast<uint8_t>(0.5f * 255.0f));
                bitmap->set_pixel({ 2, 1 }, static_cast<uint8_t>(0.6f * 255.0f));
                bitmap->set_pixel({ 0, 2 }, static_cast<uint8_t>(0.6f * 255.0f));
                bitmap->set_pixel({ 1, 2 }, static_cast<uint8_t>(0.6f * 255.0f));
                bitmap->set_pixel({ 2, 2 }, static_cast<uint8_t>(0.6f * 255.0f));

                texture_r_unsigned_byte = Wolf::Rendering::Texture::from_bitmap(bitmap, texture_config);
            }
            {
                Shared<Rendering::BitMap<float>> bitmap = std::make_shared<Rendering::BitMap<float>>(3, 3);
                Rendering::TextureConfig texture_config;
                texture_config.mag_filter = Rendering::TextureTypes::Filter::NEAREST;
                texture_config.wrap_mode = Rendering::TextureTypes::WrapMode::CLAMP_TO_EDGE;
                texture_config.pixel_format = Rendering::TextureTypes::PixelFormat::R;
                texture_config.internal_pixel_format = Rendering::TextureTypes::PixelInternalFormat::R_8;
                texture_config.pixel_type = Rendering::TextureTypes::PixelType::FLOAT;
                bitmap->set_pixel({ 0, 0 }, 0.1f);
                bitmap->set_pixel({ 1, 0 }, 0.2f);
                bitmap->set_pixel({ 2, 0 }, 0.3f);
                bitmap->set_pixel({ 0, 1 }, 0.4f);
                bitmap->set_pixel({ 1, 1 }, 0.5f);
                bitmap->set_pixel({ 2, 1 }, 0.6f);
                bitmap->set_pixel({ 0, 2 }, 0.6f);
                bitmap->set_pixel({ 1, 2 }, 0.6f);
                bitmap->set_pixel({ 2, 2 }, 0.6f);

                texture_r_float = Wolf::Rendering::Texture::from_bitmap(bitmap, texture_config);
            }

            material = std::make_shared<Rendering::Material>();
            Shared<Rendering::ShaderProgram> shader = Rendering::ShaderProgram::create(
                PathManager::get_instance().get_engine_assets_path() / "shaders/texture/renderer2d.vert",
                PathManager::get_instance().get_engine_assets_path() / "shaders/texture/renderer2d.frag");
            material->set_shader_program(shader);
        }

        virtual void on_ui_render_start()
        {
            ImGui::Begin("Test");
            ImGui::Text("Tests textures initialized with the following properties");
            ImGui::Text("- Pixel format: RGBA, Pixel type: UNSIGNED BYTE");
            ImGui::Text("- Pixel format: RGBA, Pixel type: FLOAT");
            ImGui::Text("- Pixel format: RGB, Pixel type: UNSIGNED BYTE");
            ImGui::Text("- Pixel format: RGB, Pixel type: FLOAT");
            ImGui::Text("- Pixel format: R, Pixel type: UNSIGNED BYTE");
            ImGui::Text("- Pixel format: R, Pixel type: FLOAT");
            ImGui::End();
        }

        virtual void on_render() override
        {
            static const Rendering::Camera camera(200, 200, 1);
            Rendering::Renderer2D::begin_scene(camera);

            glm::vec3 quad_size(0.2f);
            glm::vec4 color(1.0f);
            Rendering::Renderer2D::new_frame();
            Rendering::Renderer2D::submit_quad(glm::vec3(-0.5, 0.5, 0.0), quad_size, color, texture_rgba_unsigned_byte);
            Rendering::Renderer2D::submit_quad(glm::vec3(0.5, 0.5, 0.0), quad_size, color, texture_rgba_float);
            Rendering::Renderer2D::submit_quad(glm::vec3(-0.5, 0.0, 0.0), quad_size, color, texture_rgb_unsigned_byte);
            Rendering::Renderer2D::submit_quad(glm::vec3(0.5, 0.0, 0.0), quad_size, color, texture_rgb_float);
            Rendering::Renderer2D::submit_quad(glm::vec3(-0.5, -0.5, 0.0), quad_size, color, texture_r_unsigned_byte);
            Rendering::Renderer2D::submit_quad(glm::vec3(0.5, -0.5, 0.0), quad_size, color, texture_r_float);
            Rendering::Renderer2D::end_frame();
        }
    };
}
}
#endif