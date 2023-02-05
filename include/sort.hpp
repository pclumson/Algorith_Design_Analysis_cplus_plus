// include/sort.hpp
#pragma once

#include <vector>
#include <random>
#include <algorithm>

#include "utils.hpp"

extern void quicksort(IntVec& integers);
extern void random_quicksort(
    std::default_random_engine& generator, IntVec& integers
);