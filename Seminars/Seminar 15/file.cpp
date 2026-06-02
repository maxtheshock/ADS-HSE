struct Node {
    int64_t value = 0;
    int64_t sum = 0;
    int p = rd();
    Node* left = nullptr;
    Node* right = nullptr;
    int size = 1;
    explicit Node(int value) : value(value) {}
} *root = nullptr;


int size(Node* tree) {
    return !tree ? 0 : tree->size;
}

int sum(Node* tree) {
    return !tree ? 0 : tree->sum;
}

void update(Node* tree) {
    if (!tree) return;
    tree->size = size(tree->left) + size(tree->right) + 1;
    tree->sum = sum(tree->left) + sum(tree->right) + tree->value;
}

Node* merge(Node* less, Node* more) {
    if (!less) return more;
    if (!more) return less;
    // can change signs if we want (<)
    if (less->p > more->) {
        less->right = merge(less->right, more);
        update(less);
        return less;
    }
    more->left = merge(less, more->left);
    update(more);
    return more;
}

std::pair<Node*, Node*> split(Node* tree, int count) {
    if (!tree) return {nullptr, nullptr};
    if (size(tree->left) >= count) {
        auto [less, more] = split(tree->left, count);
        
    }
}

int main() {
    return 0;
}