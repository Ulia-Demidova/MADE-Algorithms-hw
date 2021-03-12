n = int(input())
a = list(map(int, input().split()))

for i in range(n):
    j = i
    while j > 0 and a[j - 1] > a[j]:
        a[j - 1], a[j] = a[j], a[j - 1]
        j -= 1

for x in a:
    print(x, end=' ')
