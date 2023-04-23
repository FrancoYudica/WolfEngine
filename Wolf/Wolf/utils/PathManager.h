#ifndef WOLF_PATH_MANAGER_H
#define WOLF_PATH_MANAGER_H
#include <filesystem>
#include <string>

namespace Wolf
{

    class Path
    {
        public:
        Path() : _path("empty") {}
        Path(const std::string& file_path)
            : _path(file_path) {}

        Path(const std::filesystem::path& path) 
            : _path(path) {}

        operator std::string () const { return _path.string(); }
        bool exists() const { return std::filesystem::exists(_path); }

        Path operator / (const std::string& extra) const
        { 
            return _path.string() + '\\' + extra;
        }
        Path& operator /= (const std::string& extra) 
        { 
            _path /= extra;
            return *this;
        }
        Path parent() { return Path(_path.parent_path()); }
        bool is_directory() { return std::filesystem::is_directory(_path); }
        private:
        std::filesystem::path _path;
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
            Path path = std::filesystem::current_path().parent_path().parent_path();
            _root_path = std::string("../../");
            _engine_assets_path = _root_path / "Wolf/Wolf/assets";
        }
        const Path& get_root_path() { return _root_path; }
        const Path& get_engine_assets_path() { return _engine_assets_path; }

        private:
        Path _root_path;
        Path _engine_assets_path;



    };
}

#endif