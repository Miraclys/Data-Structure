#include <iostream>
#include <vector>
#include <algorithm>

const int N = 1e5 + 5;
int n, m, ans[N];
int tot, ls[N * 800], rs[N * 800], sum[N * 800], t[N * 800];
int c[N * 800], cnt;

struct Data {
    int a, b, c;
    int operator==(const Data& rhs) const {
        return a == rhs.a && b == rhs.b && c == rhs.c;
    }
} a[N];

int lowbit(int x) {
    return x & (-x);
}

int modify(int pre, int l, int r, int pos, int k) {
    int cur = ++tot;
    sum[cur] = sum[pre] + k;
    ls[cur] = ls[pre], rs[cur] = rs[pre];
    if (l == r) {
        return cur;
    } 
    int mid = (l + r) >> 1;
    if (pos <= mid) {
        ls[cur] = modify(ls[pre], l, mid, pos, k);
    } else {
        rs[cur] = modify(rs[pre], mid + 1, r, pos, k);
    }
    return cur;
}

void tree_modify(int x, int y, int k) {
    for (int i = x; i <= m; i += lowbit(i)) {
        t[i] = modify(t[i], 1, m, y, k);
        // i += lowbit(i);
    }
}

int query(int l, int r, int pos) {
    if (l == r) {
        int res = 0;
        for (int i = 1; i <= cnt; ++i) {
            res += sum[c[i]];
        }
        return res;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) {
        for (int i = 1; i <= cnt; ++i)
            c[i] = ls[c[i]];
        return query(l, mid, pos);
    } else {
        int res = 0;
        for (int i = 1; i <= cnt; ++i) {
            res += sum[ls[c[i]]];
            c[i] = rs[c[i]];
        }
        return res + query(mid + 1, r, pos);
    }
}

int tree_query(int x, int y) {
    int res = 0;
    cnt = 0;
    for (int i = x; i ; i -= lowbit(i)) {
        c[++cnt] = t[i];
    }
    return query(1, m, y);
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i].a;
        std::cin >> a[i].b;
        std::cin >> a[i].c;
    }
    std::sort(a + 1, a + 1 + n, [&](Data x, Data y) -> bool {
        return x.a != y.a ? x.a < y.a : (x.b == y.b ? x.c < y.c : x.b < y.b);
    });
    int sum = 1;
    for (int i = 1; i <= n; ++i) {
        if (a[i + 1] == a[i]) {
            ++sum;
            continue;
        }
        tree_modify(a[i].b, a[i].c, sum);
        int res = tree_query(a[i].b, a[i].c);
        ans[res] += sum;
        sum = 1;
    }
    for (int i = 1; i <= n; ++i) {
        std::cout << ans[i] << "\n";
    }
    return 0;
}