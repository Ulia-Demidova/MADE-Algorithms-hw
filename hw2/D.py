COUNT = 26
CHAR_SHIFT = 97


def count(s, l, r):
    cnt = [0] * COUNT
    for i in range(l, r):
        cnt[ord(s[i]) - CHAR_SHIFT] += 1
    return cnt


def check(s, t):
    for i in range(len(s)):
        if s[i] > t[i]:
            return False
    return True


def idx(c):
    return ord(c) - CHAR_SHIFT


def substring_count(s, t):
    answer = 0
    t_cnt = count(t, 0, len(t))
    left = 0
    window = min(len(t), len(s))
    right = window
    sub_s_cnt = count(s, left, right)
    while left < len(s):
        if not check(sub_s_cnt, t_cnt):
            sub_s_cnt[idx(s[right - 1])] -= 1
            right -= 1
            continue
        else:
            answer += right - left
        sub_s_cnt[idx(s[left])] -= 1
        left += 1
        while right - left != window and right < len(s):
            right += 1
            sub_s_cnt[idx(s[right - 1])] += 1
    return answer


def main():
    n, m = map(int, input().split())
    s = input()
    t = input()
    print(substring_count(s, t))


if __name__ == "__main__":
    main()
