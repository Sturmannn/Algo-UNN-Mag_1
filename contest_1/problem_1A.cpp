#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <utility>

int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint16_t size_sequence = 0;
    std::cin >> size_sequence;

    if (size_sequence == 0) {
        return 0;
    }

    std::vector<int64_t> seq(size_sequence);
    for (uint16_t ind = 0; ind < size_sequence; ++ind) {
        std::cin >> seq[ind];
    }

    // dp[i][0] - лучший путь (вектор индексов) с шагом ВВЕРХ, заканчивающийся в i
    // dp[i][1] - лучший путь (вектор индексов) с шагом ВНИЗ, заканчивающийся в i
    std::vector<std::vector<std::vector<uint16_t>>> dp(size_sequence,
                                                       std::vector<std::vector<uint16_t>>(2));

    for (uint16_t ind = 0; ind < size_sequence; ++ind) {
        dp[ind][0] = {ind};
        dp[ind][1] = {ind};
    }

    for (uint16_t ind_i = 0; ind_i < size_sequence; ++ind_i) {
        for (uint16_t ind_j = 0; ind_j < ind_i; ++ind_j) {

            if (seq[ind_j] < seq[ind_i]) {
                auto candidate_path = dp[ind_j][1];
                candidate_path.push_back(ind_i);

                if (candidate_path.size() > dp[ind_i][0].size() ||
                    (candidate_path.size() == dp[ind_i][0].size() &&
                     candidate_path < dp[ind_i][0])) {
                    dp[ind_i][0] = std::move(candidate_path);
                }
            }

            if (seq[ind_j] > seq[ind_i]) {
                auto candidate_path = dp[ind_j][0];
                candidate_path.push_back(ind_i);

                if (candidate_path.size() > dp[ind_i][1].size() ||
                    (candidate_path.size() == dp[ind_i][1].size() &&
                     candidate_path < dp[ind_i][1])) {
                    dp[ind_i][1] = std::move(candidate_path);
                }
            }
        }
    }

    std::vector<uint16_t> best_index_path;
    if (size_sequence > 0) {
        best_index_path = dp[0][0];
    }

    for (uint16_t ind = 0; ind < size_sequence; ++ind) {
        if (dp[ind][0].size() > best_index_path.size() ||
            (dp[ind][0].size() == best_index_path.size() && dp[ind][0] < best_index_path)) {
            best_index_path = dp[ind][0];
        }
        if (dp[ind][1].size() > best_index_path.size() ||
            (dp[ind][1].size() == best_index_path.size() && dp[ind][1] < best_index_path)) {
            best_index_path = dp[ind][1];
        }
    }

    if (!best_index_path.empty()) {
        for (size_t ind = 0; ind < best_index_path.size(); ++ind) {
            std::cout << seq[best_index_path[ind]]
                      << (ind + 1 == best_index_path.size() ? "" : " ");
        }
        std::cout << '\n';
    }

    return 0;
}
