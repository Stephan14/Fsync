#include "FileServer.h"

#include <string>
#include <memory>


using grpc::ServerBuilder;
using grpc::Server;


int main()
{
    std::string server_address("0.0.0.0:18080");
    FileServer service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    
    server->Wait();
    return 0;
}
