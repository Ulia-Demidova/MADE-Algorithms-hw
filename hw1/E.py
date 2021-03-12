import random


def partition(a, l, r):
    idx = random.randint(l, r)
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
    return last_low, last_equal + 1


def quick_sort(a, l, r):
    if l >= r:
        return
    low, high = partition(a, l, r)
    quick_sort(a, l, low)
    quick_sort(a, high, r)


n = int(input())
a = list(map(int, input().split()))

quick_sort(a, 0, n - 1)

for x in a:
    print(x, end=' ')
