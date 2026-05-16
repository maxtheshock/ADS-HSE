#include <iostream>
#include <vector>

// Another non-trivial task (personally for me) on Binary Search on Answer, which I was struggling a lot with
// The core idea here is NOT to ask "Where should I put the next cow?" but to ask this question:
// "Can I place all K cows in such way, that for any of them the distance between all of them is no less than X?"
// And we just run BINARY SEARCH on this X

bool can_place(std::vector<long long>& v, int k, long long dist) {
    int count = 1; // 1st cow in v[0]
    long long last_pos = v[0];

    for (int i = 1; i < v.size(); ++i) {
        if (v[i] - last_pos >= dist) {
            last_pos = v[i];
            ++count;
        }
        if (count == k) { return true; } // all cows placed successfully
    }

    return false;
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<long long> bases;

    long long b;
    for (int i = 0; i < n; ++i) {
        std::cin >> b;
        bases.push_back(b);
    }

    long long l = 0, r = bases[n-1] - bases[0];
    long long ans = 0;

    while (l <= r) {
        long long m = (r+l) / 2;
        if (can_place(bases, k, m)) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    std::cout << ans << std::endl;
}