n, m = map(int, input().split())
adj = [[] for i in range(n+1)]
for i in range(m):
    v, u = map(int, input.split())
    adj[v].append(u)
    adj[u].append(v)

used = [0 for i in range(n+1)]

def dfs(v: int) -> None:
    used[v] = 1
    for to in adj[v]:
        if used[to] == 0:
            dfs(to)

dfs(1)
if sum(used) == n:
    print('YES')
else:
    print('NO')
    