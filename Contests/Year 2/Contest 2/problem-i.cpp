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

void printCompressed(const std::string_view word) {
    int word_length = word.length();
    std::vector<int> p = prefixFunction(word);

    int period_length = 0;

    for (int length = 1; 2 * length <= word_length; ++length) {
        if (p[2 * length - 1] >= length) {
            period_length = length;
            break;
        }
    }

    if (period_length == 0) {
        std::cout << word;
        return;
    }

    int repeated_length = 2 * period_length;

    while (repeated_length < word_length && word[repeated_length] == word[repeated_length % period_length]) {
        ++repeated_length;
    }

    int repetitions = repeated_length / period_length;
    int remainder_start = repetitions * period_length;

    std::cout << repetitions << "*(" << word.substr(0, period_length) << ")";
    if (remainder_start < word_length) {
        std::cout << "+" << word.substr(remainder_start);
    }
}

int main() {
    std::string word;
    bool first_word = true;

    while (std::cin >> word) {
        if (!first_word) {
            std::cout << ' ';
        }
        printCompressed(word);
        first_word = false;
    }

    std::cout << std::endl;
    return 0;
}
