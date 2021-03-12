import sys


class Node:
    def __init__(self, value=None):
        self.data = value
        self.prev = None
        self.min = value


class Stack:
    def __init__(self):
        self.tail = None
        self.size = 0

    def push(self, value):
        node = Node(value)
        if self.size == 0:
            self.tail = node
        else:
            node.prev = self.tail
            node.min = min(value, self.tail.min)
            self.tail = node
        self.size += 1

    def pop(self):
        self.tail = self.tail.prev
        self.size -= 1

    def find_min(self):
        return self.tail.min


def main():
    stack = Stack()
    n = int(next(sys.stdin))
    for _ in range(n):
        operation = list(map(int, next(sys.stdin).split()))
        operation_type = operation[0]
        if operation_type == 1:
            stack.push(operation[1])
        elif operation_type == 2:
            stack.pop()
        else:
            sys.stdout.write(f"{stack.find_min()}\n")


if __name__ == "__main__":
    main()
