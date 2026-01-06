#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

struct Edge {
    int32_t from_node;
    int32_t to_node;
    int32_t weight_val;
};

const int32_t kMaxN = 10005;

int32_t parent_nodes[kMaxN];
int32_t set_sizes[kMaxN];

int32_t FindSet(int32_t node_index) {
    if (node_index == parent_nodes[node_index]) {
        return node_index;
    }
    return parent_nodes[node_index] = FindSet(parent_nodes[node_index]);
}

void UnionSets(int32_t first_set, int32_t second_set) {
    first_set = FindSet(first_set);
    second_set = FindSet(second_set);
    if (first_set != second_set) {
        if (set_sizes[first_set] < set_sizes[second_set]) {
            std::swap(first_set, second_set);
        }
        parent_nodes[second_set] = first_set;
        set_sizes[first_set] += set_sizes[second_set];
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int32_t num_nodes;
    int32_t num_edges;
    if (!(std::cin >> num_nodes >> num_edges)) {
        return 0;
    }

    std::vector<Edge> edges(num_edges);
    for (int32_t edge_idx = 0; edge_idx < num_edges; ++edge_idx) {
        std::cin >> edges[edge_idx].from_node >> edges[edge_idx].to_node >>
            edges[edge_idx].weight_val;
    }

    std::sort(edges.begin(), edges.end(), [](const Edge& edge_a, const Edge& edge_b) {
        return edge_a.weight_val < edge_b.weight_val;
    });

    for (int32_t node_idx = 1; node_idx <= num_nodes; ++node_idx) {
        parent_nodes[node_idx] = node_idx;
        set_sizes[node_idx] = 1;
    }

    int32_t max_weight = 0;
    int32_t edges_count = 0;

    for (const auto& edge : edges) {
        if (FindSet(edge.from_node) != FindSet(edge.to_node)) {
            UnionSets(edge.from_node, edge.to_node);
            max_weight = edge.weight_val;
            edges_count++;
            if (edges_count == num_nodes - 1) {
                break;
            }
        }
    }

    std::cout << max_weight << std::endl;

    return 0;
}