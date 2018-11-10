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

void MetaData::PutNewFile(std::string file_path)
{
    if (file_path == "")
        return;
    mutex.lock();
    time_t current_time = getCurrentTime();
    undone_file[file_path] = current_time;
    mutex.unlock();
}

bool Cmp(const std::pair<std::string, std::time_t> &v1, const std::pair<std::string, std::time_t> &v2)
{
    return v1.second < v2.second;
}

std::string MetaData::GetNewFileByTime()
{
    std::string file_path = "";

    mutex.lock();
    std::vector<std::pair<std::string, std::time_t>> arr;
    for (std::map<std::string, std::time_t>::iterator it = undone_file.begin(); it != undone_file.end(); ++it)
    {
        arr.push_back(make_pair(it->first, it->second));
    }
    sort(arr.begin(), arr.end(), Cmp);

    if (arr.size() > 0) {
        undone_file.erase(arr[0].first);
        file_path = arr[0].first;
    }

    mutex.unlock();
    return file_path;
}

void MetaData::StartCompressFile(std::string file_path, pthread_t threadID)
{
    doing_file[file_path] = threadID;
}

void MetaData::CompleteCompressFile(std::string file_path, std::string compressedFile)
{
    auto threadID = doing_file.find(file_path);
    if (threadID == doing_file.end()) {
        return;
    }

    doing_file.erase(file_path);

    done_file[file_path] = compressedFile;
}




