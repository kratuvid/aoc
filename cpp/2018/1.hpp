#pragma once

#include <print>
#include <fstream>
#include <string_view>
#include <type_traits>

#define INPUT_FILENAME "../../inputs/2018/1"

constexpr std::string_view input {
#include INPUT_FILENAME
};
