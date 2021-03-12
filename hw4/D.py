import sys


class Node:
    def __init__(self, value, order):
        self.value = value
        self.order = order


class Heap:
    def __init__(self):
        self.elements = []
        self.size = 0

    def swap(self, i, j):
        self.elements[i], self.elements[j] = \
            self.elements[j], self.elements[i]

    def sift_up(self, i):
        while i > 0 and self.elements[i].value < self.elements[(i - 1) // 2].value:
            self.swap(i, (i - 1) // 2)
            i = (i - 1) // 2

    def sift_down(self, i):
        while 2 * i + 1 < self.size:
            min_idx = 2 * i + 1
            if 2 * i + 2 < self.size and \
                    self.elements[2 * i + 2].value < self.elements[2 * i + 1].value:
                min_idx = 2 * i + 2

            if self.elements[i].value <= self.elements[min_idx].value:
                break
            self.swap(i, min_idx)
            i = min_idx

    def push(self, node):
        self.elements.append(node)
        self.size += 1
        self.sift_up(self.size - 1)

    def extract_min(self):
        if self.size == 0:
            return '*'
        min_value = self.elements[0].value
        push_order = self.elements[0].order
        self.swap(0, self.size - 1)
        self.elements.pop()
        self.size -= 1
        self.sift_down(0)
        return min_value, push_order

    def decrease_key(self, key, value):
        for i, node in enumerate(self.elements):
            if node.order == key:
                node.value = value
                self.sift_up(i)
                break


def main():
    heap = Heap()
    i = 1
    for operation in sys.stdin.readlines():
        operation = operation.split()
        if operation[0] == "push":
            heap.push(Node(int(operation[1]), i))
        elif operation[0] == "extract-min":
            min_info = heap.extract_min()
            if min_info == '*':
                sys.stdout.write(f"{min_info}\n")
            else:
                sys.stdout.write(f"{min_info[0]} {min_info[1]}\n")
        else:
            key = int(operation[1])
            new_value = int(operation[2])
            heap.decrease_key(key, new_value)
        i += 1


if __name__ == "__main__":
    main()
