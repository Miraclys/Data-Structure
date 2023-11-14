#include <iostream>
#include "../Heap.hpp"

int main() {
    auto compareFunction = [](const int& a, const int& b) {
        if (a < b) return -1;
        else if (a == b) return 0;
        else return 1;
    };
    Heap<int> q(compareFunction);
    q.insert(2);
    q.insert(1);
    q.insert(5);
    q.insert(0);
    q.insert(-1);
    while (!q.empty()) {
        std::cout << q.top() << " " << q.size() << "\n";
        q.pop();
    }
    return 0;
}