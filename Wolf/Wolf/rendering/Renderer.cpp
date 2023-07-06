#include "Renderer.h"
#include <memory>
#include "Material.h"
#include "batch/Batch.h"
#include "batch/SpriteBatch.h"
#include "batch/CircleBatch.h"
#include "batch/LineBatch.h"
#include "glm/gtc/matrix_transform.hpp"
#include "RenderCommand.h"

namespace Wolf
{
	namespace Rendering
	{

		struct RendererData
		{
			SpriteBatch sprite_batch;
			CircleBatch circle_batch;
			LineBatch line_batch;
			Shared<VertexArray> material_vao;
		};

		// Data used for the renderer
		static RendererData _data;

		void Renderer2D::init()
		{

			// Gets the default material for SpriteBatch
			const Path assets_path = Wolf::PathManager::get_instance().get_engine_assets_path();
			{
				const Path vertex_path = assets_path / "shaders/default_sprite/renderer2d.vert";
				const Path fragment_path = assets_path / "shaders/default_sprite/renderer2d.frag";
				auto _material = std::make_shared<Material>();
				_material->set_shader_program(ShaderProgram::create(vertex_path, fragment_path));
				_data.sprite_batch.init(_material);
			}

			{
				const Path vertex_path = assets_path / "shaders/default_circle/circle.vert";
				const Path fragment_path = assets_path / "shaders/default_circle/circle.frag";
				auto _material = std::make_shared<Material>();
				_material->set_shader_program(ShaderProgram::create(vertex_path, fragment_path));
				_data.circle_batch.init(_material);
			}

			{
				const Path vertex_path = assets_path / "shaders/default_line/line.vert";
				const Path fragment_path = assets_path / "shaders/default_line/line.frag";
				auto _material = std::make_shared<Material>();
				_material->set_shader_program(ShaderProgram::create(vertex_path, fragment_path));
				_data.line_batch.init(_material);
			}
			{
				// Creates VAO, IBO and VBO
				_data.material_vao = VertexArray::create();
				_data.material_vao->bind();
				// Creates index and vertex buffer
				uint32_t* indices = new uint32_t[6] {0, 1, 2, 2, 3, 0};

				auto index_buffer = IndexBuffer::create(indices, 6);
				delete[] indices;
				
				uint32_t float_count = 4 * 2;
				uint32_t buffer_size = sizeof(float) * float_count;
				auto vertex_buffer = VertexBuffer::allocate(buffer_size);
				vertex_buffer->set_buffer_layout(
					{
						{"UV", ShaderDataType::Float2, false},
					}
				);

				float* buffer = new float[float_count] {
					0.0f, 0.0f,
					1.0f, 0.0f,
					1.0f, 1.0f,
					0.0f, 1.0f
				};
				vertex_buffer->bind();
				vertex_buffer->set_sub_data(buffer, buffer_size, 0);
				delete[] buffer;

				_data.material_vao->add_vertex_buffer(vertex_buffer);
				_data.material_vao->set_index_buffer(index_buffer);
				_data.material_vao->unbind();
				vertex_buffer->unbind();
			}
		}

		void Renderer2D::begin_scene(const Camera& camera)
		{
			_data.sprite_batch.begin_scene(camera);
			_data.circle_batch.begin_scene(camera);
			_data.line_batch.begin_scene(camera);
		}

		void Renderer2D::shutdown()
		{
			_data.sprite_batch.shutdown();
			_data.circle_batch.shutdown();
			_data.line_batch.shutdown();
		}

		void Renderer2D::new_frame()
		{
			_data.sprite_batch.new_frame();
			_data.circle_batch.new_frame();
			_data.line_batch.new_frame();
		}

		void Renderer2D::end_frame()
		{
			_data.sprite_batch.end_frame();
			_data.circle_batch.end_frame();
			_data.line_batch.end_frame();
		}

		void Renderer2D::submit_quad(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color)
		{
			_data.sprite_batch.submit_primitive(position, size, color);
		}
		void Renderer2D::submit_quad(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color, const Shared<Texture>& texture)
		{
			uint32_t slot = 1;
			Texture::activate_texture(texture, slot);
			_data.sprite_batch.submit_primitive(position, size, color, slot);
		}


		void Renderer2D::submit_circle(const glm::vec3& position, const float radius, const glm::vec4& color, float fade)
		{
			_data.circle_batch.submit_primitive(position, radius, color, fade);
		}

		void Renderer2D::submit_line(const glm::vec2& p0, const glm::vec2& p1, const glm::vec4& color, const float thickness)
		{
			_data.line_batch.submit_primitive(p0, p1, color, thickness);
		}


		void Renderer2D::submit_line_interpolated(const glm::vec2& p0, const glm::vec2& p1, const glm::vec4& color, const float thickness)
		{
			_data.line_batch.submit_primitive_interpolated(p0, p1, color, thickness);
		}

		void Renderer2D::render_material(const Shared<Material>& material)
		{
			material->upload();
			_data.material_vao->bind();
			RenderCommand::draw_indexed(_data.material_vao, 6, PrimitiveType::Triangles);
			_data.material_vao->unbind();
		}
	}
}