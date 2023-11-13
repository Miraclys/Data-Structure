#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>

const int N = 1e5 + 5;

int n, m, in[N], VIS = 0, top = 0, fa[N], vis[N];

struct Status {
    int to;
    bool vis;
};
std::vector<Status> v[N]; 
std::vector<int> ans;

void search(int x) {
    vis[x] = 1;
    for (int i = 0; i < v[x].size(); ++i) {
        if (v[x][i].vis || vis[v[x][i].to]) continue;
        search(v[x][i].to);
    }
}

bool check_is_bridge(int u, int num) {
    memset(vis, 0, sizeof (vis));
    int pre_tot = 0;
    for (int i = 1; i <= n; ++i) {
        if (vis[i]) continue;
        ++pre_tot;
        search(i);
    }
    int suf_tot = 0;
    v[u][num].vis = 1;
    memset(vis, 0, sizeof (vis));
    for (int i = 1; i <= n; ++i) {
        if (vis[i]) continue;
        ++suf_tot;
        search(i);
    }
    v[u][num].vis = 0;
    return suf_tot != pre_tot;
}

void dfs(int x) {
    for (int i = 0; i < v[x].size(); i++) {
        if (!v[x][i].vis && !check_is_bridge(x, i)) {
            v[x][i].vis = true;
            for (int j = 0; j < v[v[x][i].to].size(); j++) {
                if (v[v[x][i].to][j].to == x) {
                    v[v[x][i].to][j].vis = true;
                    break;
                }
            }
            dfs(v[x][i].to);
        }
    }
    ans.push_back(x);
}

int main() {
    // Input:
    // 7 8
    // 1 2
    // 2 4
    // 1 3
    // 3 4
    // 4 5
    // 4 6
    // 5 7
    // 6 7
    // Output:
    std::cin >> n >> m;
    int u, vv;
    for (int i = 1; i <= m; ++i) {
        std::cin >> u >> vv;
        v[u].push_back(Status {vv, false});
        v[vv].push_back(Status {u, false});
        ++in[vv];
        ++in[u];
    }
    dfs(1);
    for (const auto& element : ans)
        std::cout << element << " ";
    return 0;
}