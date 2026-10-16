#include <iostream>
#include <vector>
#include <algorithm>

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
    int n, alphabet_size;
    long long k;

    std::cin >> n >> alphabet_size >> k;

    std::string word;
    std::cin >> word;

    std::vector<int> p = prefixFunction(word);
    std::vector<std::vector<int>> next_state(n, std::vector<int>(alphabet_size));
    long long max_rollback = 0;

    for (int state = 0; state < n; ++state) {
        for (int letter = 0; letter < alphabet_size; ++letter) {
            int next;
            if (letter == word[state] - 'a') {
                next = state + 1;
            } else if (state == 0) {
                next = 0;
            } else { next = next_state[p[state - 1]][letter]; }

            next_state[state][letter] = next;
            max_rollback = std::max(max_rollback, static_cast<long long>(state - next));
        }
    }

    long long answer = n + k * max_rollback;
    std::cout << answer << '\n';
    return 0;
}
