#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> zFunction(const std::string_view text) {
    int n = text.length();
    std::vector<int> z(n);
    z[0] = n;

    int left = 0;
    int right = 0;

    for (int i = 1; i < n; ++i) {
        if (i <= right) {
            z[i] = std::min(right - i + 1, z[i-left]);
        }
        while (i + z[i] < n && text[z[i]] == text[i + z[i]]) {
            ++z[i];
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
    std::string s;

    std::cin >> n >> s;

    std::string reversed = s;
    std::reverse(reversed.begin(), reversed.end());

    std::string joined = s + "#" + reversed;
    std::vector<int> z = zFunction(joined);

    for (int i = 0; i < n; ++i) {
        int position = 2*n - i;
        std::cout << z[position];
        if (i + 1 < n) {
            std::cout << ' ';
        }
    }

    std::cout << std::endl;
    return 0;
}
