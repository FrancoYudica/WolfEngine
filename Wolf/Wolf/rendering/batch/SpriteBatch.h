#pragma once
#ifndef __WOLF_SPRITE_BATCH_H__
#define __WOLF_SPRITE_BATCH_H__

#include "../../core/wolf_types.h"
#include "../Texture.h"
#include "Batch.h"
#include <glm/glm.hpp>
namespace Wolf {

namespace Rendering {

    struct SpriteVertex {
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 uv;
        float texture_slot;
    };

    class SpriteBatch : public Batch {
    public:
        void init(Shared<Material>& material) override;
        void shutdown() override;
        void new_frame() override;
        void end_frame() override;

        void submit_primitive(
            const glm::vec3& position,
            const glm::vec3& size,
            const glm::vec4& color);

        void submit_primitive(
            const glm::vec3& position,
            const glm::vec3& size,
            const glm::vec4& color,
            uint32_t texture_slot);

        void submit_primitive(
            const glm::vec3& position,
            const glm::vec3& size,
            const glm::vec4& color,
            uint32_t texture_slot,
            const glm::vec2& min_uv,
            const glm::vec2& max_uv);

    private:
        void _flush();

    private:
        SpriteVertex* _buffer;
    };
}

}

#endif