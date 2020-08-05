#include "../bits/stdc++.h"
#define rep(i,n) for(int i = 0; i < (n); ++i)
using namespace std;
typedef long long int ll;
typedef pair<int, int> P;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	int n, m, k;
	cin >> n >> m >> k;
	vector<string> a(n);
	rep(i,n) cin >> a[i];
	vector<vector<ll>> sum1(n+1, vector<ll>(m+1, 0)), sum2(n+1, vector<ll>(m+1, 0)),sum3(n+1, vector<ll>(m+1, 0));
	rep(i,n)rep(j,m) sum1[i+1][j+1] = sum1[i][j+1] + sum1[i+1][j] - sum1[i][j] + (a[i][j] == 'J');
	rep(i,n)rep(j,m) sum2[i+1][j+1] = sum2[i][j+1] + sum2[i+1][j] - sum2[i][j] + (a[i][j] == 'O');
	rep(i,n)rep(j,m) sum3[i+1][j+1] = sum3[i][j+1] + sum3[i+1][j] - sum3[i][j] + (a[i][j] == 'I');
	rep(i,k){
		int h1, w1, h2, w2;
		cin >> h1 >> w1 >> h2 >> w2;
		h1--; w1--;
		cout << sum1[h2][w2] - sum1[h1][w2] - sum1[h2][w1] + sum1[h1][w1] << " " << sum2[h2][w2] - sum2[h1][w2] - sum2[h2][w1] + sum2[h1][w1] << " " << sum3[h2][w2] - sum3[h1][w2] - sum3[h2][w1] + sum3[h1][w1] << '\n';
	}
	return 0;
}