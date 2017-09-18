#include "File.h"


#include <iostream>


File::File(const std::string& pt, int  md):path(pt), mode(md), fd(-1){}
File::~File(){}
File::File(const File& other){}

int File::open()
{
    fd = ::open(path.c_str(), mode); //将string转化成char *
    if(fd == -1)
    {
        std::cout << "open file " << path << " failed" << std::endl;
        return -1;
    }

    return 0;
}

void File::close()
{
    if(fd != -1)
        ::close(fd);
}

int File::read(char* buffer, int pos, int size)
{
    int i = 0;
    if((::lseek(fd, pos, SEEK_SET)) == -1)
    {
        std::cout << "file location failed" << std::endl;
        return -1;
    }

    int num = ::read(fd, &buffer[0], size);
    buffer[num] = '\0';

    return num;
}

int File::write(char* buffer, int pos, int size)
{
    if(::lseek(fd, pos, SEEK_SET) == -1)
    {
        std::cout << "file location failed" << std::endl;
        return -1;
    }

    return ::write(fd, buffer, size);
}


