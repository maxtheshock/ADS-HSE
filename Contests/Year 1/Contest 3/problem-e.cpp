#include <iostream>
#include <vector>

using ll = long long;

struct Node {
    ll key;
    int left;
    int right;
};

std::vector<Node> tree;

bool check_bst(int v, ll min_key, ll max_key) {
    if (v == -1) {
        return true;
    }

    if (tree[v].key < min_key || tree[v].key >= max_key) {
        return false;
    }

    bool left_correct = check_bst(tree[v].left, min_key, tree[v].key);
    bool right_correct = check_bst(tree[v].right, tree[v].key, max_key);

    return left_correct && right_correct;
}

int main() {
    int n;
    std::cin >> n;

    tree.resize(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> tree[i].key >> tree[i].left >> tree[i].right;
    }

    ll inf = 1LL << 62;

    if (check_bst(0, -inf, inf)) {
        std::cout << "CORRECT" << std::endl;
    } else {
        std::cout << "INCORRECT" << std::endl;
    }

    return 0;
}
