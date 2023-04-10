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
				GLShaderProgram(const char* vertex_shader_source, const char* fragment_shader_source);
				virtual void bind();
				virtual void unbind();
				virtual void set_float(const std::string& name, float value);
				virtual void set_float(const std::string& name, const glm::vec2& value);
				virtual void set_float(const std::string& name, const glm::vec3& value);
				virtual void set_float(const std::string& name, const glm::vec4& value);

				virtual void set_int(const std::string& name, int value);

			private:
				unsigned int compile_shader(const char* source, unsigned int type);
			};

		}
	}
}
#endif