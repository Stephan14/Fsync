#include "FileServer.h"

using grpc::ServerContext;
using grpc::ServerWriter;
using grpc::Status;

using FileServerInternal::ClientRequest;
using FileServerInternal::FileInfo;
using FileServerInternal::Chunk;

void FileServer::Init()
{
    std::cout << "init start" << std::endl;
    inotify_thread.Init();
    inotify_thread.AddWatchEvent("/home/zoushengfu/code/Fsync/Fsync/src", IN_CREATE|IN_DELETE|IN_MOVED_FROM|IN_MOVED_TO);
    std::cout << "init start" << std::endl;
}

void FileServer::Start()
{
    inotify_thread.Start();
}

void FileServer::Join()
{
    inotify_thread.Join();
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
