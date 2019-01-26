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

        void AddOrUpdateFileMsg(const std::string &file_path, const std::string &hash, const std::string &current_time);
        std::map<std::string, std::string> GetFileMsg();

        std::map<std::string, std::string> GetFileCompressMsg();
    private:
        std::map<std::string, std::string> FileAndHash;
        std::map<std::string, std::string> FileAndCompress;
        std::mutex mutex; // for undone_file

};

#endif
