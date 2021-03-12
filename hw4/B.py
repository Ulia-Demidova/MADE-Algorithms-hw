import sys


CAPACITY_MIN = 16


class Stack:
    def __init__(self):
        self.size = 0
        self.capacity = CAPACITY_MIN
        self.elements = [None] * self.capacity

    def get(self, idx):
        if idx < 0 or idx >= self.size:
            return None
        return self.elements[idx]

    def ensure_capacity(self):
        new_elements = [None] * self.capacity
        for i in range(self.size):
            new_elements[i] = self.elements[i]
        self.elements = new_elements

    def add(self, value):
        if self.size >= self.capacity:
            self.capacity *= 2
            self.ensure_capacity()
        self.elements[self.size] = value
        self.size += 1

    def erase(self):
        self.size -= 1
        if self.capacity >= 2 * CAPACITY_MIN and self.size <= self.capacity / 4:
            del self.elements[self.capacity // 2: self.capacity]
            self.capacity //= 2

    def back(self):
        return self.get(self.size - 1)

    def set_value(self, idx, value):
        self.elements[idx] = value


def calculate(a, b, operation):
    if operation == '+':
        return a + b
    elif operation == '-':
        return a - b
    else:
        return a * b


def main():
    stack = Stack()
    expression = sys.stdin.readline().split()
    for element in expression:
        if element == '+' or element == '-' or element == '*':
            second = stack.back()
            stack.erase()
            first = stack.back()
            stack.set_value(stack.size - 1, calculate(first, second, element))
        else:
            stack.add(int(element))

    sys.stdout.write(f"{stack.back()}")


if __name__ == "__main__":
    main()

