#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cstdint>
#include <cmath>
#include <random>
#include <chrono>

struct CustomRandomGenerator {
    uint32_t mult_coeff;
    uint32_t add_coeff;
    uint32_t current_state = 0;

    uint32_t GetNext24bit() {
        current_state = current_state * mult_coeff + add_coeff;
        return current_state >> 8;
    }

    uint32_t GetNext32bit() {
        uint32_t part_one = GetNext24bit();
        uint32_t part_two = GetNext24bit();
        return (part_one << 8) ^ part_two;
    }
};

int32_t HoarePartition(std::vector<uint32_t>& data, int32_t low_idx, int32_t high_idx) {
    const uint32_t pivot_value = data[low_idx];
    int32_t left_iterator = low_idx;
    int32_t right_iterator = high_idx;

    while (left_iterator <= right_iterator) {
        while (data[left_iterator] < pivot_value) {
            left_iterator++;
        }

        while (data[right_iterator] > pivot_value) {
            right_iterator--;
        }

        if (left_iterator <= right_iterator) {
            std::swap(data[left_iterator], data[right_iterator]);
            left_iterator++;
            right_iterator--;
        }
    }
    return right_iterator;
}

uint32_t FindKthSmallest(std::vector<uint32_t>& data, int32_t k_index) {
    int32_t low_bound = 0;
    int32_t high_bound = data.size() - 1;

    std::mt19937 random_gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());

    while (low_bound < high_bound) {
        std::uniform_int_distribution<int32_t> pivot_dist(low_bound, high_bound);
        int32_t pivot_idx_to_move = pivot_dist(random_gen);
        std::swap(data[low_bound], data[pivot_idx_to_move]);

        int32_t split_index = HoarePartition(data, low_bound, high_bound);

        if (k_index <= split_index) {
            high_bound = split_index;
        } else {
            low_bound = split_index + 1;
        }
    }
    return data[k_index];
}

void Solve() {
    int32_t num_points;
    std::cin >> num_points;

    CustomRandomGenerator generator;
    std::cin >> generator.mult_coeff >> generator.add_coeff;

    std::vector<uint32_t> points(num_points);
    for (int32_t index = 0; index < num_points; ++index) {
        points[index] = generator.GetNext32bit();
    }

    if (num_points == 0) {
        std::cout << 0 << '\n';
        return;
    }

    const int32_t median_index = num_points / 2;
    const uint32_t median_value = FindKthSmallest(points, median_index);

    uint64_t total_distance = 0;
    for (size_t index = 0; index < points.size(); ++index) {
        total_distance +=
            std::abs(static_cast<int64_t>(points[index]) - static_cast<int64_t>(median_value));
    }

    std::cout << total_distance << '\n';
}

int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    Solve();
    return 0;
}
