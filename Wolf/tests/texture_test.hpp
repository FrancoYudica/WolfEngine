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
                // Creates simple bitmap
                Shared<Wolf::Rendering::BitMap> bitmap = std::make_shared<Wolf::Rendering::BitMap>(3, 3);
                Rendering::TextureConfig texture_config;
                texture_config.mag_filter = Rendering::TextureTypes::Filter::NEAREST;
                bitmap->set_color({0, 0}, {255, 0, 0});
                bitmap->set_color({1, 0}, {255, 0, 128});
                bitmap->set_color({2, 0}, {128, 0, 255});
                bitmap->set_color({2, 1}, {128, 0, 255});
                bitmap->set_color({2, 2}, {0, 0, 255});
                texture = Wolf::Rendering::Texture::initialize_from_bitmap(bitmap, texture_config);
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