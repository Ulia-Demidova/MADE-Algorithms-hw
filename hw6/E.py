import random


def main():
    # n = random.randint(0, 10)
    # print(n)
    # prices = [random.randint(0, 200) for _ in range(n)]
    # print(prices)
    n = int(input())
    if n == 0:
        print(0)
        print(0, 0)
        return

    prices = []
    for _ in range(n):
        prices.append(int(input()))
    days = [0] * n
    cost = 0
    coupon_count = 0
    dp = [0] * n

    start = 0
    while start < n:
        cost += prices[start]
        dp[start] = cost
        if prices[start] > 100:
            coupon_count += 1
            break
        start += 1

    # if start == n:
    #     print(dp[-1])
    #     print(0, 0)
    sum_after_coupon = 0

    for i in range(start + 1, n):
        if coupon_count > 0:
            dp[i] = dp[i - 1]
            if prices[i] > 0:
                days[i] = 1
                coupon_count -= 1
                sum_after_coupon = 0
        else:
            # if days:
            min_price = float("inf")
            day_with_min_p = 0
            for j in range(i):
                if days[j] == 1 and prices[j] < min_price:
                    min_price = prices[j]
                    day_with_min_p = j

            sum_after_coupon += prices[i]

            if min_price >= sum_after_coupon:
                dp[i] = dp[i - 1] + prices[i]
                if prices[i] > 100:
                    coupon_count += 1
            elif min_price > 100:
                
                dp[i] = dp[i - 1] + min_price
                if min_price > 100:
                    coupon_count += 1
                days[day_with_min_p] = 0
                days[i] = 1
            # else:
            #     dp[i] = dp[i - 1] + prices[i]
            #     if prices[i] > 100:
            #         coupon_count += 1

    print(dp[-1])
    print(coupon_count, sum(days))
    for i in range(n):
        if days[i]:
            print(i + 1)


if __name__ == "__main__":
    main()