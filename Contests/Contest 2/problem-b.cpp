#include <iostream>
#include <string>
#include <vector>

std::vector<std::vector<int>> build_table(const std::string_view s) {
    int n = s.length();

    std::vector<std::vector<int>> next_pos(n+1, std::vector<int>(26, -1));
    std::vector<int> current_last(26, -1);

    for (int i = n-1; i >= 0; --i) {
        current_last[s[i] - 'a'] = i;
        for (int c = 0; c < 26; ++c) {
            next_pos[i][c] = current_last[c];
        }
    }

    return next_pos;
}

int main() {
    std::string x, y;
    std::cin >> x >> y;

    // we construct these special tables for both parents
    auto next_x = build_table(x);
    auto next_y = build_table(y);
    std::string res = "";
    int pos_x = 0;
    int pos_y = 0;

    while (pos_x < x.length() && pos_y < y.length()) {
        bool letter_found = false;

        for (int c = 25; c >= 0; --c) {
            int idx_x = next_x[pos_x][c];
            int idx_y = next_y[pos_y][c];

            if (idx_x != -1 && idx_y != -1) {
                res.push_back(c + 'a');
                pos_x = idx_x + 1;
                pos_y = idx_y + 1;
                letter_found = true;
                break;
            }
        }

        if (letter_found == false) { break; }
    }
    
    std::cout << res << std::endl;
    return 0;

}