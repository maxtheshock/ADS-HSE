n = int(input())

adj = [
    list(map(int, input().split())) for _ in range(n)
]

result = "YES"
for i in range(n):
    if adj[i][i] == 1:
        result = "NO"
    for j in range(n):
        if adj[i][j] != adj[j][i]:
            result = "NO"
print(result)
