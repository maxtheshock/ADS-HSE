// this program computes a prefix function for a given string s
// Def: a border is a simultaneous prefix and a suffix of a string

#include <iostream>
#include <vector>

void printVec(const std::vector<int>& v) {
    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << '\n';
}

int main() {
    std::string s;
    std::cin >> s;
    int n = s.length();
    
    std::vector<int> p(n);
    p[0] = 0;

    // we ASSUME that we already know p[0 1 ... i-1] and we
    // want to calculate the next one - p[i]
    for (int i = 1; i < n; ++i) {
        int j = p[i-1]; // j stores a value for the previous i (current best border length)

        // we try to extend a border, if it fails, we go
        // to the 2nd longest border in a substring s[from 0 to j-1]
        while (j > 0 && s[j] != s[i]) {
            j = p[j-1]; // recursion step
        }
        if (s[j] == s[i]) { ++j; }
        p[i] = j;
    }

    std::cout << s << '\n';
    printVec(p);

    return 0;
}