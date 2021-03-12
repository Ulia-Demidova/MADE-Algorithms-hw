def func(result, lengths, k):
    return sum([length // result for length in lengths]) >= k


def bin_search(left, right, lengths, k):
    while left < right:
        m = (left + right) // 2
        if func(m, lengths, k):
            left = m + 1
        else:
            right = m
    return left - 1


def main():
    n, k = map(int, input().split())
    lengths = []
    for _ in range(n):
        lengths.append(int(input()))
    left = max(min(lengths) // k, 1)
    right = max(lengths) + 1
    print(bin_search(left, right, lengths, k))


if __name__ == '__main__':
    main()