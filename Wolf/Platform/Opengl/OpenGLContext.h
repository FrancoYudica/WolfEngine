#pragma once
#ifndef __WOLF_OPENGL_CONTEXT__
#define __WOLF_OPENGL_CONTEXT__

#include "core/GraphicsContext.h"
namespace Wolf {
namespace Rendering {
    namespace GL {
        class GLGraphicsContext : public GraphicsContext {
        public:
            GLGraphicsContext() = default;
            GLGraphicsContext(void* glfwWindow)
                : _glfwWindow(glfwWindow)
            {
            }

            virtual void init();
            void on_viewport_resize(uint32_t width, uint32_t height);

        private:
            void* _glfwWindow;
        };

    }
}
}
#endif