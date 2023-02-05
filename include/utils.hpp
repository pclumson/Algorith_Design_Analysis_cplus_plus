// include/utils.hpp
#pragma once

#include <algorithm>
#include <cctype>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using Clock = std::chrono::high_resolution_clock;
using Milliseconds = std::chrono::duration<double, std::milli>;

using IntVec = std::vector<int>;
using SortFunction = std::function<void(IntVec&)>;

struct SortResults {
    SortResults();

    IntVec sorted;
    Clock::duration runtime;
};

extern IntVec generate_random_integers(
    std::default_random_engine& generator,
    size_t n
);
extern IntVec generate_increasing_integers(size_t n, size_t x);

extern SortResults run_sort(const SortFunction& sort_fn, IntVec integers);

extern void print_integers(std::ostream& file, const IntVec& integers);

// String trim utilities (https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring)

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}