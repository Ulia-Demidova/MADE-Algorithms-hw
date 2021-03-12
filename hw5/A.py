import sys

SET_SIZE = 2 * (10 ** 6)
A = 13
P = 2 * (10 ** 6) + 17


class Set:
    def __init__(self):
        self.array = [None] * SET_SIZE

    def hash(self, x):
        return ((A * x) % P) % SET_SIZE

    def insert(self, x):
        idx = self.hash(x)
        was_rip = False
        while self.array[idx] is not None:
            if self.array[idx] == x:
                return
            if not was_rip and self.array[idx] == "rip":
                was_rip = True
                rip_idx = idx
            idx = (idx + 1) % SET_SIZE
        if was_rip:
            idx = rip_idx
        self.array[idx] = x

    def exists(self, x):
        idx = self.hash(x)
        while self.array[idx] is not None:
            if self.array[idx] == x:
                return "true\n"
            idx = (idx + 1) % SET_SIZE
        return "false\n"

    def delete(self, x):
        idx = self.hash(x)
        while self.array[idx] is not None:
            if self.array[idx] == x:
                self.array[idx] = "rip"
                break
            idx = (idx + 1) % SET_SIZE


def main():
    s = Set()
    for operation in sys.stdin.buffer.readlines():
        operation, x = operation.decode().split()
        if operation == "insert":
            s.insert(int(x))
        elif operation == "delete":
            s.delete(int(x))
        else:
            sys.stdout.buffer.write(s.exists(int(x)).encode(encoding="utf-8"))


if __name__ == "__main__":
    main()
