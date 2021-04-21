#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <optional>

// Appends the correct amount of `../` to the provided PATH
// to make the PATH relative to the git root rather then the workspace used.
// Only for using with default configuration and for testing!
#define WSFIX(PATH) "../../../../../" PATH

int get_bom_skip(const std::vector<char>& buff);
bool file_exists(std::string_view filename);
std::optional<std::string> read_file_from_disk(std::string_view physical_path);