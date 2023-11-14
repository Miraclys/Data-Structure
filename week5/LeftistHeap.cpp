#include "../LeftistHeap.hpp"
#include <map>

const int N = 1e7 + 5;
int vis[N], fa[N], del[N];
LeftistHeap<int> heap[N];
std::map<int, int> trans;

int getFather(int x) {
    return x == fa[x] ? x : fa[x] = getFather(fa[x]);
}

int main() {
    LeftistHeap<int> t;
    t.insert(3);
    t.insert(2);
    t.inOrder();
    t.pop();
    t.inOrder();
    return 0;
}