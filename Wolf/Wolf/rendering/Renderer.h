#pragma once
#ifndef __WOLF_BATCH_RENDERER_H__
#define __WOLF_BATCH_RENDERER_H__

#include "Camera.h"
#include "Material.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include "../numerical/Bounds.h"

#define RENDERER_MAX_TEXTURE_SLOTS 32

namespace Wolf {
namespace Rendering {

    class Renderer2D {
        /*
         * 2D Quad batch renderer
         */

    public:
        static void init();
        static void shutdown();
        static void begin_scene(const Camera& camera);
        static void new_frame();
        static void end_frame();

        static void submit_quad(
            const glm::vec3& position,
            const glm::vec3& size,
            const glm::vec4& color);

        static void submit_quad(
            const glm::vec3& position,
            const glm::vec3& size,
            const glm::vec4& color,
            const Shared<Texture>& texture);

        static void submit_quad(
            const glm::vec3& position,
            const glm::vec3& size,
            const glm::vec4& color,
            const Shared<Texture>& texture,
            const Numerical::Bounds<glm::vec2>& bounds);

        static void submit_circle(
            const glm::vec3& position,
            const float radius,
            const glm::vec4& color,
            float fade = 0.003f);

        static void submit_line(
            const glm::vec2& p0,
            const glm::vec2& p1,
            const glm::vec4& color,
            const float thickness);

        static void submit_line_interpolated(
            const glm::vec2& p0,
            const glm::vec2& p1,
            const glm::vec4& color,
            const float thickness);

        static void render_material(const Shared<Material>& material);
    };

}
}

#endif
