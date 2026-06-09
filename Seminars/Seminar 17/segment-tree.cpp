#include <cstdint>
#include <iostream>
#include <vector>

class Tree {
    std::vector<int64_t> arr;
    std::vector<int64_t> tree;
    size_t sz = 1;
    void build(size_t v, size_t left, size_t right) {
        if (left + 1 == right) {
            tree[v] = left < arr.size() ? arr[left] : 0;
        } else {
            size_t mid = (left + right) / 2;
            build(2*v + 1, left, mid);
            build(2*v + 2, mid, right);
            tree[v] = tree[2*v+1] + tree[2*v+2];
        }
    }

    int64_t get(size_t v, size_t left, size_t right,
                size_t q_left, size_t q_right) {
        if (q_left <= left && right <= q_right) {
            return tree[v];
        }
        if (q_right <= left || right <= q_left) {
            return 0;
        }
        size_t mid = (left + right) / 2;
        return get(2*v + 1, left, right, q_left, q_right) +
            get(2*v + 2, left, right, q_left, q_right);
    }

public:
    explicit Tree(const std::vector<int64_t>& arr) : arr(arr) {
        while(sz < arr.size()) sz <<= 1;
        tree.resize(2*sz - 1);
        build(0, 0, sz);
    }

    int64_t get(size_t q_left, size_t q_right) {
        return get(0, 0, sz, q_left, q_right);
    }
};

int main() {
    std::vector<int64_t> a = {2, -1, 1, 0, -2, 1, 3};
    Tree t(a);
    std::cout << t.get(1, 5);
    return 0;
}
