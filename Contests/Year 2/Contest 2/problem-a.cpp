#include <iostream>
#include <vector>

std::vector<int> prefixFunction(const std::string_view text) {
    int n = text.length();
    std::vector<int> p(n);
    p[0] = 0;

    for (int i = 1; i < n; ++i) {
        int j = p[i-1];
        while (j > 0 && text[j] != text[i]) {
            j = p[j-1];
        }
        if (text[j] == text[i]) { ++j; }
        p[i] = j;
    }
    return p;
}

int main() {
    int n, m;

    while(std::cin >> n >> m) {
        std::vector<int> p(n+1);
        for (int i = 1; i <= n; ++i) {
            std::cin >> p[i];
        }

        if (p[1] != 0) {
            std::cout << "NO" << std::endl;
            continue;
        }

        bool pos = true;

        for (int i = 1; i <= n; ++i) {
            if (p[i] < 0 || p[i] >= i) {
                pos = false;
                break;
            }
        }
        if (pos == false) {
            std::cout << "NO" << std::endl;
            continue;
        }

        for (int i = 1; i < n; ++i) {
            if (p[i+1] > p[i] + 1) {
                pos = false;
                break;
            }
        }
        if (pos == false) {
            std::cout << "NO" << std::endl;
            continue;
        }

        std::string s = " ";
        s.resize(n+1);
        s[1] = 'a';

        for (int i = 2; i <= n; ++i) {
            if (p[i] > 0) {
                s[i] = s[p[i]];
                if (s[i] - 'a' >= m) {
                    pos = false;
                    break;
                }
            } else {
                bool forbidden[26] = {false};

                int cur = p[i-1];
                while (cur > 0) {
                    forbidden[s[cur+1] - 'a'] = true;
                    cur = p[cur];
                }
                forbidden[s[1] - 'a'] = true;

                char picked = 0;
                for (int j = 0; j < m; ++j) {
                    if (forbidden[j] == false) {
                        picked = 'a' + j;
                        break;
                    }
                }

                if (picked == 0) {
                    pos = false;
                    break;
                }
                s[i] = picked;
            }
        }

        if (pos == false) {
            std::cout << "NO" << std::endl;
            continue;
        }

        std::string ver_str = s.substr(1);
        std::vector<int> checked_string = prefixFunction(ver_str);

        for (int j = 0; j < n; ++j) {
            if (checked_string[j] != p[j+1]) {
                pos = false;
                break;
            }
        }

        if (pos == false) {
            std::cout << "NO" << std::endl;
            continue;
        }

        std::cout << "YES" << '\n';
        std::cout << ver_str << std::endl;
    
    }

    return 0;
}
