#include "1.hpp"

struct p1_result_t {
	bool is_constant_evaluated;
	int answer;
};

consteval auto part_one(const auto& input) {
	p1_result_t result {};
	
	for (char c : input) {
		(void)c;
	}

	result.is_constant_evaluated = std::is_constant_evaluated();
	return result;
}

int main() {
	try {
		constexpr auto p1_result = part_one(input);
		std::println("Part one...");
		std::println("Is constant evaluated: {}", p1_result.is_constant_evaluated);
		std::println("Final answer: {}", p1_result.answer);
	}
	catch (std::exception& e) {
		std::println("Exception: {}", e.what());
	}
}
