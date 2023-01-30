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

