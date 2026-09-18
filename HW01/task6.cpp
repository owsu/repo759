#include <cstdio>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./task6 N\n";
        return 1;
    }

    int N = std::stoi(argv[1]);

    // Count up using printf
    for (int i = 0; i <= N; ++i) {
        std::printf("%d", i);
        if (i < N) std::printf(" ");
    }
    std::printf("\n");

    // Count down
    for (int i = N; i >= 0; --i) {
        std::cout << i;
        if (i > 0) std::cout << " ";
    }
    std::cout << "\n";


    return 0;
}