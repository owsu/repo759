#include "msort.h"

#include <algorithm>
#include <vector>

namespace {

void insertion_sort(int* arr, std::size_t n) {
    for (std::size_t i = 1; i < n; ++i) {
        const int value = arr[i];
        std::size_t j = i;

        while (j > 0 && arr[j - 1] > value) {
            arr[j] = arr[j - 1];
            --j;
        }

        arr[j] = value;
    }
}

void sort_part(int* arr, int* temporary, std::size_t n,
               std::size_t threshold) {
    if (n < 2) {
        return;
    }

    if (n < threshold) {
        insertion_sort(arr, n);
        return;
    }

    const std::size_t middle = n / 2;

    #pragma omp task firstprivate(arr, temporary, middle, threshold)
    {
        sort_part(arr, temporary, middle, threshold);
    }

    #pragma omp task firstprivate(arr, temporary, middle, n, threshold)
    {
        sort_part(arr + middle, temporary + middle,
                  n - middle, threshold);
    }

    #pragma omp taskwait

    // Merge the two sorted halves into temporary storage.
    std::size_t left = 0;
    std::size_t right = middle;
    std::size_t out = 0;

    while (left < middle && right < n) {
        if (arr[left] <= arr[right]) {
            temporary[out++] = arr[left++];
        } else {
            temporary[out++] = arr[right++];
        }
    }

    while (left < middle) {
        temporary[out++] = arr[left++];
    }

    while (right < n) {
        temporary[out++] = arr[right++];
    }

    std::copy(temporary, temporary + n, arr);
}

} // namespace

void msort(int* arr, const std::size_t n,
           const std::size_t threshold) {
    if (n < 2) {
        return;
    }

    std::vector<int> temporary(n);

    #pragma omp parallel
    {
        #pragma omp single
        {
            sort_part(arr, temporary.data(), n, threshold);
        }
    }
}
