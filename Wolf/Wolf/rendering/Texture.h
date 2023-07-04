#pragma once
#ifndef WOLF_TEXTURE_H
#define WOLF_TEXTURE_H
#include <stdint.h>
#include <vector>
#include "BitMap.h"
#include "../core/wolf_types.h"


namespace Wolf
{
    namespace Rendering
    {

        namespace TextureTypes
        {
            enum WrapMode {REPEAT, MIRRORED_REPEAT, CLAMP_TO_EDGE, CLAMP_TO_BORDER};
            enum Filter {NEAREST, LINEAR};
            enum PixelFormat {R, RG, RGB, RGBA}; 
            enum PixelType {UnsignedByte, Byte, Float};
        }
        struct TextureConfig
        {
            TextureTypes::WrapMode wrap_mode;
            TextureTypes::Filter mag_filter;
            TextureTypes::Filter min_filter;
            TextureTypes::PixelFormat pixel_format;
            TextureTypes::PixelFormat internal_pixel_format;
            TextureTypes::PixelType pixel_type;
            uint32_t samples;

            TextureConfig()
                : 
                wrap_mode(TextureTypes::WrapMode::REPEAT),
                mag_filter(TextureTypes::Filter::LINEAR),
                min_filter(TextureTypes::Filter::LINEAR),
                pixel_format(TextureTypes::PixelFormat::RGB),
                internal_pixel_format(TextureTypes::PixelFormat::RGB),
                pixel_type(TextureTypes::PixelType::UnsignedByte), // Default buffer is given in [0, 255]
                samples(1)
            {}
        };

        class Texture
        {
            // GPU Texture, it doesn't store the pixel buffer
            public:
                Texture() = default;
                virtual ~Texture() = default;
                virtual void bind() = 0;

                inline uint32_t get_id() const { return _renderer_id; }
                static Shared<Texture> initialize_from_bitmap(const Shared<BitMap>& bitmap, const TextureConfig& config);
                static void activate_texture(const Shared<Texture>& texture, uint8_t slot);

            protected:
                uint32_t _renderer_id;

            
        };
    }
}

#endif