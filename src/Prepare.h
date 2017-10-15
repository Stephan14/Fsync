#include "Server.pb.h"
#include "util/File.h"

#include <map>
#include <string>


class Prepare
{
    public:
    Prepare();
    ~Prepare();

    std::map<std::string, FileServerInternal::FileInfo> prepare();
    private:
    bool loadZstdFile(const File& path, std::map<std::string, FileServerInternal::FileInfo>& infoMap) const;
    bool getAllFileInfo(const File& path, std::map<std::string, FileServerInternal::FileInfo>& infoMap) const;

    std::string path;
};
