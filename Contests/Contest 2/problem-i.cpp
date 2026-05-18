#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

struct TrafficLight {
    long double a;
    long double b;
    long double p;
};

bool check(long double v, long double T, long double D, const std::vector<TrafficLight>& lights) {
    long double time = 0.0L;
    long double pos = 0.0L;

    const long double EPS = 1e-12L;

    for (const TrafficLight& light : lights) {
        if (light.p >= D) {
            break;
        }

        time += (light.p - pos) / v;
        pos = light.p;

        if (time > T + EPS) {
            return false;
        }

        long double cycle = light.a + light.b;
        long double mod = std::fmod(time, cycle);

        if (mod < 0.0L) {
            mod += cycle;
        }

        if (mod < light.a) {
            time += light.a - mod;
        }

        if (time > T + EPS) {
            return false;
        }
    }

    time += (D - pos) / v;

    return time <= T + EPS;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long double T;
    long double D;
    int N;

    std::cin >> T >> D >> N;

    std::vector<TrafficLight> lights(N);

    for (int i = 0; i < N; i++) {
        std::cin >> lights[i].a >> lights[i].b >> lights[i].p;
    }

    std::sort(lights.begin(), lights.end(), [](const TrafficLight& x, const TrafficLight& y) {
        return x.p < y.p;
    });

    long double left = 0.0L;
    long double right = D;

    if (!check(right, T, D, lights)) {
        std::cout << "-1.0" << std::endl;
        return 0;
    }

    for (int i = 0; i < 150; i++) {
        long double mid = (left + right) / 2.0L;

        if (check(mid, T, D, lights)) {
            right = mid;
        } else {
            left = mid;
        }
    }

    std::cout << std::fixed << std::setprecision(12) << right << std::endl;

    return 0;
}
