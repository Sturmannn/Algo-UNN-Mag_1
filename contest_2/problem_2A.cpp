#include <iostream>
#include <vector>
#include <cstdint>
#include <deque>

int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t array_size = 0;
    std::cin >> array_size;

    std::vector<int32_t> array(array_size);

    for (size_t ind = 0; ind < array_size; ++ind) {
        std::cin >> array[ind];
    }

    size_t shift_count = 0;
    std::cin >> shift_count;

    std::deque<size_t> dq;

    dq.push_back(0);

    size_t left = 0;
    size_t right = 0;

    for (size_t ind = 0; ind < shift_count; ++ind) {
        char sym;
        std::cin >> sym;

        if (sym == 'R') {
            right++;

            while (!dq.empty() && array[dq.back()] <= array[right]) {
                dq.pop_back();
            }

            dq.push_back(right);
        } else {
            left++;

            if (!dq.empty() && dq.front() < left) {
                dq.pop_front();
            }
        }

        std::cout << array[dq.front()] << (ind == shift_count - 1 ? '\n' : ' ');
    }

    return 0;
}
