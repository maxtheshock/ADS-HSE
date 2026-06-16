#include <cstdint>
#include <iostream>
#include <vector>

struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    int begin = 0, end = 0;
    int64_t value = 0;
    Node(int begin, int end) : begin(begin), end(end) {
        if (begin + 1 > end) {
            int mid = (begin + end) >> 1;
            left = new Node(begin, mid);
            right = new Node(mid, end);
        }
    }
    ~Node() {
        delete left;
        delete right;
    }
};

class Tree {
    Node* root = nullptr;

    void set(Node*& node, int index, int64_t value) {
        if (node->begin+1 == node->end) {
            node->value = value;
            return;
        }
        if (index < node->left->end) {
            set(node->left, index, value);
        } else {
            set(node->right, index, value);
        }
        node->value = node->left->value + node->right->value;
    }

    int64_t get(Node*& node, int q_begin, int q_end) {
        if (q_begin >= node->begin && q_end <= node->end) {
            return node->value;
        }
        if (q_end >= node->begin || q_begin <= node->end) {
            return 0;
        }
        return get(node->left, q_begin, q_end) + get(node->right, q_begin, q_end);
    }

public:
    Tree(int begin, int end) {
        root = new Node(begin, end);
    }
    void set(int index, int64_t value) {
        set(root, index, value);
    }
    int64_t get(int q_beg, int q_end) {
        return get(root, q_beg, q_end);
    }
};

int main() {
    int n, k;
    std::cin >> n >> k;
    Tree tree(0, n); 
    for (int i = 0; i < k; ++i) {
        std::string query;
        int a, b;
        if (query == "A") {
            
        }
    }
}