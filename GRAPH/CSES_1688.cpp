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
