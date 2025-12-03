#include <aclg/aclg.h>
#include <string>

int main()
{
    // Test printf-style formatting with C-string
    const char* filepath_cstr = "example.txt";
    ACLG_INFO("Packing (C-string): %s", filepath_cstr);

    // Test printf-style formatting with std::string
    std::string filepath_std = "example2.txt";
    ACLG_INFO("Packing (std::string): %s", filepath_std.c_str());

    return 0;
}