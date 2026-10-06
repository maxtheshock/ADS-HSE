#include <iostream>
#include <map>

struct Node {
    std::map<char, Node> next;
    int count = 0;
} root;

void insert(const std::string_view s) {
    Node* v = &root;
    ++v->count;
    for (const char c : s) {
        v = &v->next[c];
        ++v->count;
    }
}

int find(const std::string_view s) {
    Node* v = &root;
    for (const char c : s) {
        if (!v->next.contains(c)) return 0;
        v = &v->next[c];
    }
    return v->count;
}


int main() {
    int n = 0, m = 0;
    std::cin >> n;
    std::string word;

    while (n-- && std::cin >> word) {
        insert(word);
    }
    std::cin >> m;
    while (m-- && std::cin >> word) {
        std::cout << find(word) << std::endl;
    }
    return 0;
}
