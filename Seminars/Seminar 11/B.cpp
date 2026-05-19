#include <iostream>
#include <deque>


int main() {

    int n = 0;
    std::cin >> n;
    std::deque<int> q;
    int cur_time = 0;

    while (n--) {
        int h = 0, m = 0, angry = 0;
        std::cin >> h >> m >> angry;
        int t = h*60 + m;

        while (!q.empty() && q.front() < t) {
            std::cout << q.front() / 60 << " " << q.front() % 60;
            q.pop_front();
        }
        if (q.empty()) {
            q.push_back(t + 20);
        } else if (q.size() <= angry) {
            q.push_back(q.back() + 20);
        } else {
            std::cout << h << " " << m << std::endl;
        }
    }

    while (!q.empty()) {
        std::cout << q.front() / 60 << " " << q.front() % 60 << std::endl;
        q.pop_front();
    }

    return 0;
}