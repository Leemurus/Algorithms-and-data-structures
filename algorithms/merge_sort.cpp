#include <iostream>

const int N = 300500;
int a[N];
int temp[N];

void merge(int l, int r, int a[]) {
    int p_newarr = 0;
    int mid = (l + r) / 2;
    int pl = l, pr = mid + 1;

    while (!(pl == mid + 1 && pr == r + 1)) {
        if (pl != mid + 1 && pr == r + 1) {
            temp[p_newarr++] = a[pl++];
        }
        else if (pl != mid + 1 && pr != r + 1) {
            if (a[pl] <= a[pr]) {
                temp[p_newarr++] = a[pl++];
            }
            else if (a[pl] > a[pr]) {
                temp[p_newarr++] = a[pr++];
            }
        }
        else if (pl == mid + 1 && pr != r + 1) {
            temp[p_newarr++] = a[pr++];
        }
    }

    for (int i = l; i <= r; i++) {
        a[i] = temp[i - l];
    }
}

void merge_sort(int l, int r, int a[]) {
    if (l == r) {
        return;
    }

    int mid = (l + r) / 2;
    merge_sort(l, mid, a);
    merge_sort(mid + 1, r, a);

    merge(l, r, a);
}

int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    merge_sort(0, n - 1, a);

    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " ";
    }

    return 0;
}