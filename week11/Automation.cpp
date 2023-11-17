#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>

const int N = 1e6 + 5;
int n;
std::string s[N];

struct Automation {
    int ch[N][26], fail[N], cnt[N], tot;
    void init() {
        tot = 0;
        memset(ch, 0, sizeof(ch));
        memset(fail, 0, sizeof(fail));
        memset(cnt, 0, sizeof(cnt));
    }
    void insert(std::string s, int len) {
        int p = 0;
        for (int i = 0; i < len; ++i) {
            int c = s[i] - 'a';
            if (!ch[p][c]) {
                ch[p][c] = ++tot;
            }
            p = ch[p][c];
        }
        cnt[p]++;
    }
    void get_fail() {
        std::queue<int> q;
        for (int i = 0; i < 26; ++i) {
            if (ch[0][i]) {
                fail[ch[0][i]] = 0;
                q.push(ch[0][i]);
            }
        }
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int i = 0; i < 26; ++i) {
                if (ch[cur][i]) {
                    fail[ch[cur][i]] = ch[fail[cur]][i];
                    q.push(ch[cur][i]);
                } else ch[cur][i] = ch[fail[cur]][i]; // 大概是这种情况也不算失配吧
            }
        }
    }
    int query(std::string s, int len) {
        int cur = 0, ans = 0;
        for (int i = 0; i < len; ++i) {
            cur = ch[cur][s[i] - 'a'];
            for (int j = cur; j && cnt[j] != -1; j = fail[j]) {
                ans += cnt[j];
                cnt[j] = -1;
            }
        }
        return ans;
    }
} A;

int main() {
    A.init();
    std::cin >> n;
    int len = 0;
    for (int i = 1; i <= n; ++i) {
        std::cin >> s[i];
        len = s[i].length();
        A.insert(s[i], len);
    }
    A.fail[0] = 0;
    A.get_fail();
    std::cin >> s[0];
    len = s[0].length();
    int ans = A.query(s[0], len);
    std::cout << ans << std::endl;
    return 0;
}