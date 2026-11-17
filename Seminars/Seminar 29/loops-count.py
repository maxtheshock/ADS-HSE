n = int(input())

adj = [
    list(map(int, input().split())) for _ in range(n)
]

result = "NO"
for i in range(n):
    if adj[i][i] == 1:
        result = "YES"

print(result)
