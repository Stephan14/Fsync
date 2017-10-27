#include <gtest/gtest.h>

#include "../Prepare.h"

TEST(PrepareGetAllFilesTest, PrepareGetAllFiles)
{
    const std::string path("./");
    std::vector<std::string> allFiles;
    ASSERT_TRUE(GetAllFiles(path, allFiles));
    for(std::vector<std::string>::iterator it = allFiles.begin(); it != allFiles.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

}

TEST(PrepareIsZstdFileTest, PrepareIsZstdFile)
{
    const std::string file1("test2.txt.zst");
    const std::string file2("test2.txt");
    ASSERT_TRUE(IsZstdFile(file1));
    ASSERT_FALSE(IsZstdFile(file2));

}

TEST(PrepareGetZstdFileName, PrepareGetZstdFileNameTest)
{
    const std::string file1("test2.txt_1489.zst");
    std::cout << GetZstdFileName(file1) << std::endl;

}

TEST(PrepareGetZstdTimestamp, PrepareGetZstdTimestampTest)
{
    const std::string file1("test2.txt_1489.zst");
    std::cout << GetZstdFileTimestamp(file1) << std::endl;

}

TEST(PrepareCreateOrInsertFileNameAndTimestamp, PrepareCreateOrInsertFileNameAndTimestampTest)
{
    std::map<std::string, std::vector<std::string>> file_and_timestamp;
    std::string file_name = GetZstdFileName("test2.txt_1489.zst");
    std::cout << file_name << std::endl;
    std::string timestamp = GetZstdFileTimestamp("test2.txt_1489.zst");
    std::cout << timestamp << std::endl; CreateOrInsertFileNameAndTimestamp(file_and_timestamp, file_name, timestamp);
    std::cout << "test" << std::endl;
    std::cout << file_and_timestamp.size() << std::endl;
   
    std::vector<std::string> v = file_and_timestamp[file_name];
    for (auto it = v.begin(); it != v.end(); ++it)
        std::cout << *it << std::endl;
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
