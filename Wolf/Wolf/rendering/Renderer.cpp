#include "Renderer.h"
#include "Material.h"
#include "RenderCommand.h"
#include "batch/Batch.h"
#include "batch/CircleBatch.h"
#include "batch/LineBatch.h"
#include "batch/SpriteBatch.h"
#include "glm/gtc/matrix_transform.hpp"
#include <memory>
#include <unordered_map>

namespace Wolf {
namespace Rendering {
    // Data used for the renderer
    static std::unordered_map<uint32_t, uint32_t> used_textures;
    static Unique<SpriteBatch> sprite_batch;
    static Unique<CircleBatch> circle_batch;
    static Unique<LineBatch> line_batch;
    static Shared<VertexArray> material_vao;

    void Renderer2D::init()
    {

        // Gets the default material for SpriteBatch
        const Path::FilePath& assets_path = Path::get_engine_assets_folder();
        {
            const Path::FilePath vertex_path = assets_path / "shaders/default_sprite/renderer2d.vert";
            const Path::FilePath fragment_path = assets_path / "shaders/default_sprite/renderer2d.frag";
            auto _material = std::make_shared<Material>();
            _material->set_shader_program(ShaderProgram::create(vertex_path, fragment_path));
            sprite_batch = std::make_unique<SpriteBatch>();
            sprite_batch->init(_material);
        }

        {
            const Path::FilePath vertex_path = assets_path / "shaders/default_circle/circle.vert";
            const Path::FilePath fragment_path = assets_path / "shaders/default_circle/circle.frag";
            auto _material = std::make_shared<Material>();
            _material->set_shader_program(ShaderProgram::create(vertex_path, fragment_path));

            circle_batch = std::make_unique<CircleBatch>();
            circle_batch->init(_material);
        }

        {
            const Path::FilePath vertex_path = assets_path / "shaders/default_line/line.vert";
            const Path::FilePath fragment_path = assets_path / "shaders/default_line/line.frag";
            auto _material = std::make_shared<Material>();
            _material->set_shader_program(ShaderProgram::create(vertex_path, fragment_path));
            line_batch = std::make_unique<LineBatch>();
            line_batch->init(_material);
        }
        {
            // Creates VAO, IBO and VBO
            material_vao = VertexArray::create();
            material_vao->bind();
            // Creates index and vertex buffer
            uint32_t* indices = new uint32_t[6] { 0, 1, 2, 2, 3, 0 };

            auto index_buffer = IndexBuffer::create(indices, 6);
            delete[] indices;

            uint32_t float_count = 4 * 2;
            uint32_t buffer_size = sizeof(float) * float_count;
            auto vertex_buffer = VertexBuffer::allocate(buffer_size);
            vertex_buffer->set_buffer_layout(
                {
                    { "UV", ShaderDataType::Float2, false },
                });

            float* buffer = new float[float_count] {
                0.0f, 0.0f,
                1.0f, 0.0f,
                1.0f, 1.0f,
                0.0f, 1.0f
            };
            vertex_buffer->bind();
            vertex_buffer->set_sub_data(buffer, buffer_size, 0);
            delete[] buffer;

            material_vao->add_vertex_buffer(vertex_buffer);
            material_vao->set_index_buffer(index_buffer);
            material_vao->unbind();
            vertex_buffer->unbind();
        }
    }

    void Renderer2D::begin_scene(const Camera& camera)
    {
        sprite_batch->begin_scene(camera);
        circle_batch->begin_scene(camera);
        line_batch->begin_scene(camera);
    }

    void Renderer2D::shutdown()
    {
        sprite_batch->shutdown();
        circle_batch->shutdown();
        line_batch->shutdown();
    }

    void Renderer2D::new_frame()
    {
        sprite_batch->new_frame();
        circle_batch->new_frame();
        line_batch->new_frame();
    }

    void Renderer2D::end_frame()
    {
        sprite_batch->end_frame();
        circle_batch->end_frame();
        line_batch->end_frame();
        used_textures.clear();
    }

    void Renderer2D::submit_quad(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color)
    {
        sprite_batch->submit_primitive(position, size, color);
    }

    void Renderer2D::submit_quad(
        const glm::vec3& position,
        const glm::vec3& size,
        const glm::vec4& color,
        const Shared<Texture>& texture)
    {
        uint32_t texture_slot;
        if (used_textures.count(texture->get_id())) {
            texture_slot = used_textures[texture->get_id()];
        } else {
            texture_slot = used_textures.size();
            used_textures[texture->get_id()] = texture_slot;
            Texture::activate_texture(texture, texture_slot);
        }
        sprite_batch->submit_primitive(position, size, color, texture_slot);

        // Out of texture slots
        if (used_textures.size() + 1 > RENDERER_MAX_TEXTURE_SLOTS - 1) {
            sprite_batch->end_frame();
            used_textures.clear();
        }
    }

    void Renderer2D::submit_quad(
        const glm::vec3& position,
        const glm::vec3& size,
        const glm::vec4& color,
        const Shared<Texture>& texture,
        const Numerical::Bounds<glm::vec2>& bounds)
    {
        uint32_t texture_slot;
        if (used_textures.count(texture->get_id())) {
            texture_slot = used_textures[texture->get_id()];
        } else {
            texture_slot = used_textures.size();
            used_textures[texture->get_id()] = texture_slot;
            Texture::activate_texture(texture, texture_slot);
        }
        sprite_batch->submit_primitive(position, size, color, texture_slot, bounds.min, bounds.max);

        // Out of texture slots
        if (used_textures.size() + 1 > RENDERER_MAX_TEXTURE_SLOTS - 1) {
            sprite_batch->end_frame();
            used_textures.clear();
        }
    }

    void Renderer2D::submit_circle(const glm::vec3& position, const float radius, const glm::vec4& color, float fade)
    {
        circle_batch->submit_primitive(position, radius, color, fade);
    }

    void Renderer2D::submit_line(const glm::vec2& p0, const glm::vec2& p1, const glm::vec4& color, const float thickness)
    {
        line_batch->submit_primitive(p0, p1, color, thickness);
    }

    void Renderer2D::submit_line_interpolated(const glm::vec2& p0, const glm::vec2& p1, const glm::vec4& color, const float thickness)
    {
        line_batch->submit_primitive_interpolated(p0, p1, color, thickness);
    }

    void Renderer2D::render_material(const Shared<Material>& material)
    {
        material->upload();
        material_vao->bind();
        RenderCommand::draw_indexed(material_vao, 6, PrimitiveType::Triangles);
        material_vao->unbind();
    }
}
}