#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, a[N], b[N];

void merge_sort(int l, int r, int a[]) {
    if (l == r) return ;
    if (l == r - 1) {
        if (a[l] >= a[r]) swap(a[l], a[r]);
        return ;
    } 
    int mid = (l + r) >> 1;
    int i = l, j = mid + 1, top = l;
    merge_sort(l, mid, a);
    merge_sort(mid + 1, r, a);
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) b[top++] = a[i++];
        else b[top++] = a[j++];
    }
    while (i <= mid) b[top++] = a[i++];
    while (j <= r) b[top++] = a[j++];
    for (int k = l; k <= r; ++k)
        a[k] = b[k];
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    merge_sort(1, n, a);
    for (int i = 1; i <= n; ++i)
        cout << a[i] << " ";
    return 0;
}