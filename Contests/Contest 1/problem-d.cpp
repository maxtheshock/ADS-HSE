#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n+1, 0);
    a[0] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = n; j >= i; --j) {
            a[j] += a[j-i];
        }
    }

    std::cout << a[n] << std::endl;
}