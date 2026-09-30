// Another stuff with Treap with an Implicit key.

#include <iostream>
#include <vector>

using ll = long long;


class DualImplicitTreap {
private:
    struct TreapElement {
        ll value;
        ll sub_sum;
        int priority;
        int subtree_size;
        int left_child;
        int right_child;
    };

    std::vector<TreapElement> pool;
    int _odd_root;
    int _even_root;

    int createNode(ll val) {
        TreapElement node;
        node.value = val;
        node.sub_sum = val;
        node.priority = rand() ^ (rand() << 15);
        node.subtree_size = 1;
        node.left_child = 0;
        node.right_child = 0;

        pool.push_back(node);
        return pool.size() - 1;
    }

    void recalc(int v) {
        if (!v) return;
        pool[v].subtree_size = 1 + pool[pool[v].left_child].subtree_size + pool[pool[v].right_child].subtree_size;
        pool[v].sub_sum = pool[v].value + pool[pool[v].left_child].sub_sum + pool[pool[v].right_child].sub_sum;
    }

    void splt(int v, int k, int& l, int& r) {
        if (!v) {
            l = r = 0;
            return;
        }
        int left_sz = pool[pool[v].left_child].subtree_size;
        if (left_sz >= k) {
            splt(pool[v].left_child, k, l, pool[v].left_child);
            r = v;
        } else {
            splt(pool[v].right_child, k-left_sz-1, pool[v].right_child, r);
            l = v;
        }
        recalc(v);
    }

    void merge(int& v, int l, int r) {
        if (!l || !r) {
            v = l ? l : r;
            return;
        }
        if (pool[l].priority > pool[r].priority) {
            merge(pool[l].right_child, pool[l].right_child, r);
            v = l;
        } else {
            merge(pool[r].left_child, l, pool[r].left_child);
            v = r;
        }
        recalc(v);
    }

    ll getTreeSum(int& root_ref, int l, int r) {
        if (l > r) return 0;
        int L, mid, R;
        splt(root_ref, l-1, L, R);
        splt(R, r-l+1, mid, R);
        ll result = pool[mid].sub_sum;
        merge(R, mid, R);
        merge(root_ref, L, R);
        return result;
    }

public:
    DualImplicitTreap() {
        TreapElement dummy = {0, 0, 0, 0, 0, 0};
        pool.push_back(dummy);
        _odd_root = 0;
        _even_root = 0;
    }

    void fill_data(const std::vector<ll>& src) {
        for (size_t i = 1; i < src.size(); ++i) {
            int nv = createNode(src[i]);
            if (i % 2 != 0) {
                merge(_odd_root, _odd_root, nv);
            } else {
                merge(_even_root, _even_root, nv);
            }
        }
    }

    void swap_intervals(int x, int y) {
        int lo, ro, le, re;
        if (x % 2 != 0) {
            lo = (x+1) / 2; ro = y/2;
            le = (x+1) / 2; re = y/2;
        } else {
            le = x/2;   re = (y-1) / 2;
            lo = x/2 + 1;   ro = (y+1) / 2;
        }

        int O_L, O_mid, O_R;
        splt(_odd_root, lo-1, O_L, O_R);
        splt(O_R, ro-lo+1, O_mid, O_R);

        int E_L, E_mid, E_R;
        splt(_even_root, le-1, E_L, E_R);
        splt(E_R, re-le+1, E_mid, E_R);

        std::swap(O_mid, E_mid);

        merge(O_R, O_mid, O_R);
        merge(_odd_root, O_L, O_R);

        merge(E_R, E_mid, E_R);
        merge(_even_root, E_L, E_R);
    }

    ll query_sum(int x, int y) {
        int lo = x/2 + 1;
        int ro = (y+1) / 2;
        int le = (x+1) / 2;
        int re = y/2;

        return getTreeSum(_odd_root, lo, ro) + getTreeSum(_even_root, le, re);
    }
};

int main() {
    int n, m;
    int case_num = 1;

    while (std::cin >> n >> m && (n != 0 || m != 0)) {
        std::vector<ll> input_array(n+1);
        for (int i = 1; i <= n; ++i) {
            std::cin >> input_array[i];
        }

        DualImplicitTreap swapper;
        swapper.fill_data(input_array);
        std::cout << "Swapper " << case_num++ << ":\n";

        for (int i = 0; i < m; ++i) {
            int type, x, y;
            std::cin >> type >> x >> y;
            if (type == 1) {
                swapper.swap_intervals(x, y);
            } else {
                std::cout << swapper.query_sum(x, y) << "\n";
            }
        }
        std::cout << "\n";
    }

    return 0;
}
