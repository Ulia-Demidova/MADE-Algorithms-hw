import sys

A = 29
MAP_SIZE = 10 ** 5


class Node:
    def __init__(self, key, value):
        self.key = key
        self.val = value


class Map:
    def __init__(self):
        self.arr = [[] for _ in range(MAP_SIZE)]

    def hash(self, string):
        res = 0
        for c in string:
            res = (res * A + ord(c)) % MAP_SIZE
        return res

    def put(self, k, v):
        idx = self.hash(k)
        for node in self.arr[idx]:
            if node.key == k:
                node.val = v
                return
        self.arr[idx].append(Node(k, v))

    def get(self, k):
        idx = self.hash(k)
        for node in self.arr[idx]:
            if node.key == k:
                return node.val
        return "none"

    def delete(self, k):
        idx = self.hash(k)
        for i, node in enumerate(self.arr[idx]):
            if node.key == k:
                self.arr[idx].pop(i)
                break


def main():
    m = Map()
    for operation in sys.stdin.readlines():
        operation = operation.split()
        if operation[0] == "put":
            m.put(operation[1], operation[2])
        elif operation[0] == "get":
            sys.stdout.write(f"{m.get(operation[1])}\n")
        else:
            m.delete(operation[1])


if __name__ == "__main__":
    main()

