// Implementation of a Knuth-Morris-Pratt algorithm, allowing us
// to find a pattern in a text in a linear O(n+m) time

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
    std::string t, s;
    std::getline(std::cin, t);
    std::getline(std::cin, s);

    int m = t.length();
    int n = s.length();

    // Stage 1: pre-processing (Constructing a prefix-array for the pattern S)
    std::vector<int> p = prefixFunction(s);

    // Stage 2: Search
    std::vector<int> occurrences;
    int j = 0;

    for (int i = 0; i < m; ++i) {
        while (j > 0 && t[i] != s[j]) {
            j = p[j-1];
        }
        if (t[i] == s[j]) { ++j; }

        // the entire pattern has been matched
        if (j == n) {
            occurrences.push_back(i-n+1);
            j = p[j-1];
        }
    }

    for (int entries : occurrences) {
        std::cout << entries << " ";
    }
    std::cout << '\n';

    return 0;
}
