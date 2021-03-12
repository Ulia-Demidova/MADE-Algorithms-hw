def main():
    n, m = map(int, input().split())
    field = [[-float("inf")] * (m + 1)]
    for _ in range(n):
        field.append([-float("inf")])
        field[-1].extend(list(map(int, input().split())))

    prev = [['Z'] * (m + 1) for _ in range(n + 1)]
    prev[1][1] = 'S'
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            if i > 1 or j > 1:
                if field[i - 1][j] > field[i][j - 1]:
                    field[i][j] += field[i - 1][j]
                    prev[i][j] = 'D'
                else:
                    field[i][j] += field[i][j - 1]
                    prev[i][j] = 'R'

    print(field[n][m])
    way = ""
    i, j = n, m
    while i > 1 or j > 1:
        way += prev[i][j]
        if prev[i][j] == 'D':
            i -= 1
        else:
            j -= 1
    print(way[::-1])


if __name__ == "__main__":
    main()