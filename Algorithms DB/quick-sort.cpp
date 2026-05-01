#include <iostream>
#include <vector>
#include <algorithm> // for std::swap

template<class T>
int pivot_index(std::vector<T>& a, int low, int high) {
    int pivot = a[high];
    int i = (low - 1); // indexes 1 position BEFORE subarray
    for (int j = low; j <= high - 1; ++j) {
        if (a[j] <= pivot) {
            ++i;
            std::swap(a[i], a[j]);
        }
    }
    std::swap(a[i+1], a[high]);
    return (i+1);
}

template<class T>
void quickSort(std::vector<T>& a, int low, int high) {
    if (low < high) {
        int pi = pivot_index(a, low, high);
        quickSort(a, low, pi-1);
        quickSort(a, pi+1, high);
    }
}

int main() {
    std::vector<int> a = {1,49,4,36,81,9,16,25,100,-1,55,90,97,-100,-12};
    quickSort(a, 0, a.size() - 1);
    for (auto item : a) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}
