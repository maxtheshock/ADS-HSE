#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// It's frustrating, but we need to build our own string addition :'(
// Here is another Binary Search on Answer task (we create an array and trying to find something)
std::string add_strings(const std::string& num1, const std::string& num2) {
    std::string res = "";
    int i = num1.length() - 1;
    int j = num2.length() - 1;

    int memor = 0;

    while (i >= 0 || j >= 0 || memor != 0) {
        int sum = memor;
        if (i >= 0) {
            sum += num1[i] - '0';
            --i;
        }
        if (j >= 0) {
            sum += num2[j] - '0';
            --j;
        }
        memor = sum / 10;
        res.push_back((sum % 10) + '0');
    }
    std::reverse(res.begin(), res.end());
    return res;
}

bool compare_strings(const std::string& num1, const std::string& num2) {
    if (num1.length() != num2.length()) {
        return num1.length() < num2.length();
    }
    return num1 < num2;
}

bool binary_search_on_answer(const std::vector<std::string>& v, const std::string& req) {
    int l = 0, r = v.size() - 1;
    while (l <= r) {
        int m = (l+r) / 2;
        if (compare_strings(v[m], req)) {
            l = m + 1;
        }
        else if (compare_strings(req, v[m])) {
            r = m - 1;
        }
        else {
            return true;
        }
    }
    return false;
}


int main() {
    std::vector<std::string> fib;
    fib.push_back("1");
    fib.push_back("1");

    for (int i = 2; i < 100000; ++i) {
        std::string next = add_strings(fib[i-1], fib[i-2]);
        if (next.length() > 5000) { break; }
        fib.push_back(next);
    }
    fib.erase(fib.begin());


    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::string req;
        std::cin >> req;
        if (binary_search_on_answer(fib, req)) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
        }
    }

    return 0;
}