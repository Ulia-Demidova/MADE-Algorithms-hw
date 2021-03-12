def main():
    a = input()
    b = input()
    n = len(a)
    m = len(b)
    dp = [list(range(m + 1))]
    for i in range(n):
        dp.append([i + 1])
        dp[-1].extend([0] * m)

    for i in range(1, n + 1):
        for j in range(1, m + 1):
            dp[i][j] = min(dp[i][j - 1] + 1,
                           dp[i - 1][j] + 1,
                           dp[i - 1][j - 1] + int(a[i - 1] != b[j - 1]))
    print(dp[n][m])


if __name__ == "__main__":
    main()
