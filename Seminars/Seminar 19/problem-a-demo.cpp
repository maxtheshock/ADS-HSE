#include <iostream>
#include <vector>
#include <cstdint>

int main() {
    size_t n = 0;
    std::cin >> n;
    std::vector<int> v(n+1);
    for (size_t i = 1; i < n+1; ++i) {
        std::cin >> v[i];
        v[i] = (v[i] == 0 ? 1 : 0);
        v[i] += v[i-1];
    }

    size_t k;
    std::cin >> k;
    for (size_t i = 0; i < k; ++i) {
        size_t l = 0, r = 0;
        std::cin >> l >> r;
        std::cout << v[r] - v[l-1] << std::endl;
    }
    
    return 0;
}
