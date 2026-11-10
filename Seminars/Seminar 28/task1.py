n = int(input())

dp = [0] * 1000

dp[0] = dp[1] = 1
dp[2] = 2

for i in range(3, n+1):
    dp[i] = sum(dp[i-3:i])
print(dp[n])
