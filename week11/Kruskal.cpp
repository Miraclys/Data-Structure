#include <bits/stdc++.h>
using namespace std;

const int M = 2e5 + 5;
typedef long long ll;
int n, m, f[5005], vis[5005];
ll ans;

struct Edge {
	int x, y, w;
}e[M << 1];

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

inline bool cmp(Edge a, Edge b) {
	return a.w < b.w;
}

int find(int a) {
	return a == f[a] ? a : f[a] = find(f[a]);
}

int main() {
	n = read(), m = read();
	for (int i = 1; i <= m; ++i) e[i].x = read(), e[i].y = read(), e[i].w = read();
	sort(e + 1, e + 1 + m, cmp);
	for (int i = 1; i <= n; ++i) f[i] = i;
	int fx, fy;
	int cot = 0;
	if (m < n - 1) {
		printf("orz\n");
		return 0;
	}
	for (int i = 1; i <= m; ++i) {
		fx = find(e[i].x), fy = find(e[i].y);
		if (fx == fy) continue;
		++cot;
		f[fy] = fx;
		ans += e[i].w;
		if (cot == n - 1) {
			printf("%lld\n", ans);
			return 0;
		}
	}
	return 0;
}