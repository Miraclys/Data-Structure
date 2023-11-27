#include <iostream>
#include <algorithm>
#define int long long

const int N = 1e5 + 5;
int n, m;

struct Tree {
    int l, r, lazy;
    int sum;
} t[N << 2];

void push_up(int cur) {
    t[cur].sum = t[cur << 1].sum + t[cur << 1 | 1].sum;
}

void build(int cur, int l, int r) {
    t[cur].l = l; t[cur].r = r;
    t[cur].lazy = 0; t[cur].sum = 0;
    if (l == r) {
        std::cin >> t[cur].sum;
        return ;
    }
    int mid = (l + r) >> 1;
    build(cur << 1, l, mid);
    build(cur << 1 | 1, mid + 1, r);
    push_up(cur);
}

void add(int cur, int l, int r, int k) {
    // t[cur].sum += k * (t[cur].r - t[cur].l + 1);
    if (std::min(t[cur].r, r) >= std::max(t[cur].l, l)) {
        t[cur].sum += k * (std::min(t[cur].r, r) - std::max(t[cur].l, l) + 1);
    }
    if (t[cur].l >= l && t[cur].r <= r) {
        t[cur].lazy += k;
        return ;
    }
    int mid = (t[cur].l + t[cur].r) >> 1;
    if (l <= mid) add(cur << 1, l, r, k);
    if (r >= mid + 1) add(cur << 1 | 1, l, r, k);
}

int query(int cur, int l, int r, int sum) {
    if (t[cur].l >= l && t[cur].r <= r) {
        return t[cur].sum + sum * (t[cur].r - t[cur].l + 1);
    }
    int mid = (t[cur].l + t[cur].r) >> 1;
    int res = 0;
    if (l <= mid) res += query(cur << 1, l, r, sum + t[cur].lazy);
    if (r >= mid + 1) res += query(cur << 1 | 1, l, r, sum + t[cur].lazy);
    return res;
}

signed main() {
    std::cin >> n >> m;
    build(1, 1, n);
    int x, y, k, opt;
    while (m--) {
        std::cin >> opt;
        if (opt == 1) {
            std::cin >> x >> y >> k;
            add(1, x, y, k);
        } else {
            std::cin >> x >> y;
            std::cout << query(1, x, y, 0) << "\n";
        }
    }
    return 0;
}