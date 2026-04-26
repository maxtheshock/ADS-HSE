#include <iostream>  
  
template<typename T>  
class TreeSet {  
    struct Node {  
        T value_;  
        Node* left = nullptr;  
        Node* right = nullptr;  
  
        Node(const T &value) : value_(value) {}  
  
        ~Node() {  
            delete left;  
            delete right;  
        }  
  
    } *root = nullptr;  
    // Node* root = nullptr; (absolutely the same)  
  
    bool find(Node*& node, const T& value) const {  
        if (!node) {  
            return false;  
        }  
        if (node->value_ == value) {  
            return true;  
        }  
        if (node->value_ > value) {  
            return find(node->left, value);  
        }  
        return find(node->right, value);  
    }  
      
    void insert(Node*& node, const T &value) const {  
        if (node == nullptr) {  
            node = new Node(value);  
        } else if (node->value_ == value) {  
            // pass  
            return;  
        } else if (node->value_ > value) {  
            insert(node->left, value);  
        } else {  
            insert(node->right, value);  
        }  
    }  
  
public:  
    void insert(const T& value) {  
  
    }  
  
    bool find(const T& value) const {  
        return true;  
    }  
  
    TreeSet() = default;  
  
    ~TreeSet() {  
        delete root;  
    }  
};  
  
int main() {  
    return 0;  
}