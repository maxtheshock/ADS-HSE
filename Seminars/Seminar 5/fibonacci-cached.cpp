#include <iostream>
#include <vector>
#include <cstdint> // required for int64_t

std::vector<int64_t> cache(101);

int64_t fib(int n) {
    if (cache[n] != 0) return cache[n]; // if a cell is not empty, return its value
    if (n == 0 || n == 1) {
        return cache[n] = n;
    }
    return cache[n] = fib(n-1) + fib(n-2);  // branching prevented because f(n-1) is called
                                            //FIRST at every recursion step
}

int main() {
    std::cout << fib(31) << std::endl;
    return 0;
}