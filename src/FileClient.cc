#include "FileClient.h"

#include <memory>


using grpc::ClientContext;
using grpc::ClientReader;
using grpc::Status;

using FileServerInternal::ClientRequest;
using FileServerInternal::FileInfo;
using FileServerInternal::Chunk;

void FileClient::prepare()
{
    std::cout << "client server!" << std::endl; 
}

void FileClient::getCompressedFile()
{
    ClientContext context;
    ClientRequest request;
    std::unique_ptr<ClientReader<FileInfo>> writer(stub_->GetCompressedFile(&context, request));
}

void FileClient::getFileInfoVector()
{
    ClientContext context;
    ClientRequest request;
    std::unique_ptr<ClientReader<Chunk>> writer(stub_->GetFileInfoVector(&context, request)); 
}
