#!/usr/bin/env bash
#SBATCH -p instruction
#SBATCH --cpus-per-task=1
#SBATCH --mem=2G
#SBATCH --time=00:10:00
#SBATCH --job-name=HW02Tests
#SBATCH --output=hw02_tests.out
#SBATCH --error=hw02_tests.err

set -euo pipefail

g++ convolution.cpp task2.cpp -Wall -O3 -std=c++17 -o task2
g++ task3.cpp matmul.cpp -Wall -O3 -std=c++17 -o task3

./task2 4 3 > task2_results.txt
./task3 > task3_results.txt