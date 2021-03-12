import sys


class FenwickTree:
    def __init__(self, array, n):
        self.a = array
        self.t = [0] * n
        self.length = n
        for i in range(n):
            self.add(i, array[i])

    def add(self, i, val):
        while i < self.length:
            self.t[i] += val
            i = i | (i + 1)

    def func(self, i):
        return i & (i + 1)

    def get(self, i):
        res = 0
        while i >= 0:
            res += self.t[i]
            i = self.func(i) - 1
        return res

    def rsq(self, left, right):
        if left == 0:
            return self.get(right)
        else:
            return self.get(right) - self.get(left - 1)

    def set(self, i, val):
        delta = val - self.a[i]
        self.a[i] = val
        self.add(i, delta)


def main():
    n = int(input())
    a = list(map(int, input().split()))
    tree = FenwickTree(a, n)
    for operation in sys.stdin.readlines():
        operation, first, second = operation.split()
        if operation == "sum":
            sys.stdout.buffer.write((str(tree.rsq(int(first) - 1, int(second) - 1))+'\n').encode(encoding="utf-8"))
        else:
            tree.set(int(first) - 1, int(second))


if __name__ == "__main__":
    main()


