#ifndef __WOLF_FILE__
#define __WOLF_FILE__

#include <filesystem>
#include <string>

using std::string;

namespace Wolf {
class File {
public:
    File(const string& path)
        : _fpath(path)
    {
    }

    string read() const;
    void write(const string&);

private:
    string _fpath;
};
}

#endif