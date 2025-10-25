#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

struct HeapNode {
    int32_t m_value;
    uint16_t m_array_ind;
    uint16_t m_elem_ind;

    HeapNode(int32_t value, uint16_t array_ind, uint16_t elem_ind)
        : m_value(value), m_array_ind(array_ind), m_elem_ind(elem_ind) {
    }

    bool operator<(const HeapNode& other) const {
        return m_value < other.m_value;
    }
};

class MinHeap {
private:
    std::vector<HeapNode> m_heap_data_;

    uint16_t Parent(uint16_t ind) {
        return (ind - 1) / 2;
    }
    uint16_t LeftChild(uint16_t ind) {
        return 2 * ind + 1;
    }
    uint16_t RightChild(uint16_t ind) {
        return 2 * ind + 2;
    }

    void Up(uint16_t index) {
        while (index > 0 && m_heap_data_[index] < m_heap_data_[Parent(index)]) {
            std::swap(m_heap_data_[index], m_heap_data_[Parent(index)]);
            index = Parent(index);
        }
    }

    void Down(uint16_t index) {
        while (LeftChild(index) < m_heap_data_.size()) {
            uint16_t smaller_child_index = LeftChild(index);
            uint16_t right_child_index = RightChild(index);

            if (right_child_index < m_heap_data_.size() &&
                m_heap_data_[right_child_index] < m_heap_data_[smaller_child_index]) {
                smaller_child_index = right_child_index;
            }

            if (!(m_heap_data_[smaller_child_index] < m_heap_data_[index])) {
                break;
            }

            std::swap(m_heap_data_[index], m_heap_data_[smaller_child_index]);
            index = smaller_child_index;
        }
    }

public:
    MinHeap() = default;

    bool Empty() const {
        return m_heap_data_.empty();
    }

    void Emplace(int32_t val, uint16_t s_idx, uint16_t e_idx) {
        m_heap_data_.emplace_back(val, s_idx, e_idx);
        Up(m_heap_data_.size() - 1);
    }

    const HeapNode& Top() const {
        return m_heap_data_[0];
    }

    void Pop() {
        m_heap_data_[0] = m_heap_data_.back();
        m_heap_data_.pop_back();

        if (!m_heap_data_.empty()) {
            Down(0);
        }
    }
};

int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint16_t arrays_count = 0;
    uint16_t arrays_size = 0;

    std::cin >> arrays_count >> arrays_size;

    if (arrays_count == 0 || arrays_size == 0) {
        return 0;
    }

    std::vector<std::vector<int32_t>> arrays(arrays_count, std::vector<int32_t>(arrays_size));

    for (size_t ind_i = 0; ind_i < arrays_count; ++ind_i) {
        for (size_t ind_j = 0; ind_j < arrays_size; ++ind_j) {
            std::cin >> arrays[ind_i][ind_j];
        }
    }

    MinHeap min_heap;

    for (uint16_t ind = 0; ind < arrays_count; ++ind) {
        min_heap.Emplace(arrays[ind][0], ind, 0);
    }

    std::vector<int32_t> result_vector;
    result_vector.reserve(arrays_count * arrays_size);

    while (!min_heap.Empty()) {
        HeapNode top_node = min_heap.Top();
        min_heap.Pop();

        result_vector.push_back(top_node.m_value);

        uint16_t next_el = top_node.m_elem_ind + 1;
        if (next_el < arrays_size) {
            min_heap.Emplace(arrays[top_node.m_array_ind][next_el], top_node.m_array_ind, next_el);
        }
    }

    for (size_t ind = 0; ind < result_vector.size(); ++ind) {
        std::cout << result_vector[ind] << (ind == result_vector.size() - 1 ? '\n' : ' ');
    }

    return 0;
}
