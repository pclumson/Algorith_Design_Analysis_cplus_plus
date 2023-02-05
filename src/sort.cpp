// src/sort.cpp

#include "sort.hpp"

#include <algorithm>

static size_t partition(IntVec& integers, size_t p, size_t r) {
    int& x = integers.at(r - 1);
    size_t i = p - 1;

    for (auto j = p; j < r - 1; j++) {
        if (integers.at(j) <= x) {
            i += 1;
            std::swap(integers.at(i), integers.at(j));
        }
    }
    std::swap(integers.at(i + 1), integers.at(r - 1));

    return i + 1;
}

static void quicksort_impl(IntVec& integers, size_t p, size_t r) {
    if (p < r) {
        size_t q = partition(integers, p, r);

        quicksort_impl(integers, p, q);
        quicksort_impl(integers, q + 1, r);
    }
}

void quicksort(IntVec& integers) {
    quicksort_impl(integers, 0, integers.size());
}

static size_t random_partition(
    std::default_random_engine& generator, IntVec& integers, size_t p, size_t r
) {
    // Swap a random element
    std::uniform_int_distribution<size_t> distribution(p, r - 1);
    auto index = distribution(generator);
    std::swap(integers[r - 1], integers[index]);

    return partition(integers, p, r);
}

static void random_quicksort_impl(
    std::default_random_engine& generator, IntVec& integers, size_t p, size_t r
) {
    if (p < r) {
        size_t q = random_partition(generator, integers, p, r);

        random_quicksort_impl(generator, integers, p, q);
        random_quicksort_impl(generator, integers, q + 1, r);
    }
}

void random_quicksort(std::default_random_engine& generator, IntVec& integers) {
    random_quicksort_impl(generator, integers, 0, integers.size());
}