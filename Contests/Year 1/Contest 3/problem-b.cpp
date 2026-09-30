#include <iostream>
#include <vector>
#include <set>
#include <queue>

using ll = long long;

struct BlockEvent {
    int time;
    int block_id;

    bool operator>(const BlockEvent& other) const {
        return time > other.time;
    }
};

int main() {
    int N = 30000;
    int T = 600;

    std::set<int> free_blocks;

    for (int i = 1; i <= N; ++i) {
        free_blocks.insert(i);
    }

    std::vector<bool> busy(N + 1, false);
    std::vector<int> release_time(N + 1, -1);

    std::priority_queue<BlockEvent, std::vector<BlockEvent>, std::greater<BlockEvent>> events;

    int current_time;
    char type;

    while (std::cin >> current_time >> type) {
        while (!events.empty() && events.top().time <= current_time) {
            BlockEvent event = events.top();
            events.pop();

            int block = event.block_id;

            if (busy[block] && release_time[block] == event.time) {
                busy[block] = false;
                free_blocks.insert(block);
            }
        }

        if (type == '+') {
            int block = *free_blocks.begin();
            free_blocks.erase(free_blocks.begin());

            busy[block] = true;
            release_time[block] = current_time + T;
            events.push({release_time[block], block});

            std::cout << block << std::endl;
        } else {
            int block;
            std::cin >> block;

            if (busy[block]) {
                release_time[block] = current_time + T;
                events.push({release_time[block], block});

                std::cout << "+" << std::endl;
            } else {
                std::cout << "-" << std::endl;
            }
        }
    }

    return 0;
}
