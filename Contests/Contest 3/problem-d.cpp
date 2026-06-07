#include <iostream>
#include <vector>
#include <limits>

using ll = long long;

struct Node {
    ll key;
    int left;
    int right;
};

bool isBST(const std::vector<Node>& tree, int u, ll min_val, ll max_val) {
    if (u == -1) {
        return true;
    }
    
    if (tree[u].key <= min_val || tree[u].key >= max_val) {
        return false;
    }
    
    return isBST(tree, tree[u].left, min_val, tree[u].key) &&
           isBST(tree, tree[u].right, tree[u].key, max_val);
}

int main() {
    int n;
    std::cin >> n;

    if (n == 0) {
        std::cout << "CORRECT" << std::endl;
        return 0;
    }

    std::vector<Node> tree(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> tree[i].key >> tree[i].left >> tree[i].right;
    }

    ll min_limit = std::numeric_limits<ll>::min();
    ll max_limit = std::numeric_limits<ll>::max();

    if (isBST(tree, 0, min_limit, max_limit)) {
        std::cout << "CORRECT" << std::endl;
    } else {
        std::cout << "INCORRECT" << std::endl;
    }

    return 0;
}
