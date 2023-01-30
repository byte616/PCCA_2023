#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
struct edg{
    int a, b;
} edge[1000005];
int par[10005];
bool destroy[1000005];
int find(int x){
    return x == par[x] ? x : par[x] = find(par[x]);
}
bool uni(int a, int b){
    int _a = find(a), _b = find(b);
    if(_a == _b) return 0;
    par[_a] = _b;
    return 1;
}
int main(){
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m, q, x;
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        cin >> edge[i].a >> edge[i].b;
    }
    for(int i = 1; i <= n; i++){
        par[i] = i;
    }
    cin >> q;
    vector<int> v(q), res(q);
    for(auto &ele : v) cin >> ele, destroy[ele] = 1;
    int ans = n;
    for(int i = 1; i <= m; i++){
        if(destroy[i]) continue;
        if(uni(edge[i].a, edge[i].b)){
            ans -= 1;
        }
    }
    for(int i = v.size() - 1; i >= 0; i--){
        res[i] = ans;
        int j = v[i];
        if(uni(edge[j].a, edge[j].b)){
            ans -= 1;
        }
    }
    for(auto i : res) cout << i << '\n';
}
