#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> normalize(const std::vector<int>& vec) {
    std::vector<int> res;
    res.reserve(vec.size());
    int f_index = 0;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] == 1) {
            f_index = i;
            break;
        }
    }
    for (size_t i = f_index; i < vec.size(); ++i) {
        res.push_back(vec[i]);
    }
    for (int i = 0; i < f_index; ++i) {
        res.push_back(vec[i]);
    }
    return res;
}

int main() {

    int n;
    if (!(std::cin >> n)) return 0;

    std::vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }

    auto v = normalize(numbers);
    std::vector<std::pair<int, int>> answers;
    
    bool changed = true;
    int max_passes = n * n; 
    int passes = 0;

    while (changed && passes < max_passes) {
        changed = false;
        for (int i = 0; i < n - 1; ++i) {
            if (v[i] > v[i+1] && (v[i] - v[i+1] > 1)) {
                answers.push_back({v[i], v[i+1]});
                std::swap(v[i], v[i+1]);
                changed = true;
            }
        }
        passes++;
    }

    for (int i = 0; i < n; ++i) {
        if (v[i] != i + 1) {
            std::cout << "-1\n";
            return 0;
        }
    }

    for (const auto& p : answers) {
        std::cout << p.first << " " << p.second << "\n";
    }
    std::cout << "0\n";

    return 0;
}
