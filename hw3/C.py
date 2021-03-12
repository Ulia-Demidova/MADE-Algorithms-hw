ITN = 40


def func(x):
    return x ** 2 + x ** 0.5


def bin_search(left, right, y):
    for _ in range(ITN):
        m = (left + right) / 2
        if func(m) < y:
            left = m
        else:
            right = m
    return right


def main():
    c = float(input())
    left = 1.0
    right = 10. ** 5
    print(bin_search(left, right, c))


if __name__ == '__main__':
    main()
