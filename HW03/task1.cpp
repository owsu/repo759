#include "matmul.h"

#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: task1 n t\n";
        return 1;
    }

    const std::size_t n = std::stoull(argv[1]);
    const int t = std::stoi(argv[2]);

    if (n == 0 || t < 1 || t > 20) {
        std::cerr << "n must be positive; t must be between 1 and 20\n";
        return 1;
    }

    omp_set_dynamic(0);
    omp_set_num_threads(t);

    std::vector<float> A(n * n);
    std::vector<float> B(n * n);
    std::vector<float> C(n * n);

    std::mt19937 generator(759);
    std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

    for (std::size_t i = 0; i < n * n; ++i) {
        A[i] = distribution(generator);
        B[i] = distribution(generator);
    }

    const auto start = std::chrono::high_resolution_clock::now();
    mmul(A.data(), B.data(), C.data(), n);
    const auto end = std::chrono::high_resolution_clock::now();

    const std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << C.front() << '\n';
    std::cout << C.back() << '\n';
    std::cout << elapsed.count() << '\n';

    return 0;
}
