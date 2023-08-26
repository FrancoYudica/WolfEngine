#pragma once
#ifndef __WOLF_GRAPHICS_CONTEXT__
#define __WOLF_GRAPHICS_CONTEXT__
#include "Window.h"
#include "wolf_types.h"
#include <memory>

namespace Wolf {
class GraphicsContext {
public:
    GraphicsContext() = default;
    virtual void init() = 0;
    virtual void on_viewport_resize(uint32_t width, uint32_t height) = 0;
    static Shared<GraphicsContext> create(Unique<Window>& window);
};
}
#endif