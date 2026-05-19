#include <iostream>

int foo(int n, int k) {
    if (n <= k) { return 1; }
    return foo(n / 2, k) + foo((n+1) / 2, k);
}

int main() {
    int n = 0, k = 0;
    std::cin >> n >> k;
    std::cout << foo(n, k);
    return 0;
}