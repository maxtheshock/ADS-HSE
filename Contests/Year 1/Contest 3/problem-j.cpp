#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using ll = long long;

struct Node {
    ll key;
    int height;
    int size;
    Node* left;
    Node* right;

    Node(ll value) {
        key = value;
        height = 1;
        size = 1;
        left = nullptr;
        right = nullptr;
    }
};

int get_height(Node* v) {
    if (v == nullptr) {
        return 0;
    }

    return v->height;
}

int get_size(Node* v) {
    if (v == nullptr) {
        return 0;
    }

    return v->size;
}

void update(Node* v) {
    if (v == nullptr) {
        return;
    }

    v->height = std::max(get_height(v->left), get_height(v->right)) + 1;
    v->size = get_size(v->left) + get_size(v->right) + 1;
}

int get_balance(Node* v) {
    return get_height(v->right) - get_height(v->left);
}

Node* rotate_left(Node* v) {
    Node* u = v->right;
    v->right = u->left;
    u->left = v;

    update(v);
    update(u);

    return u;
}

Node* rotate_right(Node* v) {
    Node* u = v->left;
    v->left = u->right;
    u->right = v;

    update(v);
    update(u);

    return u;
}

Node* balance(Node* v) {
    update(v);

    if (get_balance(v) == 2) {
        if (get_balance(v->right) < 0) {
            v->right = rotate_right(v->right);
        }

        return rotate_left(v);
    }

    if (get_balance(v) == -2) {
        if (get_balance(v->left) > 0) {
            v->left = rotate_left(v->left);
        }

        return rotate_right(v);
    }

    return v;
}

bool exists(Node* root, ll key) {
    while (root != nullptr) {
        if (key == root->key) {
            return true;
        }

        if (key < root->key) {
            root = root->left;
        } else {
            root = root->right;
        }
    }

    return false;
}

Node* insert(Node* root, ll key) {
    if (root == nullptr) {
        return new Node(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    } else {
        return root;
    }

    return balance(root);
}

Node* find_min(Node* root) {
    while (root->left != nullptr) {
        root = root->left;
    }

    return root;
}

Node* remove_min(Node* root) {
    if (root->left == nullptr) {
        return root->right;
    }

    root->left = remove_min(root->left);

    return balance(root);
}

Node* erase(Node* root, ll key) {
    if (root == nullptr) {
        return nullptr;
    }

    if (key < root->key) {
        root->left = erase(root->left, key);
    } else if (key > root->key) {
        root->right = erase(root->right, key);
    } else {
        Node* left = root->left;
        Node* right = root->right;

        delete root;

        if (right == nullptr) {
            return left;
        }

        Node* min_node = find_min(right);
        min_node->right = remove_min(right);
        min_node->left = left;

        return balance(min_node);
    }

    return balance(root);
}

bool next_value(Node* root, ll key, ll& answer) {
    bool found = false;

    while (root != nullptr) {
        if (root->key > key) {
            answer = root->key;
            found = true;
            root = root->left;
        } else {
            root = root->right;
        }
    }

    return found;
}

bool prev_value(Node* root, ll key, ll& answer) {
    bool found = false;

    while (root != nullptr) {
        if (root->key < key) {
            answer = root->key;
            found = true;
            root = root->right;
        } else {
            root = root->left;
        }
    }

    return found;
}

ll kth_value(Node* root, int k) {
    while (root != nullptr) {
        int left_size = get_size(root->left);

        if (k == left_size + 1) {
            return root->key;
        }

        if (k <= left_size) {
            root = root->left;
        } else {
            k -= left_size + 1;
            root = root->right;
        }
    }

    return -1;
}

int main() {
    Node* root = nullptr;

    std::string command;
    ll x;

    while (std::cin >> command >> x) {
        if (command == "insert") {
            root = insert(root, x);
        } else if (command == "delete") {
            root = erase(root, x);
        } else if (command == "exists") {
            if (exists(root, x)) {
                std::cout << "true" << std::endl;
            } else {
                std::cout << "false" << std::endl;
            }
        } else if (command == "next") {
            ll answer;

            if (next_value(root, x, answer)) {
                std::cout << answer << std::endl;
            } else {
                std::cout << "none" << std::endl;
            }
        } else if (command == "prev") {
            ll answer;

            if (prev_value(root, x, answer)) {
                std::cout << answer << std::endl;
            } else {
                std::cout << "none" << std::endl;
            }
        } else if (command == "kth") {
            if (x <= 0 || x > get_size(root)) {
                std::cout << "none" << std::endl;
            } else {
                std::cout << kth_value(root, static_cast<int>(x)) << std::endl;
            }
        }
    }

    return 0;
}
