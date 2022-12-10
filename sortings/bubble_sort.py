def bubble_sort(arr: list, l_index: int, r_index: int):
    """List for sorting + range [l_index, r_index]"""

    for end_offset in range(0, r_index - l_index + 1):
        for index in range(l_index, r_index - end_offset):
            if arr[index] > arr[index + 1]:
                arr[index], arr[index + 1] = arr[index + 1], arr[index]


def main():
    n = int(input())
    arr = list(map(int, input().split()))
    bubble_sort(arr, 0, n - 1)
    print(*arr)


if __name__ == '__main__':
    main()
