# CMakeList.txt : CMake project for generator-test, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (generator-test "main.cpp" "main.hpp" "parser.hpp" "parser.cpp")

# TODO: Add tests and install targets if needed.
