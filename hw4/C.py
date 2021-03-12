import sys

CAPACITY_MIN = 8


class Queue:
    def __init__(self):
        self.begin = 0
        self.end = 0
        self.size = 0
        self.capacity = CAPACITY_MIN
        self.elements = [None] * self.capacity

    def ensure_capacity(self):
        new_elements = [None] * self.capacity * 2
        for i in range(self.capacity):
            new_elements[i] = self.elements[(i + self.begin) % self.capacity]
        self.elements = new_elements
        self.begin = 0
        self.end = self.capacity
        self.capacity *= 2

    def push(self, value):
        if self.size == self.capacity:
            self.ensure_capacity()

        self.elements[self.end] = value
        self.size += 1
        self.end = (self.end + 1) % self.capacity

    def front(self):
        return self.elements[self.begin]

    def pop(self):
        self.begin = (self.begin + 1) % self.capacity
        self.size -= 1
        if self.capacity >= 2 * CAPACITY_MIN and \
                self.size < self.capacity // 4:
            new_elements = [None] * (self.capacity // 2)
            for i in range(self.size):
                new_elements[i] = self.elements[(i + self.begin) % self.capacity]
            self.capacity //= 2
            self.elements = new_elements
            self.begin = 0
            self.end = self.size


def main():
    m = int(next(sys.stdin))
    queue = Queue()
    for _ in range(m):
        command = next(sys.stdin).split()
        if command[0] == '+':
            queue.push(int(command[1]))
        else:
            sys.stdout.write(f"{queue.front()}\n")
            queue.pop()


if __name__ == "__main__":
    main()
