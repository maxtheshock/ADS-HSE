// This task gives us opportunity to implement and try the Fenwick tree
// data structure in action. Works together with a sweeping line here.

#include <iostream>
#include <vector>


class FenwickTree {
private:
    std::vector<int> tree;
    int _size;

    void _add(int index, int ch) {
        for (; index <= _size; index += index & -index) tree[index] += ch;
    }
    int _req(int index) const {
        int sum = 0;
        for (; index > 0; index -= index & -index) sum += tree[index];
        return sum;
    }

public:
    FenwickTree(int n) : _size(n) { tree.assign(n+1, 0); }
    void add(int pos, int val) {
        if (pos >= 1 && pos <= _size) {
            _add(pos, val);
        }
    }
    int req(int pos) const {
        if (pos < 1) { return 0; }
        if (pos > _size) { return _req(_size); }
        return _req(pos);
    }
    int req(int l, int r) const {
        if (l > r) { return 0; }
        return req(r) - req(l-1);
    }
};


class doSweepLine {
private:
    struct Event {
        int _req_id, _sgn, _k, _l, _next;
    };

    static constexpr int MAX_N = 100005;
    static constexpr int MAX_M = 100005;
    static constexpr int MAX_EVENTS = 200005;

    int A[MAX_N];
    int head[MAX_N];
    Event events[MAX_EVENTS];
    int ans_array[MAX_M];
    int event_cnt;
    int n, m;

    void add_event(int p, int req_id, int sgn, int k, int l) {
        if (p < 0) return;
        ++event_cnt;
        events[event_cnt] = {req_id, sgn, k, l, head[p]};
        head[p] = event_cnt;
    }

public:
    doSweepLine() : event_cnt(0) {
        for (int i = 0; i < MAX_N; ++i) { head[i] = 0; }
        for (int i = 0; i < MAX_M; ++i) { ans_array[i] = 0; }
    }

    void taskSetup() {
        std::cin >> n >> m;
        for (int i = 1; i <= n; ++i) {
            std::cin >> A[i];
        }
        for (int j = 0; j < m; ++j) {
            int x, y, k, l;
            std::cin >> x >> y >> k >> l;
            add_event(y, j, 1, k, l);
            add_event(x-1, j, -1, k, l);
        }
    }

    void solve() {
        FenwickTree tree(MAX_N);
        for (int p = 0; p <= n; ++p) {
            if (p > 0) {
                tree.add(A[p], 1);
            }
            for (int e = head[p]; e != 0; e = events[e]._next) {
                int count = tree.req(events[e]._k, events[e]._l);
                ans_array[events[e]._req_id] += events[e]._sgn * count;
            }
        }
    }

    void print() {
        for (int j = 0; j < m; ++j) {
            std::cout << ans_array[j] << std::endl;
        }
    }
};

int main() {
    doSweepLine solver;
    solver.taskSetup();
    solver.solve();
    solver.print();
    return 0;
}
