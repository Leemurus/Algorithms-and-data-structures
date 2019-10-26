#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

struct Edge{
    int from, to;
    long long weight;

    Edge () {}

    Edge (int from, int to, long long weight) : from(from), to(to), weight(weight) {}
};

std::vector<std::vector<int>> get_list(const std::vector<Edge> &edges, int n, bool rev) {
    std::vector<std::vector<int>> graph(n);
    for (Edge edge : edges) {
        if (rev) {
            graph[edge.to].push_back(edge.from);
        } else {
            graph[edge.from].push_back(edge.to);
        }
    }

    return graph;
}

void dfs(int v, const std::vector<std::vector<int>> &graph, std::vector<bool> &used) {
    used[v] = true;

    for (int to : graph[v]) {
        if (!used[to]) {
            dfs(to, graph, used);
        }
    }
}

bool reachability(int root, int n, const std::vector<Edge> &edges) {
    std::vector<bool> used(n, false);

    std::vector<std::vector< int >> graph = get_list(edges, n, false);
    dfs(root, graph, used);

    for (Edge edge : edges) {
        if (!used[edge.from] || !used[edge.to]) {
            return false;
        }
    }

    return true;
}

bool all_reachability(int root, int n, const std::vector<Edge> &edges) {
    std::vector<bool> used(n, false);

    std::vector < std::vector<int>> graph = get_list(edges, n, false);
    dfs(root, graph, used);

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            return false;
        }
    }

    return true;
}

void first_by_pass(int v, const std::vector < std::vector<int>> &graph, std::vector<bool> &used,
        std::vector<int> &list) {
    used[v] = true;

    for (int to : graph[v]) {
        if (!used[to]) {
            first_by_pass(to, graph, used, list);
        }
    }

    list.push_back(v);
}

void second_by_pass(int v, int comp_num, const std::vector < std::vector<int>> &graph,
                    std::vector<bool> &used, std::vector<int> &component) {
    if (comp_num == -1) {
        comp_num = v;
    }
    component[v] = comp_num;
    used[v] = true;

    for (int to : graph[v]) {
        if (!used[to]) {
            second_by_pass(to, comp_num, graph, used, component);
        }
    }
}

std::vector<int> condensation(std::vector<Edge> &edges, int n) {
    std::vector<int> list;
    std::vector<bool> used(n, false);

    std::vector < std::vector<int>> graph = get_list(edges, n, false);
    for (Edge edge : edges) {
        if (!used[edge.from]) {
            first_by_pass(edge.from, graph, used, list);
        }
    }

    std::vector<int> component(n);
    std::reverse(list.begin(), list.end());
    std::fill(used.begin(), used.end(), false);
    for (int i = 0; i < n; i++) {
        component[i] = i;
    }

    graph = get_list(edges, n, true);
    for (int vertex : list) {
        if (!used[vertex]) {
            second_by_pass(vertex, -1, graph, used, component);
        }
    }

    return component;
}

long long mst(const std::vector<Edge> &edges, int n, int root) {
    long long result = 0;
    std::vector < long long > min_edge(n, LLONG_MAX);

    for (Edge edge : edges) {
        min_edge[edge.to] = std::min(edge.weight, min_edge[edge.to]);
    }

    for (int i = 0; i < n; i++) {
        if (min_edge[i] != LLONG_MAX && i != root) {
            result += min_edge[i];
        }
    }

    std::vector<Edge> zeroedges;
    for (Edge edge : edges) {
        if (edge.weight == min_edge[edge.to]) {
            zeroedges.push_back(edge);
        }
    }

    if (reachability(root, n, zeroedges)) {
        return result;
    } else {
        std::vector<Edge> new_edges;
        std::vector<int> new_components;

        new_components = condensation(zeroedges, n);

        for (Edge edge : edges) {
            if (new_components[edge.from] != new_components[edge.to]) {
                edge.from = new_components[edge.from];
                edge.weight -= min_edge[edge.to];
                edge.to = new_components[edge.to];
                new_edges.push_back(edge);
            }
        }

        result += mst(new_edges, n, new_components[root]);

        return result;
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector <Edge> edges;
    while (m--) {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        edges.push_back(Edge(from - 1, to - 1, weight));
    }

    if (all_reachability(0, n, edges)) {
        std::cout << "YES" << std::endl << mst(edges, n, 0);
    } else {
        std::cout << "NO";
    }
    return 0;
}