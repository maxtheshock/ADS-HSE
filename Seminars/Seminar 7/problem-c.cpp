#include <iostream>
#include <vector>

int bin_search(const std::vector<int>& v, int key) {
    int left = -1, right = v.size();
    while (left + 1 < right) {
        int mid = (left + right) / 2;
        if (v[mid] < key) {
            left = mid;
        } else {
            right = mid;
        }
    }
    if (right != v.size() && v[right] == key) {
        return right;
    return -right - 1; }
}

int main() {
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector<int> v(n);
    for (auto& item : v) {
        std::cin >> item;
    }
    for (int i = 0; i < m; ++i) {
        int key = 0;
        std::cin >> key;
        std::cout << (bin_search(v, key) >= 0 ? "YES\n" : "NO\n");
    }
    return 0;
}