#include "../util/File.h"

#include  <gtest/gtest.h>

#include <iostream>


using namespace std;

int main()
{
    File* f = new File("test.txt", "wb"); 

    ASSERT_TRUE(f != NULL);
    if(f->open())    
    {
        char str[] = "test";
        f->write(str, 10, 3);
        cout << "sdfa" << endl;
        f->close();
    }

    delete f;
}
