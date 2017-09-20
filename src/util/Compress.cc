#include "Compress.h"
#include "File.h"
#include "zstd.h"

#include <iostream>

Compress::Compress(const std::string& path, const std::string& compressPath):path(path),compressPath(compressPath),buffIn(NULL),buffOut(NULL){
    buffInSize = ZSTD_CStreamInSize();
    buffOutSize = ZSTD_CStreamOutSize();
}

Compress::Compress(const Compress& other){}

Compress::~Compress(){
    if(buffIn != NULL)
        delete []buffIn;
    if(buffOut != NULL)
        delete []buffOut;
}

void Compress::allocate()
{
    buffIn = new char[buffInSize]();
    buffOut = new char[buffOutSize]();
}

void Compress::free()
{
    if(buffIn != NULL)
        delete []buffIn;
    if(buffOut != NULL)
        delete []buffOut;
}

bool Compress::compress()
{
    File fin(path, O_RDONLY);
    File fout(compressPath + "temp", O_WRONLY); 

    if(fin.isDir() || fin.size() == 0)
        return false;
    else
    {
        ZSTD_CStream* const cstream = ZSTD_createCStream();
        if(cstream == NULL)
        {
            std::cout << "ZSTD_createCStream() error" << std::endl; 
            return false;
        }
        size_t const initResult = ZSTD_initCStream(cstream, 3);
        if(ZSTD_isError(initResult))
        {
            std::cout << "ZSTD_initCStream() error" << std::endl; 
            return false;
        }
        
        size_t read, toRead = buffInSize;
        fin.open();
        fout.open();
        allocate();

        while(read = fin.read(buffIn, toRead))
        {
            ZSTD_inBuffer input = { buffIn, buffInSize, 0};
            while(input.pos < input.size) 
            {
                ZSTD_outBuffer output = { buffOut, buffOutSize, 0};
                size_t toRead = ZSTD_compressStream(cstream, &output, &input);
                if(ZSTD_isError(toRead))
                {
                    std:: cout << "execute compressStream failed!"<< std::endl; 
                    fin.close();
                    fout.close();
                    free();
                    return false;
                }
                if(toRead > buffInSize)
                    toRead = buffInSize;
                fout.write(buffOut, output.pos); 
            }
        }

        ZSTD_outBuffer output = { buffOut, buffOutSize, 0};
        const size_t remainingToflush =  ZSTD_endStream(cstream, &output);
        if(remainingToflush)
            std::cout << "not fully flushed"<< std::endl;
        fout.write(buffOut, output.pos); 
        ZSTD_freeCStream(cstream);
        
        fin.rename(compressPath );
        fin.close();
        fout.close();
        free();
        return true;
    }
}


