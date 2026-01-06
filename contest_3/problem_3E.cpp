#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <array>
#include <cstdint>

using TriangleSides = std::array<int64_t, 3>;

constexpr size_t kBucketCount = 1000003;

size_t CalculateHash(const TriangleSides& sides) {
    constexpr size_t kPrimeMultiplier = 31;
    size_t hash_value = 0;
    hash_value = hash_value * kPrimeMultiplier + std::hash<int64_t>{}(sides[0]);
    hash_value = hash_value * kPrimeMultiplier + std::hash<int64_t>{}(sides[1]);
    hash_value = hash_value * kPrimeMultiplier + std::hash<int64_t>{}(sides[2]);
    return hash_value;
}

int64_t GcdThree(int64_t a, int64_t b, int64_t c) {
    return std::gcd(std::gcd(a, b), c);
}

void Solve() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int32_t triangle_count;
    std::cin >> triangle_count;

    std::vector<std::vector<TriangleSides>> buckets(kBucketCount);
    int32_t unique_classes_count = 0;

    for (int32_t ind = 0; ind < triangle_count; ++ind) {
        TriangleSides current_sides;
        std::cin >> current_sides[0] >> current_sides[1] >> current_sides[2];

        std::sort(current_sides.begin(), current_sides.end());

        const int64_t common_divisor =
            GcdThree(current_sides[0], current_sides[1], current_sides[2]);

        current_sides[0] /= common_divisor;
        current_sides[1] /= common_divisor;
        current_sides[2] /= common_divisor;

        const size_t bucket_index = CalculateHash(current_sides) % kBucketCount;

        bool is_found = false;
        for (const TriangleSides& existing_triangle : buckets[bucket_index]) {
            if (existing_triangle == current_sides) {
                is_found = true;
                break;
            }
        }

        if (!is_found) {
            buckets[bucket_index].push_back(current_sides);
            unique_classes_count++;
        }
    }

    std::cout << unique_classes_count << '\n';
}

int main() {
    Solve();
    return 0;
}
