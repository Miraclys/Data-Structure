#include <bits/stdc++.h>

const int N = 105;
int n, m, f[N][N], src[N][N];

void print_path(int i, int j) {
    int k = src[i][j];
    if (k == 0) return ;
    print_path(i, k);
    std::cout << k << " ";
    print_path(k, j);
}

void init() {
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (f[i][j] > f[i][k] + f[k][j]) {
                    f[i][j] = f[i][k] + f[k][j];
                    src[i][j] = k;
                }
            }
        }
    }
}

int main() {
    std::cin >> n >> m;
    int u, v, w;
    for (int i = 1; i <= m; ++i) {
        std::cin >> u >> u >> w;
        f[u][v] = f[v][u] = w;
    }
    init();
    print_path(1, n);
    return 0;
}