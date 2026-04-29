#include <iostream>
#include <functional>
#include <iomanip>

int main() {
    double a = .0, b = .0, c = .0, d = .0;
    // if we write double a = 0
    //                        ^
    //                        |   there's an implicit CAST(!)
    //
    std::cin >> a >> b >> c >> d;
    std::function<double(double)> f = [&](double x) -> double {
        return a * x * x * x + b * x * x + c * x + d;
    };

    double left = 1e-6, right = 1e6;
    for (int i = 0; i < 100; ++i) {
        double mid = (left + right) / 2.0;
        if (f(left) * f(mid) < 0) {
            left = mid;
        } else {
            right = mid;
        }
    }

    std::cout << std::setprecision(10) << std::fixed;
    std::cout << left;

    return 0;
}