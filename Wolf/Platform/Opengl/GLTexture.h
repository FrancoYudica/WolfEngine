#pragma once
#ifndef GL_TEXTURE_H
#define GL_TEXTURE_H
#include "rendering/Texture.h"


namespace Wolf
{
    namespace Rendering
    {
        namespace GL
        {
            class GLTexture : public Texture
            {
                // GPU Texture, it doesn't store the pixel buffer
                public:
                    GLTexture() = default;
                    ~GLTexture() override;
                    void bind() override;
                private:
                    uint32_t _target;
                friend Shared<Texture> Texture::initialize_from_bitmap(const Shared<BitMap>&, const TextureConfig&);
            };
        }
    }
}

#endif