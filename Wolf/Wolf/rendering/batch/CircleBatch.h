#pragma once
#ifndef __WOLF_CIRCLE_BATCH_H__
#define __WOLF_CIRCLE_BATCH_H__

#include "Batch.h"
#include <glm/glm.hpp>

namespace Wolf {

namespace Rendering {

    struct CircleVertex {
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 uv;
        float radius;
        float fade;
    };

    class CircleBatch : public Batch {
    public:
        void init(Shared<Material>& material) override;
        void shutdown() override;
        void new_frame() override;
        void end_frame() override;
        void submit_primitive(const glm::vec3& position, const float radius, const glm::vec4& color, float fade);

    private:
        void _flush();

    private:
        CircleVertex* _buffer;
    };
}

}

#endif