#include "Prepare.h"

#include <vector>

#include <dirent.h>


using FileServerInternal::FileInfo;

bool getAllFiles(const std::string& path, std::vector<std::string>& allFiles)
{
    DIR *dir;
    struct dirent *dirOrFileMsg;

    if((dir = opendir(path.c_str())) == NULL)
    {
        std::cout << "open directory " << path.c_str() << " failed!" << std::endl;
        return false;
    }
    
    while((dirOrFileMsg = readdir(dir)) != NULL)
    {
        std::string fileName(dirOrFileMsg->d_name);
        if(fileName== "." || fileName== "..")
            continue;
        else if(dirOrFileMsg->d_type == 4)
            getAllFiles(path + fileName + "/", allFiles);
        else if(dirOrFileMsg->d_type == 8)
            allFiles.push_back(path + fileName);
    }
    return true;
}

bool isZstdFile(const std::string& path) 
{
    auto const pos = path.find_last_of('.');
    if(std::string::npos != pos  && path.substr(pos + 1) == "zst") 
        return true;
    else
        return false;

}

std::string getZstdFileName(const std::string& path)
{
    auto const pos = path.find_first_of("_");
    if(pos == std::string::npos)
        return "";
    else
        return path.substr(0, pos);
}

std::string getZstdFileTimestamp(const std::string& path)
{
    auto const pos = path.find_first_of("_");
    if(pos == std::string::npos)
        return "";
    else
        return path.substr(pos + 1, 14); //TODO 根据时间戳长度进行修改
}

void createOrInsertFileNameAndTimestamp(std::map<std::string, std::vector<std::string>>& allIndexedFiles, const std::string& fileName, const std::string& timestamp)
{
    if(allIndexedFiles.count(fileName) != 0 && !timestamp.empty())
        allIndexedFiles[fileName].push_back(timestamp);//TODO优化push_back
    else if(!timestamp.empty())
        allIndexedFiles[fileName] = std::vector<std::string>(1, timestamp);
    else
        allIndexedFiles[fileName] = std::vector<std::string>();
}

void indexFileName(std::vector<std::string>& allFiles, std::map<std::string, std::vector<std::string>>& allIndexedFiles)
{
    for(std::vector<std::string>::const_iterator it = allFiles.begin(); it != allFiles.end(); ++it)  
    {
        if(isZstdFile(*it)) 
        {
            std::string fileName = getZstdFileName(*it);
            std::string fileTimestamp = getZstdFileTimestamp(*it);
            createOrInsertFileNameAndTimestamp(allIndexedFiles, fileName, timestamp);
        }
        else
            createOrInsertFileNameAndTimestamp(allIndexedFiles, *it, "");
    }
}

Prepare::Prepare()
{
}


Prepare::~Prepare()
{
}

std::map<std::string, FileInfo> Prepare::prepare()
{
    File zstdFile(path + "/zstdfile");
    std::map<std::string, FileInfo> infoMap; 
    if(zstdFile.isExist() && loadZstdFile(zstdFile, infoMap))
        return infoMap;
    else

    return infoMap;        
}


bool Prepare::loadZstdFile(const File& path, std::map<std::string, FileInfo>& infoMap) const
{
    return true;
    
}
bool Prepare::getAllFileInfo(const File& path, std::map<std::string, FileInfo>& infoMap) const
{
    return true;
}

int main()
{
    std::vector<std::string> files;
    if(getAllFiles("/Users/zoushengfu/Documents/code/Fsync/src/", files))
        if(!files.empty())
            for(auto file : files)
                std::cout << file << std::endl;
        else
            std::cout << "ssile" << std::endl;
    
   std::cout << "file" << std::endl;
    return 0;
}
