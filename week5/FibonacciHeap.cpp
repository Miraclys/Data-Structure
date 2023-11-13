#include <iostream>
#include <algorithm>
#include "../FibonacciHeap.hpp"

int main() {
    int n;
    std::cin >> n;
    FibonacciHeap<int> heap;
    int opt, x;
    for (int i = 1; i <= n; ++i) {
        std::cin >> opt;
        if (opt == 1) {
            std::cin >> x;
            heap.insert(x);
        } else if (opt == 2) {
            std::cout << heap.top() << "\n";
        } else {
            heap.pop();
        }
    }
    return 0;
}