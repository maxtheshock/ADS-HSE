#include <iostream>
#include <vector>

unsigned int cur = 0;
unsigned int a, b;

unsigned int nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}

unsigned int nextRand32() {
    unsigned int a = nextRand24();
    unsigned int b = nextRand24();
    return (a << 8) ^ b;
}

// Quickselect algorithm (Finding k-th ordered entry after sorting)
unsigned int quickselect(std::vector<unsigned int>& arr, int left, int right, int target_idx) {
    if (left == right) {
        return arr[left];
    }

    unsigned int pivot = arr[(right + left) / 2];
    
    int i = left;
    int j = right;

    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    if (target_idx <= j) {
        return quickselect(arr, left, j, target_idx);
    } else if (target_idx >= i) {
        return quickselect(arr, i, right, target_idx);
    }
    return arr[target_idx];
}

int main() {
    unsigned int n, q;
    std::cin >> n >> q;
    std::cin >> a >> b;

    std::vector<unsigned int> x;
    for (int i = 0; i < n; ++i) {
        x.push_back(nextRand32());
    }

    auto final = quickselect(x, 0, n-1, q-1);
    std::cout << final << std::endl;
    return 0;
}