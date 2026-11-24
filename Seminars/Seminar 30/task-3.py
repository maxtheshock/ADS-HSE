import sys

sys.setrecursionlimit(200000)
input = sys.stdin.readline

n, m = map(int, input().split())
adj = [[] for _ in range(n + 1)]

for _ in range(m):
    v, u = map(int, input().split())
    adj[v].append(u)
    adj[u].append(v)

used = [0] * (n + 1)
is_bipartite = True

def dfs(v: int, c: int) -> None:
    global is_bipartite
    used[v] = c
    for to in adj[v]:
        if used[to] == 0:
            dfs(to, 3 - c)
        elif used[v] == used[to]:
            is_bipartite = False

for v in range(1, n + 1):
    if used[v] == 0:
        dfs(v, 1)

print('YES' if is_bipartite else 'NO')
