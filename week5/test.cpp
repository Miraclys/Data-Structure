#include <bits/stdc++.h>
using namespace std;
int ans = 0;
int a[105];
bool use[105];
int id(int x, int y,int z){
    return x * 9 + y * 3 + z * 1;
}
int main() {
    /*
    0 = R
    1 = G
    2 = B
    */
    stack<pair<int, int> > stk;
    a[1] = 0;
    stk.push(make_pair(0, 0));
    while(!stk.empty()){
        int len = stk.top().first, status = stk.top().second;
        stk.pop();
        ans = max(ans, len);
        if(len <= 2){
            if(status == 0){
                a[len + 1] = 0; 
                stk.push(make_pair(len, 1));
                stk.push(make_pair(len + 1, 0));
                if(len == 2)use[id(a[1], a[2], a[3])] = true;
            }else if(status == 1){
                if(len == 2)use[id(a[1], a[2], a[3])] = false;
                a[len + 1] = 1;
                if(len == 2)use[id(a[1], a[2], a[3])] = true;
                stk.push(make_pair(len, 2));
                stk.push(make_pair(len + 1, 0));
            }else{
                if(len == 2)use[id(a[1], a[2], a[3])] = false;
                a[len + 1] = 2;
                if(len == 2)use[id(a[1], a[2], a[3])] = true;
                stk.push(make_pair(len + 1, 0));
            }

        }else{
            if(status == 0){
                int index = id(a[len - 1], a[len], 0);
                if(!use[index]){
                    use[index] = true;
                    a[len + 1] = 0;
                    stk.push(make_pair(len, 1));
                    stk.push(make_pair(len + 1, 0));
                }else{
                    stk.push(make_pair(len, 2));
                }
            }else if(status == 1){
                use[id(a[len - 1], a[len], 0)] = 0;
                stk.push(make_pair(len, 2));
            }else if(status == 2){
                int index = id(a[len - 1], a[len], 1);
                if(!use[index]){
                    use[index] = true;
                    a[len + 1] = 1;
                    stk.push(make_pair(len, 3));
                    stk.push(make_pair(len + 1, 0));
                }else{
                    stk.push(make_pair(len, 4));
                }
            }else if(status == 3){
                use[id(a[len - 1], a[len], 1)] = 0;
                stk.push(make_pair(len, 4));
            }else if(status == 4){
                int index = id(a[len - 1], a[len], 2);
                if(!use[index]){
                    use[index] = true;
                    a[len + 1] = 2;
                    stk.push(make_pair(len, 5));
                    stk.push(make_pair(len + 1, 0));
                }
            }else if(status == 5){
                use[id(a[len - 1], a[len], 2)] = 0;
            }
        }
    }
    cout << ans << endl;
    return 0;
}



/*
000
001
010
*/