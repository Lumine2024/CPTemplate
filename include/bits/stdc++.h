// bits/stdc++.h for compatibility of clang-cl, clang, and MSVC

#pragma once

#ifdef _MSC_VER
#define CCVER _MSVC_LANG
#else
#define CCVER __cplusplus
#endif

// c libraries
#ifdef _MSC_VER
#include <conio.h>
#endif
#include <crtdbg.h>
#include <direct.h>
#include <fpieee.h>
#include <io.h>
#include <malloc.h>
#include <mbstring.h>
#include <process.h>
#include <sal.h>
#include <search.h>
#include <share.h>
#include <sys/locking.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <sys/utime.h>
#include <tchar.h>

// c++ libraries
#include <algorithm>
#include <array>
#include <atomic>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <chrono>
#include <cinttypes>
#include <climits>
#include <clocale>
#include <cmath>
#include <codecvt>
#include <complex>
#include <condition_variable>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cuchar>
#include <cwchar>
#include <cwctype>
#include <deque>
#include <exception>
#include <forward_list>
#include <fstream>
#include <functional>
#include <future>
#include <initializer_list>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <mutex>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <set>
#include <shared_mutex>
#include <setjmp.h>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <vector>
#include <version>

#ifdef _MSC_VER
// Legacy C/C++ headers kept only for MSVC compatibility.
#include <ccomplex>
#include <ciso646>
#include <cstdalign>
#include <cstdbool>
#include <ctgmath>
#include <strstream>

// int128 extension
#include <__msvc_int128.hpp>
using __int128_t = std::_Signed128;
using __uint128_t = std::_Unsigned128;
#define __int128 __int128_t
// bit extension
#if CCVER > 201703L
#include <bit>
constexpr int __builtin_clz(unsigned x) noexcept {
	return std::countl_zero(x);
}
constexpr int __builtin_clzl(unsigned long x) noexcept {
	return std::countl_zero(x);
}
constexpr int __builtin_clzll(unsigned long long x) noexcept {
	return std::countl_zero(x);
}
constexpr int __builtin_ctz(unsigned x) noexcept {
	return std::countr_zero(x);
}
constexpr int __builtin_ctzl(unsigned long x) noexcept {
	return std::countr_zero(x);
}
constexpr int __builtin_ctzll(unsigned long long x) noexcept {
	return std::countr_zero(x);
}
constexpr int __builtin_popcount(unsigned x) noexcept {
	return std::popcount(x);
}
constexpr int __builtin_popcountl(unsigned long x) noexcept {
	return std::popcount(x);
}
constexpr int __builtin_popcountll(unsigned long long x) noexcept {
	return std::popcount(x);
}
#else
constexpr int __builtin_clz(unsigned x) noexcept {
	for(int i = 31; i >= 0; --i) {
		if(((1u << i) & x) != 0) return 31 - i;
	}
	return 32;
}
constexpr int __builtin_clzl(unsigned long x) noexcept {
	return __builtin_clz(x);
}
constexpr int __builtin_clzll(unsigned long long x) noexcept {
	for(int i = 63; i >= 0; --i) {
		if(((1ull << i) & x) != 0) return 63 - i;
	}
	return 64;
}
constexpr int __builtin_ctz(unsigned x) noexcept {
	for(int i = 0; i < 31; ++i) {
		if(((1u << i) & x) != 0) return i;
	}
	return 32;
}
constexpr int __builtin_ctzl(unsigned long x) noexcept {
	return __builtin_ctz(x);
}
constexpr int __builtin_ctzll(unsigned long long x) noexcept {
	for(int i = 0; i < 63; ++i) {
		if(((1ull << i) & x) != 0) return i;
	}
	return 64;
}
constexpr int __builtin_popcount(unsigned x) noexcept {
	int res = 0;
	for(int i = 0; i < 32; ++i) {
		if((x >> i) & 1) ++res;
	}
	return res;
}
constexpr int __builtin_popcountl(unsigned long x) noexcept {
	return __builtin_popcount(x);
}
constexpr int __builtin_popcountll(unsigned long long x) noexcept {
	int res = 0;
	for(int i = 0; i < 64; ++i) {
		if((x >> i) & 1) ++res;
	}
	return res;
}
#endif
#endif

#if CCVER > 201402L
#include <any>
#include <charconv>
#include <execution>
#include <filesystem>
#include <memory_resource>
#include <optional>
#include <string_view>
#include <variant>

#if CCVER > 201703L
#include <barrier>
#include <bit>
#include <compare>
#include <concepts>
#include <coroutine>
#include <format>
#include <latch>
#include <numbers>
#include <ranges>
#include <semaphore>
#include <source_location>
#include <span>
#include <stop_token>
#include <syncstream>

#if CCVER > 202002L
#include <expected>
#include <print>
#include <spanstream>
#include <stacktrace>
#include <stdfloat>

#endif
#endif
#endif