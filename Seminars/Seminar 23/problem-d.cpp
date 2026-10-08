#include <iostream>
#include <map>
#include <vector>

int count = 0;

struct Node {
    std::map<char, Node> next;
    int is_terminal = -1;
} root;

void insert(const std::string_view s) {
    Node* v = &root;
    for (const char c : s) {
        v = &v->next[c];
    }
    v->is_terminal = count;
    ++count;
}

int main() {
    std::string text;
    std::cin >> text;
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::string word;
        std::cin >> word;
        insert(word);
    }
    std::vector<int> mask(n);
    for (int i = 0; i < text.size(); ++i) {
        Node* v = &root;
        for (int j = i; j < text.size(); ++j) {
            char c = text[j];
            if (!v->next.contains(c)) { break; };
            v = &v->next[c];
            if (v->is_terminal != -1) {
                mask[v->is_terminal] = 1;
            }
        }
    }
    for (const int i : mask) {
        std::cout << (i ? "Yes" : "No") << '\n';
    }
    return 0;
}
