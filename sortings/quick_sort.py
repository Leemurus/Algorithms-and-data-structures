import random


def swap(arr: list, index1: int, index2: int):
    arr[index1], arr[index2] = arr[index2], arr[index1]


def partition(arr: list, l_index: int, r_index: int, pivot_index: int) -> int:
    """The main idea of partition that we need split the segment of array on
    three parts:
    the left part is less than or equal to pivot
    the middle part is pivot (returning index)
    the right part is greater than pivot
    """

    pivot = arr[pivot_index]
    swap(arr, pivot_index, r_index)

    cur_left = l_index - 1
    for cur_right in range(l_index, r_index):
        if arr[cur_right] <= pivot:
            cur_left += 1
            swap(arr, cur_left, cur_right)

    swap(arr, cur_left + 1, r_index)
    return cur_left + 1


def bubble_sort(arr: list, l_index: int, r_index: int):
    """List for sorting + range [l_index, r_index]"""

    for end_offset in range(0, r_index - l_index + 1):
        for index in range(l_index, r_index - end_offset):
            if arr[index] > arr[index + 1]:
                swap(arr, index, index + 1)


def quick_sort(arr: list, l_index: int, r_index: int):
    """List for sorting + range [l_index, r_index]"""
    if r_index - l_index < 10:
        bubble_sort(arr, l_index, r_index)
        return

    pivot_index = random.randint(l_index, r_index)
    partition_index = partition(arr, l_index, r_index, pivot_index)

    quick_sort(arr, l_index, partition_index - 1)
    quick_sort(arr, partition_index + 1, r_index)


def main():
    n = int(input())
    arr = list(map(int, input().split()))
    quick_sort(arr, 0, n - 1)
    print(*arr)


if __name__ == '__main__':
    main()
