#ifndef WOLF_PATH_MANAGER_H
#define WOLF_PATH_MANAGER_H
#include <filesystem>
#include <string>

using namespace std::filesystem;

namespace Wolf
{

    class Path
    {
        public:
            Path() : _path("empty") {}
            Path(const std::string& file_path)
                : _path(file_path) {}

            Path(const char* c_str)
                : _path(std::string(c_str)) {}

            Path(const path& path) 
                : _path(path) {}

            operator std::string () const { return _path.string(); }
            bool exists() const { return std::filesystem::exists(_path); }

            Path operator / (const std::string& extra) const
            { 
                return _path.string() + '/' + extra;
            }
            Path& operator /= (const std::string& extra) 
            { 
                _path /= extra;
                return *this;
            }
            inline Path parent() const { return Path(_path.parent_path()); }
            inline bool is_directory() const { return std::filesystem::is_directory(_path); }
            inline const char* c_str() const { return _path.string().c_str();  }

        private:
            path _path;
    };

    class PathManager
    {
        // Class used to store important paths, relative to the build folder
        public:
            static PathManager& get_instance() {
                static PathManager manager;
                return manager;
            }

            PathManager() {
                _root_path = std::string("..");
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