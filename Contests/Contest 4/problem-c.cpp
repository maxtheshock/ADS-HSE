#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;

struct BankState {
    long long data[2][2];
    BankState() {
        data[0][0] = data[0][1] = data[1][0] = data[1][1] = -2e18;
    }
};

class VaultManager {
    int sz;
    std::vector<BankState> tree;
    BankState join(const BankState& left, const BankState& right) {
        BankState res;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    for (int l = 0; l < 2; ++l) {
                        if (k && l) { continue; }
                        ll val = left.data[i][k] + right.data[l][j];
                        if (val > res.data[i][j]) res.data[i][j] = val;
                    }
                }
            }
        }
        return res;
    }

    void fill(int idx, int L, int R, const std::vector<ll>& arr) {
        if (L == R) {
            tree[idx].data[0][0] = 0;
            tree[idx].data[1][1] = arr[L];
            return;
        }
        int mid = (L + R) >> 1;
        fill(idx << 1, L, mid, arr);
        fill((idx << 1) | 1, mid + 1, R, arr);
        tree[idx] = join(tree[idx << 1], tree[(idx << 1) | 1]);
    }

    void modify(int idx, int L, int R, int pos, ll val) {
        if (L == R) {
            tree[idx].data[1][1] = val;
            return;
        }
        int mid = (L + R) >> 1;
        if (pos <= mid) modify(idx << 1, L, mid, pos, val);
        else modify((idx << 1) | 1, mid + 1, R, pos, val);
        tree[idx] = join(tree[idx << 1], tree[(idx << 1) | 1]);
    }

public:
    VaultManager(const std::vector<ll>& arr) {
        sz = (int)arr.size() - 1;
        tree.resize(4*sz + 1);
        fill(1, 1, sz, arr);
    }

    void update(int pos, ll val) {
        modify(1, 1, sz, pos, val);
    }

    ll query() {
        ll best = 0;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                best = std::max(best, tree[1].data[i][j]);
        return best;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<ll> banks(n+1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> banks[i];
    }
    VaultManager vm(banks);
    std::cout << vm.query() << std::endl;
    while (m--) {
        int pos;
        ll val;
        std::cin >> pos >> val;
        vm.update(pos, val);
        std::cout << vm.query() << "\n";
    }

    return 0;
}
