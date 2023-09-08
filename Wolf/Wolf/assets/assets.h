#ifndef __WOLF_ASSETS_H__
#define __WOLF_ASSETS_H__
#include "../core/wolf_types.h"
#include "../rendering/BitMap.h"
#include "../utils/PathManager.h"

namespace Wolf {
namespace Assets {
    
    /// @brief Loads bitmap from disk
    Shared<Rendering::BitMap<RGBA8_UI>> load_bitmap(
        const FilePath path,
        bool& success);

    /// @brief Writes bitmap to disk with png format
    bool save_bitmap_png(
        const FilePath path,
        const Shared<Rendering::BitMap<RGBA8_UI>>& bitmap,
        bool flip_vertically = true);

    /// @brief Writes bitmap to disk with jpg format
    bool save_bitmap_jpg(
        const FilePath path,
        const Shared<Rendering::BitMap<RGBA8_UI>>& bitmap,
        uint32_t quality,
        bool flip_vertically = true);
}
}

#endif