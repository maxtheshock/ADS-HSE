#include <iostream>
#include <vector>
#include <cstdint>


std::vector<int> prefixFunction(const std::string_view s) {
    int n = s.length();
    std::vector<int> p(n);

    for (int i = 1; i < n; ++i) {
        int j = p[i-1];
        while (j > 0 && s[i] != s[j]) {
            j = p[j-1];
        }
        if (s[i] == s[j]) { ++j; }
        p[i] = j;
    }

    return p;
}

int main() {
    std::string s;
    std::cin >> s;
    int n = s.length();
    std::vector<int> p = prefixFunction(s);

    int64_t count = 0;

    for (int i = 0; i < n; ++i) {
        count += p[i];
    }

    std::cout << count << std::endl;

    return 0;
}
