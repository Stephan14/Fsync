#include "File.h"

#include <stdio.h>
#include <stdlib.h>

#include <iostream>

using namespace std;

File::File(string pt, string md):path(pt), mode(md), fd(NULL){}
File::~File(){}
File::File(const File& other){}

int File::open()
{
    fd = fopen(path.c_str(), mode.c_str()); //将string转化成char *
    if(fd == NULL)
    {
        cout << "open file " << path << "failed" << endl;
        return 0;
    }

    return 1;
}

void File::close()
{
    fclose(fd);
}

int File::read(char* buffer, int pos, int size)
{
    if(fseek(fd, pos, SEEK_SET) != 0)
    {
        cout << "file location failed" << endl;
        return -1;
    }

    return fread(buffer, 1, size, fd);
}

int File::write(char* buffer, int pos, int size)
{
    if(fseek(fd, pos, SEEK_SET) != 0)
    {
        cout << "file location failed" << endl;
        return -1;
    }

    return fwrite(buffer, 1, size, fd);
}


