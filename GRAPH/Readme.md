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
### Zerojudge d808 

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

### CSES #1688 

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

### Luogu P3384 

[題目 link](https://www.luogu.com.cn/problem/P3384#submit)

想法: heavy-light decomposition

```cpp
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
vector<int> v[100005];
ll p, z, arr[100005], Time;
// depth : parent : subtree size
int dep[100005], par[100005], sub[100005];
// max son's index : chain's top : dfs id : reorder index
int mxson[100005], topf[100005], id[100005], idx[100005];
int n, m, r, a, b, op, x, y;
void dfs1(int x, int pre){
    sub[x] = 1;
    mxson[x] = 0;
    for(auto i :v[x]){
        if(i == pre) continue;
        dep[i] = dep[x] + 1;
        par[i] = x;
        dfs1(i, x);
        // find subtree size biggest
        sub[x] += sub[i];
        if(sub[i] > sub[mxson[x]]){
            mxson[x] = i;
        }
    }
}
void dfs2(int x, int top){
    topf[x] = top;
    id[x] = ++Time;
    idx[Time] = x; // for segment tree
    // search mxson first -> ensure heavy chain's DFS order continous
    if(mxson[x]){
        dfs2(mxson[x], top);
    }
    // then, DFS other child(light)
    for(auto i : v[x]){
        if(i != par[x] && i != mxson[x]){
            dfs2(i, i);
        }
    }
}
// segment tree
struct node{
    ll val, add;
} tree[400005];
void build(int i, int l, int r){
    if(l == r){
        tree[i].val = arr[idx[l]];
        return;
    }
    int mid = (l + r) / 2;
    build(i * 2, l, mid);
    build(i * 2 + 1, mid + 1, r);
    tree[i].val = (tree[i * 2].val + tree[i * 2 + 1].val) % p;
}
void update(int i, int l, int r, int L, int R, ll v){
    if(l > R || r < L) return;
    int right = min(R, r), left = max(l, L);
    tree[i].val = (tree[i].val + v * (right - left + 1)) % p;
    if(L <= l && r <= R){
        tree[i].add = (tree[i].add + v) % p;
        return;
    }
    int mid = (l + r) / 2;
    update(i * 2, l, mid, L, R, v);
    update(i * 2 + 1, mid + 1, r, L, R, v);
}
ll query(int i, int l, int r, int L, int R, ll add){
    if(l > R || r < L) return 0;
    if(L <= l && r <= R) return (tree[i].val + add * (r - l + 1)) % p;
    int mid = (l + r) / 2;
    ll ret = query(i * 2, l, mid, L, R, add + tree[i].add) % p;
    ret += query(i * 2 + 1, mid + 1, r, L, R, add + tree[i].add) % p;
    return ret % p;
}
int main(){
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m >> r >> p;
    for(int i = 1; i <= n; i++){
        cin >> arr[i];
    }
    for(int i = 1; i < n; i++){
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    dfs1(r, 0);
    dfs2(r, r);
    build(1, 1, n);
    while(m--){
        cin >> op;
        if(op == 1){
            cin >> x >> y >> z;
            while(topf[x] != topf[y]){ // different chain
                // x always deep chain, x -> jump
                if(dep[topf[x]] < dep[topf[y]]) swap(x, y);
                update(1, 1, n, id[topf[x]], id[x], z);
                // jump to parent(escap this chain to another one)
                x = par[topf[x]];
            }
            // on the same chain, check the boundary and update
            if(dep[x] > dep[y]) swap(x, y);
            update(1, 1, n, id[x], id[y], z);
        }
        else if(op == 2){
            cin >> x >> y;
            ll res = 0;
            while(topf[x] != topf[y]){
                if(dep[topf[x]] < dep[topf[y]]) swap(x, y);
                res = (res + query(1, 1, n, id[topf[x]], id[x], 0)) % p;
                x = par[topf[x]];
            }
            if(dep[x] > dep[y]) swap(x, y);
            res = (res + query(1, 1, n, id[x], id[y], 0)) % p;
            cout << res << '\n';
        }
        else if(op == 3){
            cin >> x >> z;
            update(1, 1, n, id[x], id[x] + sub[x] - 1, z);
        }
        else{
            cin >> x;
            cout << query(1, 1, n, id[x], id[x] + sub[x] - 1, 0) << '\n';
        }
    }
}

```

## 簡單題
### Zerojudge b570

### TIOJ 1687

### CSES #1138

## 難題
### CF 1213G

### TIOJ 1163

### TIOJ 1798

## 其他練習題
### TIOJ 1929

### TIOJ 1981

### TIOJ 1868

### CSES #1137

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
