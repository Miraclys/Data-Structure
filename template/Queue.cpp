#include "Queue.hpp"

int main() {
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    std::cout << q << std::endl;
    q.dequeue();
    std::cout << q << std::endl;
    std::cout << q.size() << std::endl;
    return 0;
}