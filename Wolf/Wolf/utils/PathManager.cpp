#include "PathManager.h"
#include <filesystem>

namespace Wolf {
namespace Path {
    static FilePath s_root_path = "./..";
    static FilePath s_engine_assets_path = s_root_path / (std::string(WOLF_ENGINE_PATH) + "/Wolf/engine_assets");
    FilePath get_root_folder()
    {
        return s_root_path;
    }
    FilePath get_engine_assets_folder()
    {
        return s_engine_assets_path;
    }

    std::vector<FilePath> get_folder_files(const FilePath folder)
    {
        std::vector<FilePath> files;
        for (const auto& file : std::filesystem::directory_iterator(folder.string())) {
            files.push_back(FilePath(file.path().string()));
        }
        return files;
    }
}
}