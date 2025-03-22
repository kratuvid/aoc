#pragma once

#include <print>
#include <fstream>
#include <exception>
#include <cerrno>
#include <cstring>

// Macro definitions
#define UU __attribute__((unused))

[[nodiscard]]
auto open_file(std::string_view filename) {
  std::ifstream file(filename.data());
  if (!file.is_open())
    throw std::runtime_error(std::format("Couldn't open input file {}: {}", filename, std::strerror(errno)));
  return file;
}

