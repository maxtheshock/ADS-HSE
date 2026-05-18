#include <iostream>
#include <string>
#include <map>

// A helper-function for counting digits in a string (Notice: we use std::string_view to avoid copies)
std::map<char, int> count_chars(const std::string_view s) {
    std::map<char, int> res;
    for (size_t i = 0; i < s.length(); ++i) {
        res[s[i]]++;
    }
    return res;
}

// void printMap(std::map<char, int>& m) {
//     for (const auto& [key, value] : m) {
//         std::cout << key << " " << value << std::endl;
//     }
// }

int main() {
    std::string x, y;
    std::cin >> x >> y;

    auto f = count_chars(x);
    return 0;
}