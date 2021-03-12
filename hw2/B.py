COUNT = 101


def main():
    a = list(map(int, input().split()))
    cnt = [0] * COUNT
    for i in a:
        cnt[i] += 1
    for i in range(COUNT):
        for _ in range(cnt[i]):
            print(i, end=' ')


if __name__ == "__main__":
    main()
