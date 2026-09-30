#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

uint64_t getStringHash(const std::vector<uint64_t>& hashes, const std::vector<uint64_t>& powers, int left, int right) {
    return hashes[right] - hashes[left]*powers[right-left];
}

class MatrixHasher {
private:
    int _r, _c;
    uint64_t _row_p;
    uint64_t _column_p;

    std::vector<uint64_t> _row_powers;
    std::vector<uint64_t> _column_powers;
    std::vector<uint64_t> _hashes;

    uint64_t getHash(int i, int j) const {
        return _hashes[i*(_c+1) + j];
    }

public:
    MatrixHasher(const std::vector<std::string>& matrix, uint64_t row_p, uint64_t column_p) :
        _r(matrix.size()), _c(matrix[0].size()), _row_p(row_p), _column_p(column_p) {
            _row_powers.resize(_r+1);
            _column_powers.resize(_c+1);
            _hashes.assign((_r+1)*(_c+1), 0);
            _row_powers[0] = 1;
            for (int i = 1; i <= _r; ++i) { _row_powers[i] = _row_powers[i-1]*_row_p; }
            _column_powers[0] = 1;
            for (int j = 1; j <= _c; ++j) { _column_powers[j] = _column_powers[j-1]*_column_p; }
            for (int i = 0; i < _r; ++i) {
                for (int j = 0; j < _c; ++j) {
                    uint64_t value = matrix[i][j] - 'A' + 1;
                    _hashes[(i+1)*(_c+1) + j+1] = value + getHash(i, j+1)*_row_p + getHash(i+1, j)*_column_p - getHash(i, j)*_row_p*_column_p;
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

int main() {
    int r, c;
    std::cin >> r >> c;
    std::vector<std::string> picture(r);
    for (int i = 0; i < r; ++i) { std::cin >> picture[i]; }

    const uint64_t p1 = 1000003;
    const uint64_t p2 = 1000033;
    std::vector<uint64_t> powers1(c+1);
    std::vector<uint64_t> powers2(c+1);

    powers1[0] = powers2[0] = 1;

    for (int i = 1; i <= c; ++i) {
        powers1[i] = powers1[i-1]*p1;
        powers2[i] = powers2[i-1]*p2;
    }

    std::vector<bool> possible(c/2 + 1, true);
    std::vector<uint64_t> hashes1(c+1);
    std::vector<uint64_t> hashes2(c+1);

    for (int i = 0; i < r; ++i) {
        hashes1[0] = hashes2[0] = 0;
        for (int j = 0; j < c; ++j) {
            uint64_t value = picture[i][j] - 'A' + 1;
            hashes1[j+1] = hashes1[j]*p1 + value;
            hashes2[j+1] = hashes2[j]*p2 + value;
        }
        for (int width = 1; width <= c/2; ++width) {
            if (!possible[width]) { continue; }
            bool first_equal = getStringHash(hashes1, powers1, 0, c-width) == getStringHash(hashes1, powers1, width, c);
            bool second_equal = getStringHash(hashes2, powers2, 0, c-width) == getStringHash(hashes2, powers2, width, c);
            if (!first_equal || !second_equal) { possible[width] = false; }
        }
    }

    int b = 1;
    while (!possible[b]) { ++b; }
    std::vector<std::string> periodic(r, std::string(2*b, 'A'));

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < 2*b; ++j) {
            periodic[i][j] = picture[i][j%b];
        }
    }

    MatrixHasher hash1(periodic, 1000037, 1000081);
    MatrixHasher hash2(periodic, 1000099, 1000117);

    for (int a = 1; a <= r/2; ++a) {
        uint64_t upper_hash1 = hash1.get(0, 0, r-a, b);
        uint64_t upper_hash2 = hash2.get(0, 0, r-a, b);
        for (int s = 0; s < b; ++s) {

            bool first_equal = upper_hash1 == hash1.get(a, s, r, s+b);
            if (!first_equal) { continue; }
            bool second_equal = upper_hash2 == hash2.get(a, s, r, s+b);
            if (second_equal) {
                std::cout << a << ' ' << b << ' ' << s << '\n';
                return 0;
            }
        }
    }
    return 0;
}
