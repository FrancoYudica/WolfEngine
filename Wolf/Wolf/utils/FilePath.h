/*

FilePath class implementation.
This implementation works with relative paths, so all paths
should start with "./" or ".". It means that if we want to
set a file path, adding the relative folder is necessary.
Exceptions only work WOLF_DEBUG_MODE
*/

#ifndef __WOLF_FILE_PATH_H__
#define __WOLF_FILE_PATH_H__
#include <string>

#ifdef WOLF_DEBUG_MODE
#include <cstring>
#include <iostream>
#include <cassert>
#define WOLF_ASSERT(expr, msg)                                                                            \
    if (!(expr)) {                                                                                        \
        std::cout << "[WOLF_ASSERT]: " << __FILE__ << " at line " << __LINE__ << " " << msg << std::endl; \
        assert(false);                                                                                    \
    }
#else
#define WOLF_ASSERT(e, m)
#endif

namespace Wolf {

class FilePath {
public:
    FilePath()
        : _path("./")
    {
    }
    FilePath(const FilePath& p) 
        : _path(p.c_str())
    {
        WOLF_ASSERT((char)p.c_str()[0] == '.', "Trying to create non relative FilePath: " << p.c_str());
    }
    FilePath(const std::string& file_path)
        : _path(file_path)
    {
        WOLF_ASSERT((char)file_path.at(0) == '.', "Trying to create non relative path: " << file_path);
    }

    FilePath(const char* c_str)
        : _path(c_str)
    {
        WOLF_ASSERT((char)c_str[0] == '.', "Trying to create non relative FilePath: " << c_str);
    }

    bool exists() const;
    bool is_directory() const;

    operator std::string() const
    {
        return _path;
    }

    FilePath operator/(const std::string& extra) const
    {
        return _path + '/' + extra;
    }
    FilePath& operator/=(const std::string& extra)
    {
        _path = *this / extra;
        return *this;
    }
    inline const char* c_str() const
    {
        return _path.c_str();
    }

private:
    std::string _path;
};
}

#endif