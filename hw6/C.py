def main():
    n = int(input())
    a = list(map(int, input().split()))
    dp = [1] * n
    prev = [i for i in range(n)]
    for i in range(1, n):
        for j in range(i):
            if (a[j] < a[i]) and (dp[j] + 1 > dp[i]):
                dp[i] = dp[j] + 1
                prev[i] = j
    lis_length = 1
    idx = 0
    for i in range(1, n):
        if dp[i] > lis_length:
            lis_length = dp[i]
            idx = i
    print(lis_length)
    ans = [a[idx]]

    while idx > 0:
        if idx == prev[idx]:
            break
        ans.append(a[prev[idx]])
        idx = prev[idx]

    for i in ans[::-1]:
        print(i, end=' ')


if __name__ == '__main__':
    main()
