#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>

uint64_t get_hash( const std::vector<uint64_t>& hashes, const std::vector<uint64_t>& powers,
    int start, int left, int right) {
        return hashes[start+right] - hashes[start+left]*powers[right-left];
    }

int main() {
    int A, B;
    std::cin >> A >> B;
    std::vector<uint8_t> field(A*B);

    for (int i = 0; i < A; ++i) {
        for (int j = 0; j < B; ++j) {
            int value;
            std::cin >> value;
            field[i*B + j] = value;
        }
    }

    const uint64_t p = 1000003;

    int max_side = std::max(A, B);
    std::vector<uint64_t> powers(max_side+1);

    powers[0] = 1;
    for (int i = 1; i <= max_side; ++i) {
        powers[i] = powers[i-1]*p;
    }

    std::vector<uint64_t> rows(A*(B+1));
    std::vector<uint64_t> reversed_rows(A*(B+1));

    for (int i = 0; i < A; ++i) {
        int start = i*(B+1);
        for (int j = 0; j < B; ++j) {
            rows[start + j+1] =
                rows[start + j]*p +
                field[i*B + j] + 1;

            reversed_rows[start + j+1] =
                reversed_rows[start + j]*p +
                field[i*B + (B-1-j)] + 1;
        }
    }

    std::vector<uint64_t> columns(B*(A+1));
    std::vector<uint64_t> reversed_columns(B*(A+1));

    for (int j = 0; j < B; ++j) {
        int start = j*(A+1);
        for (int i = 0; i < A; ++i) {
            columns[start + i+1] =
                columns[start + i]*p +
                field[i*B + j] + 1;
            reversed_columns[start + i+1] =
                reversed_columns[start + i]*p +
                field[(A-1-i)*B + j] + 1;
        }
    }

    auto is_correct = [&](int x, int y, int size) {
        int row_start = x*(B+1);
        int column_start = y*(A+1);

        uint64_t right = get_hash(rows, powers, row_start, y+1, y+1+size);
        uint64_t left = get_hash(reversed_rows, powers, row_start, B-y, B-y+size);
        if (left != right) { return false; }

        uint64_t down = get_hash(columns, powers, column_start, x+1, x+1+size);
        if (down != right) { return false; }

        uint64_t up = get_hash(reversed_columns, powers, column_start, A-x, A-x+size);
        return up == right;
    };

    auto find_cross = [&](int size, int& res_x, int& res_y) {
        for (int x = size; x < A-size; ++x) {
            for (int y = size; y < B-size; ++y) {
                if (is_correct(x, y, size)) {
                    res_x = x;
                    res_y = y;
                    return true;
                }
            }
        }
        return false;
    };

    int left = 0;
    int right = (std::min(A,B)-1)/2;

    while (left < right) {
        int middle = (left + right + 1)/2;
        int x, y;

        if (find_cross(middle, x, y)) {
            left = middle;
        } else {
            right = middle - 1;
        }
    }

    int answer_x = 0;
    int answer_y = 0;

    find_cross(left, answer_x, answer_y);
    std::cout << left << ' ' << answer_x+1 << ' ' << answer_y+1 << '\n';
    return 0;
}
