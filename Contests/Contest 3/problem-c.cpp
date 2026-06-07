// As I understand, we're about to use Dynamic Segment tree here. BUT
// Why didn't we discuss in our course... I do not know... What the hell???

#include <iostream>
#include <vector>
#include <algorithm>

struct Node {
    long long max_free;
    long long pref;
    long long suff;
    int l;
    int r;
    int lazy;
};

std::vector<Node> tree;

int create_node(long long len) {
    tree.push_back({len, len, len, -1, -1, -1});
    return tree.size() - 1;
}

void push(int v, long long tl, long long tr) {
    if (tree[v].lazy != -1) {
        long long tm = tl + (tr - tl) / 2;
        
        if (tree[v].l == -1) tree[v].l = create_node(tm - tl + 1);
        if (tree[v].r == -1) tree[v].r = create_node(tr - tm);

        int l = tree[v].l;
        int r = tree[v].r;
        int val = tree[v].lazy;

        tree[l].lazy = val;
        tree[r].lazy = val;

        if (val == 1) {
            tree[l].max_free = tree[l].pref = tree[l].suff = 0;
            tree[r].max_free = tree[r].pref = tree[r].suff = 0;
        } else {
            tree[l].max_free = tree[l].pref = tree[l].suff = tm - tl + 1;
            tree[r].max_free = tree[r].pref = tree[r].suff = tr - tm;
        }
        tree[v].lazy = -1;
    }
}

void update(int v, long long tl, long long tr, long long ql, long long qr, int val) {
    if (ql > qr) return;
    
    if (ql == tl && qr == tr) {
        tree[v].lazy = val;
        if (val == 1) {
            tree[v].max_free = tree[v].pref = tree[v].suff = 0;
        } else {
            tree[v].max_free = tree[v].pref = tree[v].suff = tr - tl + 1;
        }
        return;
    }
    
    push(v, tl, tr);
    
    long long tm = tl + (tr - tl) / 2;
    if (tree[v].l == -1) tree[v].l = create_node(tm - tl + 1);
    if (tree[v].r == -1) tree[v].r = create_node(tr - tm);

    update(tree[v].l, tl, tm, ql, std::min(qr, tm), val);
    update(tree[v].r, tm + 1, tr, std::max(ql, tm + 1LL), qr, val);

    int l = tree[v].l;
    int r = tree[v].r;
    long long len_l = tm - tl + 1;
    long long len_r = tr - tm;

    tree[v].pref = tree[l].pref;
    if (tree[l].pref == len_l) tree[v].pref += tree[r].pref;

    tree[v].suff = tree[r].suff;
    if (tree[r].suff == len_r) tree[v].suff += tree[l].suff;

    tree[v].max_free = std::max({tree[l].max_free, tree[r].max_free, tree[l].suff + tree[r].pref});
}

long long find_leftmost(int v, long long tl, long long tr, long long K) {
    if (tree[v].max_free < K) return -1;
    if (tl == tr) return tl;
    
    push(v, tl, tr);
    
    long long tm = tl + (tr - tl) / 2;
    if (tree[v].l == -1) tree[v].l = create_node(tm - tl + 1);
    if (tree[v].r == -1) tree[v].r = create_node(tr - tm);

    if (tree[tree[v].l].max_free >= K) {
        return find_leftmost(tree[v].l, tl, tm, K);
    }
    if (tree[tree[v].l].suff + tree[tree[v].r].pref >= K) {
        return tm - tree[tree[v].l].suff + 1;
    }
    return find_leftmost(tree[v].r, tm + 1, tr, K);
}

struct Query {
    long long start;
    long long length;
};

int main() {
    long long N;
    int M;
    std::cin >> N >> M;

    tree.reserve(10000000); 
    create_node(N);

    std::vector<Query> history(M + 1, {-1, 0});

    for (int i = 1; i <= M; ++i) {
        int req;
        std::cin >> req;
        
        if (req > 0) {
            long long K = req;
            long long start = find_leftmost(0, 1, N, K);
            
            if (start != -1) {
                update(0, 1, N, start, start + K - 1, 1);
                history[i] = {start, K};
                std::cout << start << std::endl;
            } else {
                std::cout << -1 << std::endl;
            }
        } else {
            int T = -req;
            if (history[T].start != -1) {
                update(0, 1, N, history[T].start, history[T].start + history[T].length - 1, 0);
                history[T].start = -1;
            }
        }
    }

    return 0;
}
