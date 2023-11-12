#include "./week9/SkipList.hpp"

int main() {
    Skiplist s;
    
    s.add(1);
    s.add(1);
    std::cout << s.search(1);
    s.erase(1);
    std::cout << s.search(1);
    s.erase(1);
    std::cout << s.search(1);
    return 0;
}