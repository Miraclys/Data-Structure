#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <functional>

const int N = 1e5 + 5;
int n, m, cnt = 1, head[N], bridge[N], vis[N], ans[N], tot = 0, in[N];
int dfn[N], low[N];

struct Edge {
    int to, nxt;
} e[N];

void add(int x, int y) {
    e[++cnt].to = y;
    e[cnt].nxt = head[x];
    head[x] = cnt;
}

void Tarjan(int x, int fa) {
    low[x] = dfn[x] = ++tot;
    for (int i = head[x]; i ; i = e[i].nxt) {
        int to = e[i].to;
        if (vis[i] || to == fa) continue;
        if (!dfn[to]) {
            Tarjan(to, x);
            low[x] = std::min(low[x], low[to]);
            if (low[to] > dfn[x]) bridge[i] = true;
        } else if (dfn[x] > dfn[to]) {
            low[x] = std::min(low[x], dfn[to]);
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
        ++in[u];
        ++in[v];
    }
    int odd_vertex = 0, start = -1;
    for (int i = 1; i <= n; ++i) {
        if (in[i] & 1) {
            ++odd_vertex;
            if (start == -1) start = i;
        }
    }
    std::vector<int> ans;
    if (odd_vertex = 2 || !odd_vertex) {
        if (odd_vertex != 2) start = 1;
        ans.push_back(start);
        int tot = 0;
        memset(low, 0, sizeof (low));
        memset(dfn, 0, sizeof (dfn));
        // memset(vis, 0, sizeof (vis));
        Tarjan(start, 0);
        while (tot < m) {
            bool flag = false;
            for (int i = head[start]; i ; i = e[i].nxt) {
                if (vis[i]) continue;
                if (!bridge[i]) {
                    flag = true;
                    vis[i] = vis[i ^ 1] = 1;
                    start = e[i].to;
                    ans.push_back(start);
                    ++tot;
                    break;
                }
            }
            if (!flag) {
                for (int i = head[start]; i ; i = e[i].nxt) {
                    if (vis[i]) continue;
                    vis[i] = vis[i ^ 1] = 1;
                    start = e[i].to;
                    ans.push_back(start);
                    ++tot;
                    break;
                }
            }
            memset(low, 0, sizeof (low));
            memset(dfn, 0, sizeof (dfn));
            // memset(vis, 0, sizeof (vis));
            Tarjan(start, 0);
        }
        std::cout << ans.size() << "\n";
        for (const auto& element : ans) {
            std::cout << element << " ";
        }
    } else {
        std::cout << "Illegal!\n";
    }
    return 0;
}