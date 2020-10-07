#include "../bits/stdc++.h"
#define rep(i,n) for(int i = 0; i < (n); ++i)
using namespace std;
typedef long long int ll;
typedef pair<int, int> P;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

template<typename T>
struct BIT{
    private:
        vector<T> array;
        const int n;
    public:
        BIT(int _n) : array(_n + 1, 0), n(_n) {}
        // [1, i], i is 1-indexed
        T sum(int i){
            T s = 0;
            while(i > 0){
                s += array[i];
                i -= i & -i;
            }
            return s;
        }
        // [i, j), i and j are 1-indexed
        T sum(int i, int j){
            T ret_i = sum(i-1);
            T ret_j = sum(j);
            return ret_j - ret_i;
        }
        // i is 1-indexed
        void add(int i, T x){
            while(i <= n){
                array[i] += x;
                i += i & -i;
            }
        }

        // debug
        void print(){
            for(int i = 1; i < (int)array.size(); ++i){
                cout << sum(i, i+1) << " ";
            }
            cout << endl;
        }
};

template<typename T>
struct twodimBIT{
    private:
        vector<vector<T>> array;
        const int n;
        const int m;
    public:
        twodimBIT(int _n, int _m) : array(_n+1, vector<T>(_m+1, 0)), n(_n), m(_m) {}
        //(1, 1)から(x, y)までの累積和を求める．
        T sum(int x, int y){
            T s = 0;
            for(int i = x; i > 0; i-=i&(-i)){
                for(int j = y; j > 0; j-=j&(-j)){
                    s += array[i][j];
                }
            }
            return s;
        }
        //[(x1, y1), (x2, y2)]の要素の総和
        T sum(int x1, int y1, int x2, int y2){
            return sum(x2, y2) - sum(x1-1, y2) - sum(x2, y1-1) + sum(x1-1, y1-1);
        }
        //(x, y)に要素kを追加
        void add(int x, int y, T k){
            for(int i = x; i <= n; i+=i&(-i)){
                for(int j = y; j <= m; j+=j&(-j)){
                    array[i][j] += k;
                }
            }
        }
};

//バブルソートの回数
int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    BIT<int> b(n);
    vector<int> a(n);
    map<int, int> m;
    rep(i,n){
        cin >> a[i];
        m[a[i]];
    }
    int newnum = 1;
    for(auto &x : m) x.second = newnum++;
    rep(i,n) a[i] = m[a[i]];
    int ans = 0;
    rep(j,n){
        ans += j - b.sum(a[j]);
        b.add(a[j], 1);
    }
    cout << ans << endl;
}

//二次元累積和
int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
    int m, n, k;
    cin >> m >> n >> k;
    twodimBIT<int> cntJ(m, n), cntO(m, n), cntI(m, n);
    rep(i,m){
        string s;
        cin >> s;
        rep(j,n){
            if(s[j] == 'J') cntJ.add(i+1, j+1, 1);
            if(s[j] == 'O') cntO.add(i+1, j+1, 1);
            if(s[j] == 'I') cntI.add(i+1, j+1, 1);
        }
    }
    rep(i,k){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        int ansJ = cntJ.sum(x1, y1, x2, y2);
        int ansO = cntO.sum(x1, y1, x2, y2);
        int ansI = cntI.sum(x1, y1, x2, y2);
        cout << ansJ << " " << ansO << " " << ansI << endl;
    }
	return 0;
}

//l, r, xが与えられるので．A_l, A_(l+1), …, A_rにxを加える．
//l, rが与えられるので，A_l, A_(l+1), …, A_rの和を求める．
int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    BIT<int> bit0(n), bit1(n);
    vector<int> a(n+1);
    rep(i,n){
        cin >> a[i+1];
        bit0.add(i+1, a[i+1]);
    }
    vector<char> t(q);
    vector<int> l(q), r(q), x(q);
    rep(i,q){
        cin >> t[i] >> l[i] >> r[i];
        if(t[i] == 'C'){
            cin >> x[i];
            bit0.add(l[i], -x[i] * (l[i] - 1));
            bit1.add(l[i], x[i]);
            bit0.add(r[i]+1, x[i] * r[i]);
            bit1.add(r[i]+1, -x[i]);
        }
        else{
            int ans = 0;
            ans += bit0.sum(r[i]) + bit1.sum(r[i]) * r[i];
            ans -= bit0.sum(l[i] - 1) + bit1.sum(l[i] - 1) * (l[i] - 1);
            cout << ans << endl;
        }
    }
}