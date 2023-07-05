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
            // The way the texture is sampled, when the sampling bounds are reached
            enum WrapMode {REPEAT, MIRRORED_REPEAT, CLAMP_TO_EDGE, CLAMP_TO_BORDER};

            // For magnification and minimization filters
            enum Filter {NEAREST, LINEAR};

            // Pixel format specifies the format of the color in the given buffer
            enum PixelFormat {R, RGB, RGBA}; 

            // Internal format specifies the format in which the rendering API interprets colors
            enum PixelInternalFormat {R_8, RGB_8, RGBA_8}; 

            // Pixel type specifies the range in which the color values are
            enum PixelType {UNSIGNED_BYTE, BYTE, FLOAT};
        }
        struct TextureConfig
        {
            TextureTypes::WrapMode wrap_mode;
            TextureTypes::Filter mag_filter;
            TextureTypes::Filter min_filter;
            TextureTypes::PixelFormat pixel_format;
            TextureTypes::PixelInternalFormat internal_pixel_format;
            TextureTypes::PixelType pixel_type;
            uint32_t samples;

            TextureConfig()
                : 
                wrap_mode(TextureTypes::WrapMode::REPEAT),
                mag_filter(TextureTypes::Filter::LINEAR),
                min_filter(TextureTypes::Filter::LINEAR),
                pixel_format(TextureTypes::PixelFormat::RGBA),
                internal_pixel_format(TextureTypes::PixelInternalFormat::RGBA_8),
                pixel_type(TextureTypes::PixelType::UNSIGNED_BYTE),
                samples(1)
            {}
        };

        class Texture
        {
            // GPU Texture, it doesn't store the pixel buffer
            public:
                Texture() = default;
                Texture(uint32_t renderer_id) : _renderer_id(renderer_id) {}
                virtual ~Texture() = default;
                virtual void bind() = 0;

                inline uint32_t get_id() const { return _renderer_id; }

                static void activate_texture(const Shared<Texture>& texture, uint8_t slot);

                static Shared<Texture> from_bitmap(const Shared<BitMap<glm::u8vec4>>& bitmap, const TextureConfig& config);
                static Shared<Texture> from_bitmap(const Shared<BitMap<glm::u8vec3>>& bitmap, const TextureConfig& config);
                static Shared<Texture> from_bitmap(const Shared<BitMap<glm::vec4>>& bitmap, const TextureConfig& config);
                static Shared<Texture> from_bitmap(const Shared<BitMap<glm::vec3>>& bitmap, const TextureConfig& config);
                static Shared<Texture> from_bitmap(const Shared<BitMap<float>>& bitmap, const TextureConfig& config);

            protected:
                uint32_t _renderer_id;

            
        };
    }
}

#endif