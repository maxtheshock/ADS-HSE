#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

std::ostream &operator<<(std::ostream &os, const std::vector<int> &v) {
    for (auto i: v) {
        os << i << ' ';
    }
    return os;
}

int main() {
    std::string s = "abacaba";
    s.push_back('\0');
    int n = s.size();
    std::vector<int> p(n);
    for (int i = 0; i < n; ++i) p[i] = i;
    std::ranges::sort(p, [&](int i, int j)-> bool {
        return s[i] < s[j];
    });
    std::cout << p << '\n';
    std::vector<int> c(n);
    for (int i = 1; i < n; ++i) {
        // 7 0 2 4 6 1 5 3
        c[p[i]] = c[p[i - 1]] + (s[p[i]] != s[p[i - 1]]);
    }
    std::cout << c << '\n'; // 1 2 1 3 1 2 1 0
    for (int len = 1; len < n; len *= 2) {
        std::vector<std::pair<int, int> > pc(n);
        for (int i = 0; i < n; ++i) {
            pc[i] = {c[i], c[(i + len) % n]};
        }
        std::ranges::sort(p, [&](int i, int j)-> bool {
            return pc[i] < pc[j];
        });
        std::cout << p << '\n';
        for (int i = 1; i < n; ++i) {
            c[p[i]] = c[p[i - 1]] + (pc[p[i]] != pc[p[i - 1]]);
        }
    }
    return 0;
}
