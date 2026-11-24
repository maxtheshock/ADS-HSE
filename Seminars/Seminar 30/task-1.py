n, m = map(int, input().split())

dp = [[0 for _ in range(m)] for _ in range(n)]
dp[0][0] = 1

steps = [
    (1, -2), (-1, -2), (-2, -1), (-2, 1)
]

def f(i, j):
    if i < 0 or j < 0 or i >= n or j >= m:
        return 0
    if dp[i][j] != 0:
        return dp[i][j]
    for di, dj in steps:
        dp[i][j] += f(i+di, j+dj)
    return dp[i][j]

print(f(n-1, m-1))