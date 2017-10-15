#include <gtest/gtest.h>

#include "../Prepare.h"

TEST(PrepareGetAllFilesTest, PrepareGetAllFiles)
{
    const std::string path("./");
    std::vector<std::string> allFiles;
    ASSERT_TRUE(getAllFiles(path, allFiles));
    for(std::vector<std::string>::iterator it = allFiles.begin(); it != allFiles.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
