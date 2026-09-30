#include <iostream>
#include <vector>

bool solve(const std::vector<int>& a) {
    // Base case: only 1 number left
    if (a.size() == 1) {
        return a[0] == 24;
    }

    // Brute-forcing all possible pairs: (i,j)-th entries
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a.size(); ++j) {
            if (i != j) {
                // New array for the next step, excluding a[i] and a[j]
                std::vector<int> next_a;
                
                // Copy all elements, except the i-th and j-th
                for (int k = 0; k < a.size(); ++k) {
                    if (k != i && k != j) {
                        next_a.push_back(a[k]);
                    }
                }

                // Trying addition
                next_a.push_back(a[i] + a[j]);
                if (solve(next_a)) return true;
                next_a.pop_back(); // Убираем результат, чтобы попробовать следующую операцию

                // Trying subtraction (order matters, but since
                // the loops iterate over all pairs (i, j), we will check both a-b and b-a)
                // Loops trying all (i, j), we check a-b, b-a)
                next_a.push_back(a[i] - a[j]);
                if (solve(next_a)) return true;
                next_a.pop_back();

                // Trying multiplication
                next_a.push_back(a[i] * a[j]);
                if (solve(next_a)) return true;
                next_a.pop_back();
            }
        }
    }

    // If none of the combinations give 24
    return false;
}

int main() {
    std::vector<int> cards(4);
    std::cin >> cards[0] >> cards[1] >> cards[2] >> cards[3];

    if (solve(cards)) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    return 0;
}