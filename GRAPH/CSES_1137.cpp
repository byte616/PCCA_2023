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
