#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int main() {

    int n;
    std::cin >> n;

    std::vector<long long> x(n), y(n);
    long long min_u = 4e18, max_u = -4e18;
    long long min_v = 4e18, max_v = -4e18;

    for (int i = 0; i < n; ++i) {
        std::cin >> x[i] >> y[i];
        long long u = x[i] + y[i];
        long long v = x[i] - y[i];
        min_u = std::min(min_u, u);
        max_u = std::max(max_u, u);
        min_v = std::min(min_v, v);
        max_v = std::max(max_v, v);
    }

    long long mid_u = (min_u + max_u) / 2;
    long long mid_v = (min_v + max_v) / 2;

    long long best_x = 0;
    long long best_y = 0;
    long long min_max_dist = 4e18;

    for (long long u_cand = mid_u - 2; u_cand <= mid_u + 2; ++u_cand) {
        for (long long v_cand = mid_v - 2; v_cand <= mid_v + 2; ++v_cand) {
            if ((u_cand + v_cand) % 2 != 0) {
                continue;
            }

            long long cx = (u_cand + v_cand) / 2;
            long long cy = (u_cand - v_cand) / 2;

            long long current_max = 0;
            current_max = std::max(current_max, std::abs(min_u - u_cand));
            current_max = std::max(current_max, std::abs(max_u - u_cand));
            current_max = std::max(current_max, std::abs(min_v - v_cand));
            current_max = std::max(current_max, std::abs(max_v - v_cand));

            if (current_max < min_max_dist) {
                min_max_dist = current_max;
                best_x = cx;
                best_y = cy;
            }
        }
    }

    std::cout << best_x << " " << best_y << std::endl;
    return 0;
}
