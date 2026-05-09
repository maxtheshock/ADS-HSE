#include <iostream>
#include <vector>

template<class T>
std::vector<T> countingSort(const std::vector<T>& vec) {
    // Step 1: Determine the range of the array (find MAX)
    T max_el = 0;           // we also call it K sometimes
    size_t n = vec.size();
    for (int i = 0; i < n; ++i) {
        if (vec[i] > max_el) { max_el = vec[i]; }
    }
    // Step 2: Create an auxiliary array
    std::vector<T> aux(max_el + 1, 0);
    for (int i = 0; i < n; ++i) {
        aux[vec[i]]++;
    }
    // Step 3: Compute prefix sum
    for (int i = 0; i < max_el; ++i) {
        aux[i+1] += aux[i];
    }

    // Step 4: Create the final, sorted array and distribute elements
    // we start from the end to ensure STABILITY of the algorithm
    std::vector<T> final(n, 0);
    for (int i = n-1; i >= 0; --i) {
        final[aux[vec[i]]-1] = vec[i];
        aux[vec[i]]--;
    }
    return final;
}

template<class T>
void printArray(const std::vector<T>& vec) {
    for (T item : vec) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> tmp = {1, 4, 1, 2, 7, 5, 2};
    std::vector<int> s_tmp = countingSort(tmp);

    printArray(s_tmp);

    return 0;
}