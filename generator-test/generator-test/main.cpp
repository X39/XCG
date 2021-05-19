// generator-test.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <chrono>

#include "main.hpp"
#include "parser.hpp"

using namespace std;
using namespace std::string_view_literals;


int main()
{
    auto file = read_file_from_disk(WSFIX("examples/example.ys"));
    if (file.has_value())
    {
        yaoosl::parsing::instance i(*file, "NA");
        auto now = std::chrono::high_resolution_clock::now();
        auto res = i.parse();
        auto then = std::chrono::high_resolution_clock::now();
        cout << "Time needed for parsing: " << std::endl;
        cout << " - " << std::chrono::duration_cast<std::chrono::minutes>(then - now) << std::endl;
        cout << " - " << std::chrono::duration_cast<std::chrono::seconds>(then - now) << std::endl;
        cout << " - " << std::chrono::duration_cast<std::chrono::milliseconds>(then - now) << std::endl;
        cout << " - " << std::chrono::duration_cast<std::chrono::nanoseconds>(then - now) << std::endl;
        std::stringstream sstream;
        auto lines = i.create_string_tree(res, *file);
        for (auto line : lines)
        {
            cout << line << "\n";
        }
        cout << std::endl;
        return 0;
    }
    else
    {
        return -1;
    }
}


bool file_exists(std::string_view filename)
{
    std::ifstream infile(filename.data());
    return infile.good();
}

std::optional<std::string> read_file_from_disk(std::string_view physical_path)
{
    if (!file_exists(physical_path))
    {
        return {};
    }
    std::ifstream file(physical_path.data(), std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
        return {};
    }

    auto fileSize = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return std::string(buffer.begin() + get_bom_skip(buffer), buffer.end());
}
int get_bom_skip(const std::vector<char>& buff)
{
    if (buff.empty())
        return 0;
    // We are comparing against unsigned
    auto ubuff = reinterpret_cast<const unsigned char*>(buff.data());
    if (ubuff[0] == 0xEF && ubuff[1] == 0xBB && ubuff[2] == 0xBF)
    {
        //UTF-8
        return 3;
    }
    else if (ubuff[0] == 0xFE && ubuff[1] == 0xFF)
    {
        //UTF-16 (BE)
        return 2;
    }
    else if (ubuff[0] == 0xFE && ubuff[1] == 0xFE)
    {
        //UTF-16 (LE)
        return 2;
    }
    else if (ubuff[0] == 0x00 && ubuff[1] == 0x00 && ubuff[2] == 0xFF && ubuff[3] == 0xFF)
    {
        //UTF-32 (BE)
        return 2;
    }
    else if (ubuff[0] == 0xFF && ubuff[1] == 0xFF && ubuff[2] == 0x00 && ubuff[3] == 0x00)
    {
        //UTF-32 (LE)
        return 2;
    }
    else if (ubuff[0] == 0x2B && ubuff[1] == 0x2F && ubuff[2] == 0x76 &&
        (ubuff[3] == 0x38 || ubuff[3] == 0x39 || ubuff[3] == 0x2B || ubuff[3] == 0x2F))
    {
        //UTF-7
        return 4;
    }
    else if (ubuff[0] == 0xF7 && ubuff[1] == 0x64 && ubuff[2] == 0x4C)
    {
        //UTF-1
        return 3;
    }
    else if (ubuff[0] == 0xDD && ubuff[1] == 0x73 && ubuff[2] == 0x66 && ubuff[3] == 0x73)
    {
        //UTF-EBCDIC
        return 3;
    }
    else if (ubuff[0] == 0x0E && ubuff[1] == 0xFE && ubuff[2] == 0xFF)
    {
        //SCSU
        return 3;
    }
    else if (ubuff[0] == 0xFB && ubuff[1] == 0xEE && ubuff[2] == 0x28)
    {
        //BOCU-1
        if (ubuff[3] == 0xFF)
            return 4;
        return 3;
    }
    else if (ubuff[0] == 0x84 && ubuff[1] == 0x31 && ubuff[2] == 0x95 && ubuff[3] == 0x33)
    {
        //GB 18030
        return 3;
    }
    return 0;
}