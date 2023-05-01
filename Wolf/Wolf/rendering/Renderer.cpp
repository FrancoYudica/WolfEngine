#include "Renderer.h"
#include <memory>
#include "Material.h"
#include "batch/Batch.h"
#include "batch/SpriteBatch.h"
#include "glm/gtc/matrix_transform.hpp"

using namespace Wolf::Rendering;

struct RendererData
{
	SpriteBatch sprite_batch;
	SpriteBatch circle_batch;
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
	//_material->add_float4(std::string("u_Color"), {0.1f, 0, 1, 1});

}

void Renderer2D::begin_scene(const Camera& camera)
{
	_data.sprite_batch.begin_scene(camera);
}

void Renderer2D::shutdown()
{
	_data.sprite_batch.shutdown();
}

void Renderer2D::new_frame()
{
	_data.sprite_batch.new_frame();
}

void Renderer2D::end_frame()
{
	_data.sprite_batch.end_frame();
}

void Renderer2D::submit_quad(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color)
{
	_data.sprite_batch.submit_primitive(position, size, color);
}