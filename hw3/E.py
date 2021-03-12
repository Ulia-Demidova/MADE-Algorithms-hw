def func(n, t, x, y):
    first_time = min(x, y)
    return 1 + (t - first_time) // x + (t - first_time) // y >= n


def bin_search(left, right, n, x, y):
    while left < right:
        m = (left + right) // 2
        if func(n, m, x, y):
            right = m
        else:
            left = m + 1
    return left


def main():
    n, x, y = map(int, input().split())
    left = 0
    right = n * max(x, y)
    print(bin_search(left, right, n, x, y))


if __name__ == '__main__':
    main()
