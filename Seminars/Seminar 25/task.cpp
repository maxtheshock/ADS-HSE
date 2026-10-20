#include <iostream>
#include <map>

int global_count = 0;

struct Node {
    std::map<char, Node> next;
    int count = 0;
} root;

Node* u = &root;

void insert(const std::string_view s) {
    Node* v = &root;
    ++v->count;
    for (const char c : s) {
        v = &v->next[c];
        if (v->next.size())
        ++v->count;
    }
}

bool find(const std::string_view s) {
    Node* v = &root;
    for (const char c : s) {
        if (!v->next.contains(c)) return 0;
        v = &v->next[c];
    }
    return 1;
}


int main() {
    int n;
    std::string s;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::cin >> s;
        if (find(s) == 0) {
            insert(s);
        }
    }

    std::cout << root.count << std::endl;
    return 0;
}
