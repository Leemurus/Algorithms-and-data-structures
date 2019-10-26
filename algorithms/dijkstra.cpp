#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <set>

long long d[30000];
std::vector <std::vector <std::pair <int, long long >> > g;

void dijkstra(int start) {
    std::set <std::pair <long long, int>> s;
    std::fill(d, d + g.size(), LLONG_MAX);

    d[start] = 0;
    s.insert(std::make_pair(0, start));

    while (s.size()) {
        int vertex = s.begin() -> second;
        s.erase(s.begin());

        for (auto to : g[vertex]) {
            if (d[vertex] + to.second < d[to.first]) {
                s.erase(std::make_pair(d[to.first], to.first));
                d[to.first] = d[vertex] + to.second;
                s.insert(std::make_pair(d[to.first], to.first));
            }
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    g.resize(n);
    while (m--) {
        int v, to, w;
        std::cin >> v >> to >> w;
        g[v - 1].push_back(std::make_pair(to - 1, w));
        g[to - 1].push_back(std::make_pair(v - 1, w));
    }

    dijkstra(0);

    for (int i = 0; i < n; i++) {
        std::cout << d[i] << " ";
    }

    return 0;
}