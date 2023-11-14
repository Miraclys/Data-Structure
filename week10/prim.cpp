#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>

const int N = 5005;

int n, m, cnt, head[N], vis[N];
int ans, tot;

struct Edge {
    int to, nxt, w;
} e[N * (N - 1) / 2];

struct Status {
    int v, w;
    bool operator<(const Status& rhs) const {
        return w > rhs.w;
    }
    Status(int value, int weight)
        : v(value), w(weight) {}
};

void add(int x, int y, int z) {
    e[++cnt].to = y;
    e[cnt].nxt = head[x];
    head[x] = cnt;
    e[cnt].w = z;
}

void Prim() {
    std::priority_queue<Status> q;
    q.push(Status(1, 0));
    while (!q.empty()) {
        Status cur = q.top();
        q.pop();
        if (vis[cur.v]) continue;
        vis[cur.v] = 1;
        ans += cur.w;
        ++tot;
        if (tot == n) {
            return ;
        }
        for (int i = head[cur.v]; i; i = e[i].nxt) {
            if (!vis[e[i].to]) {
                q.push(Status(e[i].to, e[i].w));
            }
        }
    }
    ans = -1;
}

int main() {
    // Input:
    // 4 5
    // 1 2 2
    // 1 3 2
    // 1 4 3
    // 2 3 4
    // 3 4 3
    // Output:
    // 7
    std::cin >> n >> m;
    int x, y, z;
    for (int i = 1; i <= m; ++i) {
        std::cin >> x >> y >> z;
        add(x, y, z);
        add(y, x, z);
    }
    Prim();
    // std::cout << "tot" << tot << "\n";
    if (ans != -1) std::cout << ans << "\n";
    else std::cout << "orz" << "\n";
    return 0;
}