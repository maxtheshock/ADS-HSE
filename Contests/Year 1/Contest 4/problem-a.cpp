// To solve this task we used a simplified version of the SegmentTree data structure.
// This tree was based not on the sum of contiguous elements, but on the maximum value

#include <iostream>
#include <vector>


using ll = long long;

ll max(const ll& n1, const ll& n2) {
    return n1 >= n2 ? n1 : n2;
}


class SegmentTree {
    size_t sz;
    std::vector<ll> tree;

    void update(int l, int r, ll val, int index, int l_dyn, int r_dyn) {
        if (l >= r_dyn || r <= l_dyn) {
            return;
        }
        if (l <= l_dyn && r >= r_dyn) {
            if (val > tree[index]) { tree[index] = val; };
            return;
        }
        int mid = (l_dyn + r_dyn) / 2;
        update(l, r, val, 2*index + 1, l_dyn, mid);
        update(l, r, val, 2*index + 2, mid, r_dyn);
    }

    ll req(int i, int index, int l_dyn, int r_dyn) {
        if (abs(l_dyn - r_dyn) == 1) { return tree[index]; }
        int mid = (l_dyn + r_dyn) / 2;

        ll val = tree[index];
        if (i < mid) {
            val = max(val, req(i, 2*index + 1, l_dyn, mid));
        } else {
            val = max(val, req(i, 2*index + 2, mid, r_dyn));
        }
        return val;
    }

public:
    SegmentTree(int n) : sz(n) {
        sz = 1;
        while (sz < n) { sz *= 2; };
        tree.assign(2*sz, 0);
    }

    void update(int l, int r, ll val) {
        update(l, r, val, 0, 0, sz);
    }
    ll req(int i) {
        return req(i, 0, 0, sz);
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;

    SegmentTree tr(n);
    for (int j = 0; j < m; ++j) {
        int switcher;
        std::cin >> switcher;
        if (switcher == 1) {
            ll val;
            int l, r;
            std::cin >> l >> r >> val;
            tr.update(l, r, val);
        } else {
            int i;
            std::cin >> i;
            std::cout << tr.req(i) << std::endl;
        }
    }
    return 0;
}