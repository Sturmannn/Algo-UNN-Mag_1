#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <random>
#include <chrono>
#include <cstdint>

std::mt19937 random_generator(std::chrono::high_resolution_clock::now().time_since_epoch().count());

struct Node {
    char key_char;
    int32_t priority_val;
    int32_t subtree_size;
    std::shared_ptr<Node> left_child, right_child;

    explicit Node(char char_val)
        : key_char(char_val),
          priority_val(random_generator()),
          subtree_size(1),
          left_child(nullptr),
          right_child(nullptr) {
    }
};

using NodePtr = std::shared_ptr<Node>;

int32_t GetSize(NodePtr node_ptr) {
    return node_ptr ? node_ptr->subtree_size : 0;
}

void UpdateSize(NodePtr node_ptr) {
    if (node_ptr) {
        node_ptr->subtree_size = 1 + GetSize(node_ptr->left_child) + GetSize(node_ptr->right_child);
    }
}

void Split(NodePtr tree_node, int32_t position, NodePtr& left_tree, NodePtr& right_tree) {
    if (!tree_node) {
        left_tree = right_tree = nullptr;
        return;
    }
    int32_t left_size = GetSize(tree_node->left_child);
    if (position <= left_size) {
        Split(tree_node->left_child, position, left_tree, tree_node->left_child);
        right_tree = tree_node;
    } else {
        Split(tree_node->right_child, position - left_size - 1, tree_node->right_child, right_tree);
        left_tree = tree_node;
    }
    UpdateSize(tree_node);
}

NodePtr Merge(NodePtr left_tree, NodePtr right_tree) {
    if (!left_tree || !right_tree) {
        return left_tree ? left_tree : right_tree;
    }
    if (left_tree->priority_val > right_tree->priority_val) {
        left_tree->right_child = Merge(left_tree->right_child, right_tree);
        UpdateSize(left_tree);
        return left_tree;
    } else {
        right_tree->left_child = Merge(left_tree, right_tree->left_child);
        UpdateSize(right_tree);
        return right_tree;
    }
}

void PrintTreap(NodePtr tree_node) {
    if (!tree_node) {
        return;
    }
    PrintTreap(tree_node->left_child);
    std::cout << tree_node->key_char;
    PrintTreap(tree_node->right_child);
}

struct ShiftOperation {
    int32_t start_index, end_index, shift_amount;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string final_string;
    std::cin >> final_string;

    int32_t num_operations;
    std::cin >> num_operations;

    std::vector<ShiftOperation> operations(num_operations);
    for (int32_t op_idx = 0; op_idx < num_operations; ++op_idx) {
        std::cin >> operations[op_idx].start_index >> operations[op_idx].end_index >>
            operations[op_idx].shift_amount;
    }

    NodePtr root_node = nullptr;
    for (char character : final_string) {
        root_node = Merge(root_node, std::make_shared<Node>(character));
    }

    for (int32_t op_idx = num_operations - 1; op_idx >= 0; --op_idx) {
        int32_t range_start = operations[op_idx].start_index - 1;
        int32_t range_end = operations[op_idx].end_index - 1;
        int32_t shift_val = operations[op_idx].shift_amount;

        int32_t range_length = range_end - range_start + 1;
        if (range_length <= 1) {
            continue;
        }

        int32_t actual_shift = shift_val % range_length;
        int32_t right_shift_val = range_length - actual_shift;
        if (right_shift_val == range_length) {
            right_shift_val = 0;
        }

        if (right_shift_val == 0) {
            continue;
        }

        NodePtr prefix_tree, middle_tree, suffix_tree;
        NodePtr middle_prefix, middle_suffix;

        Split(root_node, range_end + 1, prefix_tree, suffix_tree);
        Split(prefix_tree, range_start, prefix_tree, middle_tree);

        Split(middle_tree, range_length - right_shift_val, middle_prefix, middle_suffix);
        middle_tree = Merge(middle_suffix, middle_prefix);

        root_node = Merge(prefix_tree, middle_tree);
        root_node = Merge(root_node, suffix_tree);
    }

    PrintTreap(root_node);
    std::cout << '\n';

    return 0;
}
