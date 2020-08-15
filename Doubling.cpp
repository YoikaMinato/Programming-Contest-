#include "../bits/stdc++.h"
#define rep(i,n) for(int i = 0; i < (n); ++i)
using namespace std;
typedef long long int ll;
typedef pair<int, int> P;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

const int D = 60;
const int MAX_N = 200005;
int to[D][MAX_N];

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int n;
    ll k;
    cin >> n >> k;
    rep(i,n){
        cin >> to[0][i];
        to[0][i]--;
    }
    rep(i,D-1){
        rep(j,n){
            to[i+1][j] = to[i][to[i][j]];
        }
    }
    int v = 0;
    for(int i = D-1; i >= 0; --i){
        ll l = 1LL<<i;
        if(l <= k){
            v = to[i][v];
            k -= l;
        }
    }
    cout << v + 1 << endl;
    return 0;
}