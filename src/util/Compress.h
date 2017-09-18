/*************************************************************************
	> File Name: Compress.h
	> Author: 
	> Mail: 
	> Created Time: Mon 18 Sep 2017 06:49:04 PM CST
 ************************************************************************/

#ifndef _COMPRESS_H
#define _COMPRESS_H
#include <string>


class Compress
{
    public:
        Compress(const std::string& path, const std::string& compressName);
        Compress(const Compress& other);
        ~Compress();
        
        int compress();
    private:
        std::string path;
        std::string compressName;
};
#endif
