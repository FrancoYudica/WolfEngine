#pragma once
#ifndef __WOLF_VERTEX_ARRAY_H__
#define __WOLF_VERTEX_ARRAY_H__
#include "../core/wolf_types.h"
#include "Buffer.h"

namespace Wolf {
namespace Rendering {
    class VertexArray {
    public:
        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual void add_vertex_buffer(const Shared<VertexBuffer>& vb) = 0;
        virtual void set_index_buffer(const Shared<IndexBuffer>& ib) = 0;
        virtual const std::vector<Shared<VertexBuffer>>& get_vertex_buffers() const = 0;
        virtual const Shared<IndexBuffer>& get_index_buffer() const = 0;

        static Shared<VertexArray> create();
    };

}
}

#endif