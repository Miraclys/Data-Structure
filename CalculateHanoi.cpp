#include <iostream>
#include <cstring>

#define ull unsigned long long
const int mod = 1e8;
ull ans[1005], a[1005], c[1005];

int main() {
    int n;
    std::cin >> n;
    ans[0] = a[0] = 1;
    a[1] = 2;
    ans[1] = 1;
    while (n) {
        if (n & 1) {
            memset(c, 0, sizeof (c));
            for (int i = 1; i <= a[0]; ++i)
                for (int j = 1; j <= ans[0]; ++j)
                    c[i + j - 1] += ans[j] * a[i];
            c[0] = a[0] + ans[0];
            for (int i = 1; i <= c[0]; ++i) {
                c[i + 1] += c[i] / mod;
                c[i] %= mod;
            }
            while (!c[c[0]]) --c[0];
            memcpy(ans, c, sizeof (ans));
        }
        memset(c, 0, sizeof (c));
        for (int i = 1; i <= a[0]; ++i)
            for (int j = 1; j <= a[0]; ++j)
                c[i + j - 1] += a[i] * a[j];
        c[0] = a[0] + a[0];
        for (int i = 1; i <= c[0]; ++i) {
            c[i + 1] += c[i] / mod;
            c[i] %= mod;
        }   
        while (!c[c[0]]) --c[0];
        memcpy(a, c, sizeof (a));
        n >>= 1;
    }
    --ans[1];
    std::cout << ans[ans[0]];
    for (int i = ans[0] - 1; i >= 1; --i)
        printf("%08lld", ans[i]);
    return 0;
}