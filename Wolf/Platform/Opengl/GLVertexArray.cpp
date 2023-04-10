#include "GLVertexArray.h"
#include <glad/glad.h>

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

Wolf::Rendering::GL::GLVertexArray::GLVertexArray()
{
	glGenVertexArrays(1, &ID);
	_AttributeIndex = 0;
}

Wolf::Rendering::GL::GLVertexArray::~GLVertexArray()
{
	glDeleteVertexArrays(1, &ID);
}

void Wolf::Rendering::GL::GLVertexArray::bind()
{
	glBindVertexArray(ID);
}

void Wolf::Rendering::GL::GLVertexArray::unbind()
{
	glBindVertexArray(0);
}

void Wolf::Rendering::GL::GLVertexArray::add_vertex_buffer(const std::shared_ptr<VertexBuffer> vb)
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

void Wolf::Rendering::GL::GLVertexArray::set_index_buffer(const std::shared_ptr<IndexBuffer> ib)
{
	bind();
	ib->bind();
	_IndexBuffer = ib;

}
