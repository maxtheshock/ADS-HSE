#include <iostream>
#include <random>
#include <ctime>

std::mt19937_64 rd(time(nullptr));

// Actually it's a bad realization because we need smart pointers
struct Node {
    int value_ = 0;
    uint64_t p = rd();
    Node* left = nullptr;
    Node* right = nullptr;
    explicit Node(int value) : value_(value) {}
    ~Node() {
        delete left;
        delete right;
    }
};

class Treap {
    Node* root = nullptr;

    Node* merge(Node* less, Node* more) {
        if (!less) return more;
        if (!more) return less;
        if (less->p > more->p) {
            less->right = merge(less->right, more);
            return less;
        }
        more->left = merge(less, more->left);
        return more;
    }

    std::pair<Node*, Node*> split(Node* tree, int key) {
        if (!tree) return {nullptr, nullptr};
        if (tree->value_ > key) {
            auto[less, more] = split(tree->left, key);
            tree->left = more;
            return {less, tree};
        }
        auto[less, more] = split(tree->right, key);
        tree->left = more;
        return {tree, more};
    }

    void print(Node* tree) {
        if (!tree) return;
        print(tree->left);
        std::cout << tree->value_ << " ";
        print(tree->right);
    }

    int hi(Node* tree) {
        if (!tree) return 0;
        return std::max(hi(tree->left), hi(tree->right)) + 1;
    }

public:

    void insert(int value) {
        auto[less, more] = split(root, value);
        root = merge(less, new Node(value));
        root = merge(root, more);
    }
    void print() {
        print(root);
    }
    int64_t hi() {
        return {hi(root)};
    }
};

int main() {
    Treap t;
    for (int i = 0; i < (1 << 10); ++i) {
        t.insert(rd());
    }
    std::cout << t.hi();
    return 0;
}