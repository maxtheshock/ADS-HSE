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
    std::string source;
    std::string last_word;

    std::cin >> source >> last_word;

    std::string text = source + "#" + last_word;
    std::vector<int> z = zFunction(text);

    int source_length = source.length();
    int word_length = last_word.length();
    int shift = source_length + 1;

    std::vector<int> previous(word_length + 1, -1);
    previous[0] = 0;

    int rightmost = 0;

    for (int i = 0; i < word_length && i <= rightmost; ++i) {
        int prefix_length = std::min(source_length, z[shift+i]);
        int new_right = std::min(word_length, i + prefix_length);
        if (new_right > rightmost) {
            for (int position = rightmost + 1; position <= new_right; ++position) {
                previous[position] = i;
            }
            rightmost = new_right;
        }
    }

    if (previous[word_length] == -1) {
        std::cout << "Yes\n";
        return 0;
    }

    std::vector<std::string> parts;

    int position = word_length;
    while (position > 0) {
        int start = previous[position];
        parts.push_back(last_word.substr(start, position - start));
        position = start;
    }

    std::reverse(parts.begin(), parts.end());
    std::cout << "No\n";

    for (int i = 0; i < static_cast<int>(parts.size()); ++i) {
        std::cout << parts[i] << (i + 1 == static_cast<int>(parts.size()) ? "" : " ");
    }
    std::cout << '\n';

    return 0;
}
