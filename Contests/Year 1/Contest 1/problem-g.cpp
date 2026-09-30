#include <stack>
#include <algorithm>
#include <stdexcept>

class MinQueue {
private:
    std::stack<std::pair<int, int>> s1;
    std::stack<std::pair<int, int>> s2;
    int get_min_of_stack(const std::stack<std::pair<int, int>>& s) const {
        if (s.empty()) {
            return 2e9;
        }
        return s.top().second;
    }

    void pour() {
        if (s2.empty()) {
            while (!s1.empty()) {
                int val = s1.top().first;
                s1.pop();
                int current_min = s2.empty() ? val : std::min(val, get_min_of_stack(s2));
                s2.push({val, current_min});
            }
        }
    }

public:
    void push(int val) {
        int current_min = s1.empty() ? val : std::min(val, get_min_of_stack(s1));
        s1.push({val, current_min});
    }

    void pop() {
        pour();
        if (!s2.empty()) {
            s2.pop();
        }
    }

    int front() {
        pour();
        return s2.top().first;
    }

    int get_min() const {
        return std::min(get_min_of_stack(s1), get_min_of_stack(s2));
    }
};