#include <iostream>

void solveHanoi(int n, char source, char target, char auxiliary) {
    if (n == 1) {
        std::cout << "Move from " << source << " to " << target << std::endl;
        return ;
    }
    solveHanoi(n - 1, source, auxiliary, target);
    solveHanoi(1, source, target, auxiliary);
    solveHanoi(n - 1, auxiliary, target, source);
}

int main() {
    int n;
    std::cin >> n;
    solveHanoi(n, 'a', 'c', 'b');
    return 0;
}