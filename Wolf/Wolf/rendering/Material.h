#pragma once
#ifndef __WOLF_MATERIAL_H__
#define __WOLF_MATERIAL_H__

#include "../core/wolf_types.h"
#include "MaterialAttribute.h"
#include <vector>

namespace Wolf {
namespace Rendering {
    class Material {
    public:
        Material() = default;

        bool contains_property(const std::string& name) const;
        Shared<MaterialProperty>& get_property(const std::string& name);
        inline const Shared<ShaderProgram>& get_shader() const { return _shader; }
        void set_shader_program(const Shared<ShaderProgram>& shader);
        void upload() const;

        void add_float(const std::string& name, float value);
        void add_float2(const std::string& name, glm::vec2 value);
        void add_float3(const std::string& name, glm::vec3 value);
        void add_float4(const std::string& name, glm::vec4 value);

    private:
        void _control_existing_property(const std::string& attr);

    private:
        std::vector<Shared<MaterialProperty>> _properties;
        Shared<ShaderProgram> _shader;
    };
}
}

#endif