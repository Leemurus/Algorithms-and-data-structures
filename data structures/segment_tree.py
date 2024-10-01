class SegmentTree:
    def __init__(self, arr: list[int]):
        self._size = len(arr)
        self._tree = [0] * 4 * self.size
        self._build(arr=arr, v=1, tl=0, tr=self.size - 1)
        
    @property
    def size(self) -> int:
        return self._size

    def _build(self, arr: list[int], v: int, tl: int, tr: int):
        if tl == tr:
            self._tree[v] = arr[tl]
            return

        tm = (tl + tr) // 2
        self._build(arr=arr, v=v * 2, tl=tl, tr=tm)
        self._build(arr=arr, v=v * 2 + 1, tl=tm + 1, tr=tr)
        self._tree[v] = self._tree[v * 2] + self._tree[v * 2 + 1]

    def _get_sum(self, v: int, tl: int, tr: int, l: int, r: int) -> int:
        if l > r:
            return 0

        if l == tl and r == tr:
            return self._tree[v]

        tm = (tl + tr) // 2
        left_sum = self._get_sum(v=v * 2, tl=tl, tr=tm, l=l, r=min(r, tm))
        right_sum = self._get_sum(
            v=v * 2 + 1, tl=tm + 1, tr=tr, l=max(l, tm + 1), r=r
        )

        return left_sum + right_sum

    def get_sum(self, l: int, r: int) -> int:
        return self._get_sum(v=1, tl=0, tr=self.size - 1, l=l, r=r)

    def _update(self, v: int, tl: int, tr: int, index: int, value: int):
        if tl == tr:
            self._tree[v] = value
            return

        tm = (tl + tr) // 2
        if index <= tm:
            self._update(v=v * 2, tl=tl, tr=tm, index=index, value=value)
        else:
            self._update(
                v=v * 2 + 1, tl=tm + 1, tr=tr, index=index, value=value
            )
        self._tree[v] = self._tree[v * 2] + self._tree[v * 2 + 1]

    def update(self, index: int, value: int):
        self._update(v=1, tl=0, tr=self.size - 1, index=index, value=value)


def main():
    tree = SegmentTree(arr=[1, 2, 3, 4, 5, 6])

    print(tree.get_sum(0, 3))
    print(tree.update(3, 1))
    print(tree.get_sum(0, 3))


if __name__ == "__main__":
    main()
