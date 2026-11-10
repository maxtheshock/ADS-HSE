# for j in steps(10):
#    print(j)

from collections import deque

def steps(i):
    yield i-1
    if i % 2 == 0:
        yield i // 2
    if i % 3 == 0:
        yield i // 3


n = int(input())
dp = [float('inf')] * 100_001
p = [-1] * 100_001
dp[1] = 0


for i in range(2, n+1):
    for j in steps(i):
        if dp[i] > dp[j] + 1:
            dp[i] = dp[j] + 1
            p[i] = j

print(dp[n])

# NOT: res = [] (!)
res = deque()
v = n

while v != -1:
    res.appendleft(v)
    v = p[v]
print(*res)
