#include<bits/stdc++.h>
#define MAXN 1010
using namespace std;
typedef long long ll;
struct node{
    int x1, y1, x2, y2;
    ll tag_ass, tag_add, sum;
};
node tree[MAXN * MAXN << 2];
int n, m, q;
ll a[MAXN][MAXN];
/*
    四叉树时：
        x = 0 ——> 左上方子矩阵
        x = 1 ——> 右上方子矩阵
        x = 2 ——> 左下方子矩阵
        x = 3 ——> 右下方子矩阵
    二叉树时：
        x = 0 ——> 左/上方子矩阵
        x = 1 ——> 右/下方子矩阵
*/
int get_son(int p, int x){ return p * 4 - 2 + x; }
/*
    op = 0 ——> 二叉树
    op = 1 ——> 四叉树
*/
void push_up(int now, int op){
    tree[now].sum = tree[get_son(now, 0)].sum + tree[get_son(now, 1)].sum;
    if(op == 0) return ;
    for(int i = 2; i < 4; i++) tree[now].sum += tree[get_son(now, i)].sum;
}
void push_down(int now){
    if(tree[now].tag_add != 0){
        if(tree[now].y1 == tree[now].y2){
            int son0 = get_son(now, 0), son1 = get_son(now, 1);
            tree[son0].tag_add += tree[now].tag_add;
            tree[son1].tag_add += tree[now].tag_add;
            tree[son0].sum += (tree[son0].x2 - tree[son0].x1 + 1) * tree[now].tag_add;
            tree[son1].sum += (tree[son1].x2 - tree[son1].x1 + 1) * tree[now].tag_add;
        }else if(tree[now].x1 == tree[now].x2){
            int son0 = get_son(now, 0), son1 = get_son(now, 1);
            tree[son0].tag_add += tree[now].tag_add;
            tree[son1].tag_add += tree[now].tag_add;
            tree[son0].sum += (tree[son0].y2 - tree[son0].y1 + 1) * tree[now].tag_add;
            tree[son1].sum += (tree[son1].y2 - tree[son1].y1 + 1) * tree[now].tag_add;
        }else{
            for(int i = 0; i < 4; i++){
                int son = get_son(now, i), s = (tree[son].x2 - tree[son].x1 + 1) * ((tree[son].y2 - tree[son].y1 + 1));
                tree[son].sum += s * tree[now].tag_add;
                tree[son].tag_add += tree[now].tag_add;
            }
        }
        tree[now].tag_add = 0;
    }
    if(tree[now].tag_ass >= 0){
        if(tree[now].x1 == tree[now].x2){
            int son0 = get_son(now, 0), son1 = get_son(now, 1);
            tree[son0].tag_ass = tree[now].tag_ass;
            tree[son1].tag_ass = tree[now].tag_ass;
            tree[son0].tag_add = tree[son1].tag_add = 0;
            tree[son0].sum = (tree[son0].y2 - tree[son0].y1 + 1) * tree[now].tag_ass;
            tree[son1].sum = (tree[son1].y2 - tree[son1].y1 + 1) * tree[now].tag_ass;
        }else if(tree[now].y1 == tree[now].y2){
            int son0 = get_son(now, 0), son1 = get_son(now, 1);
            tree[son0].tag_ass = tree[now].tag_ass;
            tree[son1].tag_ass = tree[now].tag_ass;
            tree[son0].tag_add = tree[son1].tag_add = 0;
            tree[son0].sum = (tree[son0].x2 - tree[son0].x1 + 1) * tree[now].tag_ass;
            tree[son1].sum = (tree[son1].x2 - tree[son1].x1 + 1) * tree[now].tag_ass;
        }else{
            for(int i = 0; i < 4; i++){
                int son = get_son(now, i), s = (tree[son].x2 - tree[son].x1 + 1) * ((tree[son].y2 - tree[son].y1 + 1));
                tree[son].tag_add = 0;
                tree[son].sum = s * tree[now].tag_ass;
                tree[son].tag_ass = tree[now].tag_ass;
            }
        }
        tree[now].tag_ass = -1;
    }
}
// 建树
void build(int now, int x1, int y1, int x2, int y2){
    tree[now].x1 = x1; tree[now].y1 = y1; tree[now].x2 = x2; tree[now].y2 = y2;
    tree[now].tag_ass = -1; tree[now].tag_add = 0;
    if(x1 == x2 && y1 == y2){
        tree[now].sum = a[x1][y2];
        return ;
    }
    int midx = (x1 + x2) >> 1, midy = (y1 + y2) >> 1;
    if(x1 == x2){
        build(get_son(now, 0), x1, y1, x2, midy); build(get_son(now, 1), x1, midy + 1, x2, y2);
        push_up(now, 0);
    }else if(y1 == y2){
        build(get_son(now, 0), x1, y1, midx, y2); build(get_son(now, 1), midx + 1, y1, x2, y2);
        push_up(now, 0);
    }else{
        build(get_son(now, 0), x1, y1, midx, midy);
        build(get_son(now, 1), midx + 1, y1, x2, midy);
        build(get_son(now, 2), x1, midy + 1, midx, y2);
        build(get_son(now, 3), midx + 1, midy + 1, x2, y2);
        push_up(now, 1);
    }
}
// 矩阵加法
void update_add(int now, int x1, int y1, int x2, int y2, int val){
    if(tree[now].x1 > x2 || tree[now].x2 < x1 || tree[now].y1 > tree[now].y2 || tree[now].y2 < tree[now].y1) return ;
    if(tree[now].x1 >= x1 && tree[now].x2 <= x2 && tree[now].y1 >= y1 && tree[now].y2 <= y2){
        tree[now].tag_add += val;
        if(tree[now].tag_ass >= 0) tree[now].tag_ass += val;
        tree[now].sum += (tree[now].x2 - tree[now].x1 + 1) * (tree[now].y2 - tree[now].y1 + 1) * val;
        return ;
    }
    push_down(now);
    if(tree[now].x1 == tree[now].x2 || tree[now].y1 == tree[now].y2){
        update_add(get_son(now, 0), x1, y1, x2, y2, val);
        update_add(get_son(now, 1), x1, y1, x2, y2, val);
        push_up(now, 0);
    }else{
        for(int i = 0; i < 4; i++) update_add(get_son(now, i), x1, y1, x2, y2, val);
        push_up(now, 1);
    }
}
// 矩阵赋值
void update_ass(int now, int x1, int y1, int x2, int y2, int val){
    if(tree[now].x1 > x2 || tree[now].x2 < x1 || tree[now].y1 > tree[now].y2 || tree[now].y2 < tree[now].y1) return ;
    if(tree[now].x1 >= x1 && tree[now].x2 <= x2 && tree[now].y1 >= y1 && tree[now].y2 <= y2){
        tree[now].tag_add = 0;
        tree[now].tag_ass = val;
        tree[now].sum = (tree[now].x2 - tree[now].x1 + 1) * (tree[now].y2 - tree[now].y1 + 1) * val;
        return ;
    }
    push_down(now);
    if(tree[now].x1 == tree[now].x2 || tree[now].y1 == tree[now].y2){
        update_ass(get_son(now, 0), x1, y1, x2, y2, val);
        update_ass(get_son(now, 1), x1, y1, x2, y2, val);
        push_up(now, 0);
    }else{
        for(int i = 0; i < 4; i++) update_ass(get_son(now, i), x1, y1, x2, y2, val);
        push_up(now, 1);
    }
}
// 查询矩阵中所有元素的和
ll query(int now, int x1, int y1, int x2, int y2){
    if(tree[now].x1 > x2 || tree[now].x2 < x1 || tree[now].y1 > tree[now].y2 || tree[now].y2 < tree[now].y1) return 0;
    if(tree[now].x1 >= x1 && tree[now].x2 <= x2 && tree[now].y1 >= y1 && tree[now].y2 <= y2){
        return tree[now].sum;
    }
    push_down(now);
    if(tree[now].x1 == tree[now].x2 || tree[now].y1 == tree[now].y2){
        return query(get_son(now, 0), x1, y1, x2, y2) + query(get_son(now, 1), x1, y1, x2, y2);
    }else{
        ll res = 0;
        for(int i = 0; i < 4; i++) res += query(get_son(now, i), x1, y1, x2, y2);
        return res;
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            scanf("%lld",&a[i][j]);
        }
    }
    build(1, 1, 1, n, m);
    scanf("%d",&q);
    for(int i = 1; i <= q; i++){
        int op, x1, y1, x2, y2;
        scanf("%d%d%d%d%d",&op,&x1,&y1,&x2,&y2);
        if(op == 1){
            ll val; scanf("%lld",&val);
            update_add(1, x1, y1, x2, y2, val);
        }else if(op == 2){
            ll val; scanf("%lld",&val);
            update_ass(1, x1, y1, x2, y2, val);
        }else printf("%lld\n",query(1, x1, y1, x2, y2));
    }
    return 0;
}