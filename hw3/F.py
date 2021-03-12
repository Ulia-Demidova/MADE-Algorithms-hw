ITN = 35


def func(x, a, v_p, v_f):
    return ((1 - a) ** 2 + x ** 2) ** 0.5 / v_p + \
           ((1 - x) ** 2 + a ** 2) ** 0.5 / v_f


def ternary_search(left, right, a, v_p, v_f):
    for _ in range(ITN):
        m1 = left + (right - left) / 3
        m2 = left + 2 * (right - left) / 3
        if func(m1, a, v_p, v_f) < func(m2, a, v_p, v_f):
            right = m2
        else:
            left = m1
    return right


def main():
    v_p, v_f = map(int, input().split())
    a = float(input())
    left = 0.
    right = 1.
    print(ternary_search(left, right, a, v_p, v_f))


if __name__ == '__main__':
    main()
