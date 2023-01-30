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
