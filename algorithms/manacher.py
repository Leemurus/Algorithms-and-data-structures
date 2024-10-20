def calc_manacher_odd(s: str) -> list[int]:
    dp = [0] * len(s)

    l, r = 0, -1
    for index in range(len(s)):
        size = 1

        if index < r:
            size = min(r - index + 1, dp[r - index + l])

        while (
            index - size > -1
            and index + size < len(s)
            and s[index - size] == s[index + size]
        ):
            size += 1

        dp[index] = size
        if index + size - 1 > r:
            r = index + size - 1
            l = index - size + 1

    return dp


def calc_manacher_even(s: str) -> list[int]:
    dp = [0] * len(s)

    l, r = 0, -1
    for index in range(len(s)):
        size = 0

        if index < r:
            size = min(r - index + 1, dp[r - index + l + 1])

        while (
            index - size - 1 > -1
            and index + size < len(s)
            and s[index - size - 1] == s[index + size]
        ):
            size += 1

        dp[index] = size
        if index + size - 1 > r:
            r = index + size - 1
            l = index - size

    return dp


def main():
    s = input()
    dp_odd = calc_manacher_odd(s)
    dp_even = calc_manacher_even(s)

    print(f"manacher_odd({s}) = {dp_odd}")
    print(f"manacher_even({s}) = {dp_even}")


if __name__ == '__main__':
    main()
