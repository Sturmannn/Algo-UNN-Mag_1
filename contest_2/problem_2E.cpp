#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

const int64_t kInfinity = 1e18;

struct Coin {
    int32_t position;
    int32_t deadline;

    bool operator<(const Coin& other) const {
        return position < other.position;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int32_t num_coins;
    std::cin >> num_coins;

    std::vector<Coin> coins(num_coins);
    for (int32_t coin_idx = 0; coin_idx < num_coins; ++coin_idx) {
        std::cin >> coins[coin_idx].position >> coins[coin_idx].deadline;
    }

    std::sort(coins.begin(), coins.end());

    std::vector<std::vector<std::vector<int64_t>>> dp(
        num_coins,
        std::vector<std::vector<int64_t>>(num_coins, std::vector<int64_t>(2, kInfinity)));

    for (int32_t coin_idx = 0; coin_idx < num_coins; ++coin_idx) {
        if (0 <= coins[coin_idx].deadline) {
            dp[coin_idx][coin_idx][0] = 0;
            dp[coin_idx][coin_idx][1] = 0;
        }
    }

    for (int32_t length = 2; length <= num_coins; ++length) {
        for (int32_t left_bound = 0; left_bound <= num_coins - length; ++left_bound) {
            int32_t right_bound = left_bound + length - 1;

            int64_t time_from_left = dp[left_bound + 1][right_bound][0] +
                                     (coins[left_bound + 1].position - coins[left_bound].position);
            int64_t time_from_right = dp[left_bound + 1][right_bound][1] +
                                      (coins[right_bound].position - coins[left_bound].position);

            int64_t min_time_to_i = std::min(time_from_left, time_from_right);
            if (min_time_to_i <= coins[left_bound].deadline) {
                dp[left_bound][right_bound][0] = min_time_to_i;
            }

            time_from_left = dp[left_bound][right_bound - 1][0] +
                             (coins[right_bound].position - coins[left_bound].position);
            time_from_right = dp[left_bound][right_bound - 1][1] +
                              (coins[right_bound].position - coins[right_bound - 1].position);

            int64_t min_time_to_j = std::min(time_from_left, time_from_right);
            if (min_time_to_j <= coins[right_bound].deadline) {
                dp[left_bound][right_bound][1] = min_time_to_j;
            }
        }
    }

    int64_t result = std::min(dp[0][num_coins - 1][0], dp[0][num_coins - 1][1]);

    if (result >= kInfinity) {
        std::cout << "No solution" << '\n';
    } else {
        std::cout << result << '\n';
    }

    return 0;
}
