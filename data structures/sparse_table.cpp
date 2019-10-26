#include <iostream>
#include <vector>

int a[100];
int LOG[100];
std::vector<std::vector<int>> sparse;

void build(int n) {
    for (int i = 0; i < n; i++) {
        sparse[0].push_back(a[i]);
    }
    for (int p = 1; p <= LOG[n]; p++) {
        sparse[p].resize(n - (1 << p) + 1);

        for (int i = 0; i < sparse[p].size(); i++) {
            sparse[p][i] = std::min(sparse[p - 1][i], sparse[p - 1][i + (1 << (p - 1))]);
        }
    }
}

int get_min(int l, int r) {
    int len = LOG[r - l + 1];
    return std::min(sparse[len][l], sparse[len][r - (1 << len) + 1]);
}

int main() {
    int n, m;
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 2; i <= n; i++) {
        LOG[i] = LOG[i / 2] + 1;
    }

    sparse.resize(LOG[n] + 1);
    build(n);

    while (m--) {
        int l, r;
        std::cin >> l >> r;
        std::cout << get_min(l - 1, r - 1) << std::endl;
    }
    return 0;
}