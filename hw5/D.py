import sys

A = 29
MAP_SIZE = 3 * 10 ** 5
P = 361275


class Map:
    def __init__(self):
        self.arr = [(None, [None] * MAP_SIZE) for _ in range(MAP_SIZE)]

    def hash(self, string):
        res = 0
        for c in string:
            res = (res * A + ord(c)) % P
        return res % MAP_SIZE

    def put(self, k, v):
        idx_key = self.hash(k)
        idx_val = self.hash(v)
        was_rip = False
        while self.arr[idx_key][0] is not None:
            if self.arr[idx_key][0] == k:
                while self.arr[idx_key][1][idx_val] is not None:
                    if self.arr[idx_key][1][idx_val] == v:
                        return
                    idx_val = (idx_val + 1) % MAP_SIZE
                self.arr[idx_key][1][idx_val] = v
                return
                # for i in range(1, len(self.arr[idx])):
                #     if self.arr[idx][i] == v:
                #         return
                # self.arr[idx].append(v)
                # return
            if not was_rip and self.arr[idx_key][0] == "0":
                was_rip = True
                rip_idx = idx_key
            idx_key = (idx_key + 1) % MAP_SIZE

        if was_rip:
            idx_key = rip_idx
        self.arr[idx_key][0] = k
        self.arr[idx_key][1][idx_val] = v
        # idx = self.hash(k)
        # for node in self.arr[idx]:
        #     if node[0] == k and node[1] == v:
        #         return
        # self.arr[idx].append((k, v))

    def get(self, k):
        idx_key = self.hash(k)
        # count = 0
        # values = []
        while self.arr[idx_key][0] is not None:
            if self.arr[idx_key][0] == k:
                values = []
                for val in self.arr[idx_key][1]:
                    if val is not None and val != "0":
                        values.append(val)
                return len(values), values
            idx_key = (idx_key + 1) % MAP_SIZE
        # for node in self.arr[idx]:
        #     if node[0] == k:
        #         count += 1
        #         values.append(node[1])
        return 0, []

    def delete(self, k, v):
        idx_key = self.hash(k)
        idx_val = self.hash(v)

        while self.arr[idx_key][0] is not None:
            if self.arr[idx_key][0] == k:
                while self.arr[idx_key][1][idx_val] is not None:
                    if self.arr[idx_key][1][idx_val] == v:
                        self.arr[idx_key][1][idx_val] = "0"
                        return
                    idx_val = (idx_val + 1) % MAP_SIZE
                return
                # for i in range(1, len(self.arr[idx])):
                #     if self.arr[idx][i] == v:
                #         self.arr[idx].pop(i)
                #         return
            idx = (idx + 1) % MAP_SIZE

        # for i, node in enumerate(self.arr[idx]):
        #     if node[0] == k and node[1] == v:
        #         self.arr[idx].pop(i)
        #         break

    def delete_all(self, k):
        idx_key = self.hash(k)
        while self.arr[idx_key][0] is not None:
            if self.arr[idx_key][0] == k:
                self.arr[idx_key][0] = "0"
                self.arr[idx_key][1] = [None] * MAP_SIZE
                return
            idx_key = (idx_key + 1) % MAP_SIZE

        # i = 0
        # for _ in range(len(self.arr[idx])):
        #     if self.arr[idx][i][0] == k:
        #         self.arr[idx][i] = self.arr[idx][-1]
        #         self.arr[idx].pop()
        #     else:
        #         i += 1


def main():
    m = Map()
    for operation in sys.stdin.buffer.readlines():
        operation = operation.decode().split()
        if operation[0] == "put":
            m.put(operation[1], operation[2])
        elif operation[0] == "get":
            count, vals = m.get(operation[1])
            answer = str(count) + ' ' + ' '.join(vals) + '\n'
            sys.stdout.buffer.write(answer.encode(encoding="utf-8"))
            # sys.stdout.write(f"{m.get(operation[1])}\n")
        elif operation[0] == "delete":
            m.delete(operation[1], operation[2])
        else:
            m.delete_all(operation[1])


if __name__ == "__main__":
    main()

