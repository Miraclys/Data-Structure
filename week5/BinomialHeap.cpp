#include "../BinomialHeap.hpp"
#include <iostream>

int main() {
    BinomialHeap<int> heap;
    heap.insert(5);
    heap.insert(3);
    heap.insert(7);
    heap.insert(2);
    heap.insert(1); 
    std::cout << heap.top() << "\n";
    heap.pop();
    std::cout << heap.top() << "\n";
    heap.pop();
    std::cout << heap.top() << "\n";
    heap.pop();
    std::cout << heap.top() << "\n";
    heap.pop();
    std::cout << heap.top() << "\n";
    return 0;
}