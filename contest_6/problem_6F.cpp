#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <cstdint>
#include <limits>

struct Agent {
    int64_t pos_x, pos_y;
};

long double DistSq(const Agent& first_agent, const Agent& second_agent) {
    long double diff_x = static_cast<long double>(first_agent.pos_x) - second_agent.pos_x;
    long double diff_y = static_cast<long double>(first_agent.pos_y) - second_agent.pos_y;
    return diff_x * diff_x + diff_y * diff_y;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int32_t num_agents;
    std::cin >> num_agents;

    std::vector<Agent> agents(num_agents);
    for (int32_t agent_idx = 0; agent_idx < num_agents; ++agent_idx) {
        std::cin >> agents[agent_idx].pos_x >> agents[agent_idx].pos_y;
    }

    if (num_agents <= 1) {
        std::cout << std::fixed << std::setprecision(10) << 0.0 << std::endl;
        return 0;
    }

    std::vector<long double> min_dist_to_tree_sq(num_agents,
                                                 std::numeric_limits<long double>::max());
    std::vector<bool> visited(num_agents, false);

    min_dist_to_tree_sq[0] = 0;
    long double max_edge_needed_sq = 0.0;

    for (int32_t step_idx = 0; step_idx < num_agents; ++step_idx) {
        int32_t current_agent_idx = -1;

        for (int32_t candidate_idx = 0; candidate_idx < num_agents; ++candidate_idx) {
            if (!visited[candidate_idx]) {
                if (current_agent_idx == -1 ||
                    min_dist_to_tree_sq[candidate_idx] < min_dist_to_tree_sq[current_agent_idx]) {
                    current_agent_idx = candidate_idx;
                }
            }
        }

        if (current_agent_idx == -1) {
            break;
        }

        if (min_dist_to_tree_sq[current_agent_idx] > max_edge_needed_sq) {
            max_edge_needed_sq = min_dist_to_tree_sq[current_agent_idx];
        }

        visited[current_agent_idx] = true;

        for (int32_t neighbor_idx = 0; neighbor_idx < num_agents; ++neighbor_idx) {
            if (!visited[neighbor_idx]) {
                long double dist_sq_val = DistSq(agents[current_agent_idx], agents[neighbor_idx]);
                if (dist_sq_val < min_dist_to_tree_sq[neighbor_idx]) {
                    min_dist_to_tree_sq[neighbor_idx] = dist_sq_val;
                }
            }
        }
    }

    std::cout << std::fixed << std::setprecision(10) << std::sqrt(max_edge_needed_sq) << std::endl;

    return 0;
}
