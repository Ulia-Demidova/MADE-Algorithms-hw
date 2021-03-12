import sys
import random
import string

A = 29
MAP_SIZE = 2 * 10 ** 5
# P = MAP_SIZE + 17


class Map:
    def __init__(self):
        self.arr = [None] * MAP_SIZE

    def hash(self, string):
        res = 0
        for c in string:
            res = (res * A + ord(c)) % MAP_SIZE
        return res

    # def get_pair(self, k):
    #     idx = self.hash(k)
    #     values = []
    #     while self.arr[idx] is not None:
    #         if self.arr[idx][0] == k:
    #             values.append(self.arr[idx][1])
    #         idx = (idx + 1) % MAP_SIZE
    #
    #     return values

    def put(self, k, v):
        idx = self.hash(k)
        was_rip = False
        while self.arr[idx] is not None:
            if self.arr[idx] == (k, v):
                # print("Map: Nothing put")
                # print("Map: ", self.get_pair(k))
                return

            if not was_rip and self.arr[idx] == "0":
                was_rip = True
                rip_idx = idx

            idx = (idx + 1) % MAP_SIZE
        if was_rip:
            idx = rip_idx
        self.arr[idx] = (k, v)
        # print("Map: ", self.get_pair(k))
        # return f"({self.arr[idx][0]}, {self.arr[idx][1]})"

    def get(self, k):
        idx = self.hash(k)
        count = 0
        values = []

        while self.arr[idx] is not None:
            if self.arr[idx][0] == k:
                count += 1
                values.append(self.arr[idx][1])
            idx = (idx + 1) % MAP_SIZE

        return str(count) + ' ' + " ".join(values) + '\n'

    # return str(count) + ' ' + " ".join(values)

    def delete(self, k, v):
        idx = self.hash(k)
        while self.arr[idx] is not None:
            if self.arr[idx] == (k, v):
                self.arr[idx] = "0"
                break
            idx = (idx + 1) % MAP_SIZE

    def delete_all(self, k):
        idx = self.hash(k)
        while self.arr[idx] is not None:
            if self.arr[idx][0] == k:
                self.arr[idx] = "0"
            idx = (idx + 1) % MAP_SIZE


# def get_random_string(length):
#     letters = string.ascii_lowercase
#     result_str = ''.join(random.choice(letters) for i in range(length))
#     return result_str
    # print("Random string of length", length, "is:", result_str)


def main():
    m = Map()
    for operation in sys.stdin.buffer.readlines():
        operation = operation.decode().split()
        if operation[0] == "put":
            m.put(operation[1], operation[2])
        elif operation[0] == "get":
            sys.stdout.buffer.write(m.get(operation[1]).encode(encoding="utf-8"))
            # sys.stdout.write(f"{m.get(operation[1])}\n")
        elif operation[0] == "delete":
            m.delete(operation[1], operation[2])
        else:
            m.delete_all(operation[1])

    # commands = ['put', 'delete', 'get', 'deleteall']
    # d = {}
    #
    # n = 50000
    # for _ in range(n):
    #     string_length = random.randint(1, 5)
    #     command = random.choice(commands)
    #     random_string_key = get_random_string(string_length)
    #     if command == "put":
    #         string_length_2 = random.randint(1, 5)
    #         random_string_value = get_random_string(string_length_2)
    #         print("put", random_string_key, random_string_value)
    #         m.put(random_string_key, random_string_value)
    #         # print("Map: put ", m.put(random_string_key, random_string_value))
    #         if random_string_key in d:
    #             if random_string_value not in d[random_string_key]:
    #                 d[random_string_key].append(random_string_value)
    #                 # print(f"Dict: put ({random_string_key}, {random_string_value})")
    #             else:
    #                 print("Dict: Nothing put")
    #
    #         else:
    #             d[random_string_key] = [random_string_value]
    #             # print(f"Dict: put ({random_string_key}, {random_string_value})")
    #         print("Dict: ", d[random_string_key])
    #
    #     elif command == "get":
    #         count = 0
    #         vals = []
    #         if random_string_key in d:
    #             count = len(d[random_string_key])
    #             vals = d[random_string_key]
    #         map_count, map_values = m.get(random_string_key)
    #         if map_count != count:
    #             print(f"Dict {random_string_key}: {count}", vals)
    #             print(f"Map {random_string_key}: {map_count}", map_values)
    #             print()
    #     elif command == 'delete':
    #         string_length_2 = random.randint(1, 5)
    #         random_string_value = get_random_string(string_length_2)
    #         print("delete ", random_string_key, random_string_value)
    #         m.delete(random_string_key, random_string_value)
    #         print("Map: ", m.get_pair(random_string_key))
    #         if random_string_key in d:
    #             if random_string_value in d[random_string_key]:
    #                 d[random_string_key].remove(random_string_value)
    #             print("Dict: ", d[random_string_key])


if __name__ == "__main__":
    main()

