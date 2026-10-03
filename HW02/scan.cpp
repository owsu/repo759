#include "scan.h"

void scan(const float* arr, float* output, std::size_t n) {
    float total = 0.0f;

    for (std::size_t i = 0; i < n; ++i) {
        total += arr[i];
        output[i] = total;
    }
}