#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
int len1, len2, f[N];
char a[N], b[N];

int main() {
    // 输入：
    // ABABABC
    // ABA
    // 输出：
    // 1
    // 3
    // 0 0 1 
    cin >> (a + 1) >> (b + 1);
    len1 = strlen(a + 1);
    len2 = strlen(b + 1);
    int j = 0;
    f[1] = 0;
    for (int i = 2; i <= len2; ++i) {
        while (j && b[j + 1] != b[i]) j = f[j];
        if (b[j + 1] == b[i]) ++j;
        f[i] = j;
    }
    j = 0;
    for (int i = 1; i <= len1; ++i) {
        while (j && a[i] != b[j + 1]) j = f[j];
        if (a[i] == b[j + 1]) ++j;
        if (j == len2) {
            printf("%d\n", i - len2 + 1);
            j = f[j];
        }
    }
    for (int i = 1; i <= len2; ++i)
        cout << f[i] << " ";
    return 0;
}