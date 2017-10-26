#include "Compress.h"
#include "File.h"
#include "zstd.h"

#include <iostream>

Compress::Compress(const std::string& path, const std::string& compressPath):path_(path),compressPath_(compressPath),buffIn_(NULL),buffOut_(NULL){
    buffInSize_ = ZSTD_CStreamInSize();
    buffOutSize_ = ZSTD_CStreamOutSize();
}

Compress::Compress(const Compress& other){}

Compress::~Compress(){
    if(buffIn_ != NULL)
        delete []buffIn_;
    if(buffOut_ != NULL)
        delete []buffOut_;
}

void Compress::allocate()
{
    buffIn_  = new char[buffInSize_]();
    buffOut_ = new char[buffOutSize_]();
}

void Compress::free()
{
    if(buffIn_ != NULL)
        delete []buffIn_;
    if(buffOut_ != NULL)
        delete []buffOut_;
}

bool Compress::compress()
{
    File fin(path_, O_RDONLY);
    File fout(compressPath_ + "temp", (char*)"w"); 

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
        
        size_t read, toRead = buffInSize_;
        fin.open();
        fout.open();
        allocate();

        while(read = fin.read(buffIn_, toRead))
        {
            ZSTD_inBuffer input = { buffIn_, buffInSize_, 0};
            while(input.pos < input.size) 
            {
                ZSTD_outBuffer output = { buffOut_, buffOutSize_, 0};
                size_t toRead = ZSTD_compressStream(cstream, &output, &input);
                if(ZSTD_isError(toRead))
                {
                    std:: cout << "execute compressStream failed!"<< std::endl; 
                    fin.close();
                    fout.close();
                    free();
                    return false;
                }
                if(toRead > buffInSize_)
                    toRead = buffInSize_;
                fout.write(buffOut_, output.pos); 
            }
        }

        ZSTD_outBuffer output = { buffOut_, buffOutSize_, 0};
        const size_t remainingToflush =  ZSTD_endStream(cstream, &output);
        if(remainingToflush)
            std::cout << "not fully flushed"<< std::endl;
        fout.write(buffOut_, output.pos); 
        ZSTD_freeCStream(cstream);
        
        fin.rename(compressPath_ );
        fin.close();
        fout.close();
        free();
        return true;
    }
}

