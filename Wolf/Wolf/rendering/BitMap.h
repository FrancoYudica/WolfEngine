#ifndef WOLF_BIT_MAP
#define WOLF_BIT_MAP
#include <stdint.h>
#include <vector>
#include <glm/glm.hpp>
#include <cstring>
#include <iostream>

namespace Wolf
{
    namespace Rendering
    {
        template<typename T>
        class BitMap
        {
            public:
                const uint32_t width;
                const uint32_t height;

            public:
                BitMap(const BitMap& other)
                    : width(other.width), height(other.height)
                {
                    // Creates a new buffer
                    _raw_buffer = new T[width * height];
                    memcpy(_raw_buffer, other.buffer_raw_ptr(), sizeof(T) * width * height);
                    clear();
                }
                BitMap(uint32_t width, uint32_t height) 
                : width(width), height(height) {
                    _raw_buffer = new T[width * height];
                    clear();
                }

                BitMap(const glm::u32vec3& size) 
                : width(size.x), height(size.y) {
                    _raw_buffer = new T[width * height];
                    clear();
                }
                ~BitMap()
                {
                    delete[] _raw_buffer;
                }
                inline const T* buffer_raw_ptr() const { return _raw_buffer; }
                void clear()
                {
                    memset(_raw_buffer, 0, sizeof(T) * width * height);
                }

                void set_color(const glm::u32vec2& position, const T& color) 
                {
#ifdef WOLF_DEBUG_MODE
                    if (position.x > width - 1 || position.y > height - 1)
                    {
                        std::cout << "Index out of bounds" << std::endl;
                        throw "[BitMap::set_color] Pixel position out of bounds";
                    }
#endif  
                    _raw_buffer[position.x + position.y * width] = color;
                }

                T get_color(const glm::u32vec2 position) const
                {
                    // Returns a copy of the color
                    return _raw_buffer[position.x + position.y * width];
                }

            private:
                T* _raw_buffer;
        };
    }
}




#endif