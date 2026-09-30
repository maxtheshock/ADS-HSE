#include <iostream>

int main() {
    long long n, x, y;
    std::cin >> n >> x >> y;

    long long first = std::min(x, y);
    // we just made first copy
    --n; // one less required

    // in this task, we use binary search on the answer
    // formula for copies produced in N seconds: N/x + N/y
    // but we cannot simply find N because of integer numbers nature
    long long l = 0, r = 1e18;
    while (l < r) {
        long long m = (l+r) / 2;
        if (m / x + m / y >= n) {
            r = m;
        } else {
            l = m + 1; // because m is already bad
                       // otherwise, infinite loop is reached at the last step(!)
        }
    }

    std::cout << first + l;
}