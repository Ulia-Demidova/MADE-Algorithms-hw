def merge(a, b):
    result = []
    i, j = 0, 0
    while i < len(a) and j < len(b):
        if a[i] <= b[j]:
            result.append(a[i])
            i += 1
        else:
            result.append(b[j])
            j += 1
    if i >= len(a):
        result.extend(b[j:])
    if j >= len(b):
        result.extend(a[i:])
    return result


def merge_sort(a):
    if len(a) == 1:
        return a
    l = 0
    r = len(a) - 1
    m = (l + r) // 2
    return merge(merge_sort(a[:m + 1]), merge_sort(a[m + 1:]))


n = int(input())
a = list(map(int, input().split()))

for x in merge_sort(a):
    print(x, end=' ')
