def main():
    n, k = map(int, input().split())
    coins = list(map(int, input().split()))
    dp = [0] * (n - 1)
    prev = [0] * (n - 1)

    for i in range(1, n - 1):
        dp[i] = dp[max(i - k, 0)]
        prev[i] = max(i - k, 0)
        for j in range(max(i - k + 1, 1), i):
            if dp[i] < dp[j]:
                dp[i] = dp[j]
                prev[i] = j
        dp[i] += coins[i - 1]

    max_coin = dp[max(0, n - 1 - k)]
    last_column = max(0, n - 1 - k)
    for i in range(max(0, n - k), n - 1):
        if dp[i] > max_coin:
            max_coin = dp[i]
            last_column = i
    print(max_coin)
    answer = [n - 1, last_column]
    i = last_column
    while i > 0:
        i = prev[i]
        answer.append(i)

    print(len(answer) - 1)
    for column in answer[::-1]:
        print(column + 1, end=' ')


if __name__ == "__main__":
    main()