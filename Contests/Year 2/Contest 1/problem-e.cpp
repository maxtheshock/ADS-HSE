#include <iostream>
#include <cstdint>
#include <string>
#include <array>

int getIndex(char symbol) {
    if (symbol >= 'a' && symbol <= 'z') { return symbol-'a'; }
    return symbol-'A'+26;
}

int main() {
    int g, size;
    std::string word, sequence;
    std::cin >> g >> size >> word >> sequence;

    std::array<int, 52> required{};
    std::array<int, 52> current{};

    for (char symbol : word) { ++required[getIndex(symbol)]; }
    for (int i = 0; i < g; ++i) { ++current[getIndex(sequence[i])]; }

    int differences = 0;

    for (int i = 0; i < 52; ++i) {
        if (required[i] != current[i]) { ++differences; }
    }

    auto change = [&](int index, int value) {
        if (current[index] == required[index]) { ++differences; }
        current[index] += value;
        if (current[index] == required[index]) { --differences; }
    };

    int64_t answer = (differences == 0);

    for (int right = g; right < size; ++right) {
        change(getIndex(sequence[right-g]), -1);
        change(getIndex(sequence[right]), 1);
        if (differences == 0) { ++answer; }
    }

    std::cout << answer << '\n';
    return 0;
}
