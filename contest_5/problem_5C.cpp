#include <algorithm>
#include <iostream>
#include <vector>


struct Edge {
    int to;
    int weight;
};

const int kMaxn = 50005;
const int kInf = 2000000001;

std::vector<Edge> adj[kMaxn];
int tin[kMaxn];
int low[kMaxn];
int timer;
int min_cost = kInf;

void Dfs(int current_vertex, int parent_vertex = -1) {
    tin[current_vertex] = low[current_vertex] = timer++;

    for (const auto &edge : adj[current_vertex]) {
        int neighbor_vertex = edge.to;

        if (neighbor_vertex == parent_vertex) {
            continue;
        }

        if (tin[neighbor_vertex] != -1) {
            low[current_vertex] = std::min(low[current_vertex], tin[neighbor_vertex]);
        } else {
            Dfs(neighbor_vertex, current_vertex);
            low[current_vertex] = std::min(low[current_vertex], low[neighbor_vertex]);

            if (low[neighbor_vertex] > tin[current_vertex]) {
                if (edge.weight < min_cost) {
                    min_cost = edge.weight;
                }
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int num_vertices;
    int num_edges;
    if (!(std::cin >> num_vertices >> num_edges)) {
        return 0;
    }

    for (int vertex_idx = 0; vertex_idx <= num_vertices; ++vertex_idx) {
        tin[vertex_idx] = -1;
    }

    for (int edge_idx = 0; edge_idx < num_edges; ++edge_idx) {
        int vertex_u;
        int vertex_v;
        int edge_weight;
        std::cin >> vertex_u >> vertex_v >> edge_weight;
        adj[vertex_u].push_back({vertex_v, edge_weight});
        adj[vertex_v].push_back({vertex_u, edge_weight});
    }

    timer = 0;
    Dfs(1);

    if (min_cost == kInf) {
        std::cout << -1 << std::endl;
    } else {
        std::cout << min_cost << std::endl;
    }

    return 0;
}
