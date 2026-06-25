#include <iostream>
#include <vector>

void countingSort(int n) {
    constexpr int kMinValue = -1000000;
    constexpr int kMaxValue = 1000000;
    constexpr int kShift = -kMinValue;
    constexpr int kRange = kMaxValue - kMinValue + 1;

    std::vector<int> count(kRange, 0);

    for (int i = 0; i < n; ++i) {
        int value = 0;
        std::cin >> value;
        ++count[value + kShift];
    }

    bool is_first = true;

    for (int index = 0; index < kRange; ++index) {
        const int value = index - kShift;

        for (int amount = 0; amount < count[index]; ++amount) {
            if (is_first == false) {
                std::cout << ' ';
            }

            std::cout << value;
            is_first = false;
        }
    }

    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    std::cin >> n;
    countingSort(n);

    return 0;
}
