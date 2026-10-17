#include "msort.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: task3 n t ts\n";
        return 1;
    }

    const std::size_t n = std::stoull(argv[1]);
    const int t = std::stoi(argv[2]);
    const std::size_t threshold = std::stoull(argv[3]);

    if (n == 0 || t < 1 || t > 20 || threshold == 0) {
        std::cerr << "n and ts must be positive; t must be 1 through 20\n";
        return 1;
    }

    omp_set_dynamic(0);
    omp_set_num_threads(t);

    std::vector<int> arr(n);
    std::mt19937 generator(759);
    std::uniform_int_distribution<int> distribution(-1000, 1000);

    for (std::size_t i = 0; i < n; ++i) {
        arr[i] = distribution(generator);
    }

    // prepares an independent reference outside the timed region.
    std::vector<int> expected = arr;
    std::sort(expected.begin(), expected.end());

    const auto start = std::chrono::high_resolution_clock::now();
    msort(arr.data(), n, threshold);
    const auto end = std::chrono::high_resolution_clock::now();

    const std::chrono::duration<double, std::milli> elapsed = end - start;

    if (arr != expected) {
        std::cerr << "Merge sort result mismatch\n";
        return 1;
    }

    std::cout << arr.front() << '\n';
    std::cout << arr.back() << '\n';
    std::cout << elapsed.count() << '\n';

    return 0;
}
