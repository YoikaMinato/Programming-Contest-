#include "../bits/stdc++.h"
#define rep(i,n) for(int i = 0; i < (n); ++i)
using namespace std;
typedef long long int ll;
typedef pair<int, int> P;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

struct Sieve{
	int n;
	vector<int> f, primes;
	Sieve(int n):n(n), f(n+1){
		f[0] = f[1] = -1;
		for(long long i = 2; i <= n; i++){
			if(f[i]) continue;
			primes.push_back(i);
			f[i] = i;
			for(long long j = i*i; j <= n; j += i){
				if(!f[j]) f[j] = i;
			}
		}
	}
	bool isPrime(int x){return f[x] == x;}
	vector<int> factorList(int x){
		vector<int> res;
		while(x != 1){
			res.push_back(f[x]);
			x /= f[x];
		}
		return res;
	}
	vector<pair<int, int>> factor(int x){
		vector<int> fl = factorList(x);
		if(fl.size() == 0) return {};
		vector<pair<int, int>> res(1, pair<int, int>(fl[0], 0));
		for(int p : fl){
			if(res.back().first == p){
				res.back().second++;
			}
			else{
				res.emplace_back(p, 1);
			}
		}
		return res;
	}
};