// src/utils.cpp

#include "utils.hpp"

#include <chrono>

SortResults::SortResults() :
    runtime(0)
{
}

IntVec generate_random_integers(
    std::default_random_engine& generator, size_t n
) {
    constexpr int MAX_RANGE = 10000;

    IntVec integers;
    std::uniform_int_distribution<int> distribution(0, MAX_RANGE);

    for (size_t i = 0; i < n; i++) {
        integers.push_back(distribution(generator));
    }

    return integers;
}
IntVec generate_increasing_integers(size_t n, size_t x) {
    IntVec integers;

    if (n != 0) {
        integers.push_back(n + x);
        for (size_t i = 1; i < n; i++) {
            integers.push_back(n + (i + 1) * x);
        }
    }

    return integers;
}

SortResults run_sort(
    const std::function<void(IntVec&)>& sort_fn,
    IntVec integers
) {
    SortResults results;

    auto start = Clock::now();
    sort_fn(integers);
    auto end = Clock::now();

    results.sorted = std::move(integers);
    results.runtime = end - start;

    return results;
}

void print_integers(std::ostream& file, const IntVec& integers) {
    file << "[";

    for (int i = 0; i < (integers.size() - 1); i++) {
        file << integers[i] << ", ";
    }

    file << integers.back() << "]" << std::endl;
}