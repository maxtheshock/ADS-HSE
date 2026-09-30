#include <iostream>
#include <cstdint>
#include <vector>

int64_t H(const std::vector<int64_t>& a, int64_t _p, int64_t _m) {
    int n = a.size();
    int64_t res = 0;
    for (int i = 0; i < n; ++i) {
        res = ((_p*res) + a[i]) % _m;
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
    nums.reserve(n);
    // 2nd row + powers vector set-up
    for (int i = 0; i < n; ++i) {
        std::cin >> curr_num;
        nums.push_back(curr_num);
    }

    // this is designed to store powers[i] = p^i mod m
    std::vector<int64_t> powers(n);
    powers[0] = 1;
    for (int i = 1; i < n; ++i) {
        powers[i] = (powers[i-1]*p) % m;
    }

    int64_t hash = H(nums, p, m);

    // 3rd row (then go requests)
    int64_t q;
    std::cin >> q;

    int i;
    int64_t x;
    for (int64_t j = 0; j < q; ++j) {
        std::cin >> i >> x;

        int64_t difference = (x - nums[i-1])*powers[n-i] % m;
        int64_t new_hash = (hash + difference) % m;
        if (new_hash < 0) { new_hash += m; }

        std::cout << new_hash << '\n';
    }
    return 0;
}
