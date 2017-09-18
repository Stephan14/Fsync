#include "Compress.h"
#include "File.h"
#include "zstd.h"

Compress::Compress(const std::string& path, const std::string& compressName):path(path),compressName(compressName){}

Compress::Compress(const Compress& other){}

Compress::~Compress(){}


int Compress::compress()
{

}


