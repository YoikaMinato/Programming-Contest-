#include "../bits/stdc++.h"
#define rep(i,n) for(int i = 0; i < (n); ++i)
using namespace std;
typedef long long int ll;
typedef pair<int, int> P;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

// RMQ：[0,n-1] について、区間ごとの最小値を管理する構造体
// set(i,x), build(): i番目の要素をxにセット。まとめてセグ木を構築する。O(n)
// update(a,b,x): 区間[a,b) の要素を x に更新。O(log(n))
// query(a,b): 区間 [a,b) での最小の要素を取得。O(log(n))
// find_rightest(a,b,x): [a,b) で x以下の要素を持つ最右位置を求める。O(log(n))
// find_leftest(a,b,x): [a,b) で x以下の要素を持つ最左位置を求める。O(log(n))

template <typename T>
struct RMQ {
    const T INF = numeric_limits<T>::max();
    int n;
    vector<T> dat, lazy;
    RMQ(int n_) : n(), dat(n_*4, INF), lazy(n_*4, INF) {
        int x = 1;
        while(n_ > x) x *= 2;
        n = x;
    }
 
    void set(int i, T x) { dat[i + n - 1] = x; }
    void build() {
        for (int k = n - 2; k >= 0; k--) dat[k] = min(dat[2 * k + 1], dat[2 * k + 2]);
    }
 
    void eval(int k) {
        if (lazy[k] == INF) return;
        if (k < n - 1) {
            lazy[k * 2 + 1] = lazy[k];
            lazy[k * 2 + 2] = lazy[k];
        }
        dat[k] = lazy[k];
        lazy[k] = INF;
    }
 
    void update(int a, int b, T x, int k, int l, int r) {
        eval(k);
        if (a <= l && r <= b) {
            lazy[k] = x;
            eval(k);
        } else if (a < r && l < b) {            
            update(a, b, x, k * 2 + 1, l, (l + r) / 2); 
            update(a, b, x, k * 2 + 2, (l + r) / 2, r);  
            dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }
    void update(int a, int b, T x) { update(a, b, x, 0, 0, n); }
 
    T query_sub(int a, int b, int k, int l, int r) {
        eval(k);
        if (r <= a || b <= l) { 
            return INF;
        } else if (a <= l && r <= b) { 
            return dat[k];
        } else { 
            T vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
            T vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
            return min(vl, vr);
        }
    }
    T query(int a, int b) { return query_sub(a, b, 0, 0, n); }
 
    T find_rightest(int a, int b, int x) { return find_nearest_sub(a, b, x, 0, 0, n, true); }
    T find_leftest(int a, int b, int x) { return find_nearest_sub(a, b, x, 0, 0, n, false); }
    T find_nearest_sub(int a, int b, int x, int k, int l, int r, bool is_right) {
        eval(k);
        if (dat[k] > x || r <= a || b <= l) {  
            return -1;
        } else if (k >= n - 1) { 
            return (k - (n - 1));
        } else {
            if (is_right) {
                int vr = find_nearest_sub(a, b, x, 2 * k + 2, (l + r) / 2, r, is_right);
                if (vr != -1) {  
                    return vr;
                } else {  
                    return find_nearest_sub(a, b, x, 2 * k + 1, l, (l + r) / 2, is_right);
                }
            } else {
                int vl = find_nearest_sub(a, b, x, 2 * k + 1, l, (l + r) / 2, is_right);
                if (vl != -1) { 
                    return vl;
                } else { 
                    return find_nearest_sub(a, b, x, 2 * k + 2, (l + r) / 2, r, is_right);
                }
            }
        }
    }
};

const ll INF = 1e18;

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	ll n, x;
	cin >> n >> x;
	RMQ<ll> rmq(n);
	vector<ll> a(n);
	rep(i,n){
		cin >> a[i];
		rmq.set(i, a[i]);
	}
	rmq.build();
	ll ans = INF;
	rep(i,n+1){
		ll cost = x * i;
		rep(j,n){
			ll c = INF;
			chmin(c, rmq.query(max(0, j-i), j+1));
			if(j-i < 0) chmin(c, rmq.query(n - (i - j), n));
			cost += c;
		}
		chmin(ans, cost);
	}
	cout << ans << endl;
	return 0;
}