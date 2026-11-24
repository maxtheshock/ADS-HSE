import sys

sys.setrecursionlimit(200000)

n = int(input())
adj = [[] for _ in range(n + 1)]

for _ in range(n-1):
    v, u = map(int, input().split())
    adj[v].append(u)
    adj[u].append(v)

used = [0] * (n + 1)
path, res = [], []

def dfs(v: int) -> None:
    global used, path, res
    used[v] = 1
    path.append(v)
    for to in adj[v]:
        if used[to] == 0:
            dfs(to)
    if len(res) < len(path):
        res = path[::]
    path.pop()

dfs(1)
used = [0 for _ in range(n+1)]
dfs(res[-1])

print(len(res))
