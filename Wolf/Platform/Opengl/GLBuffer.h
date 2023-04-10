#pragma once
#ifndef GL_BUFFER_H
#define GL_BUFFER_H

#include "rendering/Buffer.h"

namespace Wolf
{
	namespace Rendering
	{

		namespace GL
		{
			class GLVertexBuffer : public Wolf::Rendering::VertexBuffer
			{
			public:

				unsigned int ID;
				GLVertexBuffer() = default;
				GLVertexBuffer(const void* vertices, unsigned int size);
				GLVertexBuffer(unsigned int size);
				virtual ~GLVertexBuffer();
				virtual void bind();
				virtual void unbind();
				virtual void set_sub_data(const void* data, unsigned int size, unsigned int offset);
				virtual void set_buffer_layout(const Wolf::Rendering::BufferLayout& layout) { _Layout = layout; }
				virtual Wolf::Rendering::BufferLayout& get_buffer_layout() { return _Layout; }

			private:
				Wolf::Rendering::BufferLayout _Layout;

			};


			class GLIndexBuffer : public Wolf::Rendering::IndexBuffer
			{
			public:
				unsigned int ID;

				GLIndexBuffer() = default;
				GLIndexBuffer(const unsigned int* indices, unsigned int count);

				virtual ~GLIndexBuffer();
				virtual void bind();
				virtual void unbind();
				virtual void set_sub_data(const void* data, unsigned int size, unsigned int offset);
				virtual unsigned int get_count() const { return _Count; }

			private:
				unsigned int _Count;
			};
		}
	}
}

#endif