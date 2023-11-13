#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

const int N = 1e5 + 5;

int n, m, in[N], vis = 0, top = 0;

std::vector<int> g[N], ans;

void dfs(int id) {
    std::stack<int> current;
    current.push(id);
    while (!current.empty()) {
        int u = current.top();
        if (g[u].empty()) {
            ans.push_back(u);
            current.pop();
            ++top;
        } else {
            int v = g[u].back();
            g[u].pop_back();
            current.push(v);
        }
    }
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