#include <iostream>
#include "./Queue&Stack.hpp"

int main() {
    Queue<int> q;
    for (const auto& i : {1, 2, 3, 4, 5}) {
        q.push(i);
    }
    while (!q.isEmpty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << std::endl;

    Stack<int> s;
    for (const auto& i : {1, 2, 3, 4, 5}) {
        s.push(i);
    }
    while (!s.isEmpty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;
    return 0;
}