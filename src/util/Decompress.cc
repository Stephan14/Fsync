#include "Decompress.h"
#include "File.h"
#include "zstd.h"

#include <iostream>

Decompress::Decompress(const std::string& path, const std::string& decompressPath):path(path),decompressPath(decompressPath),buffIn(NULL),buffOut(NULL){
        buffInSize = ZSTD_DStreamInSize();    
        buffOutSize = ZSTD_DStreamOutSize();  /* can always flush a full block */
}

Decompress::Decompress(const Decompress& other){}
Decompress::~Decompress(){}

void Decompress::allocate()
{

    buffIn  = new char[buffInSize]();
    buffOut = new char[buffOutSize]();
}

void Decompress::free()
{
    if(buffIn != NULL)
        delete []buffIn;
    if(buffOut != NULL)
        delete []buffOut;
}

bool Decompress::decompress()
{    
    File fin  = File(path, O_RDONLY);
    File fout = File(decompressPath, O_WRONLY);

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

        size_t read, toRead = buffInSize;
        fin.open();
        fout.open();
        allocate();
        
        //读一次写多次
        while(read = fin.read(buffIn, toRead)) 
        {
            ZSTD_inBuffer input = { buffIn, read, 0 };
            while(input.pos < input.size) 
            {
                ZSTD_outBuffer output = { buffOut, buffOutSize, 0 };
                toRead = ZSTD_decompressStream(dstream, &output , &input);  
                if(ZSTD_isError(toRead)) { 
                    std::cout << "ZSTD_decompressStream() error" << std::endl; 
                    fin.close();
                    fout.close();
                    free();
                    return false;
                }
                fout.write(buffOut, output.pos);
            }
        }

        ZSTD_freeDStream(dstream);
        fin.close();
        fout.close();
        free();
        return true;
    }

}
