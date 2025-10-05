#include <iostream>
#include <string>
#include <stack>

int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);

    std::string input;
    std::cin >> input;

    std::stack<char> stack;

    size_t itr = 0;
    const size_t input_size = input.size();
    char top_bracket = 0;
    char current_bracket = 0;

    for (itr = 0; itr < input_size; ++itr) {
        current_bracket = input[itr];
        if (!stack.empty()) {
            top_bracket = stack.top();
            if ((current_bracket == ')' && top_bracket == '(') ||
                (current_bracket == ']' && top_bracket == '[') ||
                (current_bracket == '}' && top_bracket == '{')) {
                stack.pop();
            } else if ((current_bracket == '(') || (current_bracket == '[') ||
                       (current_bracket == '{')) {
                stack.push(current_bracket);
            } else {
                std::cout << itr << '\n';
                return 0;
            }
        } else if ((current_bracket == ')') || (current_bracket == ']') ||
                   (current_bracket == '}')) {
            std::cout << itr << '\n';
            return 0;
        } else {
            stack.push(current_bracket);
        }
    }

    if (!stack.empty()) {
        std::cout << itr << '\n';
    } else {
        std::cout << "CORRECT" << '\n';
    }
    return 0;
}
