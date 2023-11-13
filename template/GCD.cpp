#include <iostream>

int x, y;

void exgcd(int a, int b) {
    if (b == 0) {
        x = 1;
        y = 0;
        return ;
    }
    exgcd(b, a % b);
    int temp = x;
    x = y;
    y = temp - (a / b) * y;
}

int main() {
    int a, b;
    std::cin >> a >> b;
    exgcd(a, b);
    std::cout << x << " " << y << std::endl;
    std::cout << (x % b + b) % b << std::endl;
    return 0;
}