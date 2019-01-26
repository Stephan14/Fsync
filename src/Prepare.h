#ifndef _PREPARE_H
#define _PREPARE_H

#include "Server.pb.h"
#include "util/File.h"

#include <map>
#include <string>
#include <iostream>


bool GetAllFiles(const std::string& path, std::vector<std::string>& allFiles);

bool IsZstdFile(const std::string& path);
std::string GetZstdFileName(const std::string& path);
std::string GetZstdFileTimestamp(const std::string& path);
void CreateOrInsertFileNameAndTimestamp(std::map<std::string, std::vector<std::string> >& allIndexedFiles, const std::string& fileName, const std::string& timestamp);
void IndexFileName(std::vector<std::string>& allFiles, std::map<std::string, std::vector<std::string> >& allIndexedFiles);


class Prepare
{
    public:
    Prepare();
    ~Prepare();

    std::map<std::string, FileServerInternal::FileInfo> PrepareAdvance();
    private:
    bool LoadZstdFile(const File& path, std::map<std::string, FileServerInternal::FileInfo>& infoMap) const;
    bool GetAllFileInfo(const File& path, std::map<std::string, FileServerInternal::FileInfo>& infoMap) const;

    std::string Path;
};
#endif
