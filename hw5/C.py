import sys

A = 29
MAP_SIZE = 10 ** 5


class Node:
    def __init__(self, key, value):
        self.key = key
        self.val = value
        self.next = None
        self.prev = None


class Map:
    def __init__(self):
        self.arr = [[] for _ in range(MAP_SIZE)]
        self.head = None
        self.tail = None

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
        node = Node(k, v)
        if self.head is None:
            self.head = self.tail = node
        else:
            node.prev = self.tail
            self.tail.next = node
            self.tail = node

        self.arr[idx].append(node)

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
                if self.head == self.tail:
                    self.head = self.tail = None

                elif self.head == node:
                    self.head = node.next
                    node.next.prev = node.prev

                elif self.tail == node:
                    self.tail = node.prev
                    node.prev.next = node.next

                else:
                    node.prev.next = node.next
                    node.next.prev = node.prev

                self.arr[idx].pop(i)
                break

    def prev(self, k):
        idx = self.hash(k)
        for node in self.arr[idx]:
            if node.key == k:
                if self.head == node:
                    return "none"
                else:
                    return node.prev.val
        return "none"

    def next(self, k):
        idx = self.hash(k)
        for node in self.arr[idx]:
            if node.key == k:
                if self.tail == node:
                    return "none"
                else:
                    return node.next.val
        return "none"


def main():
    m = Map()
    for operation in sys.stdin.readlines():
        operation = operation.split()
        if operation[0] == "put":
            m.put(operation[1], operation[2])
        elif operation[0] == "get":
            sys.stdout.write(f"{m.get(operation[1])}\n")
        elif operation[0] == "delete":
            m.delete(operation[1])
        elif operation[0] == "prev":
            sys.stdout.write(f"{m.prev(operation[1])}\n")
        else:
            sys.stdout.write(f"{m.next(operation[1])}\n")


if __name__ == "__main__":
    main()

