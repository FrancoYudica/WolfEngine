#include "Renderer.h"

#include <memory>
#include "Buffer.h"
#include "VertexArray.h"
#include "RenderCommand.h"
#include "ShaderProgram.h"
#include "ShaderProgram.h"


using namespace Wolf::Rendering;


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec4 aColor;\n"
"out vec4 _Color;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"	_Color = aColor;\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 _Color;\n"
"uniform vec3 _UniformColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(_Color.xyz, 1.0f);\n"
"}\n\0";



struct QuadVertex
{
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 uv;
	unsigned int texture_index;
};

struct RendererData
{
	unsigned int BatchSize; // Max amount of Quads, (4 QuadVertex per quad)
	unsigned int Submitions;
	std::shared_ptr<VertexArray> VAO;
	std::shared_ptr<VertexBuffer> VBO;
	std::shared_ptr<IndexBuffer> IBO;
	std::shared_ptr<ShaderProgram> ShaderProgram;
	QuadVertex* VerticesPtr;
	
};

// Data used for the renderer
static RendererData _Data;


void Renderer2D::Init()
{
	_Data.BatchSize = 2;
	_Data.Submitions = 0;
	_Data.VerticesPtr = new QuadVertex[_Data.BatchSize];

	// The indices are always the same, so i set them once, therefore there is no
	// need for indices allocation
	unsigned int vertices_per_quad = 4;
	unsigned int indices_per_quad = 6;
	unsigned int total_vertices = _Data.BatchSize * vertices_per_quad;
	unsigned int indices_count = total_vertices * indices_per_quad;

	// Creates the indices array, it's not necessary to re-calculate
	auto indices = new unsigned int[indices_count];
	for (unsigned int quad_index = 0; quad_index < _Data.BatchSize; quad_index++)
	{
		unsigned int index = quad_index * vertices_per_quad * indices_per_quad;
		indices[index] = index;
		indices[index + 1] = index + 1;
		indices[index + 2] = index + 2;
	
		indices[index + 3] = index;
		indices[index + 4] = index + 2;
		indices[index + 5] = index + 3;
	}

	// Creates VAO, IBO and VBO
	_Data.VAO = VertexArray::Create();
	_Data.VAO->bind();
	// Creates index and vertex buffer
	_Data.IBO = IndexBuffer::Create(indices, indices_count);
	delete[] indices;

	_Data.VBO = VertexBuffer::Allocate(_Data.BatchSize * sizeof(QuadVertex) * 4);

	_Data.VBO->set_buffer_layout(
		BufferLayout{
			BufferAttribute("Position", ShaderDataType::Float3, false),
			BufferAttribute("Color", ShaderDataType::Float4, false),
			BufferAttribute("UV", ShaderDataType::Float2, false),
			BufferAttribute("TextureIndex", ShaderDataType::Int, false)
			}
	);
	//_Data.VAO->add_vertex_buffer(_Data.VBO);
	_Data.VAO->set_index_buffer(_Data.IBO);

	_Data.VAO->unbind();
	_Data.ShaderProgram = ShaderProgram::Create(vertexShaderSource, fragmentShaderSource);
}

void Renderer2D::Shutdown()
{
	// Deallocates the memory
	delete[] _Data.VerticesPtr;
}

void Renderer2D::NewFrame()
{
	if (_Data.Submitions != 0)
	{
		assert(false);
	}
	_Data.Submitions = 0;
}

void Renderer2D::EndFrame()
{
	_Flush();
}

void Renderer2D::SubmitQuad(const glm::vec3& position, const glm::vec3 size, const glm::vec4& color)
{
	unsigned int index = _Data.Submitions * 4;

	QuadVertex v0 = { position + glm::vec3(-size.x, -size.y, 0), color, glm::vec2(0), 0 };
	QuadVertex v1 = { position + glm::vec3(+size.x, -size.y, 0), color, glm::vec2(0), 0 };
	QuadVertex v2 = { position + glm::vec3(+size.x, +size.y, 0), color, glm::vec2(0), 0 };
	QuadVertex v3 = { position + glm::vec3(-size.x, +size.y, 0), color, glm::vec2(0), 0 };

	_Data.VerticesPtr[index + 0] = v0;
	_Data.VerticesPtr[index + 1] = v1;
	_Data.VerticesPtr[index + 2] = v2;
	_Data.VerticesPtr[index + 3] = v3;

	_Data.Submitions++;

}

void Wolf::Rendering::Renderer2D::_Flush()
{

	// Renders the batched quads
	_Data.ShaderProgram->bind();
	_Data.VAO->bind();
	_Data.VBO->bind();
	_Data.VBO->set_sub_data(_Data.VerticesPtr, 4 * _Data.Submitions * sizeof(QuadVertex), 0);
	Rendering::RenderCommand::DrawIndexed(_Data.VAO, _Data.Submitions);
	_Data.VAO->unbind();

	// Rests
	_Data.Submitions = 0;
}
