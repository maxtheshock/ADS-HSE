#include <iostream>
#include <string>
#include <vector>
#include <array>

class SuffixAutomat {
private:
    struct State {
        int length;
        int link;
        std::array<int, 26> next;
        State() : length(0), link(-1) { next.fill(-1); }
    };
    std::vector<State> _states;
    int _last;

public:
    SuffixAutomat(int max_length) : _last(0) {
        _states.reserve(2*max_length);
        _states.push_back(State());
    }

    void add(char symbol) {
        int c = symbol-'A';
        int current = _states.size();

        _states.push_back(State());
        _states[current].length = _states[_last].length+1;
        int previous = _last;

        while (previous != -1 && _states[previous].next[c] == -1) {
            _states[previous].next[c] = current;
            previous = _states[previous].link;
        }

        if (previous == -1) {
            _states[current].link = 0;
        } else {
            int next_state = _states[previous].next[c];
            if (_states[previous].length+1 == _states[next_state].length) {
                _states[current].link = next_state;
            } else {
                int clone = _states.size();
                _states.push_back(_states[next_state]);
                _states[clone].length = _states[previous].length+1;
                while (previous != -1 && _states[previous].next[c] == next_state) {
                    _states[previous].next[c] = clone;
                    previous = _states[previous].link;
                }
                _states[next_state].link = clone;
                _states[current].link = clone;
            }
        }
        _last = current;
    }

    std::string findLongestCommonSubstring(const std::string& string) const {
        int state = 0;
        int current_length = 0;
        int best_length = 0;
        int best_end = -1;
        int string_length = string.size();
        for (int i = 0; i < string_length; ++i) {
            int c = string[i]-'A';
            if (_states[state].next[c] != -1) {
                state = _states[state].next[c];
                ++current_length;
            } else {
                while (state != -1 && _states[state].next[c] == -1) {
                    state = _states[state].link;
                }
                if (state == -1) {
                    state = 0;
                    current_length = 0;
                } else {
                    current_length = _states[state].length+1;
                    state = _states[state].next[c];
                }
            }
            if (current_length > best_length) {
                best_length = current_length;
                best_end = i;
            }
        }
        return string.substr(best_end-best_length+1, best_length);
    }
};

int main() {
    int n;
    std::string first, second;
    std::cin >> n >> first >> second;
    SuffixAutomat automaton(n);

    for (char symbol : first) {
        automaton.add(symbol);
    }

    std::cout << automaton.findLongestCommonSubstring(second) << '\n';
    return 0;
}
