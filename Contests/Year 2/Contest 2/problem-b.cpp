#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> z(n);
    for (int& x : z) {
        std::cin >> x;
    }

    std::vector<int> pi(n, 0);

    for (int i = 1; i < n; ++i) {
        for (int len = z[i]; len > 0; --len) {
            int pos = i + len - 1;
            if (pi[pos] != 0) {
                break;
            }
            pi[pos] = len;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            std::cout << ' ';
        }
        std::cout << pi[i];
    }
    std::cout << '\n';
}
