#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long

const int N = 4e5 + 5, INF = 0x3f3f3f3f;
int n, m, root;

struct Point {
    int x[2];
};
Point pi[N];

struct Node {
    int l, r;
    Point p;
    int L[2], R[2], sz;
} t[N];
int cnt;
ll res = 4e18;

void pushup(int rt) {
    auto &L = t[t[rt].l], &R = t[t[rt].r];
    t[rt].sz = L.sz + R.sz + 1;
    for (int i = 0; i <= 1; ++i) {
        t[rt].L[i] = std::min(t[rt].p.x[i], std::min(L.L[i], R.L[i]));
        t[rt].R[i] = std::max(t[rt].p.x[i], std::max(L.R[i], R.R[i]));
    }
}

int build(int l, int r, int d) {
    if (l > r) return 0;
    int mid = (l + r) >> 1;
    int rt = ++cnt;
    std::nth_element(pi + l, pi + mid, pi + r + 1, [d](Point a, Point b) {
        return a.x[d] < b.x[d];
    });
    t[rt].p = pi[mid];
    t[rt].l = build(l, mid - 1, d ^ 1);
    t[rt].r = build(mid + 1, r, d ^ 1);
    pushup(rt);
    return rt;
}

ll H(int u, Point tar) {
    auto square = [](int x) {
        return 1ll * x * x;
    };
    ll x = tar.x[0], y = tar.x[1];
    ll res = 0;
    if (x < t[u].L[0]) res += square(x - t[u].L[0]);
    if (x > t[u].R[0]) res += square(x - t[u].R[0]);
    if (y < t[u].L[1]) res += square(y - t[u].L[1]);
    if (y > t[u].R[1]) res += square(y - t[u].R[1]);
    return res;
}

void query(int u, Point tar) {
    if (!u) return ;
    if (t[u].p.x[0] != tar.x[0] || t[u].p.x[1] != tar.x[1]) {
        res = std::min(res, 1ll * (t[u].p.x[0] - tar.x[0]) * (t[u].p.x[0] - tar.x[0]) + 1ll * (t[u].p.x[1] - tar.x[1]) * (t[u].p.x[1] - tar.x[1]));
    };
    ll LV = 4e18, RV = 4e18;
    if (t[u].l) LV = H(t[u].l, tar);
    if (t[u].r) RV = H(t[u].r, tar);
    // if (LV < RV) {
    if (LV < res) query(t[u].l, tar);
    if (RV < res) query(t[u].r, tar);
    // } else {
    //     if (RV < res) query(t[u].r, tar);
    //     if (LV < res) query(t[u].l, tar);
    // }
}

int main() {
    std::cin >> n;
    t[0].L[0] = t[0].L[1] = INF;
    t[0].R[0] = t[0].R[1] = -INF;
    int x, y;
    for (int i = 1; i <= n; ++i) {
        std::cin >> x >> y;
        pi[i] = Point{x, y};
    }
    std::sort(pi + 1, pi + n + 1, [](Point a, Point b) {
        return a.x[0] == b.x[0] ? a.x[1] < b.x[1] : a.x[0] < b.x[0];
    });
    root = build(1, n, 0);
    for (int i = 1; i <= n; ++i) {
        query(root, pi[i]);
    }
    std::cout << res << "\n";
    return 0;
}