/*

Path class implementation.
This implementation works with relative paths, so all paths
should start with "./" or ".". It means that if we want to
set a file path, adding the relative folder is necessary.
Exceptions only work WOLF_DEBUG_MODE
*/

#ifndef __WOLF_PATH_MANAGER_H__
#define __WOLF_PATH_MANAGER_H__
#include <filesystem>

using namespace std::filesystem;

#ifdef WOLF_DEBUG_MODE
#include <cstring>
#include <iostream>
#define WOLF_ASSERT(expr, msg)                                                                            \
    if (!(expr)) {                                                                                        \
        std::cout << "[WOLF_ASSERT]: " << __FILE__ << " at line " << __LINE__ << " " << msg << std::endl; \
        assert(false);                                                                                    \
    }
#else
#define WOLF_ASSERT(e, m)
#endif

namespace Wolf {

class Path {
public:
    Path()
        : _path("./")
    {
    }
    Path(const Path& p)
        : _path(p.c_str())
    {
        WOLF_ASSERT((char)p.c_str()[0] == '.', "Trying to create non relative path: " << p.c_str());
    }
    Path(const std::string& file_path)
        : _path(file_path)
    {
        WOLF_ASSERT((char)file_path.at(0) == '.', "Trying to create non relative path: " << file_path);
    }

    Path(const char* c_str)
        : _path(c_str)
    {
        WOLF_ASSERT((char)c_str[0] == '.', "Trying to create non relative path: " << c_str);
    }

    Path(const path& p)
        : _path(p)
    {
        WOLF_ASSERT(((char)p.c_str()[0] == '.'), "Trying to create non relative path: " << p);
    }

    operator std::string() const
    {
        return _path.c_str();
    }
    bool exists() const
    {
        return std::filesystem::exists(_path);
    }

    Path operator/(const std::string& extra) const
    {
        return _path.string() + '/' + extra;
    }
    Path& operator/=(const std::string& extra)
    {
        _path /= extra;
        return *this;
    }
    inline Path parent() const
    {
        return Path(_path.parent_path());
    }
    inline bool is_directory() const
    {
        return std::filesystem::is_directory(_path);
    }
    inline const char* c_str() const
    {
        return _path.c_str();
    }

private:
    path _path;
};

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
    const Path& get_root_path() { return _root_path; }
    const Path& get_engine_assets_path() { return _engine_assets_path; }

private:
    Path _root_path;
    Path _engine_assets_path;
};
}

#endif