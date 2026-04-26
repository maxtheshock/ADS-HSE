#include <iostream>
#include <vector>

// Merging template function for 2 sorted(!) arrays

template<class T>
std::vector<T> merge(const std::vector<T>& a, const std::vector<T>& b) {
    std::vector<T> c; // creating std::vector for resulting array
    c.reserve(a.size() + b.size()); // better to allocate memory separately
    size_t i = 0, j = 0; // pointers for the left and right arrays
    while (i < a.size() && j < b.size()) {
        if (a[i] < b[j]) {
            c.push_back(a[i]); // generally, safer than c[i+j] = ...
            ++i;
        } else {
            c.push_back(b[j]);
            ++j;
        }
    }

    // if some elements left, we push them into the end

    while (i < a.size()) {
        c.push_back(a[i]);
        ++i;
    }
    while (j < b.size()) {
        c.push_back(b[j]);
        ++j;
    }

    return c;
}



// Sorting algorithm (Divide and conquer)

template<class T>
std::vector<T> sort(const std::vector<T>& arr) {
    if (arr.size() < 2) {
        return arr;
    }
    size_t mid = arr.size() / 2;
    std::vector<T> left = sort(std::vector<T>(arr.begin(), arr.begin() + mid));
    std::vector<T> right = sort(std::vector<T>(arr.begin() + mid, arr.end()));
    return merge(left, right);
}

int main() {
    std::vector<int> a = {1,49,4,36,81,9,16,25,100,-1,55,90,97,-100,-12};
    std::vector<int> c = sort(a);

    for (auto item : c) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}