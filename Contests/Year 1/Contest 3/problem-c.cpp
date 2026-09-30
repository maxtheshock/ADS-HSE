// As I understand, we're about to use Dynamic Segment tree here. BUT
// Why didn't we discuss in our course... I do not know... What the hell???

#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;

struct Node {
    ll max_free;
    ll pref;
    ll suff;
    int left;
    int right;
    int lazy;
};

std::vector<Node> tree;

int create_node(ll len) {
    tree.push_back({len, len, len, -1, -1, -1});
    return static_cast<int>(tree.size()) - 1;
}

void apply(int v, ll len, int val) {
    tree[v].lazy = val;

    if (val == 1) {
        tree[v].max_free = 0;
        tree[v].pref = 0;
        tree[v].suff = 0;
    } else {
        tree[v].max_free = len;
        tree[v].pref = len;
        tree[v].suff = len;
    }
}

void ensure_children(int v, ll tl, ll tr) {
    if (tl == tr) {
        return;
    }

    ll tm = tl + (tr - tl) / 2;

    if (tree[v].left == -1) {
        tree[v].left = create_node(tm - tl + 1);
    }

    if (tree[v].right == -1) {
        tree[v].right = create_node(tr - tm);
    }
}

void push(int v, ll tl, ll tr) {
    if (tree[v].lazy == -1 || tl == tr) {
        return;
    }

    ensure_children(v, tl, tr);

    ll tm = tl + (tr - tl) / 2;

    int left = tree[v].left;
    int right = tree[v].right;
    int val = tree[v].lazy;

    apply(left, tm - tl + 1, val);
    apply(right, tr - tm, val);

    tree[v].lazy = -1;
}

void pull(int v, ll tl, ll tr) {
    ll tm = tl + (tr - tl) / 2;

    int left = tree[v].left;
    int right = tree[v].right;

    ll len_left = tm - tl + 1;
    ll len_right = tr - tm;

    tree[v].pref = tree[left].pref;
    if (tree[left].pref == len_left) {
        tree[v].pref += tree[right].pref;
    }

    tree[v].suff = tree[right].suff;
    if (tree[right].suff == len_right) {
        tree[v].suff += tree[left].suff;
    }

    tree[v].max_free = std::max({
        tree[left].max_free,
        tree[right].max_free,
        tree[left].suff + tree[right].pref
    });
}

void update(int v, ll tl, ll tr, ll ql, ll qr, int val) {
    if (ql > qr) {
        return;
    }

    if (ql == tl && qr == tr) {
        apply(v, tr - tl + 1, val);
        return;
    }

    push(v, tl, tr);
    ensure_children(v, tl, tr);

    ll tm = tl + (tr - tl) / 2;

    update(tree[v].left, tl, tm, ql, std::min(qr, tm), val);
    update(tree[v].right, tm + 1, tr, std::max(ql, tm + 1), qr, val);

    pull(v, tl, tr);
}

ll find_leftmost(int v, ll tl, ll tr, ll k) {
    if (tree[v].max_free < k) {
        return -1;
    }

    if (tl == tr) {
        return tl;
    }

    push(v, tl, tr);
    ensure_children(v, tl, tr);

    ll tm = tl + (tr - tl) / 2;

    int left = tree[v].left;
    int right = tree[v].right;

    if (tree[left].max_free >= k) {
        return find_leftmost(left, tl, tm, k);
    }

    if (tree[left].suff + tree[right].pref >= k) {
        return tm - tree[left].suff + 1;
    }

    return find_leftmost(right, tm + 1, tr, k);
}

struct Query {
    ll start = -1;
    ll length = 0;
};

int main() {
    ll N;
    int M;

    std::cin >> N >> M;

    tree.reserve(7000000);
    create_node(N);

    std::vector<Query> history(M + 1);

    for (int i = 1; i <= M; ++i) {
        ll req;
        std::cin >> req;

        if (req > 0) {
            ll k = req;
            ll start = find_leftmost(0, 1, N, k);

            if (start == -1) {
                std::cout << -1 << std::endl;
            } else {
                update(0, 1, N, start, start + k - 1, 1);

                history[i].start = start;
                history[i].length = k;

                std::cout << start << std::endl;
            }
        } else {
            int t = static_cast<int>(-req);

            if (history[t].start != -1) {
                ll left = history[t].start;
                ll right = history[t].start + history[t].length - 1;

                update(0, 1, N, left, right, 0);

                history[t].start = -1;
                history[t].length = 0;
            }
        }
    }

    return 0;
}
