import sys
sys.setrecursionlimit(100000)

n, m = map(int, input().split())
adj = [[] for i in range(n+1)]
for i in range(m):
    v, u = map(int, input().split())
    adj[v].append(u)
    adj[u].append(v)

used = [0 for i in range(n+1)]
color = 0
def dfs(v: int) -> None:
    used[v] = color
    for to in adj[v]:
        if used[to] == 0:
            dfs(to)

for v in range(1, n+1):
    if used[v] == 0:
        color += 1
        dfs(v)

dfs(1)

if (n == (m + 1)) and (n == sum(used)):
    print('YES')
else:
    print('NO')
