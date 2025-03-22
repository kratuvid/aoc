#include "utils.hpp"
#include <map>
#include <list>
#include <algorithm>

auto main() -> int {
  try {
    const auto lines = []{
      std::list<std::string> _lines;
      std::string line;
      auto file = open_file("../../inputs/2018/2");
      while (file >> line) {
        _lines.emplace_back(std::move(line));
      }
      return _lines;
    }();

    // Part 1
    int global_has_two = 0, global_has_three = 0;

    for (auto const& line : lines) {
      std::map<char, int> frequency_map;
      for (char c : line) {
        auto [iter, success] = frequency_map.insert({c, 0});
        iter->second++;
      }

      int twos = 0, threes = 0;
      for (auto [_, count] : frequency_map) {
        if (count == 2) twos++;
        if (count == 3) threes++;
      }

      global_has_two += static_cast<int>(twos > 0);
      global_has_three += static_cast<int>(threes > 0);
    }

    const int checksum = global_has_two * global_has_three;
    std::println("Checksum: {}", checksum);
    std::println();

    // Part 2
    decltype(lines)::const_iterator matches[2];

    for (auto it = lines.cbegin(); it != lines.cend(); it++) {
      std::println("Superior: {}", *it);
      for (auto it_inner = std::next(it); it_inner != lines.cend(); it_inner++) {
        auto it_inner_str = it_inner->begin();
        auto differences = std::ranges::count_if(*it, [&it_inner_str](char c) {
          return c != *it_inner_str++;
        });
        std::print("  Inferior: {}, Δ: {}", *it_inner, differences);
        if (differences == 1) std::print(", CANDIDATE");
        std::println();

        if (differences == 1) {
          matches[0] = it;
          matches[1] = it_inner;
          goto matched;
        }
      }
    }

matched:
    std::println("\nCandidates:\n{}\n{}", *matches[0], *matches[1]);
    auto [it1_mm, it2_mm] = std::ranges::mismatch(*matches[0], *matches[1]);
    std::println("Mismatch at index {}: {}", std::distance(matches[0]->begin(), it1_mm), *it1_mm);

    std::string common_str(*matches[0]);
    common_str.erase(std::distance(matches[0]->begin(), it1_mm), 1);
    std::println("Common string: {}", common_str);
  } catch (std::exception& e) {
    std::println(stderr, "Exception caught: {}", e.what());
    return 1;
  }
}
