#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

class StringSet {
private:
    static constexpr int TABLE_SIZE = 1 << 21;
    static constexpr int MASK = TABLE_SIZE - 1;
    std::vector<uint64_t> _keys;
    std::vector<uint8_t> _states;
    int getIndex(uint64_t key) const {
        key += 0x9e3779b97f4a7c15ULL;
        key = (key ^ (key >> 30))*0xbf58476d1ce4e5b9ULL;
        key = (key ^ (key >> 27))*0x94d049bb133111ebULL;
        key ^= key >> 31;
        return key & MASK;
    }
public:
    StringSet() : _keys(TABLE_SIZE), _states(TABLE_SIZE, 0) {}

    bool contains(uint64_t key) const {
        int index = getIndex(key);
        while (_states[index] != 0) {
            if (_states[index] == 1 && _keys[index] == key) { return true; }
            index = (index+1) & MASK;
        }
        return false;
    }

    void add(uint64_t key) {
        int index = getIndex(key);
        int deleted_index = -1;
        while (_states[index] != 0) {
            if (_states[index] == 1 && _keys[index] == key) { return; }
            if (_states[index] == 2 && deleted_index == -1) { deleted_index = index; }
            index = (index+1) & MASK;
        }
        if (deleted_index != -1) { index = deleted_index; }
        _keys[index] = key;
        _states[index] = 1;
    }

    void del(uint64_t key) {
        int index = getIndex(key);
        while (_states[index] != 0) {
            if (_states[index] == 1 && _keys[index] == key) {
                _states[index] = 2;
                return;
            }
            index = (index+1) & MASK;
        }
    }
};

uint64_t encode(const std::string& string) {
    uint64_t result = 0;

    for (char symbol : string) {
        result = result*27 + symbol-'a'+1;
    }
    return result;
}

int main() {
    StringSet set;
    char operation;

    while (std::cin >> operation && operation != '#') {
        std::string string;
        std::cin >> string;
        uint64_t key = encode(string);
        if (operation == '+') {
            set.add(key);
        } else if (operation == '-') {
            set.del(key);
        } else {
            std::cout << (set.contains(key) ? "YES" : "NO") << '\n';
        }
    }
    return 0;
}
