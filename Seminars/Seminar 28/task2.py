n = int(input())

dp = [0] * 1000
cost = [0] + [int(x) for x in input().split()]
dp[1] = cost[1]

for i in range(2, n+1):
    dp[i] = min(dp[i-2:i]) + cost[i]
print(dp[n])
