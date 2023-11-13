#include <iostream>

const int N = 1e6 + 5;
const int mod = 998244353;
int n, a[N], t[N];
long long ans, fac[N];

int lowbit(int x) {
    return x & (-x);
}

void add(int x, int k) {
    while (x <= n) {
        t[x] = (t[x] + k) % mod;
        x += lowbit(x);
    }
}

int query(int x) {
    long long cur = 0;
    while (x) {
        cur = (cur + t[x]) % mod;
        x -= lowbit(x);
    }
    return cur;
}

int main() {
    std::cin >> n;
    int x, ans = 0;
    fac[1] = fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = (fac[i - 1] * i) % mod;
    ans = 1;
    for (int i = 1; i <= n; ++i) {
        std::cin >> x;
        add(x, 1);
        ans = (ans + ((x - query(x)) * fac[n - i]) % mod) % mod;
    }
    std::cout << ans << std::endl;
    return 0;
}