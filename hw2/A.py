import random


def partition(a, l, r):
    idx = random.randint(l, r)
    a[l], a[idx] = a[idx], a[l]
    a[l], a[idx] = a[idx], a[l]
    x = a[l]
    last_low = last_equal = l
    for i in range(l + 1, r + 1):
        if a[i] <= x:
            last_equal += 1
            a[last_equal], a[i] = a[i], a[last_equal]
            if a[last_equal] < x:
                last_low += 1
                a[last_low], a[last_equal] = a[last_equal], a[last_low]
    a[l], a[last_low] = a[last_low], a[l]
    last_low -= 1
    return last_low, last_equal + 1


def find(a, k, i, j):
    if j - i == 0:
        return a[k]
    low, high = partition(a, i, j)
    if low < k < high:
        return a[k]
    elif k <= low:
        return find(a, k, i, low)
    else:
        return find(a, k, high, j)


def main():
    n = int(input())
    a = list(map(int, input().split()))
    m = int(input())
    for _ in range(m):
        i, j, k = map(int, input().split())
        print(find(a[i - 1: j], k - 1, 0, j - i))


if __name__ == "__main__":
    main()
