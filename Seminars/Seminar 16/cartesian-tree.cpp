#include <iostream>
#include <cstdint>
#include <random>
#include <ctime>

std::mt19937 rd(time(nullptr));

struct Node {
    int64_t value = 0;
    uint32_t p = rd();
    int size = 1;
    Node* left = nullptr;
    Node* right = nullptr;

    explicit Node(int64_t value) : value(value) {}
} *root = nullptr;

int size(Node* tree) {
    return tree ? tree->size : 0;
}

void update(Node* tree) {
    if (!tree) return;
    tree->size = size(tree->left) + size(tree->right) + 1;
}

std::pair<Node*, Node*> split(Node* tree, int count) {
    if (!tree) return {nullptr, nullptr};
    if (size(tree->left) >= count) {
        auto [less, more] = split(tree->left, count);
        tree->left = more;
        update(tree);
        return {less, more};
    }
    auto [less, more] = split(tree->right, count - 1 - size(tree->left));
    tree->right = less;
    update(tree);
    return {tree, more};
}

Node* merge(Node* less, Node* more) {
    if (!less) return more;
    if (!more) return less;
    if (less->p < more->p) {
        less->right = merge(less->right, more);
        update(less);
        return less;
    }
    more->left = merge(less, more->left);
    update(more);
    return more;
}
