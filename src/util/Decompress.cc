#include "Decompress.h"
#include "File.h"
#include "zstd.h"

#include <iostream>

Decompress::Decompress(const std::string& path, const std::string& decompressPath):path_(path),decompressPath_(decompressPath),buffIn_(NULL),buffOut_(NULL){
        buffInSize_ = ZSTD_DStreamInSize();    
        buffOutSize_ = ZSTD_DStreamOutSize();  /* can always flush a full block */
}

Decompress::Decompress(const Decompress& other){}
Decompress::~Decompress(){}

void Decompress::allocate()
{

    buffIn_  = new char[buffInSize_]();
    buffOut_ = new char[buffOutSize_]();
}

void Decompress::free()
{
    if(buffIn_ != NULL)
        delete []buffIn_;
    if(buffOut_ != NULL)
        delete []buffOut_;
}

bool Decompress::decompress()
{    
    File fin  = File(path_, O_RDONLY);
    File fout = File(decompressPath_, (char*)"w");

    if(fin.isDir() || fin.size() == 0)
        return false;
    else
    {
        ZSTD_DStream* const dstream = ZSTD_createDStream();
        if(dstream == NULL) 
        { 
            std::cout <<"ZSTD_createDStream() error"  << std::endl;
            return false;
        }
        size_t const initResult = ZSTD_initDStream(dstream);
        if(ZSTD_isError(initResult)) 
        { 
            std::cout << "ZSTD_initDStream() error" << std::endl; 
            return false; 
        }

        size_t read, toRead = buffInSize_;
        fin.open();
        fout.open();
        allocate();
        
        //读一次写多次
        while(read = fin.read(buffIn_, toRead)) 
        {
            ZSTD_inBuffer input = { buffIn_, read, 0 };
            while(input.pos < input.size) 
            {
                ZSTD_outBuffer output = { buffOut_, buffOutSize_, 0 };
                toRead = ZSTD_decompressStream(dstream, &output , &input);  
                if(ZSTD_isError(toRead)) { 
                    std::cout << "ZSTD_decompressStream() error" << std::endl; 
                    fin.close();
                    fout.close();
                    free();
                    return false;
                }
                fout.write(buffOut_, output.pos);
            }
        }

        ZSTD_freeDStream(dstream);
        fin.close();
        fout.close();
        free();
        return true;
    }

}
