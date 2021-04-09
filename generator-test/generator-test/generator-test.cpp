// generator-test.cpp : Defines the entry point for the application.
//

#include "generator-test.hpp"

#include "parser.hpp"

using namespace std;

int main()
{
    yaoosl::parsing::instance i("1 + 1 + 1 + 1", "NA");
    return 0;
}
