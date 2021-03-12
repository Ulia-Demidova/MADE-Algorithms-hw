import math


def update_a(prev_a):
    return (23 * prev_a + 21563) % 16714589


def update_u(prev_u, prev_answer, it, n):
    return ((17 * prev_u + 751 + prev_answer + 2 * it) % n) + 1


def update_v(prev_v, prev_answer, it, n):
    return ((13 * prev_v + 593 + prev_answer + 5 * it) % n) + 1


def main():
    n, m, a = map(int, input().split())
    u, v = map(int, input().split())

    prefix_min = [[] for _ in range(n)]
    for i in range(n):
        prefix_min[i].append(a)
        a = update_a(a)

    for k in range(1, int(math.log2(n)) + 1):
        for i in range(n - 2 ** k + 1):
            prefix_min[i].append(min(prefix_min[i][k - 1], prefix_min[i + 2 ** (k - 1)][k - 1]))

    max_pow = [0] * n
    for i in range(1, n):
        max_pow[i] = max_pow[i - 1]
        if 1 << (max_pow[i] + 1) <= (i + 1):
            max_pow[i] += 1

    for i in range(1, m + 1):
        left = min(u, v)
        right = max(u, v)
        k = max_pow[right - left]
        answer = min(prefix_min[left - 1][k], prefix_min[right - 2 ** k][k])
        if i == m:
            print(u, v, answer)
        u = update_u(u, answer, i, n)
        v = update_v(v, answer, i, n)


if __name__ == '__main__':
    main()



