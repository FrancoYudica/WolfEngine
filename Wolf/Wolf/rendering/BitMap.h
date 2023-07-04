#ifndef WOLF_BIT_MAP
#define WOLF_BIT_MAP
#include <stdint.h>
#include <vector>
#include <glm/glm.hpp>
#include <cstring>

namespace Wolf
{
    namespace Rendering
    {
        class BitMap
        {
            // 3 Channel bit buffer
            public:
                const uint32_t width;
                const uint32_t height;

            public:
                BitMap(uint32_t width, uint32_t height) 
                : width(width), height(height) {
                    _buffer.reserve(width * height);
                    memset(_buffer.data(), 0, sizeof(glm::u8vec3) * width * height);
                }

                BitMap(const glm::u32vec3& size) 
                : width(size.x), height(size.y) {
                    _buffer.reserve(width * height);
                    memset(_buffer.data(), 0, sizeof(glm::u8vec3) * width * height);
                }

                inline const std::vector<glm::u8vec3>& get_buffer() const { return _buffer; }

                void clear()
                {
                    memset(_buffer.data(), 0, sizeof(glm::u8vec3) * width * height);
                }

                void set_color(const glm::u32vec2& position, const glm::u8vec3& color) 
                {
                    _buffer[position.x + position.y * width] = color;
                }

                glm::u8vec3 get_color(const glm::u32vec2 position) const
                {
                    // Returns a copy of the color
                    return _buffer[position.x + position.y * width];
                }

            private:

                std::vector<glm::u8vec3> _buffer;
        };
    }
}




#endif