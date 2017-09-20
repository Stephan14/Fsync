/*************************************************************************
	> File Name: Decompress.h
	> Author: 
	> Mail: 
	> Created Time: Wed 20 Sep 2017 02:49:31 PM CST
 ************************************************************************/

#ifndef _DECOMPRESS_H
#define _DECOMPRESS_H
#include <string>

class Decompress
{
    public:
        Decompress(const std::string& path, const std::string& decompressPath);
        Decompress(const Decompress& other);
        ~Decompress();

        bool decompress(); 
    private:
        std::string path;
        std::string decompressPath;
        char *buffIn;
        char *buffOut;
        size_t buffInSize;
        size_t buffOutSize;
        void allocate();
        void free();
};
#endif
