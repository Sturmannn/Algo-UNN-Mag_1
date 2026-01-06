#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using CalcType = int64_t;
const CalcType kModConst = 123456789;

void SolveProblem() {
    int num_nodes;
    if (!(std::cin >> num_nodes)) {
        return;
    }

    std::vector<int> values(num_nodes);
    for (int i = 0; i < num_nodes; ++i) {
        std::cin >> values[i];
    }

    std::sort(values.begin(), values.end());

    std::vector<std::vector<CalcType>> memo(num_nodes + 2, std::vector<CalcType>(num_nodes + 2, 1));

    for (int range_len = 1; range_len <= num_nodes; ++range_len) {
        for (int left = 0; left <= num_nodes - range_len; ++left) {
            int right = left + range_len - 1;
            CalcType combinations = 0;

            for (int root = left; root <= right; ++root) {
                if (root == left || values[root] != values[root - 1]) {
                    CalcType left_sub = memo[left][root - 1];
                    CalcType right_sub = memo[root + 1][right];

                    CalcType current_trees = (left_sub * right_sub) % kModConst;
                    combinations = (combinations + current_trees) % kModConst;
                }
            }
            memo[left][right] = combinations;
        }
    }

    if (num_nodes > 0) {
        std::cout << memo[0][num_nodes - 1] << '\n';
    } else {
        std::cout << 0 << '\n';
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    SolveProblem();
    return 0;
}
