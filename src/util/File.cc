#include "File.h"

#include <iostream>

#include <stdio.h>
#include <string.h>

File::File(const std::string& pt, char* md):path_(pt), fd_(NULL)
{
    mode_ = new char[strlen(md) + 1];//注意长度
    strcpy(mode_, md); //不用考虑\0   
}
File::File(const std::string& pt):path_(pt), fd_(NULL){}
File::~File(){}
File::File(const File& other){}

int File::open()
{
    fd_ = ::fopen(path_.c_str(), mode_); //将string转化成char *
    if(!fd_)
    {
        std::cout << "open file " << path_ << " failed" << std::endl;
        return -1;
    }

    return 0;
}

void File::close()
{
    if(fd_)
        ::fclose(fd_);
}

int File::read(char* buffer, int pos, int size)
{
    int i = 0;
    if((::fseek(fd_, pos, SEEK_SET)) != 0)
    {
        std::cout << "file location failed" << std::endl;
        return -1;
    }

    int num = ::fread(&buffer[0], sizeof(char), size, fd_);
    //buffer[num] = '\0';

    return num;
}

int File::write(char* buffer, int pos, int size)
{
    if(::fseek(fd_, pos, SEEK_SET) != 0)
    {
        std::cout << "file location failed" << std::endl;
        return -1;
    }

    return ::fwrite(&buffer[0], sizeof(char), size, fd_);
}

int File::read(char* buffer, int size)
{
    int num = ::fread(&buffer[0], sizeof(char), size, fd_);//当num返回值为0时说明已经到达文件尾了
    //buffer[num] = '\0';
    return num; 
}

int File::write(char* buffer, int size)
{
    return ::fwrite(&buffer[0], sizeof(char), size, fd_);
}


int File::size() const
{
    struct stat  st;
    if(!path_.empty() && 
       ::stat(path_.c_str(), &st) == 0) 
        return st.st_size;
    else
        return -1;
}

bool File::isDir() const
{
   struct stat st;
    if(!path_.empty() &&
       ::stat(path_.c_str(), &st) == 0)
        return  S_ISDIR(st.st_mode);    
    else
        return false;
}

int File::rename(const std::string& newpath)
{
    if(::rename(path_.c_str(), newpath.c_str()) == 0)
    {
        path_ = newpath;
        return 0;
    }
    else
        return -1;
        
}

bool File::isExist() const
{
    if(::access(path_.c_str(), F_OK) == 0) 
        return true;
    else
        return false;
}

bool File::getLine(char *buffer, size_t size) const
{
    if(::fgets(buffer, size, fd_) == NULL) 
        return false;
    else
        return true;
}
