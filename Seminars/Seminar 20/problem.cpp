#include <iostream>
#include <string>
#include <map>

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

}
