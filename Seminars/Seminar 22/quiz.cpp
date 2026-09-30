#include <iostream>
#include <cstdint>
#include <vector>

int64_t H(const std::vector<int64_t>& a, int64_t _p, int64_t _m, int ch_pos, int64_t ch_val) {
    int n = a.size();
    int64_t res = 0;

    for (int i = 0; i < n; ++i) {
        if (i != ch_pos-1) {
            res = ((_p*res) + a[i]) % _m;
        } else {
            res = ((_p*res) + ch_val) % _m;
        }
    }

    return res;
}

int main() {
    // 1st row
    int n;
    int64_t p, m; // amount, base, modulo
    std::cin >> n >> p >> m;
    int64_t curr_num;

    std::vector<int64_t> nums;
    // 2nd row
    for (int i = 0; i < n; ++i) {
        std::cin >> curr_num;
        nums.push_back(curr_num);
    }

    // 3rd row
    int64_t q;
    std::cin >> q;

    // requests part
    int i;
    int64_t x;
    for (int64_t j = 0; j < q; ++j) {
        // every request
        std::cin >> i >> x;
        std::cout << H(nums, p, m, i, x) << std::endl;
    }
    return 0;
}
