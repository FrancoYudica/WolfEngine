#include <filesystem>
#include "FilePath.h"



bool Wolf::FilePath::is_directory() const
{
    return std::filesystem::is_directory(_path);
}
bool Wolf::FilePath::exists() const
{
    return std::filesystem::exists(_path);
}