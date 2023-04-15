
#include <glad/glad.h>
#include "OpenGLLayer.h"
#include <glm/glm.hpp>


const char* vertexSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec4 _Color;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"	_Color = vec4(aColor, 1);\n"
"}\0";
//Fragment Shader source code
const char* fragmentrSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 _Color;\n"
"uniform vec3 _UniformColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(_Color.xyz, 1.0f);\n"
"}\n\0";


struct Vertex
{
	glm::vec3 pos;
	glm::vec3 color;
	Vertex(glm::vec3 position, glm::vec3 color) : pos(position), color(color) {}
};


namespace Wolf
{
	namespace SandboxLayers
	{


		void OpenGLLayer::on_start()
		{

			gladLoadGL();

			auto program = Wolf::Rendering::ShaderProgram::create(vertexSource, fragmentrSource);
			Shaders.add("shader", program);

			Vertex v0 = Vertex({ 0.5f, 0.5f, 0.0f }, { 1, 0, 0 });
			Vertex v1 = Vertex({ 0.5f, -0.5f, 0.0f }, { 0, 1, 0 });
			Vertex v2 = Vertex({ -0.5f, -0.5f, 0.0f }, { 0, 0, 1 });
			Vertex v3 = Vertex({ -0.5f,  0.5f, 0.0f }, { 1, 1, 0 });

			Wolf::Rendering::Renderer2D::init();

			Vertex vertices[] = {v0, v1, v2, v3};

			// INDEX BUFFER DATA
			unsigned int indices[] = {0, 1, 2, 0, 2, 3};
			//unsigned int VBO, IBO;
			VAO = Wolf::Rendering::VertexArray::create();
			VAO->bind();

			auto vbo = Wolf::Rendering::VertexBuffer::create(vertices, sizeof(float) * 6 * 4);

			Wolf::Rendering::BufferLayout layout = {
				Wolf::Rendering::BufferAttribute("aPosition", Wolf::Rendering::Float3, false),
				Wolf::Rendering::BufferAttribute("aColor", Wolf::Rendering::Float3, false)
			};
			vbo->set_buffer_layout(layout);

			auto ibo = Wolf::Rendering::IndexBuffer::create(indices, 6);

			VAO->add_vertex_buffer(vbo);
			VAO->set_index_buffer(ibo);
			VAO->unbind();

		}
		void OpenGLLayer::on_update(const Time& delta)
		{

		}
		void OpenGLLayer::on_event(const Event& event)
		{
		}
		void OpenGLLayer::on_ui_render_start()
		{
		}
		void OpenGLLayer::on_ui_render_finish()
		{
		}
		void OpenGLLayer::on_end()
		{
		}
		void OpenGLLayer::on_render()
		{
			auto program = Shaders.get("shader");
			program->bind();
			program->set_float("_UniformColor", glm::vec3(1, .5, .4));
			VAO->bind();
			Rendering::RenderCommand::draw_indexed(VAO, 6);
			VAO->unbind();
		}
	}
}

