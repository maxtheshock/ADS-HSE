#include <iostream>
#include <map>
#include <vector>

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

std::string find(const std::string& s) {
    Node* v = &root;
    std::string pref;
    for (const char c : s) {
        v = &v->next[c];
        pref.push_back(c);
        if (v->count == 1) return pref;
    }
    return "-1";
}


int main() {
    int n = 0;
    std::cin >> n;
    std::vector<std::string> words(n);
    for (auto& w : words) {
        std::cin >> w;
        insert(w);
    }
    for (auto& w : words) {
        std::cout << find(w) << '\n';
    }
    return 0;
}
