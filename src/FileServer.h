/*************************************************************************
	> File Name: FileServer.h
	> Author: 
	> Mail: 
	> Created Time: Fri 15 Sep 2017 04:28:01 PM CST
 ************************************************************************/

#ifndef _FILESERVER_H
#define _FILESERVER_H
#include <iostream>

#include <grpc++/grpc++.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc++/security/server_credentials.h>


#include "Server.grpc.pb.h"

#include "Inotify.h"

class FileServer final : public FileServerInternal::Server::Service
{
    public:
    FileServer() = default;
    ~FileServer() = default;

    void Init();
    void Start();
    void Join();
    grpc::Status getCompressedFile(grpc::ServerContext* context, const FileServerInternal::ClientRequest* request, grpc::ServerWriter<FileServerInternal::FileInfo>* writer);
    grpc::Status getFileInfoVector(grpc::ServerContext* context, const FileServerInternal::ClientRequest* request, grpc::ServerWriter<FileServerInternal::Chunk>* writer);

    private:
    Inotify inotify_thread;
};
#endif
