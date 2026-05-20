#include <iostream>
#include <vector>

int main() {
    int n, S, a_i;
    std::cin >> n >> S;

    std::vector<int> robots;
    for (int i = 0; i < n; ++i) {
        std::cin >> a_i;
        robots.push_back(a_i);
    }
}