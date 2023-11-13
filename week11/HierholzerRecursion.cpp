#include <iostream>
#include <vector>
#include <algorithm>

const int N = 1e5 + 5;

int n, m, in[N], vis = 0, top = 0;

std::vector<int> g[N], ans;

void dfs(int id) {
    while (!g[id].empty()) {
        int v = g[id].back();
        g[id].pop_back();
        dfs(v);
    }
    ans.push_back(id);
    ++top;
}

int main() {
    std::cin >> n >> m;
    int u, v;
    for (int i = 1; i <= m; ++i) {
        std::cin >> u >> v;
        g[u].push_back(v);
        ++in[v];
    }
    for (int i = 1; i <= n; ++i) {
        std::sort(g[i].begin(), g[i].end(), std::greater<int>());
        if(abs((int) g[i].size() - in[i]) > 1) puts("No"), exit(0);
        if (g[i].size() > in[i]) {
            if (vis) puts("No"), exit(0);
            else vis = i;
        }
    }
    dfs(vis ? vis : 1);
    if (top != m + 1) puts("No"), exit(0);
    else {
        std::reverse(ans.begin(), ans.end());
        for (const auto& element : ans)
            std::cout << element << " ";
    }
    return 0;
}