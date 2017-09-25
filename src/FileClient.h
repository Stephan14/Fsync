/*************************************************************************
	> File Name: FileCleint.h
	> Author: 
	> Mail: 
	> Created Time: 日  9/24 19:56:09 2017
 ************************************************************************/

#ifndef _FILECLEINT_H
#define _FILECLEINT_H
#include <iostream>

#include <grpc/grpc.h>
#include <grpc++/grpc++.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>

#include "Server.grpc.pb.h"

class FileClient
{
    public:
    FileClient(std::shared_ptr<grpc::Channel> channel):stub_(FileServerInternal::Server::NewStub(channel)){}
    ~FileClient() = default;

    void prepare();
    void getCompressedFile();
    void getFileInfoVector();

    private:
    std::unique_ptr<FileServerInternal::Server::Stub> stub_;
};
#endif
