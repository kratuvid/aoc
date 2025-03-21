#include <charconv>
#include <cstring>
#include <sstream>
#include <vector>
#include "1.hpp"

CONSTEVAL auto solver(std::string_view input) {
	int sum = 0, twice_visited = std::numeric_limits<int>::min();

	auto predicate = [](char x) {
		return is_whitespace(x) || x == '+';
	};
	auto error = [&sum]() {
		sum = std::numeric_limits<int>::min();
	};

	constexpr size_t visited_capacity = 8192;
	size_t visited_size = 0;
	std::array<int, visited_capacity> visited {};

	while (input.size() > 0) {
		input = trim(input, predicate);

		int drift = 0;
		auto status = std::from_chars(input.data(), input.data() + input.size(), drift);
		if (status.ec != std::errc{}) { error(); break; }

		sum += drift;
		input = std::string_view(status.ptr, input.data() + input.size());

		if (twice_visited == std::numeric_limits<int>::min()) {
			if (visited_size >= visited_capacity) { error(); break; }

			auto end = visited.begin() + visited_size + 1;
			if (std::find(visited.begin(), end, sum) == end)
				visited[visited_size++] = sum;
			else
				twice_visited = sum;
		}
	}

	using value_t = std::variant<int, std::string_view>;
	return std::array<std::pair<std::string_view, value_t>, 3> {{
		{"sum", sum}, {"twice_visited", twice_visited}
	}};
}

auto solver2(std::string_view input) -> std::optional<int> {
  std::istringstream iss(input.data());
  std::vector<int> visited;
  int current = 0;

  while (iss) {
    int drift = 0;
    iss >> drift;
    current += drift;

    if (std::find(visited.begin(), visited.end(), current) == visited.end()) {
      visited.push_back(current);
    } else {
      return current;
    }
  }

  return std::nullopt;
};

int main() {
	try {
		const auto solution {solver(g_input)};
		print_results(solution);
    std::println("Part 2: {}", *solver2(g_input));
	}
	catch (std::exception& e) {
		std::println("Exception (std): {}", e.what());
	} catch (const char*& e) {
		std::println("Exception (char*): {}", e);
	} catch (std::string_view& e) {
		std::println("Exception (string view): {}", e);
	}
}
