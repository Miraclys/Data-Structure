#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>

const int N = 1e5 + 5;
const int M = 3e6 + 5;
int T, n, q, t[M][65], cnt[M], tot;
char a[M], b[M];

int get_num(char x) {
    if (x >= 'A' && x <= 'Z') {
        return x - 'A';
    } else if (x >= 'a' && x <= 'z') {
        return x - 'a' + 26;
    } else {
        return x - '0' + 52;
    }
}

void insert(char target[]) {
    int len = strlen(target);
    int p = 0;
    for (int i = 0; i < len; ++i) {
        int c = get_num(target[i]);
        if (!t[p][c]) {
            t[p][c] = ++tot;
        }
        p = t[p][c];
        cnt[p]++;
    }
}

int query(char target[]) {
    int len = strlen(target);
    int p = 0;
    for (int i = 0; i < len; ++i) {
        int c = get_num(target[i]);
        if (!t[p][c]) {
            return 0;
        }
        p = t[p][c];
    }
    return cnt[p];
}

int main() {
    std::cin >> T;
    while (T--) {
        for(int i = 0;i <= tot; i++)
            for(int j = 0; j <=122; j++)
                t[i][j]=0;
        for (int i = 0; i <= tot; ++i)
            cnt[i] = 0;
        tot = 0;
        std::cin >> n >> q;
        for (int i = 1; i <= n; ++i) {
            scanf("%s", a);
            insert(a);
        }
        for (int i = 1; i <= q; ++i) {
            scanf("%s", b);
            printf("%d\n", query(b));
        }
    }
    return 0;
}