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
//并且使用open close write close等函数，不是fclose
//fopen fwrite等函数

#include <string>

//不可以放到.cc文件中，否则测试用例编译通不过
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <unistd.h> //for close()
class File
{

    public:

        File(const std::string& pt, char* md);//一定要加std::否则编译出错
        File(const std::string& pt);
        File(const File& other);
        ~File();

        int  open();
        int  read(char* buffer, int pos, int size);
        int  write(char* buffer, int pos, int size);
        int  read(char* buffer, int size);
        int  write(char* buffer, int size);
        void close(); 

        int  size()  const;
        bool isDir() const;
        int  rename(const std::string& newPath);
        int  isExist() const;

    private:
        FILE*       fd_;
        char*       mode_;
        std::string path_;
};
#endif
