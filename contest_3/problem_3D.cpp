#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <cstdint>
#include <algorithm>

std::multiset<int64_t> small_elements;
std::multiset<int64_t> large_elements;
size_t k_statistic = 0;

void AddElement(int64_t value) {
    if (small_elements.size() < k_statistic) {
        small_elements.insert(value);
        return;
    }

    int64_t max_in_small = *small_elements.rbegin();
    if (value < max_in_small) {
        large_elements.insert(max_in_small);
        small_elements.erase(std::prev(small_elements.end()));
        small_elements.insert(value);
    } else {
        large_elements.insert(value);
    }
}

void RemoveElement(int64_t value) {
    auto it_large = large_elements.find(value);
    if (it_large != large_elements.end()) {
        large_elements.erase(it_large);
    } else {
        auto it_small = small_elements.find(value);
        if (it_small != small_elements.end()) {
            small_elements.erase(it_small);
            if (!large_elements.empty()) {
                small_elements.insert(*large_elements.begin());
                large_elements.erase(large_elements.begin());
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int32_t elements_count;
    size_t operations_count;
    std::cin >> elements_count >> operations_count >> k_statistic;

    std::vector<int64_t> sequence_values(elements_count);
    for (int32_t index = 0; index < elements_count; ++index) {
        std::cin >> sequence_values[index];
    }

    std::string operations_str;
    if (operations_count > 0) {
        std::cin >> operations_str;
    }

    int32_t left_pointer = 0;
    int32_t right_pointer = -1;

    for (char operation_char : operations_str) {
        if (operation_char == 'R') {
            right_pointer++;
            AddElement(sequence_values[right_pointer]);
        } else {
            RemoveElement(sequence_values[left_pointer]);
            left_pointer++;
        }

        if (left_pointer > right_pointer ||
            k_statistic > static_cast<size_t>(right_pointer - left_pointer + 1)) {
            std::cout << -1 << '\n';
        } else {
            std::cout << *small_elements.rbegin() << '\n';
        }
    }

    return 0;
}
