#include <iostream>
#include <cmath>

void Hanoi(int n) {
    int num = pow(2, n) - 1;
    for (int i = 1; i <= num; ++i) {
        int source = (i & i - 1) % 3;
        int target = ((i | i - 1) + 1) % 3;
        std::cout << "Move from " << source + 1 << " to " << target + 1 << "\n";
    }
}

int main() {
    int n;
    std::cin >> n;
    Hanoi(n);
    return 0;
}