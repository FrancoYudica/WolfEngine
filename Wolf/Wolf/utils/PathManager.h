#ifndef __WOLF_PATH_MANAGER_H__
#define __WOLF_PATH_MANAGER_H__
#include "FilePath.h"
#include <vector>

namespace Wolf {
namespace Path {

    /// @return Relative executable filepath
    FilePath get_root_folder();

    /// @return Relative engine assets folder path
    FilePath get_engine_assets_folder();

    std::vector<FilePath> get_folder_files(const FilePath folder);

}
}

#endif