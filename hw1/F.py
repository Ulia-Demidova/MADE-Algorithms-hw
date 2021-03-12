def rome_to_num(rome):
    s = 0
    if len(rome) == 1:
        return nums[rome]
    i = 0
    while i < len(rome):
        if i + 1 < len(rome) and rome[i:i + 2] in nums:
            s += nums[rome[i:i + 2]]
            i += 2
        else:
            s += nums[rome[i]]
            i += 1
    return s


nums = {
    'I': 1,
    'IV': 4,
    'V': 5,
    'IX': 9,
    'X': 10,
    'XX': 20,
    'XL': 40,
    'L': 50
}

n = int(input())
kings = []
for _ in range(n):
    kings.append(input().split())

kings.sort(key=lambda king: (king[0], rome_to_num(king[1])))
for king in kings:
    print(king[0], king[1])
