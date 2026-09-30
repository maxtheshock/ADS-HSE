#include <iostream>
#include <vector>
#include <cstdio>

using ll = long long;

struct FenwickNode {
    ll const_val;
    ll lin_val;
};

struct Stage {
    int left_idx;
    int right_idx;
    ll start_amt;
    ll step_amt;
};

int num_jars, num_stages;
std::vector<FenwickNode> fenwick_tree;
std::vector<Stage> stages;
std::vector<ll> start_jam;
std::vector<ll> required_jam;
std::vector<int> final_results;

void modify_tree(int index, ll delta_c, ll delta_l) {
    while (index <= num_jars + 1) {
        fenwick_tree[index].const_val += delta_c;
        fenwick_tree[index].lin_val += delta_l;
        index += index & (-index);
    }
}

void toggle_stage(int stage_id, int multiplier) {
    const Stage& s = stages[stage_id];
    
    if (s.left_idx > s.right_idx) {
        return; 
    }

    ll c_part = (s.start_amt - 1LL * s.left_idx * s.step_amt) * multiplier;
    ll l_part = s.step_amt * multiplier;

    modify_tree(s.left_idx, c_part, l_part);
    modify_tree(s.right_idx + 1, -c_part, -l_part);
}

ll calculate_added(int jar_id) {
    ll c_total = 0;
    ll l_total = 0;
    int curr = jar_id;

    while (curr > 0) {
        c_total += fenwick_tree[curr].const_val;
        l_total += fenwick_tree[curr].lin_val;
        curr -= curr & (-curr);
    }

    return c_total + l_total * jar_id;
}

void divide_and_conquer(int search_left, int search_right, const std::vector<int>& active_queries) {
    if (active_queries.empty()) {
        return;
    }

    if (search_left == search_right) {
        for (int jar : active_queries) {
            final_results[jar] = search_left;
        }
        return;
    }

    int mid_point = search_left + (search_right - search_left) / 2;

    for (int i = search_left; i <= mid_point; ++i) {
        toggle_stage(i, 1);
    }

    std::vector<int> successful_jars;
    std::vector<int> pending_jars;

    for (int jar : active_queries) {
        if (calculate_added(jar) >= required_jam[jar] - start_jam[jar]) {
            successful_jars.push_back(jar);
        } else {
            pending_jars.push_back(jar);
        }
    }

    divide_and_conquer(mid_point + 1, search_right, pending_jars);

    for (int i = search_left; i <= mid_point; ++i) {
        toggle_stage(i, -1);
    }

    divide_and_conquer(search_left, mid_point, successful_jars);
}

int main() {

    std::freopen("input.txt", "r", stdin);
    std::freopen("output.txt", "w", stdout);

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    if (!(std::cin >> num_jars)) return 0;

    start_jam.resize(num_jars + 1);
    required_jam.resize(num_jars + 1);
    fenwick_tree.assign(num_jars + 2, {0, 0});
    final_results.assign(num_jars + 1, -1);

    for (int i = 1; i <= num_jars; ++i) std::cin >> start_jam[i];
    for (int i = 1; i <= num_jars; ++i) std::cin >> required_jam[i];

    std::cin >> num_stages;
    stages.resize(num_stages + 1);

    for (int i = 1; i <= num_stages; ++i) {
        std::cin >> stages[i].left_idx >> stages[i].right_idx >> stages[i].start_amt >> stages[i].step_amt;
    }

    std::vector<int> initial_queries;
    
    for (int i = 1; i <= num_jars; ++i) {
        if (start_jam[i] >= required_jam[i]) {
            final_results[i] = 0;
        } else {
            initial_queries.push_back(i);
        }
    }

    divide_and_conquer(1, num_stages + 1, initial_queries);

    for (int i = 1; i <= num_jars; ++i) {
        if (final_results[i] == 0) {
            std::cout << 0;
        } else if (final_results[i] > num_stages) {
            std::cout << -1;
        } else {
            std::cout << final_results[i];
        }

        if (i < num_jars) std::cout << " ";
    }
    
    std::cout << '\n';

    return 0;
}
