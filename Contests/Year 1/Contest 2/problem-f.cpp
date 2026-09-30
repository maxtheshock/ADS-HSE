#include <iostream>
#include <iomanip>

double eval_cubic(int a, int b, int c, int d, double x) {
    return a*x*x*x + b*x*x + c*x + d;
}

int main() {
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;

    double l = -2000.0, r = 2000.0;
    for (int i = 0; i < 100; ++i) {
        double m = (r+l) / 2.0;
        if ((eval_cubic(a,b,c,d,m) > 0) == (a > 0)) {
            r = m;
        } else {
            l = m;
        }
    }

    std::cout << std::fixed << std::setprecision(6) << l << std::endl;
}