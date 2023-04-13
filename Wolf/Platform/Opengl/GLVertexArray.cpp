#include "GLVertexArray.h"
#include <glad/glad.h>

using namespace Wolf::Rendering::GL;

static GLenum ShaderDataTypeToOpenGLBaseType(Wolf::Rendering::ShaderDataType type)
{
	switch (type)
	{
		case Wolf::Rendering::ShaderDataType::Float:    return GL_FLOAT;
		case Wolf::Rendering::ShaderDataType::Float2:   return GL_FLOAT;
		case Wolf::Rendering::ShaderDataType::Float3:   return GL_FLOAT;
		case Wolf::Rendering::ShaderDataType::Float4:   return GL_FLOAT;
		case Wolf::Rendering::ShaderDataType::Mat2:     return GL_FLOAT;
		case Wolf::Rendering::ShaderDataType::Mat3:     return GL_FLOAT;
		case Wolf::Rendering::ShaderDataType::Mat4:     return GL_FLOAT;
		case Wolf::Rendering::ShaderDataType::Int:      return GL_INT;
		case Wolf::Rendering::ShaderDataType::Int2:     return GL_INT;
		case Wolf::Rendering::ShaderDataType::Int3:     return GL_INT;
		case Wolf::Rendering::ShaderDataType::Int4:     return GL_INT;
		default:
			std::cout << "Unimplememted shader data type to GL base type: " << type << std::endl;
	}
	return 1;

}

GLVertexArray::GLVertexArray()
{
	ID = 0;
	glGenVertexArrays(1, &ID);
	_AttributeIndex = 0;
}

GLVertexArray::~GLVertexArray()
{
	glDeleteVertexArrays(1, &ID);
}

void GLVertexArray::bind()
{
	glBindVertexArray(ID);
}

void GLVertexArray::unbind()
{
	glBindVertexArray(0);
}

void GLVertexArray::add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vb)
{
	_VertexBuffers.push_back(vb);
	bind();
	vb->bind();

	BufferLayout layout = vb->get_buffer_layout();

	for (BufferAttribute& attribute : layout)
	{
		glEnableVertexAttribArray(_AttributeIndex);
		glVertexAttribPointer(
			_AttributeIndex,
			attribute.GetComponentCount(),
			ShaderDataTypeToOpenGLBaseType(attribute.Type),
			attribute.Normalized ? GL_TRUE : GL_FALSE,
			layout.GetStride(),
			(void*)0//attribute.Offset
		);
		_AttributeIndex++;
	}
}

void GLVertexArray::set_index_buffer(const std::shared_ptr<IndexBuffer>& ib)
{
	bind();
	ib->bind();
	_IndexBuffer = ib;

}
