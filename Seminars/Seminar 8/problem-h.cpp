#include <iostream>
#include <vector>
#include <cstdint>

int main() {
    int64_t n = 0, a = 0, b = 0, w = 0, h = 0;
    std::cin >> n >> a >> b >> w >> h;
    auto f = [&](int64_t d ) -> int64_t {
        int64_t a2d = a + 2*d;
        int64_t b2d = b + 2*d;
        return std::max((w / a2d) * (h / b2d), (h / a2d) * (w / b2d));
    };
    int64_t left = 0, right = std::max(w, h);

    while (left + 1 < right) {
        int64_t mid = (left + right) / 2;
        if (f(mid) >= n) { // < > <= >=
            left = mid;
        } else {
            right = mid;
        }
    }
    std::cout << right;
    return 0;
}