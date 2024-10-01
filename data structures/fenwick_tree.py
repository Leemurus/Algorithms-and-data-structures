class FenwickTree:
    def __init__(self, arr: list[int]):
        self.size = len(arr)
        self.arr = arr
        self.tree = [0] * self.size
        self._build(arr)

    def _build(self, arr: list[int]):
        for index in range(len(arr)):
            self._inc(index, arr[index])

    def _inc(self, index: int, delta: int):
        while index < self.size:
            self.tree[index] += delta
            index |= index + 1

    def _get_prefix_sum(self, index: int) -> int:
        result = 0

        while index > -1:
            result += self.tree[index]
            index = (index & (index + 1)) - 1

        return result

    def get_sum(self, l: int, r: int) -> int:
        return self._get_prefix_sum(r) - self._get_prefix_sum(l - 1)

    def update(self, index: int, value: int):
        self._inc(index, value - self.arr[index])
        self.arr[index] = value


def main():
    tree = FenwickTree(arr=[1, 2, 3, 4, 5, 6])

    print(tree.get_sum(0, 3))
    print(tree.update(3, 1))
    print(tree.get_sum(0, 3))


if __name__ == "__main__":
    main()
