#include <iostream>
#include <string>
#include <vector>

// A helper-function for counting digits in a string (Notice: we use std::string_view to avoid copies)
std::vector<int> count_digits(const std::string_view s) {
    std::vector<int> res(10, 0);
    for (size_t i = 0; i < s.length(); ++i) {
        res[s[i] - '0']++;
    }
    return res;
}

// Main function for intersecting maps and computing the largest possible number
std::string solver(const std::string_view s1, const std::string_view s2) {
    std::vector<int> digits_s1 = count_digits(s1);
    std::vector<int> digits_s2 = count_digits(s2);

    std::vector<int> intersection(10, 0);
    int total_length = 0;
    for (int i = 0; i < 10; ++i) {
        int curr_digit_s1 = digits_s1[i];
        int curr_digit_s2 = digits_s2[i];
        intersection[i] = std::min(digits_s1[i], digits_s2[i]);
        total_length += intersection[i];
    }
    
    if (total_length == 0) { return "-1"; }
    std::string res = "";
    res.reserve(total_length);

    for (int i = 9; i >= 0; --i) {
        int entry = intersection[i];
        while (entry > 0) {
            res += (i + '0');
            --entry;
        }
    }

    if (res[0] == '0') { return "0"; }

    return res;
}


int main() {
    std::string a, b;
    std::cin >> a >> b;
    
    std::string final = solver(a, b);
    std::cout << final << std::endl;
    return 0;
}