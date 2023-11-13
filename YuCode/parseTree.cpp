#include <bits/stdc++.h>
using namespace std;

#define lint long long

int fa[130];
char root;

vector<char> g[130];

struct Stage {
    char ch;
    int stage;
    Stage(char ch, int stage) : ch(ch), stage(stage) {}
};

void prior() {
    stack<Stage> s;
    s.push(Stage(root, 0));
    while (!s.empty()) {
        Stage x = s.top();
        s.pop();
        if (x.stage == 0) {
            cout << x.ch << endl;
            x.stage = 1;
            s.push(x);
        } else if (x.stage == 1) {
            x.stage = 2;
            s.push(x);
            if (g[x.ch].size() >= 1) {
                s.push(Stage(g[x.ch][0], 0));
            }
        } else if (x.stage == 2) {
            x.stage = 3;
            s.push(x);
            if (g[x.ch].size() >= 2) {
                s.push(Stage(g[x.ch][1], 0));
            }
        }
    }
}

int main() {
    string s;
    cin >> s;
    stack<char> sta;
    for (int i = 0; i < s.size(); ++i) {
        char x = s[i];
        if (x == ',') continue;
        if (x == '(') {
            sta.push(s[i - 1]);
        } else if (x == ')') {
            sta.pop();
        } else {
            if (sta.size()) {
                fa[s[i]] = sta.top();
                g[fa[s[i]]].push_back(s[i]);
            } else {
                root = s[i];
            }
        }
    }

    prior();
    
}