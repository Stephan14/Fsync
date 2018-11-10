/*************************************************************************
	> File Name: File.h
	> Author: 
	> Mail: 
	> Created Time: Fri 15 Sep 2017 04:39:02 PM CST
 ************************************************************************/

#ifndef _METADATA_H
#define _METADATA_H

#include <map>
#include <string>
#include <ctime>
#include <mutex>

#include <pthread.h>

class MetaData
{
    public:
        MetaData();
        ~MetaData();

        void PutNewFile(std::string file_path);
        std::string GetNewFileByTime();
        void StartCompressFile(std::string file_path, pthread_t threadId);
        void CompleteCompressFile(std::string file_path, std::string compressedFile);

    private:
        std::map<std::string, std::string> done_file;
        std::map<std::string, std::time_t> undone_file;
        std::map<std::string, pthread_t> doing_file;
        std::mutex mutex; // for undone_file

};

#endif
