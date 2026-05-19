#include <cstdint>
#include <iostream>

int main() {
    uint64_t n = 0;
    while (std::cin >> n) {
        uint64_t left = 0, right = 1ULL << 32;
        while (left + 1 < right) {
            uint64_t m = (left + right) / 2;
            if (m*m <= n) {
                left = m;
            } else {
                right = m;
            }
        }
        std::cout << left << std::endl;
    }
}