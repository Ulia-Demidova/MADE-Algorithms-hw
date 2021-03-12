def binary_search(a, x):
    left = 0
    right = len(a) - 1

    while left < right:
        m = (left + right) // 2
        if a[m] == x:
            return x

        if a[m] < x:
            left = m + 1
        else:
            right = m

    if a[left] == x or left == 0:
        return a[left]

    if a[left] > x and x - a[left - 1] <= a[left] - x:
        return a[left - 1]
    else:
        return a[left]


def main():
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    queries = map(int, input().split())

    for q in queries:
        print(binary_search(a, q))


if __name__ == "__main__":
    main()
