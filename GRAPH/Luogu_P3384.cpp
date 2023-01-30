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
