#include <iostream>
#include <vector>
#include <algorithm>

const int N = 1e4 + 5;
int n, m, cnt, tot, head[N], dfn[N], low[N], s[N], top, bel[N], vis[N];

struct Edge {
    int to, nxt;
} e[N * (N - 1) / 2];

void add(int x, int y) {
    e[++cnt].to = y;
    e[cnt].nxt = head[x];
    head[x] = cnt;
}

void Tarjan(int x, int fa) {
    dfn[x] = low[x] = ++tot;
    s[++top] = x;
    vis[x] = 1;
    for (int i = head[x]; i ; i = e[i].nxt) {
        int to = e[i].to;
        if (to == fa) continue;
        if (!dfn[to]) {
            Tarjan(to, x);
            low[x] = std::min(low[x], low[to]);
        } else if (vis[to]) {
            low[x] = std::min(low[x], dfn[to]);
        }
    }
    if (low[x] == dfn[x]) {
        int y;
        while (top) {
            y = s[top--];
            bel[y] = x;
            vis[y] = 0;
            if (y == x) break;
        }
    }
}

int main() {
    std::cin >> n >> m;
    int u, v;
    for (int i = 1; i <= m; ++i) {
        std::cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    for (int i = 1; i <= n; ++i) {
        if (dfn[i]) continue;
        Tarjan(i, 0);
    }
    for (int i = 1; i <= n; ++i) {
        std::cout << i << " " << bel[i] << "\n";
    }
    return 0;
}