#include "Prepare.h"

#include <vector>

#include <dirent.h>


using FileServerInternal::FileInfo;

bool GetAllFiles(const std::string& path, std::vector<std::string>& all_files) {
    DIR *dir;
    struct dirent *file_msg;

    if ((dir = opendir(path.c_str())) == NULL) {
        std::cout << "open directory " << path.c_str() << " failed!" << std::endl;
        return false;
    }
     
    while ((file_msg = readdir(dir)) != NULL) {
        std::string file_name(file_msg->d_name);
        if(file_name== "." || file_name== "..")
            continue;
        else if(file_msg->d_type == 4)
            GetAllFiles(path + file_name + "/", all_files);
        else if(file_msg->d_type == 8)
            all_files.push_back(path + file_name);
    }

    return true;
}

bool IsZstdFile(const std::string& path) {
    auto const pos = path.find_last_of('.');
    if(std::string::npos != pos  && path.substr(pos + 1) == "zst") 
        return true;
    else
        return false;
}

std::string GetZstdFileName(const std::string& path) {
    auto const pos = path.find_first_of("_");
    if(pos == std::string::npos)
        return "";
    else
        return path.substr(0, pos);
}

std::string GetZstdFileTimestamp(const std::string& path) {
    auto const pos = path.find_first_of("_");
    if(pos == std::string::npos)
        return "";
    else
        return path.substr(pos + 1, 4); //TODO 根据时间戳长度进行修改
}

void CreateOrInsertFileNameAndTimestamp(std::map<std::string, std::vector<std::string>>& all_indexed_files, const std::string& file_name, const std::string& timestamp) {
    if(all_indexed_files.count(file_name) != 0 && !timestamp.empty())
        all_indexed_files[file_name].push_back(timestamp);//TODO优化push_back
    else if(!timestamp.empty())
        all_indexed_files[file_name] = std::vector<std::string>(1, timestamp);
    else
        all_indexed_files[file_name] = std::vector<std::string>();
}

void IndexFileName(std::vector<std::string>& all_files, std::map<std::string, std::vector<std::string>>& all_indexed_files)
{
    for(std::vector<std::string>::const_iterator it = all_files.begin(); it != all_files.end(); ++it) {
        if(IsZstdFile(*it)) {
            std::string file_name = GetZstdFileName(*it);
            std::string file_timestamp = GetZstdFileTimestamp(*it);
            CreateOrInsertFileNameAndTimestamp(all_indexed_files, file_name, file_timestamp);
        } else {
            CreateOrInsertFileNameAndTimestamp(all_indexed_files, *it, "");

        }
    }
}

Prepare::Prepare()
{
}


Prepare::~Prepare()
{
}

std::map<std::string, FileInfo> Prepare::PrepareAdvance()
{
    File zstdFile(Path + "/zstdfile");
    std::map<std::string, FileInfo> infoMap; 
    if(zstdFile.isExist() && LoadZstdFile(zstdFile, infoMap))
        return infoMap;
    else

    return infoMap;        
}


bool Prepare::LoadZstdFile(const File& path, std::map<std::string, FileInfo>& infoMap) const
{
    return true;
    
}

bool Prepare::GetAllFileInfo(const File& path, std::map<std::string, FileInfo>& infoMap) const
{
    return true;
}

//int main()
//{
//    std::vector<std::string> files;
//    if(getAllFiles("./", files))
//        if(!files.empty())
//            for(auto file : files)
//                std::cout << file << std::endl;
//        else
//            std::cout << "ssile" << std::endl;
//    
//   std::cout << "file" << std::endl;
//    return 0;
//}
