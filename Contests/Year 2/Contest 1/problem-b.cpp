#include <iostream>
#include <string>

int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::string current;
        for (int bit = 0; bit < 8; ++bit) {
            if ((i >> bit) & 1) {
                current += "ln";
            } else {
                current += "mm";
            }
        }
        std::cout << current << '\n';
    }
    return 0;
}
