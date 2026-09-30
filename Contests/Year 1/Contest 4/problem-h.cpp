// Another good (because it's relatively simple) example of
// a situation when a Treap with an Implicit key kicks out all
// other data structures.

#include <iostream>
#include <random>

// The part of the setup is taken from Problem E
struct Node {
    int _l = 0, _r = 0;
    int _sz = 0;
    int _pr = 0;
    int val = 0;
    bool rev = false;
};

constexpr int MAX_NODES = 110005;
Node tree[MAX_NODES];
int node_cnt = 0;
int root = 0;

std::mt19937 rng(1337);

void push(int t) {
    if (t && tree[t].rev) {
        std::swap(tree[t]._l, tree[t]._r);
        if (tree[t]._l) {
            tree[tree[t]._l].rev ^= true;
        }
        if (tree[t]._r) {
            tree[tree[t]._r].rev ^= true;
        }
        tree[t].rev = false;
    }
}

void update(int t) {
    if (t) {
        tree[t]._sz = 1 + tree[tree[t]._l]._sz + tree[tree[t]._r]._sz;
    }
}

int buildNode(int val) {
    int id = ++node_cnt;
    tree[id].val = val;
    tree[id]._sz = 1;
    tree[id]._pr = rng();
    tree[id]._l = tree[id]._r = 0;
    tree[id].rev = false;
    return id;
}

void split(int t, int k, int& l, int& r) {
    if (!t) {
        l = r = 0;
        return;
    }
    push(t);
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
    push(l);
    push(r);
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

void reverseSegment(int l, int r) {
    int t1, t2, t3;
    split(root, r, t1, t3);
    split(t1, l-1, t1, t2);
    if (t2) {
        tree[t2].rev ^= true;
    }
    root = merge(merge(t1, t2), t3);
}

void printTree(int t) {
    if (!t) { return; }
    push(t);
    printTree(tree[t]._l);
    std::cout << tree[t].val << " ";
    printTree(tree[t]._r);
}


int main() {
    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        root = merge(root, buildNode(i));
    }
    for (int i = 0; i < m; ++i) {
        int l, r;
        std::cin >> l >> r;
        reverseSegment(l, r);
    }
    printTree(root);
    std::cout << std::endl;
    return 0;
}
