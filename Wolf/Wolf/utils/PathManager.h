#ifndef __WOLF_PATH_MANAGER_H__
#define __WOLF_PATH_MANAGER_H__
#include "FilePath.h"

namespace Wolf
{
class PathManager {
    // Class used to store important paths, relative to the build folder
public:
    static PathManager& get_instance()
    {
        static PathManager manager;
        return manager;
    }

    PathManager()
    {
        _root_path = std::string("./..");
        _engine_assets_path = _root_path / (std::string(WOLF_ENGINE_PATH) + "/Wolf/Wolf/engine_assets");
    }
    const FilePath& get_root_path() { return _root_path; }
    const FilePath& get_engine_assets_path() { return _engine_assets_path; }

private:
    FilePath _root_path;
    FilePath _engine_assets_path;
};
}

#endif