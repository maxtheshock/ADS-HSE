#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>

class MatrixHasher {
private:
    int _n, _m;
    uint64_t _row_p;
    uint64_t _column_p;

    std::vector<uint64_t> _row_powers;
    std::vector<uint64_t> _column_powers;
    std::vector<uint64_t> _hashes;

    uint64_t getHash(int i, int j) const {
        return _hashes[i*(_m+1) + j];
    }

public:
    MatrixHasher(const std::vector<std::string>& matrix, uint64_t row_p, uint64_t column_p) :
        _n(matrix.size()), _m(matrix[0].size()), _row_p(row_p), _column_p(column_p) {
            _row_powers.resize(_n+1);
            _column_powers.resize(_m+1);
            _hashes.assign((_n+1)*(_m+1), 0);

            _row_powers[0] = 1;
            for (int i = 1; i <= _n; ++i) { _row_powers[i] = _row_powers[i-1]*_row_p; }

            _column_powers[0] = 1;
            for (int j = 1; j <= _m; ++j) { _column_powers[j] = _column_powers[j-1]*_column_p; }

            for (int i = 0; i < _n; ++i) {
                for (int j = 0; j < _m; ++j) {
                    uint64_t value = matrix[i][j] - 'a' + 1;
                    _hashes[(i+1)*(_m+1) + j+1] = value + getHash(i, j+1)*_row_p + getHash(i+1, j)*_column_p - getHash(i, j)*_row_p*_column_p;
                }
            }
        }

    uint64_t get(int x1, int y1, int x2, int y2) const {
        int height = x2-x1;
        int width = y2-y1;

        return getHash(x2, y2) -
               getHash(x1, y2)*_row_powers[height] -
               getHash(x2, y1)*_column_powers[width] +
               getHash(x1, y1)*_row_powers[height]*_column_powers[width];
    }
};

struct SquareHash {
    uint64_t first;
    uint64_t second;
    bool operator==(const SquareHash& other) const {
        return first == other.first && second == other.second;
    }
};

struct SquareHashFunction {
    size_t operator()(const SquareHash& value) const {
        uint64_t result = value.first;
        result ^= value.second + 0x9e3779b97f4a7c15ULL + (result << 6) + (result >> 2);
        return static_cast<size_t>(result);
    }
};

bool findEqualSquares(const MatrixHasher& hash1, const MatrixHasher& hash2, int n, int m, int size,
    std::pair<int, int>& first, std::pair<int, int>& second) {
    
    std::unordered_map<SquareHash, std::pair<int, int>, SquareHashFunction> positions;

    positions.max_load_factor(0.7f);
    positions.reserve((n-size+1)*(m-size+1));

    for (int i = 0; i+size <= n; ++i) {
        for (int j = 0; j+size <= m; ++j) {
            SquareHash current = {
                hash1.get(i, j, i+size, j+size),
                hash2.get(i, j, i+size, j+size)
            };

            auto it = positions.find(current);

            if (it != positions.end()) {
                first = it->second;
                second = {i, j};
                return true;
            }

            positions.emplace(current, std::make_pair(i, j));
        }
    }

    return false;
}

int main() {

    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> matrix(n);
    for (int i = 0; i < n; ++i) { std::cin >> matrix[i]; }
    MatrixHasher hash1(matrix, 1000003, 1000033);
    MatrixHasher hash2(matrix, 1000037, 1000081);

    int left = 0;
    int right = std::min(n, m);

    while (left < right) {
        int middle = (left+right+1)/2;
        std::pair<int, int> first, second;
        if (findEqualSquares(hash1, hash2, n, m, middle, first, second)) {
            left = middle;
        } else {
            right = middle-1;
        }
    }

    if (left == 0) {
        std::cout << 0 << '\n';
        return 0;
    }

    std::pair<int, int> first, second;
    findEqualSquares(hash1, hash2, n, m, left, first, second);

    std::cout << left << '\n';
    std::cout << first.first+1 << ' ' << first.second+1 << '\n';
    std::cout << second.first+1 << ' ' << second.second+1 << '\n';

    return 0;
}
