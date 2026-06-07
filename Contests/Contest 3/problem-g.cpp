#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;

struct Node {
    ll key;
    int left;
    int right;
};

int main() {
    int n;
    std::cin >> n;
    std::vector<Node> tree(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> tree[i].key >> tree[i].left >> tree[i].right;
    }
    std::vector<int> order;
    std::vector<int> stack;

    stack.push_back(0);

    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();
        order.push_back(v);
        if (tree[v].left != -1) {
            stack.push_back(tree[v].left);
        }

        if (tree[v].right != -1) {
            stack.push_back(tree[v].right);
        }
    }
    std::vector<ll> subtree_sum(n, 0);

    for (int i = static_cast<int>(order.size()) - 1; i >= 0; --i) {
        int v = order[i];
        subtree_sum[v] = tree[v].key;
        if (tree[v].left != -1) {
            subtree_sum[v] += subtree_sum[tree[v].left];
        }

        if (tree[v].right != -1) {
            subtree_sum[v] += subtree_sum[tree[v].right];
        }
    }

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            std::cout << ' ';
        }
        std::cout << subtree_sum[i];
    }

    std::cout << std::endl;
    return 0;
}