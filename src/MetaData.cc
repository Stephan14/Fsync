#include "MetaData.h"


#include <vector>
#include <iostream>
#include <algorithm>

#include "util/File.h"


MetaData::MetaData()
{
}

MetaData::~MetaData()
{
}

void MetaData::AddOrUpdateFileMsg(const std::string &filePath, const std::string &hash, const std::string &compressFile)
{
    if (filePath == "")
        return;
    mutex.lock();
    FileAndHash[filePath] = hash;
    FileAndCompress[filePath] = compressFile;
    mutex.unlock();
}

std::map<std::string, std::string> MetaData::GetFileMsg()
{
    std::map<std::string, std::string> res;
    mutex.lock();
    res = FileAndHash;
    mutex.unlock();
    return res;
}

std::map<std::string, std::string> MetaData::GetFileCompressMsg()
{
    std::map<std::string, std::string> res;
    mutex.lock();
    res = FileAndCompress;
    mutex.unlock();
    return res;
}

