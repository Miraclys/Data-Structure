#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 400005;
const int inf = 9223372036854775807;
int n;

struct Node {
    int x, y;    
} a[N], cur[N], c[N];

struct SortByX {
    bool operator()(const Node& l, const Node& r) const {
        return l.x < r.x;
    }
};

struct SortByY {
    bool operator()(const Node& l, const Node& r) const {
        return l.y < r.y;
    }
};

int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    return x * f;
}

double dis(int l, int r, Node a[]) {
    return sqrt((a[l].x - a[r].x) * (a[l].x - a[r].x) + (a[l].y - a[r].y) * (a[l].y - a[r].y));
}

void merge_sort(int l, int r, Node b[]) {
    if (l == r) return ;
    if (l == r - 1) {
        if (b[l].y >= b[r].y) swap(b[l], b[r]);
        return ;
    }
    int mid = (l + r) >> 1;
    int i = l, j = mid + 1, top = l;
    merge_sort(l, mid, b);
    merge_sort(mid + 1, r, b);
    while (i <= mid && j <= r) {
        if (b[i].y <= b[j].y) c[top++] = b[i++];
        else c[top++] = b[j++];
    }
    while (i <= mid) c[top++] = b[i++];
    while (j <= r) c[top++] = b[j++];
    for (int k = l; k <= r; ++k)
        b[k] = c[k];
}

double getClosestPoints(int l, int r) {
    if (l == r) return inf;
    if (l == r - 1) return dis(l, r, a);
    int mid = (l + r) >> 1;
    double Min = min(getClosestPoints(l, mid), getClosestPoints(mid + 1, r));
    int top = 0;
    for (int i = l; i <= r; ++i)
        if (fabs(a[mid].x - a[i].x) < Min)
            cur[++top] = a[i];
    merge_sort(1, top, cur);
    for (int i = 1; i <= top; ++i) {
        for (int j = i + 1; j <= top && (cur[j].y - cur[i].y) < Min; ++j) {
            Min = min(Min, dis(i, j, cur));
        }
    }
    return Min;
}

signed main() {
    n = read();
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].x >> a[i].y;
    }
    // merge_sort(1, n, a);
    // for (int i = 1; i <= n; ++i)
    //     cout << a[i].x << " " << a[i].y << endl;
    sort(a + 1, a + 1 + n, SortByX());
    double ans = getClosestPoints(1, n);
    cout << (int)(ans * ans) << endl;
    return 0;
}