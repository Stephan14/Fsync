#include "../util/File.h"

#include <gtest/gtest.h>
#include <sys/types.h>

TEST(FileConstructionTest, PointTest)
{
    File* f = new File("test.txt", O_RDONLY); 
    ASSERT_TRUE(f != NULL);
    delete f;
}


TEST(FileOpenTest, OpenSuccess)
{
    File* f = new File("test.txt", O_RDONLY); 
    ASSERT_EQ(f->open(), 0); 
    f->close();
    delete f;
}

TEST(FileOpenTest, OpenFailed)
{
    File* f = new File("test2.txt", O_RDONLY); 
    ASSERT_EQ(f->open(), -1); 
    f->close();
    delete f;
}

TEST(FileReadTest, StringRead)
{
    File* f = new File("test.txt", O_RDONLY); 
    ASSERT_EQ(f->open(), 0); 
    char buf[10];
    EXPECT_EQ(f->read(buf, 0, 3), 3);
    f->close();
    delete f;
}

TEST(FileWriteTest, StringWrite)
{
    File* f = new File("test.txt", O_WRONLY); 
    f->open(); 
    char buf[10] = "abc";
    ASSERT_EQ(f->write(buf, 14, 3), 3);
    f->close();
    delete f;
}

TEST(FileExistTest, FileExist)
{
    File* f = new File("test.txt"); 
    ASSERT_TRUE(f->isExist());
    delete f;
}


TEST(FileExistTest, FileIsnotExist)
{
    File* f = new File("test33.txt"); 
    ASSERT_FALSE(f->isExist());
    delete f;
}

int main(int argc, char* argv[])
{
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}
