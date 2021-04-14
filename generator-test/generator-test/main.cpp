// generator-test.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <vector>

#include "main.hpp"
#include "parser.hpp"

using namespace std;
using namespace std::string_view_literals;

int main()
{
    auto sv = "1 + 1 * 1 + 1 * (1 - 1)"sv;
    yaoosl::parsing::instance i(sv, "NA");
    auto res = i.parse();
    std::stringstream sstream;
    i.print_tree(res, {}, sv, sstream);
    cout << sstream.str();
    return 0;
}
