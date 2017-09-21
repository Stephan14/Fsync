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
        Compress(const std::string& path, const std::string& compressPath);
        Compress(const Compress& other);
        ~Compress();
        
        bool compress();
    private:
        std::string path_;
        std::string compressPath_;
        size_t buffInSize_;
        size_t buffOutSize_;
        char* buffIn_;
        char* buffOut_;

        void allocate();
        void free();
};
#endif
