// src/main.cpp

#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

#include "utils.hpp"
#include "sort.hpp"

struct Results {
    IntVec original;

    SortResults quicksort;
    SortResults random_quicksort;
};

Results run(std::default_random_engine& generator, IntVec original_integers) {
    Results results;

    results.quicksort = run_sort(
        [](IntVec& integers) {
            quicksort(integers);
        },
        original_integers
    );

    results.random_quicksort = run_sort(
        [&generator](IntVec& integers) {
            random_quicksort(generator, integers);
        },
        original_integers
    );

    results.original = std::move(original_integers);

    return results;
}

void write_sort_results(std::ostream& output, const SortResults& results) {
    print_integers(output, results.sorted);
    output
        << "Runtime(ms): " << std::chrono::duration_cast<Milliseconds>(results.runtime).count()
        << '\n';
}

void write_results(std::ostream& output, const Results& results) {
    output << "Original: \n";
    print_integers(output, results.original);
    output << '\n';

    output << "Quicksort Results: \n";
    write_sort_results(output, results.quicksort);
    output << '\n';

    output << "Randomized Quicksort Results: \n";
    write_sort_results(output, results.random_quicksort);
    output << '\n';
}

bool prompt_increasing() {
    while (true) {
        std::string line;
        std::cout << "Generate increasing integers? [y/n] ";
        std::getline(std::cin, line);
        trim(line);

        if (line == "y") {
            return true;
        } else if (line == "n") {
            return false;
        } else {
            std::cerr << "Invalid input - must be [y/n]" << std::endl;
        }
    }
}

size_t prompt_n() {
    while (true) {
        try {
            std::string line;
            std::cout << "Enter N: " << std::flush;
            std::getline(std::cin, line);

            size_t n = std::stoul(line);

            return n;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Unable to convert N to an integer\n" << std::endl;
        }
    }
}

size_t prompt_x() {
    while (true) {
        try {
            std::string line;
            std::cout << "Enter X: " << std::flush;
            std::getline(std::cin, line);

            size_t x = std::stoul(line);

            return x;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Unable to convert X to an integer\n" << std::endl;
        }
    }
}

void run_randomized(std::default_random_engine& generator) {
    size_t n = prompt_n();

    auto integers = generate_random_integers(generator, n);
    auto results = run(generator, integers);

    {
        std::ofstream output_file("output.txt");
        write_results(output_file, results);
    }

    std::cout
        << "The results have been written to output.txt"
        << std::endl;
}

void run_increasing(std::default_random_engine& generator) {
    size_t n = prompt_n();
    size_t x = prompt_x();

    auto integers = generate_increasing_integers(n, x);
    auto results = run(generator, integers);

    {
        std::ofstream output_file("output.txt");
        write_results(output_file, results);
    }

    std::cout
        << "The results have been written to output.txt"
        << std::endl;
}

int main(int argc, char** argv) {
    std::default_random_engine generator(
        std::chrono::system_clock::now().time_since_epoch().count()
    );

    bool is_increasing = prompt_increasing();

    if (is_increasing) {
        run_increasing(generator);
    } else {
        run_randomized(generator);
    }

    return 0;
}