#include <iostream>
#include <algorithm>
#include "../FibonacciHeap.hpp"

const int N = 5e3 + 5;
const int M = 2e5 + 5;
int n, m, cnt, head[N], ans, tot, vis[N];

struct Edge {
    int to, nxt, w;
} e[M << 1];

void add(int u, int v, int w) {
    e[++cnt].to = v;
    e[cnt].nxt = head[u];
    e[cnt].w = w;
    head[u] = cnt;
}

struct Status {
    int dis;
    int num;
    bool operator<(const Status& rhs) const {
        return dis < rhs.dis;
    }
};

void Prim() {
    FibonacciHeap<Status> heap;
    heap.insert(Status {0, 1});
    while (!heap.empty()) {
        Status top = heap.top();
        heap.pop();
        if (vis[top.num]) continue;
        vis[top.num] = 1;
        ans += top.dis;
        if (++tot == n) {
            return ;
        }
        for (int i = head[top.num]; i ; i = e[i].nxt) {
            int to = e[i].to;
            if (vis[to]) continue;
            heap.insert(Status {e[i].w, to});
        }
    }
}

int main() {
    std::cin >> n >> m;
    int x, y, z;
    for (int i = 1; i <= m; ++i) {
        std::cin >> x >> y >> z;
        add(x, y, z);
        add(y, x, z);
    }
    Prim();
    // std::cout << tot << "\n";
    if (tot != n) std::cout << "orz\n";
    else std::cout << ans << "\n";
    return 0;
}