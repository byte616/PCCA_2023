# PROBLEM LIST

## 模板題
### TIOJ 1312 

[題目 link](https://tioj.ck.tp.edu.tw/problems/1312)

想法: 併查集(DSU)
 
```cpp
#include <iostream>
using namespace std;
int par[10005];
int find(int x){
    return x == par[x] ? x : par[x] = find(par[x]);
}
void uni(int a, int b){
    int _a = find(a), _b = find(b);
    if(_a != _b){
        par[max(_a, _b)] = min(_a, _b);
    }
}
int main(){
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m, a, b;
    while(cin >> n >> m){
        for(int i = 1; i <= n; i++){
            par[i] = i;
        }
        while(m--){
            cin >> a >> b;
            uni(a, b);
        }
        cin >> m;
        cout << find(m) << '\n';
    }
}
```
Zerojudge d808 

[題目 link](https://zerojudge.tw/ShowProblem?problemid=d808)

想法: 併查集(DSU)、DFS

`DSU`
```cpp
#include <iostream>
#include <map>
using namespace std;
int par[1000005];
int find(int x){
    return x == par[x] ? x : par[x] = find(par[x]);
}
void uni(int a, int b){
    int _a = find(a), _b = find(b);
    if(_a != _b) par[_a] = _b;
}
int main(){
    ios::sync_with_stdio(0), cin.tie(0);
    int n, x;
    while(cin >> n){
        map<int,int> mp;
        for(int i = 1; i <= n; i++){
            par[i] = i;
        }
        for(int i = 1; i <= n; i++){
            cin >> x;
            uni(i, x);
        }
        int ma = 0;
        for(int i = 1; i <= n; i++){
            int y = find(i);
            mp[y]++;
            ma = max(ma, mp[y]);
        }
        cout << mp.size() << " " << ma << '\n';
    }
}
```

`DFS`
```cpp
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
vector<int> v[1000005];
bool vis[1000005];
int tmp = 0;
void dfs(int x){
    vis[x] = 1;
    tmp += 1;
    for(auto i : v[x]){
        if(!vis[i]){
            dfs(i);
        }
    }
}
int main(){
    ios::sync_with_stdio(0), cin.tie(0);
    int n, x;
    while(cin >> n){
        for(int i = 1; i <= n; i++)
            v[i].clear();
        memset(vis, 0, sizeof(vis));
        for(int i = 1; i <= n; i++){
            cin >> x;
            v[i].push_back(x);
            v[x].push_back(i);
        }
        int ans = 0, ma = 0;
        for(int i = 1; i <= n; i++){
            if(!vis[i]){
                tmp = 0;
                dfs(i);
                ans += 1;
                ma = max(tmp, ma);
            }
        }
        cout << ans << " " << ma << '\n';
    }
}

```

CSES #1688 

[題目 link](https://cses.fi/problemset/task/1688)

想法: 最小共同祖先(LCA)

```cpp
#include <iostream>
#include <vector>
using namespace std;
vector<int> v[200005];
int arr[21][200005], dep[200005];
int lca(int a, int b){
    if(dep[a] > dep[b]) swap(a, b);
    int dif = dep[b] - dep[a];
    for(int i = 0; i <= 20; i++){
        if(dif & (1 << i)) b = arr[i][b];
    }
    if(a == b) return a;
    for(int i = 20; i >= 0; i--){
        if(arr[i][a] != arr[i][b]){
            a = arr[i][a];
            b = arr[i][b];
        }
    }
    return arr[0][a];
}
void dfs(int x){
    for(auto i : v[x]){
        dep[i] = dep[x] + 1;
        dfs(i);
    }
}
int main(){
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m, a ,b;
    cin >> n >> m;
    for(int i = 2; i <= n; i++){
        cin >> arr[0][i];
        v[arr[0][i]].push_back(i);
    }
    for(int i = 1; i <= 20; i++){
        for(int j = 1; j <= n; j++){
            arr[i][j] = arr[i - 1][arr[i - 1][j]];
        }
    }
    dfs(1);
    while(m--){
        cin >> a >> b;
        cout << lca(a, b) << '\n';
    }
}

```

Luogu P3384 

## 簡單題
Zerojudge b570

TIOJ 1687

CSES #1138

## 難題
CF 1213G

TIOJ 1163

TIOJ 1798

## 其他練習題
TIOJ 1929

TIOJ 1981

TIOJ 1868

CSES #1137

[題目 link](https://cses.fi/problemset/task/1137)

想法: 樹壓平 

```cpp
// 利用時間戳記排好序列 + BIT管理區間
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
ll tree[200005], arr[200005], x;
int in[200005], out[200005], Time = 0;
int n, m, a, b, op, s;
vector<int> v[200005];
void dfs(int x, int pre){
    in[x] = ++Time;
    for(auto i : v[x]){
        if(i == pre) continue;
        dfs(i, x);
    }
    out[x] = Time;
}
ll sum(int k){
    ll ret = 0;
    while(k >= 1){
        ret += tree[k];
        k -= k & -k;
    }
    return ret;
}
void update(int k, ll x){
    while(k <= n){
        tree[k] += x;
        k += k & -k;
    }
}
int main(){
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> arr[i];
    }
    for(int i = 1; i < n; i++){
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    dfs(1, 0);
    // index -> in
    for(int i = 1; i <= n; i++){
        update(in[i], arr[i]);
    }
    while(m--){
        cin >> op >> s;
        if(op & 1){
            cin >> x;
            update(in[s], x - arr[s]);
            arr[s] = x;
        }
        else{
            cout << sum(out[s]) - sum(in[s] - 1) << '\n';
        }
    }
}
```
EXAMPLE

<center>
<img src = "https://i.imgur.com/D3nQqdf.png" width=600, height=450>
</center>
