#include <bits/stdc++.h>

const int N = 1e5 + 5;
const int inf = 0x3f3f3f3f;

int n, m, t[N << 2], cnt, a[N], ls[N], rs[N], lazy[N], sum[N];

void push_up(int cur) {
    sum[cur] = sum[ls[cur]] + sum[rs[cur]];
}

void build(int& cur, int l, int r) {
    cur = ++cnt;
    if (l == r) {
        sum[cur] = a[l];
        return ;
    }
    int mid = (l + r) >> 1;
    build(ls[cur], l, mid);
    build(rs[cur], mid + 1, r);
    push_up(cur);
}

int update(int pre, int l, int r, int x, int y, int k) {
    // std::cout << "sadasdsad";
    ++cnt;
    ls[cnt] = ls[pre], rs[cnt] = rs[pre];
    sum[cnt] = sum[pre] + (std::min(r, y) - std::max(x, l) + 1) * k;
    // std::cout << sum[cnt] << "asdasda ";
    lazy[cnt] = lazy[pre];
    if (l >= x && r <= y) {
        lazy[cnt] += k;
        return cnt;
    }
    int mid = (l + r) >> 1;
    if (x <= mid) ls[cnt] = update(ls[pre], l, mid, x, y, k);
    if (y >= mid + 1) rs[cnt] = update(rs[pre], mid + 1, r, x, y, k);
    return cnt; 
}

int query(int pre, int l, int r, int x, int y, int s) {
    // std::cout << s << " asdas";
    if (l >= x && r <= y) {
        // std::cout << "asd" << sum[pre] + s * (r - l + 1) << " "
        return sum[pre] + s * (r - l + 1);
    }
    int mid = (l + r) >> 1;
    int res = 0;
    if (x <= mid) res += query(ls[pre], l, mid, x, y, s + lazy[pre]);
    if (y >= mid + 1) res += query(rs[pre], mid + 1, r, x, y, s + lazy[pre]);
    return res;
}

void init() {
    cnt = 0;
}

int main() {
    // while (~scanf("%d%d", &n, &m)) {
        std::cin >> n >> m;
        init();
        for (int i = 1; i <= n; ++i) {
            std::cin >> a[i];
        }
        int time = 0;
        build(t[0], 1, n);
        // traverse(t[0]);s
        char o[3];
        int l, r, v;
        while (m--) {
            scanf("%s", o);
            if (o[0] == 'C') {
                std::cin >> l >> r >> v;
                ++time;
                t[time] = update(t[time - 1], 1, n, l, r, v);
            } else if (o[0] == 'Q') {
                std::cin >> l >> r;
                std::cout << query(t[time], 1, n, l, r, 0) << "\n";
            } else if (o[0] == 'H') {
                std::cin >> l >> r >> v;
                std::cout << query(t[v], 1, n, l, r, 0) << "\n";
            } else {
                std::cin >> v;
                time = v;
            }
        }
    // }
    return 0;
}