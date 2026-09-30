#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <list>

class HashTable {
private:
    static constexpr int64_t P = 1000000007;
    static constexpr int64_t X = 263;
    int _m;
    std::vector<std::list<std::string>> _table;
    int getHash(const std::string& string) const {
        int64_t hash = 0;
        int64_t power = 1;
        for (char symbol : string) {
            hash = (hash + static_cast<int64_t>(symbol)*power) % P;
            power = (power*X) % P;
        }
        return hash % _m;
    }

public:
    HashTable(int m) : _m(m), _table(m) {}
    void add(const std::string& string) {
        int index = getHash(string);
        for (const std::string& current : _table[index]) {
            if (current == string) { return; }
        }
        _table[index].push_front(string);
    }

    void del(const std::string& string) {
        int index = getHash(string);
        for (auto it = _table[index].begin(); it != _table[index].end(); ++it) {
            if (*it == string) {
                _table[index].erase(it);
                return;
            }
        }
    }

    bool find(const std::string& string) const {
        int index = getHash(string);
        for (const std::string& current : _table[index]) {
            if (current == string) { return true; }
        }
        return false;
    }

    void check(int index) const {
        bool first = true;
        for (const std::string& string : _table[index]) {
            if (!first) { std::cout << ' '; }
            std::cout << string;
            first = false;
        }
        std::cout << '\n';
    }
};

int main() {
    int m, n;
    std::cin >> m >> n;
    HashTable table(m);

    for (int i = 0; i < n; ++i) {
        std::string operation;
        std::cin >> operation;
        if (operation == "check") {
            int index;
            std::cin >> index;
            table.check(index);
        } else {
            std::string string;
            std::cin >> string;
            if (operation == "add") {
                table.add(string);
            } else if (operation == "del") {
                table.del(string);
            } else {
                std::cout << (table.find(string) ? "yes" : "no") << '\n';
            }
        }
    }
    return 0;
}
