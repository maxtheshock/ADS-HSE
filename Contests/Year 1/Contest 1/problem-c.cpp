#include <iostream>
#include <vector>

int n, t;
std::vector<int> current_perm;
std::vector<int> unused;

void run(int pos) {
    if (t == 0) return;
    if (pos == n + 1) {
        for (int i = 0; i < n; ++i) {
            std::cout << current_perm[i] << (i == n - 1 ? "" : " ");
        }
        std::cout << "\n";
        t--;
        return;
    }

    int sz = unused.size();
    for (int i = 0; i < sz; ++i) {
        int val = unused[i];
        if (val == pos) continue;
        unused.erase(unused.begin() + i);
        current_perm.push_back(val);
        run(pos + 1);

        current_perm.pop_back();
        unused.insert(unused.begin() + i, val);

        if (t == 0) return;
    }
}

int main() {
    std::cin >> n >> t;
    for (int i = 1; i <= n; ++i) {
        unused.push_back(i);
    }
    run(1);
    
    return 0;
}