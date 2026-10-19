#include <iostream>
#include <vector>
#include <iomanip>

class BigInteger {
    static const int base = 1000000000;
    std::vector<int> digits;
public:
    BigInteger(int value = 0) {
        do {
            digits.push_back(value % base);
            value /= base;
        } while (value > 0);
    }
    void multiply(const int value) {
        long long carry = 0;

        for (int i = 0; i < static_cast<int>(digits.size()); ++i) {
            long long current = 1LL * digits[i] * value + carry;
            digits[i] = current % base;
            carry = current / base;
        }

        while (carry > 0) {
            digits.push_back(carry % base);
            carry /= base;
        }
    }

    void add(const BigInteger& other) {
        int new_size = std::max(digits.size(), other.digits.size());
        digits.resize(new_size, 0);

        long long carry = 0;

        for (int i = 0; i < new_size; ++i) {
            long long current = digits[i] + carry;

            if (i < static_cast<int>(other.digits.size())) {
                current += other.digits[i];
            }

            digits[i] = current % base;
            carry = current / base;
        }

        if (carry > 0) {
            digits.push_back(carry);
        }
    }

    void print() const {
        std::cout << digits.back();

        for (int i = static_cast<int>(digits.size()) - 2; i >= 0; --i) {
            std::cout << std::setw(9) << std::setfill('0') << digits[i];
        }
    }
};

std::vector<int> prefixFunction(const std::string_view text) {
    int n = text.length();
    std::vector<int> p(n);
    p[0] = 0;

    for (int i = 1; i < n; ++i) {
        int j = p[i-1];
        while (j > 0 && text[j] != text[i]) {
            j = p[j-1];
        }
        if (text[j] == text[i]) {
            ++j;
        }
        p[i] = j;
    }

    return p;
}

int main() {
    int alphabet_size;
    std::string word;

    std::cin >> alphabet_size >> word;

    int word_length = word.length();
    std::vector<int> p = prefixFunction(word);
    std::vector<char> is_border(word_length+1, false);

    int border_length = word_length;

    while (border_length > 0) {
        is_border[border_length] = true;
        border_length = p[border_length-1];
    }

    BigInteger current_power(1);
    BigInteger answer(0);

    for (int length = 1; length <= word_length; ++length) {
        current_power.multiply(alphabet_size);
        if (is_border[length]) {
            answer.add(current_power);
        }
    }

    answer.print();
    std::cout << std::endl;
    return 0;
}
