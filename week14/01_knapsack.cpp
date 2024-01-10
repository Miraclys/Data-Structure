#include <iostream>
#include <cmath>
#include <algorithm>

const int N = 105;
int a[N], v[N], f[N];

int main() {
    int n, w;
    std::cin >> n >> w;
    for (int i = 1; i <= n; ++i) 
        std::cin >> a[i] >> v[i];
    for (int i = 1; i <= n; ++i) {
        for (int j = w; j >= a[i]; --j) {
            f[j] = std::max(f[j], f[j - a[i]] + v[i]);
        }
    }
    std::cout << f[w] << std::endl;
    return 0;
}