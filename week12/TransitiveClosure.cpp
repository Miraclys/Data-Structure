#include <iostream>
#include <algorithm>
#include <bitset>

const int N = 105;
int n;
std::bitset<N> g[N];

int main() {
    std::cin >> n;
    int x;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            std::cin >> x;
            g[i][j] = x;
        }
    }
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            if (!g[i][k]) continue;
            g[i] |= g[k];
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            x = g[i][j];
            std::cout << x << " ";
        }
        std::cout << "\n";
    }
    return 0;
}