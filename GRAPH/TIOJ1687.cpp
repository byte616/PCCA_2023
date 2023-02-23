#include <iostream>
#include <vector>
using namespace std;
vector<int> v[100005];
int dep[100005], par[100005], arr[20][100005];
int n, q, s, e, k, a, b, ans;
void dfs(int x, int pre){
    for(auto i : v[x]){
        if(i == pre) continue;
        dep[i] = dep[x] + 1;
        par[i] = x;
        dfs(i, x);
    }
}
void build_table(){
    for(int i = 1; i <= n; i++){
        arr[0][i] = par[i];
    }
    for(int i = 1; i < 20; i++){
        for(int j = 1; j <= n; j++){
            arr[i][j] = arr[i - 1][arr[i - 1][j]];
        }
    }
}
int LCA(int a, int b){
    if(dep[a] > dep[b]) swap(a, b);
    int dif = dep[b] - dep[a];
    for(int i = 0; i < 20; i++){
        if(dif & (1 << i)){
            b = arr[i][b];
        }
    }
    if(a == b) return a;
    for(int i = 19; i >= 0; i--){
        if(arr[i][a] != arr[i][b]){
            a = arr[i][a];
            b = arr[i][b];
        }
    }
    return arr[0][a];
}
int main(){
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> q;
    for(int i = 1; i < n; i++){
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    dfs(1, 1);
    build_table();
    while(q--){
        cin >> s >> e >> k;
        int lca = LCA(s, e);
        int path = dep[s] + dep[e] - dep[lca] * 2;
        if(k > path){
            cout << -1 << '\n';
        }
        else{
            if(k <= dep[s] - dep[lca]){
                ans = s;
                for(int i = 0; i < 20; i++){
                    if(k & (1 << i)){
                        ans = arr[i][ans];
                    }
                }
            }
            else{
                k -= (dep[s] - dep[lca]);
                k = (dep[e] - dep[lca]) - k;
                ans = e;
                for(int i = 0; i < 20; i++){
                    if(k & (1 << i)){
                        ans = arr[i][ans];
                    }
                }
            }
            cout << ans << '\n';
        }
    }
}