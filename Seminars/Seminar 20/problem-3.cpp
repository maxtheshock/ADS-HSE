#include <iostream>
#include <string>
#include <map>

class Trie {
    struct Node {
        int count = 0;
        std::map<char, Node> next;
    } root;
    int vertices = 1;
public:
    void insert(const std::string_view s) {
        Node* v = &root;
        for (char ch : s) {
            if (v->next.count(ch) == 0) { vertices++; }
            v = &v->next[ch];
            ++v->count;
        }
    }
    int find(const std::string_view s) {
        Node* v = &root;
        for (char ch : s) {
            if (v->next.count(ch) == 0) return 0;
            v = &v->next[ch];
        }
        return v->count;
    }
    int getVertices() { return vertices; }
};


int main() {
    int n;
    std::cin >> n;
    Trie trie;
    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        trie.insert(s);
    }

    std::cout << trie.getVertices() << std::endl;
    return 0;
}