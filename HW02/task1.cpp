#include "scan.h"

#include <chrono>
#include <iostream>
#include <random>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: task1 n\n";
        return 1;
    }

    const std::size_t n = std::stoull(argv[1]);
    if (n == 0) {
        std::cerr << "n must be positive\n";
        return 1;
    }

    float* arr = new float[n];
    float* output = new float[n];

    std::mt19937 generator(759);
    std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

    for (std::size_t i = 0; i < n; ++i) {
        arr[i] = distribution(generator);
    }

    const auto start = std::chrono::high_resolution_clock::now();
    scan(arr, output, n);
    const auto end = std::chrono::high_resolution_clock::now();

    const std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << elapsed.count() << '\n';
    std::cout << output[0] << '\n';
    std::cout << output[n - 1] << '\n';

    delete[] arr;
    delete[] output;

    return 0;
}