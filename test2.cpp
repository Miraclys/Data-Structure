#include<cmath>
#include<set>
#include<map>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include <iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int maxn = 1e5 + 10;
const int M = maxn * 30;
const ull seed = 131;
const int INF = 0x3f3f3f3f;
const int MOD = 1000000007;
int a[maxn], root[maxn], tot;
int n, m;
struct node{
    int lson, rson;
    ll sum, lazy;
}T[maxn * 40];
void init(){
    tot = 0;
}
void pushUp(int rt){
    T[rt].sum = T[T[rt].lson].sum + T[T[rt].rson].sum;
}
void build(int l, int r, int &rt){
    rt = ++tot;
    T[rt].lazy = T[rt].sum = 0;
    if(l == r){
        T[rt].sum = a[l];
        return;
    }
    int m = (l + r) >> 1;
    build(l, m,T[rt].lson);
    build(m + 1, r, T[rt].rson);
    pushUp(rt);
}
void update(int l, int r, int L, int R, int &now, int pre, ll v){
    T[++tot] = T[pre], now = tot;
    T[now].sum += (min(R, r) - max(L, l) + 1) * v;
    if(L <= l && R >= r){
        T[now].lazy += v;
        return;
    }
    int m = (l + r) >> 1;
    if(L <= m)
        update(l, m, L, R, T[now].lson, T[pre].lson, v);
    if(R > m)
        update(m + 1, r, L, R, T[now].rson, T[pre].rson, v);
}
ll query(int l, int r, int L, int R, int rt, int sum){
    if(L <= l && R >= r){
        return T[rt].sum + (r - l + 1) * sum;
    }
    int m = (l + r) >> 1;
    // ll ans = (min(R, r) - max(L, l) + 1) * T[rt].lazy;
    ll ans = 0;
    if(L <= m)
        ans += query(l, m, L, R, T[rt].lson, sum + T[rt].lazy);
    if(R > m)
        ans += query(m + 1, r, L, R, T[rt].rson, sum + T[rt].lazy);
    return ans;
}
int main(){
    while(~scanf("%d%d", &n, &m)){
        // std::cin >> n >> m;
        init();
        for(int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        int time = 0;
        build(1, n, root[time]);
        while(m--){
            char o[3];
            int l, r, v;
            scanf("%s", o);
            if(o[0] == 'C'){
                scanf("%d%d%d", &l, &r, &v);
                ++time;
                update(1, n, l, r, root[time], root[time - 1], v);
            }
            else if(o[0] == 'Q'){
                scanf("%d%d", &l, &r);
                printf("%lld\n", query(1, n, l, r, root[time], 0));
            }
            else if(o[0] == 'H'){
                    scanf("%d%d%d", &l, &r, &v);
                    printf("%lld\n", query(1, n, l, r, root[v], 0));
            }
            else{
                scanf("%d", &v);
                time = v;
            }
        }
    }
    return 0;
}