// One more task for using SegmentTree to solve a non-trivial task

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using ll = long long;

struct Segment {
    double best_avg;
    ll p1, p2, s1, s2;
    int len;
};


class SegmTree {
private:
    int _size;
    std::vector<double> best_avg;
    std::vector<ll> p1, p2, s1, s2, lazy;

    Segment _join(const Segment& A, const Segment& B) {
        if (A.len == 0) { return B; }
        if (B.len == 0) { return A; }
        
        Segment cur;
        cur.len = A.len + B.len;
        cur.p1 = A.p1;
        cur.p2 = (A.len > 1) ? A.p2 : B.p1;
        cur.s1 = B.s1;
        cur.s2 = (B.len > 1) ? B.s2 : A.s1;
        
        cur.best_avg = std::max(A.best_avg, B.best_avg);
        
        double pair_avg = (A.s1 + B.p1) / 2.0;
        cur.best_avg = std::max(cur.best_avg, pair_avg);
        if (A.len >= 2) {
            double triple_l = (A.s2 + A.s1 + B.p1) / 3.0;
            cur.best_avg = std::max(cur.best_avg, triple_l);
        }
        if (B.len >= 2) {
            double triple_r = (A.s1 + B.p1 + B.p2) / 3.0;
            cur.best_avg = std::max(cur.best_avg, triple_r);
        }

        return cur;
    }

    void _push(int v) {
        if (lazy[v] != 0) {
            ll add = lazy[v];

            lazy[2*v] += add;
            best_avg[2*v] += add;
            p1[2*v] += add; p2[2*v] += add; s1[2*v] += add; s2[2*v] += add;

            lazy[2*v+1] += add;
            best_avg[2*v+1] += add;
            p1[2*v+1] += add; p2[2*v+1] += add; s1[2*v+1] += add; s2[2*v+1] += add;

            lazy[v] = 0;
        }
    }

    void _build(int v, int tl, int tr, const std::vector<ll>& src) {
        if (tl == tr) {
            best_avg[v] = -1e18; 
            p1[v] = s1[v] = src[tl];
            p2[v] = s2[v] = 0;
            return;
        }
        int tm = (tl + tr) / 2;
        _build(2*v, tl, tm, src);
        _build(2*v+1, tm+1, tr, src);
        
        Segment L = {best_avg[2*v], p1[2*v], p2[2*v], s1[2*v], s2[2*v], tm-tl+1};
        Segment R = {best_avg[2*v+1], p1[2*v+1], p2[2*v+1], s1[2*v+1], s2[2*v+1], tr-tm};
        Segment res = _join(L, R);

        best_avg[v] = res.best_avg;
        p1[v] = res.p1; p2[v] = res.p2;
        s1[v] = res.s1; s2[v] = res.s2;
    }

    void _update(int v, int tl, int tr, int l, int r, ll delta) {
        if (l > r) return;
        if (l == tl && r == tr) {
            lazy[v] += delta;
            best_avg[v] += delta;
            p1[v] += delta; p2[v] += delta; s1[v] += delta; s2[v] += delta;
            return;
        }
        _push(v);
        int tm = (tl+tr) / 2;
        _update(2*v, tl, tm, l, std::min(r, tm), delta);
        _update(2*v + 1, tm+1, tr, std::max(l, tm+1), r, delta);
        
        Segment L = {best_avg[2*v], p1[2*v], p2[2*v], s1[2*v], s2[2*v], tm-tl+1};
        Segment R = {best_avg[2*v+1], p1[2*v+1], p2[2*v+1], s1[2*v+1], s2[2*v+1], tr-tm};
        Segment res = _join(L, R);

        best_avg[v] = res.best_avg;
        p1[v] = res.p1; p2[v] = res.p2;
        s1[v] = res.s1; s2[v] = res.s2;
    }

    Segment _req(int v, int tl, int tr, int l, int r) {
        if (l > r) return {-1e18, 0, 0, 0, 0, 0};
        if (l == tl && r == tr) {
            return {best_avg[v], p1[v], p2[v], s1[v], s2[v], tr - tl + 1};
        }
        _push(v);
        int tm = (tl + tr) / 2;
        Segment L = _req(2*v, tl, tm, l, std::min(r, tm));
        Segment R = _req(2*v+1, tm+1, tr, std::max(l, tm+1), r);
        return _join(L, R);
    }

public:
    SegmTree(int n) : _size(n) {
        int nodes = 4*n + 5;
        best_avg.assign(nodes, -1e18);
        p1.assign(nodes, 0); p2.assign(nodes, 0);
        s1.assign(nodes, 0); s2.assign(nodes, 0);
        lazy.assign(nodes, 0);
    }

    void build(const std::vector<ll>& src) {
        _build(1, 1, _size, src);
    }
    void update(int l, int r, ll delta) {
        _update(1, 1, _size, l, r, delta);
    }
    double req(int l, int r) {
        return _req(1, 1, _size, l, r).best_avg;
    }
};

class Solver {
private:
    int n, q;
    std::vector<ll> base_array;

public:
    void run() {
        std::cin >> n >> q;
        base_array.resize(n+1);
        for (int i = 1; i <= n; ++i) {
            std::cin >> base_array[i];
        }

        SegmTree tree(n);
        tree.build(base_array);
        std::cout << std::fixed << std::setprecision(6);
        
        for (int i = 0; i < q; ++i) {
            int type, l, r;
            std::cin >> type >> l >> r;
            if (type == 1) {
                ll x;
                std::cin >> x;
                tree.update(l, r, x);
            } else {
                std::cout << tree.req(l, r) << std::endl;
            }
        }
    }
};

int main() {
    Solver runner;
    runner.run();
    return 0;
}
