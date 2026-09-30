#include <iostream>
#include <map>

using ll = long long;

int main() {
    std::map<ll, int> frequency;
    ll x;
    std::cin >> x;

    while (x != 0) {
        frequency[x]++;
        std::cin >> x;
    }
    for (std::pair<const ll, int> element : frequency) {
        std::cout << element.first << " " << element.second << std::endl;
    }
    return 0;
}
