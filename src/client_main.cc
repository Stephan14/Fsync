#include "FileClient.h"

#include <iostream>
#include <memory>

int main()
{
    FileClient client(grpc::CreateChannel("localhost:18080", grpc::InsecureChannelCredentials()));
    client.prepare();
    client.getCompressedFile();
    client.getFileInfoVector();
}
