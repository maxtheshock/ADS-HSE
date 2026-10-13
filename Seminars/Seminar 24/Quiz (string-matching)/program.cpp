#include <iostream>
#include <vector>

void printVec (const std::vector<int>& v) {
    for (int _i = 0; _i < v.size(); ++_i) {
        std::cout << v[_i] << " ";
    }
    std::cout << '\n';
}

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
    std::string a, b;
    std::cin >> a >> b;

    std::string s = b + '#' + a;
    std::string res;
    int m = a.length();

    std::vector<int> t = prefixFunction(s);
    int u = t.size();

    for (int i = 0; i < (m-t[u-1]); ++i) {
        res += a[i];
    }
    for (int i = 0; i < b.length(); ++i) {
        res += b[i];
    }

    std::cout << res << '\n';
    return 0;
}
