// src/test.cpp

#include <chrono>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

#include "utils.hpp"
#include "sort.hpp"

struct Results {
    Results() :
        successes(0),
        failures(0),
        average_runtime(0)
    {
    }

    size_t successes;
    size_t failures;
    Milliseconds average_runtime;
};

Results run_quicksort_check(
    SortFunction sort_fn,
    std::default_random_engine& generator,
    size_t iterations
) {
    constexpr size_t MAX_N = 10000;
    std::uniform_int_distribution<size_t> distribution(1, MAX_N);

    Results test_results;

    Milliseconds total_runtime(0);

    for (auto i = 0; i < iterations; i++) {
        auto n = distribution(generator);
        auto original_integers = generate_random_integers(generator, n);
        SortResults results;

        try {
            results = run_sort(sort_fn, original_integers);
            total_runtime += std::chrono::duration_cast<Milliseconds>(
                results.runtime
            );

            for (size_t j = 0; j < n - 1; j++) {
                if (results.sorted[j] > results.sorted[j + 1]) {
                    // quicksort failed
                    throw std::logic_error(
                        "failed to sort these numbers"
                    );
                }
            }

            test_results.successes += 1;
        } catch (const std::exception& e) {
            print_integers(std::cerr, original_integers);
            print_integers(std::cerr, results.sorted);
            std::cerr << e.what() << std::endl;

            test_results.failures += 1;
        }
    }


    test_results.average_runtime = Milliseconds(
        total_runtime.count()
            / static_cast<double>(iterations)
    );

    return test_results;
}

void run_random_quicksort_test(std::default_random_engine& generator) {
    std::cout << "Running Randomized Quicksort check..." << std::endl;

    auto results = run_quicksort_check(
        [&generator](IntVec& integers) {
            random_quicksort(generator, integers);
        },
        generator,
        2000
    );

    std::cout
        << "Finished Randomized Quicksort check!\n"
        << " - pass: " << results.successes << '\n'
        << " - fail: " << results.failures << '\n'
        << " - average runtime(ms): "
        << std::chrono::duration_cast<Milliseconds>(results.average_runtime)
            .count()
        << "\n"
        << std::endl;
}

void run_quicksort_test(std::default_random_engine& generator) {
    std::cout << "Running Quicksort check..." << std::endl;

    auto results = run_quicksort_check(
        &quicksort,
        generator,
        2000
    );

    std::cout
        << "Finished Quicksort check!\n"
        << " - pass: " << results.successes << '\n'
        << " - fail: " << results.failures << '\n'
        << " - average runtime(ms): "
        << std::chrono::duration_cast<Milliseconds>(results.average_runtime)
            .count()
        << "\n"
        << std::endl;
}

int main(int argc, char** argv) {
    std::default_random_engine generator(
        std::chrono::system_clock::now().time_since_epoch().count()
    );

    run_random_quicksort_test(generator);
    run_quicksort_test(generator);

    return 0;
}