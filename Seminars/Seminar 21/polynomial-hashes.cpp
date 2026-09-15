#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

int main() {
    std::string p = "aba";
    std::string s = "\0abacaba";
    size_t n = s.size();

    int64_t mod = 1e9 + 9;
    int64_t base = 257;
    
    std::vector<int64_t> k(n);
    std::vector<int64_t> pref(n);
    int64_t h_p = 0;
    
    // Pattern's hash (right down from here)
    for (size_t i = 0; i < p.size(); ++i) {
        h_p = (h_p * base + p[i]) % mod;
    }
    k[0] = 1;
    for (size_t i = 1; i < n; ++i) {
        k[i] = k[i-1] * base % mod;
        pref[i] = (pref[i-1]*base + s[i]) % mod;
    }

    int64_t len = p.size();
    for (size_t i = 0; i < n-len+1; ++i) {
        int64_t h_sbs = pref[i+len] - pref[i] * k[len] % mod;
        h_sbs = (h_sbs % mod + mod) % mod;
        if (h_p == h_sbs) {
            std::cout << i << ' ';
        }
    }
}
