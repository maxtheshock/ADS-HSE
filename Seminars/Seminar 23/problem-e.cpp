#include <iostream>
#include <cstdint>
#include <vector>
#include <map>
#include <string>
#include <ranges>
#include <queue>

int64_t count;

struct Node {
    std::map<char, Node> next;
    int64_t is_terminal = -1;
    Node* suff_link = nullptr;
    Node* term_link = nullptr;
} root;

void insert(const std::string& s) {
    Node* v = &root;
    for (const char c : s) v = &v->next[c];
    v->is_terminal = count;
    ++count;
}

// std::string find(const std::string& s) {
//     Node* v = &root;
//     std::string pref;
//     for (const char c : s) {
//         if (!v->next.num(c)) return 0;
//         v = &v->next[c];
//         pref.push_back(c);
//         if (v->num == 1) return pref;
//     }
//     return "-";
// }

void build() {
    Node* v = &root;
    std::queue<Node*> q;
    root.suff_link = &root;
    for (auto [c, to] : root.next) {
        to.suff_link = &root;
        q.push(&to);
    }
    while (!q.empty()) {
        auto c = q.front();
        q.pop();
        for (auto [c, to] : v->next) {
            auto jumper = v->suff_link;
            while (!jumper->next.count(c) && jumper != &root) jumper = jumper->suff_link;
            if (jumper->next.count(c)) to.suff_link = &jumper->next[c];
            else to.suff_link = &root;
        }
    }
}

int main() {
    std::string text;
    std::cin >> text;
    int64_t n = 0;
    std::cin >> n;
    for (int64_t i = 0; i < n; ++i) {
        std::string word;
        std::cin >> word;
        insert(word);
    }
    std::vector<int64_t> mask(n);
    build();
    //auto res = find(text);
    for (int64_t i = 0; i < text.size(); ++i) {
    }
    for (const int64_t i : mask) {
        std::cout << (i ? "Yes" : "No") << "\n";
    }
}
