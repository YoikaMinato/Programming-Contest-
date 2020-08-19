#include "../bits/stdc++.h"
#define rep(i,n) for(int i = 0; i < (n); ++i)
using namespace std;
typedef long long int ll;
typedef pair<int, int> P;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

const int MAX_V = 1001;
const int MAX_E = 2001;
const ll INF = 1e18;

struct edge{
    int from, to;
    ll cost;
};

edge es[MAX_E];

ll d[MAX_V];
int V, E;
bool update;
bool negative[MAX_V];

void bellmanford(int s){
    for(int i = 1; i <= V; i++) d[i] = INF;
    d[s] = 0;
    for(int j = 0; j < V-1; j++){
        update = false;
        for(int i = 0; i < E; i++){
            edge e = es[i];
            if(d[e.from] != INF && d[e.to] > d[e.from] + e.cost){
                d[e.to] = d[e.from] + e.cost;
                update = true;
            }
        }
        if(!update) break;
    }
    for(int j = 0; j < V; j++){
        for(int i = 0; i < E; i++){
            edge e = es[i];
            if(d[e.from] == INF) continue;
            if(d[e.to] > d[e.from] + e.cost){
                d[e.to] = d[e.from] + e.cost;
                negative[e.to] = true;
            }
            if(negative[e.from]) negative[e.to] = true;
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> V >> E;
    for(int i = 0; i < E; i++){
        int from, to;
        ll cost;
        cin >> from >> to >> cost;
        es[i] = edge{from, to, -cost};
    }
    bellmanford(1);
    if(negative[V]) cout << "inf" << endl;
    else cout << -d[V] << endl;
    return 0;
}

/*
const int INF = 1e9;

vector<int> to[2505];
vector<int> rto[2505];
bool reachableFrom1[2505];
bool reachableFromN[2505];
bool ok[2505];

void dfs(int v){
	if(reachableFrom1[v]) return;
	reachableFrom1[v] = true;
	for(int u : to[v]){
		dfs(u);
	}
}

void rdfs(int v){
	if(reachableFromN[v]) return;
	reachableFromN[v] = true;
	for(int u : rto[v]){
		rdfs(u);
	}
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	int n, m, p;
	cin >> n >> m >> p;
	vector<tuple<int, int, int>> edges;
	rep(i,m){
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--;
		c -= p;
		c = -c;
		edges.emplace_back(a, b, c);
		to[a].push_back(b);
		rto[b].push_back(a);
	}
	dfs(0);
	rdfs(n-1);
	rep(i,n) ok[i] = reachableFrom1[i]&reachableFromN[i];
	vector<int> d(n, INF);
	d[0] = 0;
	bool upd = true;
	int step = 0;
	while(upd){
		upd = false;
		rep(i,m){
			int a, b, c;
			tie(a, b, c) = edges[i];
			if(!ok[a]) continue;
			if(!ok[b]) continue;
			int newD = d[a] + c;
			if(newD < d[b]){
				upd = true;
				d[b] = newD;
			}
		}
		step++;
		if(step > n){
			cout << -1 << endl;
			return 0;
		}
	}
	int ans = -d[n-1];
	chmax(ans, 0);
	cout << ans << endl;
	return 0;
}
*/