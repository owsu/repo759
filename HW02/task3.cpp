#include "matmul.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

int main() {
    const unsigned int n = 1024;
    const std::size_t count = static_cast<std::size_t>(n) * n;

    std::vector<double> A(count);
    std::vector<double> B(count);
    std::vector<double> C(count);
    std::vector<double> reference(count);

    std::mt19937 generator(759);
    std::uniform_real_distribution<double> distribution(-1.0, 1.0);

    for (std::size_t i = 0; i < count; ++i) {
        A[i] = distribution(generator);
        B[i] = distribution(generator);
    }

    std::cout << n << '\n';

    // Time one multiplication, then print its time and last result.
    auto measure = [&](auto multiply) {
        const auto start = std::chrono::high_resolution_clock::now();
        multiply();
        const auto end = std::chrono::high_resolution_clock::now();

        const std::chrono::duration<double, std::milli> elapsed = end - start;

        std::cout << elapsed.count() << '\n';
        std::cout << C.back() << '\n';
    };

    // Compare every result element against mmul1.
    auto matches_reference = [&]() {
        for (std::size_t i = 0; i < count; ++i) {
            const double tolerance =
                1e-9 * std::max(1.0, std::abs(reference[i]));

            if (!std::isfinite(C[i]) ||
                std::abs(C[i] - reference[i]) > tolerance) {
                return false;
            }
        }
        return true;
    };

    measure([&]() { mmul1(A.data(), B.data(), C.data(), n); });
    reference = C;

    measure([&]() { mmul2(A.data(), B.data(), C.data(), n); });
    if (!matches_reference()) {
        std::cerr << "mmul2 result mismatch\n";
        return 1;
    }

    measure([&]() { mmul3(A.data(), B.data(), C.data(), n); });
    if (!matches_reference()) {
        std::cerr << "mmul3 result mismatch\n";
        return 1;
    }

    measure([&]() { mmul4(A, B, C.data(), n); });
    if (!matches_reference()) {
        std::cerr << "mmul4 result mismatch\n";
        return 1;
    }

    return 0;
}