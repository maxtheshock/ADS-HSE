#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> oddPalindromes(const std::string_view s) {
    int n = s.length();
    std::vector<int> odd(n);

    int left = 0;
    int right = -1;

    for (int center = 0; center < n; ++center) {
        int radius = 1;
        if (center <= right) {
            radius = std::min(odd[left+right-center], right-center+1);
        }
        while (center-radius >= 0 && center + radius < n && s[center-radius] == s[center+radius]) { ++radius; }
        odd[center] = radius;
        if (center+radius-1 > right) {
            left = center-radius+1;
            right = center+radius-1;
        }
    }
    return odd;
}

std::vector<int> evenPalindromes(const std::string_view s) {
    int n = s.length();
    std::vector<int> even(n);

    int left = 0;
    int right = -1;

    for (int center = 0; center < n; ++center) {
        int radius = 0;
        if (center <= right) {
            radius = std::min(even[left+right-center+1], right-center+1);
        }
        while (center-radius-1 >= 0 && center + radius < n && s[center-radius-1] == s[center+radius]) { ++radius; }
        even[center] = radius;
        if (center+radius-1 > right) {
            left = center-radius;
            right = center+radius-1;
        }
    }
    return even;
}

void addSegment(std::vector<long long>& difference, const int left, const int right) {
    if (left > right) {
        return;
    }
    ++difference[left];
    --difference[right+1];
}

int main() {
    std::string s;
    std::cin >> s;

    int n = s.length();

    std::vector<int> odd = oddPalindromes(s);
    std::vector<int> even = evenPalindromes(s);

    std::vector<long long> start_difference(n+1);
    std::vector<long long> end_difference(n+1);

    for (int center = 0; center < n; ++center) {
        addSegment(start_difference, center-odd[center]+1, center);
        addSegment(end_difference, center, center+odd[center]-1);

        addSegment(start_difference, center-even[center], center-1);
        addSegment(end_difference, center, center+even[center]-1);
    }

    std::vector<long long> starts(n);
    std::vector<long long> ends(n);

    long long current_starts = 0;
    long long current_ends = 0;

    for (int i = 0; i < n; ++i) {
        current_starts += start_difference[i];
        current_ends += end_difference[i];

        starts[i] = current_starts;
        ends[i] = current_ends;
    }

    long long answer = 0;

    for (int j = 0; j + 1 < n; ++j) {
        answer += ends[j]*starts[j+1];
    }

    std::cout << answer << std::endl;
    return 0;
}
