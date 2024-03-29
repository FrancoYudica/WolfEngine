#pragma once
#ifndef __WOLF_RENDER_COMMAND_H__
#define __WOLF_RENDER_COMMAND_H__
#include "../core/wolf_types.h"
#include "Buffer.h"
#include "VertexArray.h"

namespace Wolf {
namespace Rendering {

    enum BlendMode {
        Transparent
    };
    enum PrimitiveType {
        Triangles,
        TriangleStrip,
        Lines
    };
    class RenderCommand {
    public:
        static void set_clear_color(float r, float g, float b, float a);
        static void clear();
        static void draw_indexed(const Shared<VertexArray>& vao, int count, PrimitiveType primitive);
        static void draw_arrays(const Shared<VertexArray>& vao, uint32_t count, PrimitiveType primitive);
        static void set_blending_mode(BlendMode mode);
    };

}
}

#endif