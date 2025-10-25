#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

void Minmax(const std::vector<std::vector<size_t>> &input_pos,
            const std::vector<std::vector<size_t>> &input_neg,
            std::vector<std::pair<size_t, size_t>> &vec_of_pairs, size_t count_of_elements) {
    for (const auto &[_x, _y] : vec_of_pairs) {
        size_t minmax_ind = count_of_elements;

        size_t low = 0;
        size_t high = count_of_elements - 1;

        while (low <= high) {
            size_t mid = low + ((high - low) >> 1);
            if (input_pos[_x - 1][mid] >= input_neg[_y - 1][mid]) {
                minmax_ind = mid;
                if (mid == 0) {
                    break;
                }
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        if (minmax_ind == count_of_elements) {
            std::cout << count_of_elements << '\n';
            continue;
        } else if (minmax_ind > 0) {
            size_t minmax_current =
                std::max(input_pos[_x - 1][minmax_ind], input_neg[_y - 1][minmax_ind]);
            size_t minmax_prev =
                std::max(input_pos[_x - 1][minmax_ind - 1], input_neg[_y - 1][minmax_ind - 1]);

            if (minmax_prev < minmax_current) {
                std::cout << minmax_ind << '\n';
                continue;
            }
        }
        std::cout << minmax_ind + 1 << '\n';
    }
}

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);

    size_t increasing_array = 0;
    size_t descending_array = 0;
    size_t count_of_elements = 0;

    std::cin >> increasing_array >> descending_array >> count_of_elements;

    std::vector<std::vector<size_t>> input_pos(increasing_array,
                                               std::vector<size_t>(count_of_elements, 0));
    std::vector<std::vector<size_t>> input_neg(descending_array,
                                               std::vector<size_t>(count_of_elements, 0));

    for (size_t ind = 0; ind < increasing_array; ++ind) {
        for (size_t i = 0; i < count_of_elements; ++i) {
            std::cin >> input_pos[ind][i];
        }
    }
    for (size_t ind = 0; ind < descending_array; ++ind) {
        for (size_t i = 0; i < count_of_elements; ++i) {
            std::cin >> input_neg[ind][i];
        }
    }

    size_t pairs_count = 0;
    std::cin >> pairs_count;
    std::vector<std::pair<size_t, size_t>> vec_of_pairs(pairs_count);

    for (size_t ind = 0; ind < pairs_count; ++ind) {
        std::cin >> vec_of_pairs[ind].first >> vec_of_pairs[ind].second;
    }

    Minmax(input_pos, input_neg, vec_of_pairs, count_of_elements);

    return 0;
}
