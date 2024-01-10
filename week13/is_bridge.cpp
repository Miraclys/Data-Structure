#include <bits/stdc++.h>

const int N = 105;
std::vector<int> v[N];
int vis[N];

struct Edge {
    int u, v;
} e[N];
int cnt;

bool is_bridge(int u, int t) {
    if (u == t) return false;
    for (auto i : v[u]) {
        if (i == t) continue;
        if (vis[i]) continue;
        if (!is_bridge(i, t)) return false;
    }
    return true;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    int u, t;
    for (int i = 1; i <= m; ++i) {
        std::cin >> u >> t;
        v[u].push_back(t);
        e[++cnt].u = u;
        e[cnt].v = t;
    }
    for (int i = 1; i <= cnt; ++i) {
        std::cout << is_bridge(e[i].u, e[i].v) << std::endl;
    }
    return 0;
}