#include <filesystem>
#include "FilePath.h"

namespace Wolf {
namespace Path {
    bool FilePath::is_directory() const
    {
        return std::filesystem::is_directory(_path);
    }
    bool FilePath::exists() const
    {
        return std::filesystem::exists(_path);
    }
}
}