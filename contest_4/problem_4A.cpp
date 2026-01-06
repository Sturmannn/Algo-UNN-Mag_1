#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

const int64_t kModulo = 123456789;

int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int32_t elements_count;
    if (!(std::cin >> elements_count)) {
        return 1;
    }

    std::vector<int32_t> keys(elements_count);
    for (int32_t i = 0; i < elements_count; ++i) {
        std::cin >> keys[i];
    }

    std::sort(keys.begin(), keys.end());

    std::vector<std::vector<int64_t>> bst_counts(elements_count + 1,
                                                 std::vector<int64_t>(elements_count + 1, 0));

    for (int32_t i = 0; i <= elements_count; ++i) {
        bst_counts[i][0] = 1;
    }

    for (int32_t length = 1; length <= elements_count; ++length) {
        for (int32_t start_idx = 0; start_idx <= elements_count - length; ++start_idx) {
            int32_t end_idx = start_idx + length - 1;
            int64_t ways_count = 0;

            for (int32_t root_idx = start_idx; root_idx <= end_idx; ++root_idx) {
                if (root_idx > start_idx && keys[root_idx] == keys[root_idx - 1]) {
                    continue;
                }

                int32_t left_len = root_idx - start_idx;
                int32_t right_len = end_idx - root_idx;

                int64_t current_ways =
                    (bst_counts[start_idx][left_len] * bst_counts[root_idx + 1][right_len]) %
                    kModulo;

                ways_count = (ways_count + current_ways) % kModulo;
            }
            bst_counts[start_idx][length] = ways_count;
        }
    }

    std::cout << bst_counts[0][elements_count] << '\n';

    return 0;
}
