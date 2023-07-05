#include "WEngine.h"

namespace Tests
{
    using namespace Wolf;

    class TextureTestLayer : public Layer
    {
        public:
            Shared<Wolf::Rendering::Texture> texture;
            Shared<Wolf::Rendering::Material> material;

            TextureTestLayer() = default;
            virtual void on_start() override
            {

#define VEC4_FLOAT
#ifdef VEC4_FLOAT
                // Creates simple bitmap
                Shared<Rendering::BitMap<glm::vec4>> bitmap = std::make_shared<Rendering::BitMap<glm::vec4>>(3, 3);
                Rendering::TextureConfig texture_config;
                texture_config.mag_filter = Rendering::TextureTypes::Filter::NEAREST;
                texture_config.wrap_mode = Rendering::TextureTypes::WrapMode::CLAMP_TO_EDGE;
                texture_config.pixel_format = Rendering::TextureTypes::PixelFormat::RGBA; 
                texture_config.internal_pixel_format = Rendering::TextureTypes::PixelInternalFormat::RGBA_8;
                texture_config.pixel_type = Rendering::TextureTypes::PixelType::FLOAT;

                bitmap->set_color({0, 0}, glm::vec4{1, 0, 0, 1});
                bitmap->set_color({1, 0}, glm::vec4{0, 1, 0, 1});
                bitmap->set_color({2, 0}, glm::vec4{0, 0, 1, 1});
                bitmap->set_color({0, 1}, glm::vec4{1, 1, 0, 1});
                bitmap->set_color({1, 1}, glm::vec4{0, 1, 1, 1});
                bitmap->set_color({2, 1}, glm::vec4{1, 1, 1, 1});
#endif
#ifdef VEC3_FLOAT
                // Creates simple bitmap
                Shared<Rendering::BitMap<glm::vec3>> bitmap = std::make_shared<Rendering::BitMap<glm::vec3>>(3, 3);
                Rendering::TextureConfig texture_config;
                texture_config.mag_filter = Rendering::TextureTypes::Filter::NEAREST;
                texture_config.wrap_mode = Rendering::TextureTypes::WrapMode::CLAMP_TO_EDGE;
                texture_config.pixel_format = Rendering::TextureTypes::PixelFormat::RGB;
                texture_config.internal_pixel_format = Rendering::TextureTypes::PixelInternalFormat::RGB_8;
                texture_config.pixel_type = Rendering::TextureTypes::PixelType::FLOAT;

                bitmap->set_color({0, 0}, glm::vec3{1, 0, 0});
                bitmap->set_color({1, 0}, glm::vec3{0, 1, 0});
                bitmap->set_color({2, 0}, glm::vec3{0, 0, 1});
                bitmap->set_color({0, 1}, glm::vec3{1, 1, 0});
                bitmap->set_color({1, 1}, glm::vec3{0, 1, 1});
                bitmap->set_color({2, 1}, glm::vec3{1, 1, 1});
#endif
#ifdef RED
                // Creates simple bitmap
                Shared<Rendering::BitMap<float>> bitmap = std::make_shared<Rendering::BitMap<float>>(3, 3);
                Rendering::TextureConfig texture_config;
                texture_config.mag_filter = Rendering::TextureTypes::Filter::NEAREST;
                texture_config.wrap_mode = Rendering::TextureTypes::WrapMode::CLAMP_TO_EDGE;
                texture_config.pixel_format = Rendering::TextureTypes::PixelFormat::R;
                texture_config.internal_pixel_format = Rendering::TextureTypes::PixelInternalFormat::R_8;
                texture_config.pixel_type = Rendering::TextureTypes::PixelType::FLOAT;

                bitmap->set_color({0, 0}, 0.1f);
                bitmap->set_color({1, 0}, 0.2f);
                bitmap->set_color({2, 0}, 0.3f);
                bitmap->set_color({0, 1}, 0.4f);
                bitmap->set_color({1, 1}, 0.5f);
                bitmap->set_color({2, 1}, 0.6f);
#endif
#ifdef VEC4_UINT
                // Creates simple bitmap
                Shared<Wolf::Rendering::BitMap<glm::u8vec4>> bitmap = std::make_shared<Wolf::Rendering::BitMap<glm::u8vec4>>(3, 3);
                Rendering::TextureConfig texture_config;
                texture_config.mag_filter = Rendering::TextureTypes::Filter::NEAREST;
                texture_config.wrap_mode = Rendering::TextureTypes::WrapMode::CLAMP_TO_EDGE;
                texture_config.pixel_format = Rendering::TextureTypes::PixelFormat::RGBA;
                texture_config.internal_pixel_format = Rendering::TextureTypes::PixelInternalFormat::RGBA_8;
                texture_config.pixel_type = Rendering::TextureTypes::PixelType::UNSIGNED_BYTE;

                bitmap->set_color({0, 0}, glm::u8vec4{255, 0, 0, 255});
                bitmap->set_color({1, 0}, glm::u8vec4{0, 255, 0, 255});
                bitmap->set_color({2, 0}, glm::u8vec4{0, 0, 255, 255});
                bitmap->set_color({0, 1}, glm::u8vec4{255, 255, 0, 255});
                bitmap->set_color({1, 1}, glm::u8vec4{0, 255, 255, 255});
                bitmap->set_color({2, 1}, glm::u8vec4{255, 255, 255, 255});
#endif
#ifdef VEC3_UINT
                // Creates simple bitmap
                auto bitmap = std::make_shared<Wolf::Rendering::BitMap<glm::u8vec3>>(3, 3);
                Rendering::TextureConfig texture_config;
                texture_config.mag_filter = Rendering::TextureTypes::Filter::NEAREST;
                texture_config.wrap_mode = Rendering::TextureTypes::WrapMode::REPEAT;
                texture_config.pixel_format = Rendering::TextureTypes::PixelFormat::RGB;
                texture_config.internal_pixel_format = Rendering::TextureTypes::PixelInternalFormat::RGB_8;
                texture_config.pixel_type = Rendering::TextureTypes::PixelType::UNSIGNED_BYTE;

                bitmap->set_color({0, 0}, glm::u8vec3{255, 0, 0});
                bitmap->set_color({1, 0}, glm::u8vec3{0, 255, 0});
                bitmap->set_color({2, 0}, glm::u8vec3{0, 0, 255});
                bitmap->set_color({0, 1}, glm::u8vec3{255, 255, 0});
                bitmap->set_color({1, 1}, glm::u8vec3{0, 255, 255});
                bitmap->set_color({2, 1}, glm::u8vec3{255, 255, 255});
                
#endif
#ifdef FLOAT_BITMAP
                // Creates simple bitmap
                Shared<Rendering::BitMap<glm::vec4>> bitmap = std::make_shared<Rendering::BitMap<glm::vec4>>(3, 3);
                Rendering::TextureConfig texture_config;
                texture_config.mag_filter = Rendering::TextureTypes::Filter::NEAREST;
                texture_config.wrap_mode = Rendering::TextureTypes::WrapMode::CLAMP_TO_EDGE;
                texture_config.pixel_format = Rendering::TextureTypes::PixelFormat::RGBA;
                texture_config.internal_pixel_format = Rendering::TextureTypes::PixelInternalFormat::RGBA_8;
                texture_config.pixel_type = Rendering::TextureTypes::PixelType::FLOAT;

                bitmap->set_color({0, 0}, glm::vec4{1.0f});
                bitmap->set_color({1, 0}, glm::vec4{1.0f});
                bitmap->set_color({2, 0}, glm::vec4{1.0f});
                bitmap->set_color({2, 1}, glm::vec4{1.0f});
                bitmap->set_color({2, 2}, glm::vec4{1.0f});
#endif

                texture = Wolf::Rendering::Texture::from_bitmap(bitmap, texture_config);
                std::cout << "[TEST] Texture" << std::endl;

                material = std::make_shared<Rendering::Material>();
                Shared<Rendering::ShaderProgram> shader = Rendering::ShaderProgram::create(
                    PathManager::get_instance().get_engine_assets_path() / "shaders/texture/renderer2d.vert",
                    PathManager::get_instance().get_engine_assets_path() / "shaders/texture/renderer2d.frag"
                );
                material->set_shader_program(shader);
            }
            virtual void on_update(const Time& delta) override {}
            virtual void on_event(Event* event) override {}
            virtual void on_ui_render_start() override {}
            virtual void on_ui_render_finish() override {}
            virtual void on_end() override {}
            virtual void on_render() override 
            {
                material->get_shader()->bind();
                uint8_t texture_slot = 0;
                material->get_shader()->set_int("u_texture",  texture_slot);
                Rendering::Texture::activate_texture(texture, texture_slot);
                Rendering::Renderer2D::render_material(material);
            }
    };
}