#ifndef WOLF_TYPES_H
#define WOLF_TYPES_H
#include <memory>

namespace Wolf
{
    template<class T>
    using Shared = std::shared_ptr<T>;
    
    template<class T>
    using Unique = std::unique_ptr<T>;
    
}
#endif