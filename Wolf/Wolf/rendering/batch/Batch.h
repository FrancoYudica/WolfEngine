#pragma once
#ifndef WOLF_BATCH_H
#define WOLF_BATCH_H

#include <glm/glm.hpp>
#include "../VertexArray.h"
#include "../Buffer.h"
#include "../Material.h"
#include "../Camera.h"
#include "../../core/wolf_types.h"

namespace Wolf
{

    namespace Rendering
    {
        class Batch
        {
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