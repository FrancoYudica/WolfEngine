#pragma once
#ifndef __WOLF_SHADER_PROGRAM_H__
#define __WOLF_SHADER_PROGRAM_H__
#include "../core/wolf_types.h"
#include "../utils/File.h"
#include "../utils/PathManager.h"
#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

using std::string;

namespace Wolf {
namespace Rendering {
    class ShaderProgram {

    public:
        ShaderProgram() = default;
        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual void set_float(const string& name, float value) const = 0;
        virtual void set_float(const string& name, const glm::vec2& value) const = 0;
        virtual void set_float(const string& name, const glm::vec3& value) const = 0;
        virtual void set_float(const string& name, const glm::vec4& value) const = 0;
        virtual void set_int(const string& name, int value) const = 0;
        virtual void set_matrix(const string& name, const glm::mat4& matrix) const = 0;
        static Shared<ShaderProgram> create(const string& vertex_src, const string& fragment_src);

        static Shared<ShaderProgram> create(
            const Path::FilePath& vertex_path,
            const Path::FilePath& fragment_path)
        {

            if (!vertex_path.exists()) {
                std::cout << "ERROR: ShaderProgram::create. Vertex path doesn't exist" << std::string(vertex_path) << std::endl;
            }
            if (!fragment_path.exists()) {
                std::cout << "ERROR: ShaderProgram::create. Fragment path doesn't exist" << std::string(fragment_path) << std::endl;
            }

            auto vertex_file = Wolf::File(vertex_path);
            auto fragment_file = Wolf::File(fragment_path);
            return create(
                vertex_file.read(),
                fragment_file.read());
        }
    };

    class ShaderLibrary {
    public:
        ShaderLibrary() = default;
        void add(const string& name, const Shared<ShaderProgram>& program)
        {
            _shaders[name] = program;
        }

        Shared<ShaderProgram> get(const string& name)
        {
            return _shaders[name];
        }

    private:
        std::unordered_map<string, Shared<ShaderProgram>> _shaders;
    };

}
}

#endif