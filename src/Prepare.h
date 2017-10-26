#ifndef _PREPARE_H
#define _PREPARE_H

#include "Server.pb.h"
#include "util/File.h"

#include <map>
#include <string>


bool getAllFiles(const std::string& path, std::vector<std::string>& allFiles);

bool isZstdFile(const std::string& path);
std::string getZstdFileName(const std::string& path);
std::string getZstdFileTimestamp(const std::string& path);
void createOrInsertFileNameAndTimestamp(std::map<std::string, std::vector<std::string> >& allIndexedFiles, const std::string& fileName, const std::string& timestamp);
void indexFileName(std::vector<std::string>& allFiles, std::map<std::string, std::vector<std::string> >& allIndexedFiles);


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
#endif
