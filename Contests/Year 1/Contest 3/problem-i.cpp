// I like this task, TBH. I like sorting algorithms and trees

#include <iostream>
#include <algorithm>

struct Node {
    int key;
    int height;
    Node *left, *right;

    Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

int getHeight(Node* n) {
    return n ? n->height : 0;
}

int getBalance(Node* n) {
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

void updateHeight(Node* n) {
    n->height = 1 + std::max(getHeight(n->left), getHeight(n->right));
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

Node* balance(Node* n) {
    updateHeight(n);
    int b = getBalance(n);
    if (b > 1) {
        if (getBalance(n->left) < 0) n->left = rotateLeft(n->left);
        return rotateRight(n);
    }
    if (b < -1) {
        if (getBalance(n->right) > 0) n->right = rotateRight(n->right);
        return rotateLeft(n);
    }
    return n;
}

Node* insert(Node* n, int key) {
    if (!n) return new Node(key);
    if (key < n->key) n->left = insert(n->left, key);
    else if (key > n->key) n->right = insert(n->right, key);
    else return n;
    return balance(n);
}

Node* findMin(Node* n) {
    return n->left ? findMin(n->left) : n;
}

Node* remove(Node* n, int key) {
    if (!n) return nullptr;
    if (key < n->key) n->left = remove(n->left, key);
    else if (key > n->key) n->right = remove(n->right, key);
    else {
        if (!n->left || !n->right) {
            Node* temp = n->left ? n->left : n->right;
            delete n;
            return temp;
        }
        Node* temp = findMin(n->right);
        n->key = temp->key;
        n->right = remove(n->right, temp->key);
    }
    return balance(n);
}

bool exists(Node* n, int key) {
    while (n) {
        if (key == n->key) return true;
        n = (key < n->key) ? n->left : n->right;
    }
    return false;
}

int main() {
    Node* root = nullptr;
    std::string op;
    int x;
    while (std::cin >> op >> x) {
        if (op == "insert") root = insert(root, x);
        else if (op == "delete") root = remove(root, x);
        else if (op == "exists") {
            if (exists(root, x)) std::cout << "true" << std::endl;
            else std::cout << "false" << std::endl;
        }
    }
    return 0;
}
