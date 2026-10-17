#include <iostream>
#include <vector>

std::string addSeparators(const std::string_view text) {
    std::string result;
    result.reserve(2*text.length() + 1);

    for (char symbol : text) {
        result.push_back('#');
        result.push_back(symbol);
    }

    result.push_back('#');
    return result;
}

std::vector<int> palindromeRadii(const std::string_view text) {
    int n = text.length();
    std::vector<int> radius(n);

    int segment_left = 0;
    int segment_right = -1;

    for (int center = 0; center < n; ++center) {
        int current_radius = 0;
        if (center <= segment_right) {
            int reflected_center = segment_left + segment_right - center;
            current_radius = std::min(radius[reflected_center], segment_right - center);
        }
        while (center - current_radius - 1 >= 0 && center + current_radius + 1 < n && text[center - current_radius - 1] == text[center + current_radius + 1]) {
            ++current_radius;
        }

        radius[center] = current_radius;

        if (center + current_radius > segment_right) {
            segment_left = center - current_radius;
            segment_right = center + current_radius;
        }
    }

    return radius;
}

int main() {
    std::string text;
    std::cin >> text;

    std::string modified_text = addSeparators(text);
    std::vector<int> radius = palindromeRadii(modified_text);
    long long answer = 0;

    for (int current_radius : radius) {
        answer += (current_radius + 1) / 2;
    }
    answer -= text.length();
    std::cout << answer << '\n';

    return 0;
}
