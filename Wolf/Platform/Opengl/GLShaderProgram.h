#pragma once
#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include "rendering/ShaderProgram.h"
#include <glm/glm.hpp>

namespace Wolf
{
	namespace Rendering
	{
		namespace GL
		{


			class GLShaderProgram : public Wolf::Rendering::ShaderProgram
			{

			public:

				unsigned int ID;
				GLShaderProgram() = default;
				GLShaderProgram(const string& vertex_src, const string& fragment_src);
				virtual void bind();
				virtual void unbind();
				virtual void set_float(const string& name, float value);
				virtual void set_float(const string& name, const glm::vec2& value);
				virtual void set_float(const string& name, const glm::vec3& value);
				virtual void set_float(const string& name, const glm::vec4& value);

				virtual void set_int(const string& name, int value);

			private:
				unsigned int compile_shader(const string& source, unsigned int type);
			};

		}
	}
}
#endif