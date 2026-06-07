#include <iostream>
#include <vector>
#include <set>

using ll = long long;

int main() {
    int N, M, P;
    std::cin >> N >> M >> P;

    std::vector<std::vector<ll>> coming(P+1);
    std::vector<std::vector<ll>> leaving(P+1);

    ll total_satisfaction = 0;

    for (int i = 0; i < N; ++i) {
        ll a, b;
        int c, d;
        std::cin >> a >> b >> c >> d;
        ll diff = a - b;

        total_satisfaction += b * (d - c);

        if (diff > 0) {
            coming[c].push_back(diff);
            leaving[d].push_back(diff);
        }
    }

    // no places
    if (M == 0) {
        std::cout << total_satisfaction << std::endl;
        return 0;
    }

    // for top-M entries
    std::multiset<ll> top_m;
    std::multiset<ll> others;
    ll current_top_sum = 0;

    for (int i = 1; i < P; ++i) {

        for (ll val : leaving[i]) {
            auto it_top = top_m.find(val);
            if (it_top != top_m.end()) {
                top_m.erase(it_top);
                current_top_sum -= val;
                if (!others.empty()) {
                    auto max_other = prev(others.end());
                    top_m.insert(*max_other);
                    current_top_sum += *max_other;
                    others.erase(max_other);
                }
            } else {
                others.erase(others.find(val));
            }
        }

        for (ll val : coming[i]) {
            top_m.insert(val);
            current_top_sum += val;
            
            if (top_m.size() > M) {
                auto min_top = top_m.begin();
                others.insert(*min_top);
                current_top_sum -= *min_top;
                top_m.erase(min_top);
            }
        }

        total_satisfaction += current_top_sum;
    }

    std::cout << total_satisfaction << std::endl;
    return 0;
}
