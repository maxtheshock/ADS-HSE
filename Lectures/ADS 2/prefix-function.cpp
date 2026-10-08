// this program computes a prefix function for a given string s

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
        int j = p[i-1]; //-- can omitted, 'cause j already stored a value for the previous i

        // we try to extend a suprefix, if it fails, recursively go
        // to the 2nd longest suprefix in a substring s[from 0 to j]
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