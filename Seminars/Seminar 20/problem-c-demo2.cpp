#include <iostream>
#include <map>
#include <string>

class Trie {
    struct Node {
        int count = 0;
        std::map<char, Node> next;
    } root;
public:
    void insert(const std::string_view s) {
        Node* v = &root;
        for (char ch : s) {
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

    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        std::string t;
        std::cin >> t;
        std::cout << trie.find(t) << std::endl;
    }
}
