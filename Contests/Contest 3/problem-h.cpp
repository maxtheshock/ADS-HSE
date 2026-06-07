#include <iostream>
#include <vector>
#include <queue>
#include <utility>

std::pair<int, int> get_farthest(int start, const std::vector<std::vector<int>>& graph) {
    int n = static_cast<int>(graph.size()) - 1;

    std::vector<int> distance(n + 1, -1);
    std::queue<int> queue;
    distance[start] = 0;
    queue.push(start);
    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();

        for (int to : graph[v]) {
            if (distance[to] == -1) {
                distance[to] = distance[v] + 1;
                queue.push(to);
            }
        }
    }

    int farthest_vertex = start;
    int farthest_distance = 0;

    for (int i = 1; i <= n; ++i) {
        if (distance[i] > farthest_distance) {
            farthest_distance = distance[i];
            farthest_vertex = i;
        }
    }

    return {farthest_vertex, farthest_distance};
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> graph(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a;
        int b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    std::pair<int, int> first = get_farthest(1, graph);
    std::pair<int, int> second = get_farthest(first.first, graph);
    std::cout << second.second + 1 << std::endl;

    return 0;
}
