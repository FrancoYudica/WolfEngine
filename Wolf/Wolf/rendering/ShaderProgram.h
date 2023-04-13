#pragma once
#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#include <string>
#include <unordered_map>
#include <iostream>
#include <glm/glm.hpp>
#include <memory>

namespace Wolf
{
	namespace Rendering
	{
		class ShaderProgram
		{

		public:
			ShaderProgram() = default;
			virtual void bind() = 0;
			virtual void unbind() = 0;

			virtual void set_float(const std::string& name, float value) = 0;
			virtual void set_float(const std::string& name, const glm::vec2& value) = 0;
			virtual void set_float(const std::string& name, const glm::vec3& value) = 0;
			virtual void set_float(const std::string& name, const glm::vec4& value) = 0;

			virtual void set_int(const std::string& name, int value) = 0;

			static std::shared_ptr<ShaderProgram> Create(const char* vertex_src, const char* fragment_src);


		};

		class ShaderLibrary
		{
		public:
			ShaderLibrary() = default;
			void add(const std::string& name, const std::shared_ptr<ShaderProgram>& program)
			{
				_Shaders[name] = program;
			}

			std::shared_ptr<ShaderProgram> get(const std::string& name)
			{
				return _Shaders[name];
			}

		private:
			std::unordered_map <std::string, std::shared_ptr<ShaderProgram>> _Shaders;
		};

	}
}


#endif