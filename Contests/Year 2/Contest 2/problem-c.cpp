#include <iostream>
#include <vector>

std::vector<int> prefixToZ(const std::vector<int>& prefix) {
    int n = prefix.size();
    std::vector<int> z(n);
    z[0] = n;

    for (int i = 1; i < n; ++i) {
        if (prefix[i] > 0) {
            int start = i - prefix[i] + 1;
            z[start] = std::max(z[start],prefix[i]);
        }
    }

    int left = 0;
    int right = 0;

    for (int i = 1; i < n; ++i) {
        if (i <= right) {
            int copied_value = std::min(z[i - left], right - i + 1);
            z[i] = std::max(z[i], copied_value);
        }
        if (i + z[i] - 1 > right) {
            left = i;
            right = i + z[i] - 1;
        }
    }
    return z;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<int> prefix(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> prefix[i];
    }
    std::vector<int> z = prefixToZ(prefix);
    for (int i = 0; i < n; ++i) {
        std::cout << z[i] << (i + 1 == n ? "" : " ");
    }

    std::cout << std::endl;
    return 0;
}
