// On the one hand, if we try to solve this task with std::vector, we will end up with O(n)
// while inserting/removing elements. On the other hand, a solution based on std::list will
// give us possibility to alter elements in O(1) but the access will rocket to O(n) again.

// This is the task when we need to use a data structure with both options for just O(log n).
// This is: A Treap with an Implicit Key (or, a Cartesian tree with an Implicit Key)

#include <iostream>
#include <random>
#include <algorithm>
#include <string>

using ll = long long;

struct Node {
    int _l = 0, _r = 0;
    int _sz = 0;
    int _pr = 0;
    ll val = 0;
};

constexpr int MAX_NODES = 350005;
Node tree[MAX_NODES];
int node_cnt = 0;
int root = 0;

__int128 current_ans = 0;

std::mt19937 rng(1337);

void print128(__int128 n) {
    if (n == 0) {
        std::cout << 0 << std::endl;
        return;
    }
    std::string s;
    while (n > 0) {
        s += (char)('0' + (n % 10));
        n /= 10;
    }
    std::reverse(s.begin(), s.end());
    std::cout << s << std::endl;
}

void update(int t) {
    if (t) {
        tree[t]._sz = 1 + tree[tree[t]._l]._sz + tree[tree[t]._r]._sz;
    }
}


int buildNode(ll val) {
    int id = ++node_cnt;
    tree[id].val = val;
    tree[id]._sz = 1;
    tree[id]._pr = rng();
    tree[id]._l = tree[id]._r = 0;
    return id;
}

void split(int t, int k, int& l, int& r) {
    if (!t) {
        l = r = 0;
        return;
    }
    int left_sz = tree[tree[t]._l]._sz;
    if (left_sz >= k) {
        r = t;
        split(tree[t]._l, k, l, tree[t]._l);
        update(r);
    } else {
        l = t;
        split(tree[t]._r, k - left_sz - 1, tree[t]._r, r);
        update(l);
    }
}

int merge(int l, int r) {
    if (!l || !r) return (l ? l : r);
    if (tree[l]._pr > tree[r]._pr) {
        tree[l]._r = merge(tree[l]._r, r);
        update(l);
        return l;
    } else {
        tree[r]._l = merge(l, tree[r]._l);
        update(r);
        return r;
    }
}

ll getVal_n_Delete(int v) {
    int t1, t2, t3;
    split(root, v, t1, t3);
    split(t1, v - 1, t1, t2);
    ll val = tree[t2].val;
    root = merge(t1, t3);
    return val;
}

void insert(int v, ll val) {
    int t1, t2;
    split(root, v - 1, t1, t2);
    int new_node = buildNode(val);
    root = merge(t1, merge(new_node, t2));
}

void addToIndex(int v, ll delta) {
    int t1, t2, t3;
    split(root, v, t1, t3);
    split(t1, v - 1, t1, t2);
    current_ans -= (__int128)tree[t2].val * tree[t2].val;
    tree[t2].val += delta;
    current_ans += (__int128)tree[t2].val * tree[t2].val;
    root = merge(merge(t1, t2), t3);
}


int main() {
    int n, p;
    std::cin >> n >> p;

    for (int i = 0; i < n; ++i) {
        ll a;
        std::cin >> a;
        current_ans += (__int128)a * a;
        root = merge(root, buildNode(a));
    }
    print128(current_ans);

    int k;
    std::cin >> k;
    for (int j = 0; j < k; ++j) {
        int type, v;
        std::cin >> type >> v;
        int total_sz = tree[root]._sz;
        if (type == 2) {
            ll L = getVal_n_Delete(v);
            current_ans -= (__int128)L * L;
            ll L1 = L / 2;
            ll L2 = L - L1;
            current_ans += (__int128)L1 * L1 + (__int128)L2 * L2;
            insert(v, L2);
            insert(v, L1);
        } else if (type == 1) {

            ll L = getVal_n_Delete(v);
            current_ans -= (__int128)L * L;
            if (v == 1) {
                addToIndex(1, L);
            } else if (v == total_sz) {
                addToIndex(v - 1, L);
            } else {
                ll L1 = L / 2;
                ll L2 = L - L1;
                addToIndex(v - 1, L1);
                addToIndex(v, L2);
            }
        }
        print128(current_ans);
    }
    return 0;
}
