#pragma once

#include <print>
#include <fstream>
#include <string_view>
#include <type_traits>
#include <functional>

#define UU __attribute__((unused))

#define IS_CONSTEVAL 0
#if IS_CONSTEVAL == 1
#define CONSTEVAL consteval
#else
#define CONSTEVAL
#endif

using Log = std::array<char, 256>;

constexpr std::string_view g_input {
#include "../../inputs/2018/1"
};

template<>
struct std::formatter<Log> {
	template<class ParseContext>
	constexpr auto parse(ParseContext& ctx) {
		auto it = ctx.begin();
		auto end = ctx.end();

		if (it != end && *it != '}') {
			throw std::format_error("Invalid format specifier for Log");
		}

		return it;
	}

	template<class FormatContext>
	auto format(Log const& log, FormatContext& ctx) const {
		return std::format_to(ctx.out(), "{}", log.data());
	}
};

void print_results(auto const& results) {
	for(auto const& item : results) {
		std::print("{}: ", item.first);
		std::visit([](auto const& value){std::println("{}", value);}, item.second);
	}
}

template<class TPredicate>
CONSTEVAL std::string_view trim_left(std::string_view const& str, TPredicate predicate) {
	auto search = std::find_if_not(str.begin(), str.end(), predicate);
	return std::string_view(search, str.end());
}

CONSTEVAL std::string_view trim_left(std::string_view const& str, char c) {
	return trim_left(str, [c](char x){ return x == c; });
}

template<class TPredicate>
CONSTEVAL auto trim_right(std::string_view const& str, TPredicate predicate) {
	auto search = std::find_if_not(str.rbegin(), str.rend(), predicate);
	return str.substr(0, std::distance(search, str.rend()));
}

CONSTEVAL auto trim_right(std::string_view const& str, char c) {
	return trim_right(str, [c](char x){ return x == c; });
}

template<class TPredicate>
CONSTEVAL auto trim(std::string_view const& str, TPredicate predicate) {
	return trim_right(trim_left(str, predicate), predicate);
}

CONSTEVAL auto trim(std::string_view const& str, char c) {
	return trim_right(trim_left(str, c), c);
}

CONSTEVAL bool is_whitespace(char x) {
	static constexpr std::string_view ws {" \f\n\r\t\v"};
	return ws.find(x) != std::string_view::npos;
}

CONSTEVAL auto trim_whitespaces(std::string_view const& str) {
	return trim(str, is_whitespace);
}
