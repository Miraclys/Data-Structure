#include <bits/stdc++.h>
#define ll long long

const int N = 803;
const int inf = 0x3f3f3f3f;

struct Tree_y {
    int l, r;
    int Max, Min;
};

int n;
int rtx[N], rty[N];

struct Tree_x {
    int l, r;
    Tree_y t_y[N << 2];
    
    void build(int cur, int l, int r) {
        t_y[cur].l = l;
        t_y[cur].r = r;
        t_y[cur].Max = -inf;
        t_y[cur].Min = inf;
        if (l == r) {
            rty[l] = cur;
            return ;
        }
        int mid = (l + r) >> 1;
        build(cur << 1, l, mid);
        build(cur << 1 | 1, mid + 1, r);
    }

    int query_min(int cur, int l, int r) {
        if (t_y[cur].l >= l && t_y[cur].r <= r) {
            return t_y[cur].Min;
        }
        int mid = (t_y[cur].l + t_y[cur].r) >> 1;
        int res = inf;
        if (l <= mid) res = std::min(res, query_min(cur << 1, l, r));
        if (r >= mid + 1) res = std::min(res, query_min(cur << 1 | 1, l, r));
        return res;
    }

    int query_max(int cur, int l, int r) {
        if (t_y[cur].l >= l && t_y[cur].r <= r) {
            return t_y[cur].Max;
        }
        int mid = (t_y[cur].l + t_y[cur].r) >> 1;
        int res = -inf;
        if (l <= mid) res = std::max(res, query_max(cur << 1, l, r));
        if (r >= mid + 1) res = std::max(res, query_max(cur << 1 | 1, l, r));
        return res;
    }
} t_x[N << 2];

void build(int cur, int l, int r) {
    t_x[cur].l = l;
    t_x[cur].r = r;
    t_x[cur].build(1, 1, n);
    if (l == r) {
        rtx[l] = cur;
        return ;
    }
    int mid = (l + r) >> 1;
    build(cur << 1, l, mid);
    build(cur << 1 | 1, mid + 1, r);
}

void update(int x, int y, int val) {
    int rx = rtx[x];
    int ry = rty[y];
    t_x[rx].t_y[ry].Max = t_x[rx].t_y[ry].Min = val = val;
    for (int i = rx; i ; i >>= 1) {
        for (int j = ry; j ; j >>= 1) {
            if (i == rx && j == ry) continue;
            if (j == ry) {
                t_x[i].t_y[j].Max = std::max(t_x[i << 1].t_y[j].Max, t_x[i << 1 | 1].t_y[j].Max);
                t_x[i].t_y[j].Min = std::min(t_x[i << 1].t_y[j].Min, t_x[i << 1 | 1].t_y[j].Min);
            } else {
                t_x[i].t_y[j].Max = std::max(t_x[i].t_y[j << 1].Max, t_x[i].t_y[j << 1 | 1].Max);
                t_x[i].t_y[j].Min = std::min(t_x[i].t_y[j << 1].Min, t_x[i].t_y[j << 1 | 1].Min);
            }
        }
    }
}

int query_min(int cur, int l1, int r1, int l2, int r2) {
    if (t_x[cur].l >= l1 && t_x[cur].r <= r1) {
        return t_x[cur].query_min(1, l2, r2);
    }
    int mid = (t_x[cur].l + t_x[cur].r) >> 1;
    int res = inf;
    if (l1 <= mid) res = std::min(res, query_min(cur << 1, l1, r1, l2, r2));
    if (r1 >= mid + 1) res = std::min(res, query_min(cur << 1 | 1, l1, r1, l2, r2));
    return res;
}

int query_max(int cur, int l1, int r1, int l2, int r2) {
    if (t_x[cur].l >= l1 && t_x[cur].r <= r1) {
        return t_x[cur].query_max(1, l2, r2);
    }
    int mid = (t_x[cur].l + t_x[cur].r) >> 1;
    int res = -inf;
    if (l1 <= mid) res = std::max(res, query_max(cur << 1, l1, r1, l2, r2));
    if (r1 >= mid + 1) res = std::max(res, query_max(cur << 1 | 1, l1, r1, l2, r2));
    return res;
}

int main() {
    int T, cas = 0;
    std::cin >> T;
    while (T--) {
        std::cout << "Case #" << ++cas << ":\n";
        std::cin >> n;
        build(1, 1, n);
        int x;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                std::cin >> x;
                update(i, j, x);
            }
        }
        int q;
        std::cin >> q;
        int y, L;
        while (q--) {
            std::cin >> x >> y >> L;
            int L1 = std::max(x - L / 2, 1);
            int R1 = std::min(x + L / 2, n);
            int L2 = std::max(y - L / 2, 1);
            int R2 = std::min(y + L / 2, n);
            int Max = query_max(1, L1, R1, L2, R2);
            int Min = query_min(1, L1, R1, L2, R2);
            int val = std::floor((Max + Min) / 2);
            std::cout << val << '\n';
            update(x, y, val);
        }
    }
    return 0;
}