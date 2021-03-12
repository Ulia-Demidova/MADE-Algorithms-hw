import sys


def lower_bound(a, x):
    left = 0
    right = len(a) - 1
    while left < right:
        m = (left + right) // 2
        if a[m] >= x:
            right = m
        else:
            left = m + 1
    if a[left] >= x:
        return left
    else:
        return left + 1


def count(a, left, right):
    i = lower_bound(a, left)
    j = lower_bound(a, right + 1)
    return j - i


def main():
    next(sys.stdin)
    a = list(map(int, next(sys.stdin).split()))
    a.sort()
    k = int(next(sys.stdin))
    for _ in range(k):
        l, r = map(int, next(sys.stdin).split())
        sys.stdout.write(f"{count(a, l, r)} ")


if __name__ == '__main__':
    main()
