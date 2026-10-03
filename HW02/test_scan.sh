#!/usr/bin/env bash
#SBATCH -p instruction
#SBATCH --cpus-per-task=1
#SBATCH --mem=12G
#SBATCH --time=00:10:00
#SBATCH --job-name=HW02Scan
#SBATCH --output=scan_scaling.out
#SBATCH --error=scan_scaling.err

set -euo pipefail

g++ scan.cpp task1.cpp -Wall -O3 -std=c++17 -o task1

echo "n,time_ms,first,last" > scan_times.csv

for exponent in {10..30}; do
    n=$((1 << exponent))
    result=$(./task1 "$n")
    values=$(printf '%s\n' "$result" | paste -sd, -)
    printf '%s,%s\n' "$n" "$values" >> scan_times.csv
done