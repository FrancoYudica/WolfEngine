#pragma once
#ifndef __WOLF_BATCH_H__
#define __WOLF_BATCH_H__

#include "../../core/wolf_types.h"
#include "../Buffer.h"
#include "../Camera.h"
#include "../Material.h"
#include "../VertexArray.h"
#include <glm/glm.hpp>

namespace Wolf {

namespace Rendering {
    class Batch {
    public:
        virtual void init(Shared<Material>& material)
        {
            _material = material;
        }
        virtual void begin_scene(const Camera& camera) { _camera = camera; }
        virtual void shutdown() = 0;
        virtual void new_frame() = 0;
        virtual void end_frame() = 0;

    protected:
        Shared<VertexArray> _vertex_array;
        Shared<VertexBuffer> _vertex_buffer;
        Shared<IndexBuffer> _index_buffer;
        Shared<Material> _material;
        uint32_t _submissions_count;
        uint32_t _MAX_SUBMISSIONS;
        Camera _camera;
    };
}

}

#endif