/*************************************************************************
	> File Name: File.h
	> Author: 
	> Mail: 
	> Created Time: Fri 15 Sep 2017 04:39:02 PM CST
 ************************************************************************/

#ifndef _FILE_H
#define _FILE_H
//由于实际工程中使用C++中流处理文件的性能比较低
//所以使用C语言中的文件操作代替C++中的流处理

#include <string>
#include <stdio.h> //for FILE

class File
{

    public:

        File(std::string pt, std::string md);//一定要加std::否则编译出错
        File(const File& other);
        ~File();

        int open();
        void close(); 
        int read(char* buffer, int pos, int size);
        int write(char* buffer, int pos, int size);

    private:
        FILE*       fd;
        std::string path;
        std::string mode;
};
#endif
