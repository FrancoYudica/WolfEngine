#ifndef WOLF_TYPES_H
#define WOLF_TYPES_H
#include <memory>
#include <glm/glm.hpp>


namespace Wolf
{
    template<class T>
    using Shared = std::shared_ptr<T>;
    
    template<class T>
    using Unique = std::unique_ptr<T>;

    typedef glm::u8vec4 RGBA8_UI;
    typedef glm::vec4   RGBA32_F;

}
#endif