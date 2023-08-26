#pragma once
#ifndef __WOLF_LINE_BATCH_H__
#define __WOLF_LINE_BATCH_H__

#include "Batch.h"
#include <glm/glm.hpp>

namespace Wolf {

namespace Rendering {

    struct LineVertex {
        glm::vec3 position;
        glm::vec4 color;
    };

    class LineBatch : public Batch {
    public:
        void init(Shared<Material>& material) override;
        void shutdown() override;
        void new_frame() override;
        void end_frame() override;
        void submit_primitive(const glm::vec2& p0, const glm::vec2& p1, const glm::vec4& color, const float thickness);
        void submit_primitive_interpolated(const glm::vec2& p0, const glm::vec2& p1, const glm::vec4& color, const float thickness);

    private:
        void _flush();

    private:
        LineVertex* _buffer;
    };
}

}

#endif