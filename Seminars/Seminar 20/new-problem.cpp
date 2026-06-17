#include <iostream>
#include <vector>

using ull = unsigned long long;

int main() {
    int n;
    std::cin >> n;
    std::vector<ull> p1 = {0};
    std::vector<ull> p2 = {0};
    for (int i = 1; i < n+1; ++i) {
        std::string req;
        std::cin >> req;
        if (req == "-") {
            std::cout << p1[p1.size()-1] << std::endl;
            p1.pop_back();
            p2.pop_back();
        };
        if (req.front() == '+') {
            req.erase(0,1);
            p1.push_back(std::stoll(req));
            p2.push_back(std::stoll(req));
            int j = p2.size()-1;
            p2[j] += p2[j-1];
        }
        if (req.front() == '?') {
            int l = p1.size()-1;
            int k = std::stoi(req.erase(0,1));
            ull sum = p2[l] - p2[l-k];
            std::cout << sum << std::endl;
        }
    }
}
