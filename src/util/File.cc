#include "File.h"

#include <iostream>

#include <stdio.h>

File::File(const std::string& pt, int  md):path_(pt), mode_(md), fd_(-1){}
File::~File(){}
File::File(const File& other){}

int File::open()
{
    fd_ = ::open(path_.c_str(), mode_); //将string转化成char *
    if(fd_ == -1)
    {
        std::cout << "open file " << path_ << " failed" << std::endl;
        return -1;
    }

    return 0;
}

void File::close()
{
    if(fd_ != -1)
        ::close(fd_);
}

int File::read(char* buffer, int pos, int size)
{
    int i = 0;
    if((::lseek(fd_, pos, SEEK_SET)) == -1)
    {
        std::cout << "file location failed" << std::endl;
        return -1;
    }

    int num = ::read(fd_, &buffer[0], size);
    buffer[num] = '\0';

    return num;
}

int File::write(char* buffer, int pos, int size)
{
    if(::lseek(fd_, pos, SEEK_SET) == -1)
    {
        std::cout << "file location failed" << std::endl;
        return -1;
    }

    return ::write(fd_, buffer, size);
}

int File::read(char* buffer, int size)
{
    int num = ::read(fd_, &buffer[0], size);
    buffer[num] = '\0';
    return num; 
}

int File::write(char* buffer, int size)
{
    return ::write(fd_, buffer, size);
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
