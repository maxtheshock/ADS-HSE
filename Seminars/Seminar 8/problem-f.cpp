#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

int main() {
    int64_t n = 0, m = 0;
    std::cin >> n >> m;
    std::vector<int64_t> time(m);
    for (auto& item : time) {
        std::cin >> item;
    }
    auto f = [&](int64_t x) -> int64_t {
        int64_t c = 0;
        for (auto t : time) {
            c += x / t;
        }
        return c;
    };

    int64_t left = 0;
    int64_t right = *std::max_element(time.begin(), time.end());
    right *= n;
    while (left + 1 < right) {
        int64_t mid = (left + right) / 2;
        if (f(mid) < n) {
            left = mid;
        } else {
            right = mid;
        }
    }
    std::cout << right;
    return 0;
}