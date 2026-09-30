#include <vector>
#include <string>
#include <unordered_set>
#include <iostream>
#include <cstdint>


struct MatrixHash {
    uint64_t first;
    uint64_t second;

    bool operator==(const MatrixHash& other) const {
        return first == other.first && second == other.second;
    }
};

struct MatrixHashFunction {
    size_t operator()(const MatrixHash& value) const {
        uint64_t result = value.first;
        result ^= value.second + 0x9e3779b97f4a7c15ULL + (result << 6) + (result >> 2);
        return static_cast<size_t>(result);
    }
};

uint64_t get_power(uint64_t p, int degree) {
    uint64_t result = 1;
    for (int i = 0; i < degree; ++i) {
        result *= p;
    }
    return result;
}

int main() {
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<std::string> matrix(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> matrix[i];
    }

    const uint64_t row_p1 = 1000003;
    const uint64_t row_p2 = 1000033;
    const uint64_t column_p1 = 1000037;
    const uint64_t column_p2 = 1000081;

    uint64_t row_power1 = get_power(row_p1, k);
    uint64_t row_power2 = get_power(row_p2, k);
    uint64_t column_power1 = get_power(column_p1, k);
    uint64_t column_power2 = get_power(column_p2, k);

    int row_windows = m-k+1;
    int column_windows = n-k+1;

    std::vector<MatrixHash> row_hashes(n*row_windows);

    for (int i = 0; i < n; ++i) {
        MatrixHash current = {0, 0};
        for (int j = 0; j < k; ++j) {
            uint64_t value = matrix[i][j] - 'a' + 1;
            current.first = current.first*row_p1 + value;
            current.second = current.second*row_p2 + value;
        }

        row_hashes[i*row_windows] = current;

        for (int j = 1; j < row_windows; ++j) {
            uint64_t old_value = matrix[i][j-1] - 'a' + 1;
            uint64_t new_value = matrix[i][j+k-1] - 'a' + 1;
            current.first = current.first*row_p1 + new_value - old_value*row_power1;
            current.second = current.second*row_p2 + new_value - old_value*row_power2;
            row_hashes[i*row_windows + j] = current;
        }
    }

    std::unordered_set<MatrixHash, MatrixHashFunction> different;

    different.max_load_factor(0.7f);
    different.reserve(column_windows*row_windows);

    for (int j = 0; j < row_windows; ++j) {
        MatrixHash current = {0, 0};
        for (int i = 0; i < k; ++i) {
            const MatrixHash& row_hash = row_hashes[i*row_windows + j];
            current.first = current.first*column_p1 + row_hash.first;
            current.second = current.second*column_p2 + row_hash.second;
        }

        different.insert(current);

        for (int i = 1; i < column_windows; ++i) {
            const MatrixHash& old_hash = row_hashes[(i-1)*row_windows + j];
            const MatrixHash& new_hash = row_hashes[(i+k-1)*row_windows + j];
            current.first = current.first*column_p1 + new_hash.first - old_hash.first*column_power1;
            current.second = current.second*column_p2 + new_hash.second - old_hash.second*column_power2;
            different.insert(current);
        }
    }
    std::cout << different.size() << '\n';
    return 0;
}
