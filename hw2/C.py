COUNT = 26
CHAR_SHIFT = 97


def count_sort(a, idx):
    cnt = [0] * COUNT
    for s in a:
        cnt[ord(s[idx]) - CHAR_SHIFT] += 1
    p = [0]
    for i in range(1, COUNT):
        p.append(p[-1] + cnt[i - 1])
    a_sorted = a.copy()
    for i in range(len(a)):
        a_sorted[p[ord(a[i][idx]) - CHAR_SHIFT]] = a[i]
        p[ord(a[i][idx]) - CHAR_SHIFT] += 1
    return a_sorted


def sort(a, k):
    for idx in range(k):
        a = count_sort(a, -idx - 1)
    return a


def main():
    n, m, k = map(int, input().split())
    a = []
    for _ in range(n):
        a.append(input())
    a = sort(a, k)
    for s in a:
        print(s)


if __name__ == "__main__":
    main()


