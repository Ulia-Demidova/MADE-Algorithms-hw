def merge(a: tuple, b: tuple):
    a, a_inv = a
    b, b_inv = b
    result = []
    i, j = 0, 0
    count = 0
    while i < len(a) and j < len(b):
        if a[i] <= b[j]:
            result.append(a[i])
            i += 1
        else:
            result.append(b[j])
            j += 1
            count += len(a) - i
    if i >= len(a):
        result.extend(b[j:])
    if j >= len(b):
        result.extend(a[i:])
    return result, count + a_inv + b_inv


def merge_sort(a):
    if len(a) == 1:
        return a, 0
    l = 0
    r = len(a) - 1
    m = (l + r) // 2
    return merge(merge_sort(a[:m + 1]), merge_sort(a[m + 1:]))


n = int(input())
a = list(map(int, input().split()))

print(merge_sort(a)[1])
