#include "matmul.h"

#include <algorithm>

void mmul1(const double* A, const double* B, double* C,
           const unsigned int n) {
    const std::size_t size = n;
    std::fill(C, C + size * size, 0.0);

    for (std::size_t i = 0; i < size; ++i) {
        for (std::size_t j = 0; j < size; ++j) {
            for (std::size_t k = 0; k < size; ++k) {
                C[i * size + j] += A[i * size + k] * B[k * size + j];
            }
        }
    }
}

void mmul2(const double* A, const double* B, double* C,
           const unsigned int n) {
    const std::size_t size = n;
    std::fill(C, C + size * size, 0.0);

    for (std::size_t i = 0; i < size; ++i) {
        for (std::size_t k = 0; k < size; ++k) {
            for (std::size_t j = 0; j < size; ++j) {
                C[i * size + j] += A[i * size + k] * B[k * size + j];
            }
        }
    }
}

void mmul3(const double* A, const double* B, double* C,
           const unsigned int n) {
    const std::size_t size = n;
    std::fill(C, C + size * size, 0.0);

    for (std::size_t j = 0; j < size; ++j) {
        for (std::size_t k = 0; k < size; ++k) {
            for (std::size_t i = 0; i < size; ++i) {
                C[i * size + j] += A[i * size + k] * B[k * size + j];
            }
        }
    }
}

void mmul4(const std::vector<double>& A, const std::vector<double>& B,
           double* C, const unsigned int n) {
    const std::size_t size = n;
    std::fill(C, C + size * size, 0.0);

    for (std::size_t i = 0; i < size; ++i) {
        for (std::size_t j = 0; j < size; ++j) {
            for (std::size_t k = 0; k < size; ++k) {
                C[i * size + j] += A[i * size + k] * B[k * size + j];
            }
        }
    }
}