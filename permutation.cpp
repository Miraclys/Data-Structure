#include <iostream>
#include <vector>

const int N = 105;
int a[N];
long long fac[N];
std::vector<int> ans, v;

int main() {
    int n;
    std::cin >> n;
    fac[1] = fac[0] = 1;
    for (int i = 2; i <= n; ++i)
        fac[i] = fac[i - 1] * i;
    for (int i = 1; i <= fac[n]; ++i) {
        for (int j = 1; j <= n; ++j)
            v.push_back(j);
        ans.clear();
        long long cur = i - 1;
        for (int j = n; j >= 1; --j) {
            long long r = cur % fac[j - 1];
            long long t = cur / fac[j - 1];
            cur = r;
            ans.push_back(v[t]);
            v.erase(v.begin() + t);
        }
        for (int element : ans)
            std::cout << element;
        std::cout << "\n";
    }
    return 0;
}