#ifndef __WOLF_BOUNDS__
#define __WOLF_BOUNDS__

namespace Wolf {
namespace Numerical {
    template <class T>
    struct Bounds {
        T min;
        T max;
    };
}
}

#endif