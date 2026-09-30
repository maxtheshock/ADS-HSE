#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

class MatrixHasher {
private:
    int _n, _m;
    uint64_t _row_p;
    uint64_t _column_p;

    std::vector<uint64_t> _row_powers;
    std::vector<uint64_t> _column_powers;
    std::vector<uint64_t> _hashes;

    uint64_t get_hash(int i, int j) const {
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
                    _hashes[(i+1)*(_m+1) + j+1] = value + get_hash(i, j+1)*_row_p + get_hash(i+1, j)*_column_p - get_hash(i, j)*_row_p*_column_p;
                }
            }
        }


    uint64_t get(int x1, int y1, int x2, int y2) const {
        int height = x2-x1;
        int width = y2-y1;
        return get_hash(x2, y2) -
               get_hash(x1, y2)*_row_powers[height] -
               get_hash(x2, y1)*_column_powers[width] +
               get_hash(x1, y1)*
               _row_powers[height]*
               _column_powers[width];
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> matrix(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> matrix[i];
    }
    std::vector<std::string> rotated(n, std::string(m, 'a'));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            rotated[n-1-i][m-1-j] = matrix[i][j];
        }
    }


    MatrixHasher original_hash1(matrix, 1000003, 1000033);
    MatrixHasher rotated_hash1(rotated, 1000003, 1000033);
    MatrixHasher original_hash2(matrix, 1000037, 1000081);
    MatrixHasher rotated_hash2(rotated, 1000037, 1000081);

    int64_t answer = 0;

    for (int x1 = 0; x1 < n; ++x1) {
        for (int x2 = x1+1; x2 <= n; ++x2) {
            for (int y1 = 0; y1 < m; ++y1) {
                for (int y2 = y1+1; y2 <= m; ++y2) {
                    int rotated_x1 = n-x2;
                    int rotated_y1 = m-y2;
                    int rotated_x2 = n-x1;
                    int rotated_y2 = m-y1;

                    bool first_hash_equal = (original_hash1.get(x1, y1, x2, y2) == rotated_hash1.get(rotated_x1, rotated_y1, rotated_x2, rotated_y2));
                    if (!first_hash_equal) { continue; }

                    bool second_hash_equal = (original_hash2.get(x1, y1, x2, y2) == rotated_hash2.get(rotated_x1, rotated_y1, rotated_x2, rotated_y2));
                    if (second_hash_equal) { ++answer; }
                }
            }
        }
    }
    std::cout << answer << '\n';
    return 0;
}
