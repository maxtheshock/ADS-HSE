#include <iostream>
#include <vector>

void gen(int n, int k, std::vector<int>& tmp) { // unlikely, we need to throw a vector into a function
    // First of all, we examine the BASE CASE
    // (when maximum depth reached, we just print and then undo last step)
    if (tmp.size() == n) {
        for (int i = 0; i < n; ++i) {
            std::cout << tmp[i] << (i == n-1 ? "" : " "); // cosmetics
        }
        std::cout << std::endl;
        return;
    }

    // Core of the recursion
    for (int i = 1; i <= k; ++i) {
        tmp.push_back(i);
        gen(n, k, tmp);
        tmp.pop_back();
    }
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> nums;
    gen(n, k, nums);
    return 0;
}