#include "convolution.h"

#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: task2 n t\n";
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

    const std::size_t m = 3;
    std::vector<float> image(n * n);
    std::vector<float> mask(m * m);
    std::vector<float> output(n * n);

    std::mt19937 generator(759);
    std::uniform_real_distribution<float> image_distribution(-10.0f, 10.0f);
    std::uniform_real_distribution<float> mask_distribution(-1.0f, 1.0f);

    for (std::size_t i = 0; i < image.size(); ++i) {
        image[i] = image_distribution(generator);
    }

    for (std::size_t i = 0; i < mask.size(); ++i) {
        mask[i] = mask_distribution(generator);
    }

    const auto start = std::chrono::high_resolution_clock::now();
    convolve(image.data(), output.data(), n, mask.data(), m);
    const auto end = std::chrono::high_resolution_clock::now();

    const std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << output.front() << '\n';
    std::cout << output.back() << '\n';
    std::cout << elapsed.count() << '\n';

    return 0;
}
