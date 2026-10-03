#include "convolution.h"

#include <chrono>
#include <iostream>
#include <random>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: task2 n m\n";
        return 1;
    }

    const std::size_t n = std::stoull(argv[1]);
    const std::size_t m = std::stoull(argv[2]);

    if (n == 0 || m == 0 || m % 2 == 0) {
        std::cerr << "n must be positive; m must be positive and odd\n";
        return 1;
    }

    float* image = new float[n * n];
    float* mask = new float[m * m];
    float* output = new float[n * n];

    std::mt19937 generator(759);
    std::uniform_real_distribution<float> image_distribution(-10.0f, 10.0f);
    std::uniform_real_distribution<float> mask_distribution(-1.0f, 1.0f);

    for (std::size_t i = 0; i < n * n; ++i) {
        image[i] = image_distribution(generator);
    }

    for (std::size_t i = 0; i < m * m; ++i) {
        mask[i] = mask_distribution(generator);
    }

    const auto start = std::chrono::high_resolution_clock::now();
    convolve(image, output, n, mask, m);
    const auto end = std::chrono::high_resolution_clock::now();

    const std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << elapsed.count() << '\n';
    std::cout << output[0] << '\n';
    std::cout << output[n * n - 1] << '\n';

    delete[] image;
    delete[] mask;
    delete[] output;

    return 0;
}