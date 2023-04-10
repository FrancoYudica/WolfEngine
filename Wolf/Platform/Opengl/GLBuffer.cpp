#include "GLBuffer.h"
#include <glad/glad.h>


// VERTEX_BUFFER
Wolf::Rendering::GL::GLVertexBuffer::GLVertexBuffer(const void* vertices, unsigned int size)
{
	// Generates the buffer as an array buffer
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);

	// Sets the data
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Wolf::Rendering::GL::GLVertexBuffer::GLVertexBuffer(unsigned int size)
{
	// Generates the buffer as an array buffer
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);

	// Sets the data
	glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}



Wolf::Rendering::GL::GLVertexBuffer::~GLVertexBuffer()
{
	glDeleteBuffers(1, &ID);
}

void Wolf::Rendering::GL::GLVertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void Wolf::Rendering::GL::GLVertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Wolf::Rendering::GL::GLVertexBuffer::set_sub_data(const void* data, unsigned int size, unsigned int offset)
{
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

// INDEX_BUFFER
Wolf::Rendering::GL::GLIndexBuffer::GLIndexBuffer(const unsigned int* indices, unsigned int count)
{
	_Count = count;
	// Generates the buffer as an array buffer
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

	// Sets the data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Wolf::Rendering::GL::GLIndexBuffer::~GLIndexBuffer()
{
	glDeleteBuffers(1, &ID);
}

void Wolf::Rendering::GL::GLIndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void Wolf::Rendering::GL::GLIndexBuffer::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Wolf::Rendering::GL::GLIndexBuffer::set_sub_data(const void* data, unsigned int size, unsigned int offset)
{
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
}

