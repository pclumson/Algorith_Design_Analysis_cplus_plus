// src/bench.cpp

#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

#include "utils.hpp"
#include "sort.hpp"

using GenerateFunction = std::function<IntVec(size_t n)>;

struct BenchResults {
    BenchResults(size_t runs) :
        runs(runs),
        total_runtime(0),
        average_runtime(0)
    {
    }

    size_t runs;
    Milliseconds total_runtime;
    Milliseconds average_runtime;
};

std::ostream& operator<<(std::ostream& out, const BenchResults& results) {
    out
        << "runs: " << results.runs << '\n'
        << " - total runtime(ms): " << results.total_runtime.count() << '\n'
        << " - average runtime(ms): " << results.average_runtime.count()
        << std::endl;

    return out;
}

BenchResults benchmark_sort(
    const SortFunction& sort_fn,
    const GenerateFunction& gen_fn,
    size_t n,
    size_t runs
) {
    BenchResults bench_results(runs);

    for (auto i = 0; i < runs; i++) {
        auto integers = gen_fn(n);
        SortResults results;

        results = run_sort(sort_fn, integers);
        bench_results.total_runtime += std::chrono::duration_cast<Milliseconds>(
            results.runtime
        );
    }

    bench_results.average_runtime = Milliseconds(
        bench_results.total_runtime.count() / static_cast<double>(runs)
    );

    return bench_results;
}

void run_benchmark(
    std::ostream& out,
    const SortFunction& sort_fn,
    const GenerateFunction& gen_fn,
    size_t n,
    size_t runs
) {
    out
        << "Running N = " << n << " ..." << std::endl
        << benchmark_sort(sort_fn, gen_fn, n, runs)
        << std::endl;
}

void run_benchmark_suite(
    std::ostream& out,
    const std::string& name,
    SortFunction sort_fn,
    GenerateFunction gen_fn,
    size_t runs
) {
    std::cout << "\nBenchmarks [" << name << "]" << std::endl;

    run_benchmark(out, sort_fn, gen_fn, 10, runs);
    run_benchmark(out, sort_fn, gen_fn, 100, runs);
    run_benchmark(out, sort_fn, gen_fn, 1000, runs);
    run_benchmark(out, sort_fn, gen_fn, 10000, runs);

    std::cout << std::endl;
}

int main(int argc, char** argv) {
    bool done = false;
    std::default_random_engine generator(
        std::chrono::system_clock::now().time_since_epoch().count()
    );

    run_benchmark_suite(
        std::cout,
        "Quicksort with Random Input",
        [](IntVec& integers) {
            quicksort(integers);
        },
        [&generator](size_t n) {
            return generate_random_integers(generator, n);
        },
        5
    );

    run_benchmark_suite(
        std::cout,
        "Randomized Quicksort with Random Input",
        [&generator](IntVec& integers) {
            random_quicksort(generator, integers);
        },
        [&generator](size_t n) {
            return generate_random_integers(generator, n);
        },
        5
    );


    run_benchmark_suite(
        std::cout,
        "Quicksort with Sorted Input",
        [](IntVec& integers) {
            quicksort(integers);
        },
        [](size_t n) {
            return generate_increasing_integers(n, 1);
        },
        5
    );

    run_benchmark_suite(
        std::cout,
        "Randomized Quicksort with Sorted Input",
        [&generator](IntVec& integers) {
            random_quicksort(generator, integers);
        },
        [](size_t n) {
            return generate_increasing_integers(n, 1);
        },
        5
    );

    return 0;
}