#pragma once
#ifndef __WOLF_GL_TEXTURE__
#define __WOLF_GL_TEXTURE__
#include "rendering/Texture.h"
#include <stdint.h>

namespace Wolf {
namespace Rendering {
    namespace GL {

        struct GLTextureConfig {
            // OpenGL types equivalent to Wolf::Rendering::TextureConfig
            uint32_t target;
            int32_t pixel_format, internal_pixel_format;
            uint32_t pixel_type;

            // Texture parameters
            int32_t wrap_mode;
            int32_t mag_filter, min_filter;
            uint32_t samples;
        };

        class GLTexture : public Texture {
            // GPU Texture, it doesn't store the pixel buffer
        public:
            GLTexture() = default;
            GLTexture(uint32_t renderer_id)
                : Texture(renderer_id)
            {
            }
            ~GLTexture() override;
            void bind() override;

        public:
            uint32_t target;
        };
    }
}
}

// #include "TextureTcc.tcc"

#endif