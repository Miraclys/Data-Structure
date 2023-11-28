#include <iostream>
#include <vector>

const int N = 2e4 + 5;
const int M = 105;
int n, k, q, d;
int a[M][N], len[M], h[N];

struct Node {
    int cur, nxt;
    int val;
} b[M][N], temp[N], c[N];

void init() {
    len[k] = n;
    for (int i = 1; i <= len[k]; ++i) {
        b[k][i] = (Node){i, 0, a[k][i]};
    }
    int cnt, top;
    for (int i = k - 1; i >= 1; --i) {
        cnt = 0, top = 0;
        for (int j = 2; j <= len[i + 1]; j += 2) {
            temp[++cnt] = b[i + 1][j];
            temp[cnt].cur = j;
        }
        int l = 1, ll = 1;
        while (l <= cnt && ll <= n) {
            if (temp[l].val < a[i][ll]) {
                c[++top] = temp[l];
                c[top].cur = ll, c[top].nxt = temp[l].cur;
                l++;
            } else {
                c[++top].val = a[i][ll];
                c[top].cur = ll, c[top].nxt = temp[l].cur;
                ll++;
            }
        }
        while (l <= cnt) {
            c[++top] = temp[l];
            c[top].cur = ll, c[top].nxt = temp[l].cur;
            l++;
        }
        while (ll <= n) {
            c[++top].val = a[i][ll];
            c[top].cur = ll, c[top].nxt = temp[l - 1].cur;
            ll++;
        }
        for (int j = 1; j <= top; ++j) {
            b[i][j] = c[j];
        }
        len[i] = top;
    }
    for (int i = 1; i <= len[1]; ++i) {
        h[i] = b[1][i].val;
    }
}

int main() {
    std::cin >> n >> k >> q >> d;
    for (int i = 1; i <= k; ++i) {
        for (int j = 1; j <= n; ++j) {
            std::cin >> a[i][j];
        }
    }
    init();
    len[k + 1] = n;
    int lst_ans = 0;
    for (int i = 1; i <= q; ++i) {
        int x;
        std::cin >> x;
        x ^= lst_ans;
        lst_ans = 0;
        // int p = std::lower_bound(b[1] + 1, b[1] + len[1] + 1, (Node){0, 0, x}) - b[1];
        int p = std::lower_bound(h + 1, h + len[1] + 1, x) - h;
        for (int j = 1; j <= k; ++j) {
            while (p <= len[j] && b[j][p].val < x) ++p;
            while (p >= 2 && b[j][p - 1].val >= x) --p;
            if (p <= len[j]) {
                lst_ans ^= a[j][b[j][p].cur];
                p = b[j][p].nxt;
            } else {
                p = len[j + 1] + 1;
            }
        }
        if (i % d == 0) std::cout << lst_ans << "\n";
    }
    return 0;
}