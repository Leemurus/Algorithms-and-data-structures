#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <queue>

class Network {
private:
    const static int MAX_V = 100;

    int ptr[MAX_V];
    int dist[MAX_V];
    int source, stock;
    std::vector <int> g[MAX_V];

    struct edge {
        int v, to, cap, flow;
    };

    std::vector <edge> edges;

    bool bfs() {
        std::queue <int> q;
        std::fill(dist, dist + MAX_V, -1);

        q.push(source);
        dist[source] = 0;

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (int index_edge : g[v]) {
                int to = edges[index_edge].to;
                int cap = edges[index_edge].cap;
                int flow = edges[index_edge].flow;

                if (dist[to] == -1 && flow < cap) {
                    q.push(to);
                    dist[to] = dist[v] + 1;
                }
            }
        }
        return dist[stock] != -1;
    }

    int dfs(int v, int curr_flow) {
        if (!curr_flow) return 0;
        if (v == stock) return curr_flow;

        for (; ptr[v] < g[v].size(); ptr[v]++) {
            int index_edge = g[v][ptr[v]];
            int to = edges[index_edge].to;
            int cap = edges[index_edge].cap;
            int flow = edges[index_edge].flow;

            if (dist[v] + 1 != dist[to]) {
                continue;
            }

            int pushed = dfs(to, std::min(curr_flow, cap - flow));
            if (pushed) {
                edges[index_edge].flow += pushed;
                edges[index_edge ^ 1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }
public:
    Network (int source, int stock) : source(source), stock(stock) {}

    void add_edge(int v, int to, int cap) {
        edge straight = {v, to, cap, 0};
        edge opposite = {to, v, 0, 0};

        g[v].push_back(edges.size());
        edges.push_back(straight);

        g[to].push_back(edges.size());
        edges.push_back(opposite);
    }

    int max_flow() {
        int result = 0;
        while (bfs()) {
            std::fill(ptr, ptr + MAX_V, 0);
            while (int pushed = dfs(source, INT_MAX)) {
                result += pushed;
            }
        }
        return result;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;

    Network network(0, n - 1);
    while (m--) {
        int v, to, cap;
        std::cin >> v >> to >> cap;
        network.add_edge(v - 1, to - 1, cap);
    }

    std::cout << network.max_flow();

    return 0;
}