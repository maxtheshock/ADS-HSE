#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdint>

constexpr int kValueShift = 1000000000;

int getCurrentDigit(int key, int64_t place, int base) {
    return static_cast<int>((static_cast<int64_t>(key) / place) % base);
}

std::vector<int> readShiftedValues(int amount, int& max_key) {
    std::vector<int> values(amount);
    max_key = 0;
    for (int i = 0; i < amount; ++i) {
        int value = 0;
        std::cin >> value;
        const int key = value + kValueShift;
        values[i] = key;
        if (key > max_key) {
            max_key = key;
        }
    }
    return values;
}

void stableDigitCountingPass(
    std::vector<int>& values,
    std::vector<int>& buffer,
    std::vector<int>& position,
    int base,
    int64_t place
) {
    std::fill(position.begin(), position.end(), 0);

    const int amount = static_cast<int>(values.size());

    for (int i = 0; i < amount; ++i) {
        const int digit = getCurrentDigit(values[i], place, base);
        ++position[digit];
    }

    int next_position = 0;

    for (int digit = 0; digit < base; ++digit) {
        const int digit_amount = position[digit];
        position[digit] = next_position;
        next_position += digit_amount;
    }

    for (int i = 0; i < amount; ++i) {
        const int digit = getCurrentDigit(values[i], place, base);
        buffer[position[digit]] = values[i];
        ++position[digit];
    }

    values.swap(buffer);
}

void radixSort(std::vector<int>& values, int base, int max_key) {
    std::vector<int> buffer(values.size());
    std::vector<int> position(base, 0);
    for (int64_t place = 1; place <= max_key; place *= base) {
        stableDigitCountingPass(values, buffer, position, base, place);
    }
}

void printRestoredValues(const std::vector<int>& values) {
    const int amount = static_cast<int>(values.size());
    for (int i = 0; i < amount; ++i) {
        if (i > 0) {
            std::cout << ' ';
        }
        std::cout << values[i] - kValueShift;
    }
    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    int base = 0;
    std::cin >> n >> base;
    int max_key = 0;
    std::vector<int> values = readShiftedValues(n, max_key);

    radixSort(values, base, max_key);
    printRestoredValues(values);

    return 0;
}
