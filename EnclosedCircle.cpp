#include "../bits/stdc++.h"
#define rep(i,n) for(int i = 0; i < (n); ++i)
using namespace std;
typedef long long int ll;
typedef pair<double, double> P;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

int n;
vector<P> p;

double dist(P a, P b){
	double dx = a.first - b.first;
	double dy = a.second - b.second;
	return sqrt(dx*dx + dy*dy);
}

double f(double x, double y){
	double res = 0;
	for(int i = 0; i < n; i++){
		chmax(res, dist(P(x, y), p[i]));
	}
	return res;
}

double g(double x){
	double l = 0, r = 1000;
	for(int i = 0; i < 100; i++){
		double c1 = (l*2+r)/3;
		double c2 = (l+r*2)/3;
		if(f(x, c1) > f(x, c2)) l = c1;
		else r = c2;
	}
	return f(x, l);
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(false);
	cin >> n;
	p = vector<P>(n);
	for(int i = 0; i < n; i++){
		cin >> p[i].first >> p[i].second;
	}
	double l = 0, r = 1000;
	for(int i = 0; i < 100; i++){
		double c1 = (l*2+r)/3;
		double c2 = (l+r*2)/3;
		if(g(c1) > g(c2)) l = c1;
		else r = c2;
	}
	double ans = g(l);
	cout << fixed << setprecision(10) << ans << endl;
	return 0;
}