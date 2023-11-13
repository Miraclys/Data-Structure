#include <iostream>
#include <algorithm>

const int N = 105;
int n, a[N];

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
        a[i] = i;
    do {
        for (int i = 1; i <= n; ++i)
            std::cout << a[i];
        std::cout << "\n";
    } while (std::next_permutation(a + 1, a + 1 + n));
    return 0;
}