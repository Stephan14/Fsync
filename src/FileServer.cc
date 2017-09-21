#include "FileServer.h"
#include <grpc++/grpc++.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc++/security/server_credentials.h>

#include <iostream>
    
using grpc::ServerContext;
using grpc::ServerWriter;
using grpc::Status;

using FileServerInternal::ClientRequest;
using FileServerInternal::FileInfo;
using FileServerInternal::Chunk;

void FileServer::prepare()
{
    std::cout << "prepare" << std::endl; 
}


Status FileServer::getCompressedFile(ServerContext* context, const ClientRequest* request, ServerWriter<FileInfo>* writer)
{
    std::cout << "getCompressedFile"<< std::endl;
    return Status::OK; 
}

Status FileServer::getFileInfoVector(ServerContext* context, const ClientRequest* request, ServerWriter<Chunk>* writer)
{
    std::cout << "getFileInfoVector"<< std::endl;
    return Status::OK; 
}
