#ifndef __WOLF_ASSETS_H__
#define __WOLF_ASSETS_H__
#define STB_IMAGE_IMPLEMENTATION
#include "../core/wolf_types.h"
#include "../rendering/BitMap.h"
#include "../utils/PathManager.h"


namespace Wolf
{
    namespace Assets
    {
        class Loader
        {
            public:
                static Shared<Rendering::BitMap<RGBA8_UI>> load_bitmap(
                    const Wolf::Path& path,
                    bool& success
                );
        };

        class Writer
        {
            public:

                static bool write_bitmap_png(
                    const Wolf::Path& path,
                    const Shared<Rendering::BitMap<RGBA8_UI>>& bitmap
                );
                static bool write_bitmap_jpg(
                    const Wolf::Path& path,
                    const Shared<Rendering::BitMap<RGBA8_UI>>& bitmap,
                    uint32_t quality
                );
        };
    }
}


#endif