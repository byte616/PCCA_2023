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
