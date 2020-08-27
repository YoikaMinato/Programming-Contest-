#include "../bits/stdc++.h"
#define rep(i,n) for(int i = 0; i < (n); ++i)
using namespace std;
typedef long long int ll;
typedef pair<int, int> P;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

template<typename T>
struct BIT{
    int n;
    vector<T> d;
    BIT(int n = 0):n(n), d(n+1){}
    void add(int i, T x = 1){
        for(i++; i <= n; i += i&-i){
            d[i] += x;
        }
    }
    T sum(int i){
        T x = 0;
        for(i++; i; i -= i&-i){
            x += d[i];
        }
        return x;
    }
};

template<typename T>
struct BIT{
    int n, p;
    vector<T> d;
    BIT(int n = 0):n(n), d(n+1){
        p = 1;
        while(p < n) p *= 2;
    }
    void add(int i, T x = 1){
        for(i++; i <= n; i += i&-i){
            d[i] += x;
        }
    }
    T sum(int i){
        T x = 0;
        for(i++; i; i -= i&-i){
            x += d[i];
        }
        return x;
    }

    // v0 + v1 + v2 + ... + vx >= w となる最小のxを求める
    int lower_bound(T w){
        if(w <= 0) return 0;
        int x = 0;
        for(int i = p; i; i /= 2){
            if(i+x <= n && array[i+x] <= w){
                w -= array[i+x];
                x += i;
            }
        }
        return x;
    }
};

//example(abc153_f)
int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
    int n, d, a;
    cin >> n >> d >> a;
    vector<P> p(n);
    rep(i,n) cin >> p[i].first >> p[i].second;
    sort(p.begin(), p.end());
    BIT<ll> bit(n+1);
    ll ans = 0;
    rep(i,n){
        ll x = p[i].first;
        ll h = p[i].second;
        h -= bit.sum(i);
        if(h <= 0) continue;
        ll num = (h+a-1)/a;
        ans += num;
        ll damage = num*a;
        bit.add(i, damage);
        int rx = min(x+d*2, 1001001001LL);
        int j = upper_bound(p.begin(), p.end(), P(rx+1, -1)) - p.begin();
        bit.add(j, -damage);
    }
    cout << ans << endl;
	return 0;
}