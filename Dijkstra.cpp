#include "../bits/stdc++.h"
#define rep(i,n) for(int i = 0; i < (n); ++i)
using namespace std;
typedef long long int ll;
typedef pair<int, int> P;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

struct State{
    int at;
    ll cost;
    State(int a, ll c) : at(a), cost(c){}
    bool operator>(const State& s) const{
        return cost > s.cost;
    }
};

struct Edge{
    int to;
    ll cost;
    Edge(int t, ll c) : to(t), cost(c){}
};

using Graph = vector<vector<Edge> >;
const ll INF = 1e15;

void dijkstra(int s, const Graph& G, vector<ll>& minc){
    minc.assign(G.size(), INF);
    priority_queue<State, vector<State>, greater<State> > pq;
    pq.emplace(s, 0);
    minc[s] = 0;
    while(!pq.empty()){
        State cur = pq.top();
        pq.pop();
        if(minc[cur.at] < cur.cost) continue;
        for(const Edge& e : G[cur.at]){
            ll cost = cur.cost + e.cost;
            if(minc[e.to] <= cost) continue;
            minc[e.to] = cost;
            pq.emplace(e.to, cost);
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    s--; t--;
    Graph g1(n), g2(n);
    for(int i = 0; i < m; i++){
        int u, v;
        ll a, b;
        cin >> u >> v >> a >> b;
        u--; v--;
        g1[u].emplace_back(v, a);
        g1[v].emplace_back(u, a);
        g2[u].emplace_back(v, b);
        g2[v].emplace_back(u, b);
    }
    vector<ll> minc1(n, INF), minc2(n, INF);
    dijkstra(s, g1, minc1);
    dijkstra(t, g2, minc2);
    vector<ll> ans(n, INF);
    for(int i = n-1; i >= 0; i--){
        ans[i] = min(ans[i], minc1[i] + minc2[i]);
        if(i < n-1) ans[i] = min(ans[i], ans[i+1]);
    }
    for(int i = 0; i < n; i++){
        cout << INF - ans[i] << endl;
    }
    return 0;
}

/*

#include "bits/stdc++.h"
#define rep(i,n) for(int i = 0; i < (n); ++i)
using namespace std;
typedef long long int ll;
typedef pair<int, int> P;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }

struct Node {
    int at;
    double cost; 
    int prev;
    Node(int at, double cost, int prev) : at(at), cost(cost), prev(prev) {}
    bool operator>(const Node &s) const {
        if (cost != s.cost) return cost > s.cost;
        if (prev != s.prev) return prev > s.prev; //最短経路を辞書順最小にする(省略可)
        return at > s.at;
    }
};

struct Edge {
  int to;
  double cost;  
  Edge(int to, double cost) : to(to), cost(cost) {}  
};

typedef vector<vector<Edge> > AdjList; //隣接リスト

const double INF = 1e20;
const int NONE = -1;

AdjList graph;

//sは始点、mincは最短経路のコスト、Prevは最短経路をたどる際の前の頂点
void dijkstra(int s, vector<double> &minc, vector<int> &Prev){ 
    priority_queue<Node, vector<Node>, greater<Node> > pq;
    pq.push(Node(s, 0, NONE));
    while(!pq.empty()) {
        Node x = pq.top();
        pq.pop();
        if (minc[x.at] != INF) continue;
        minc[x.at] = x.cost;
        Prev[x.at] = x.prev;
        for(int i = 0; i < (int)graph[x.at].size(); i++) {
        	Edge e = graph[x.at][i];
            if (minc[e.to] == INF) {
            	pq.push(Node(e.to, x.cost + e.cost, x.at));
            }
        }
    }
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(false);
	double xs, ys, xt, yt;
	int n;
	cin >> xs >> ys >> xt >> yt >> n;
	vector<double> x(n), y(n), r(n);
	graph = AdjList(n + 2);
	double cost;
	cost = sqrt((xs - xt) * (xs - xt) + (ys - yt) * (ys - yt));
	graph[n].emplace_back(n + 1, cost);
	graph[n + 1].emplace_back(n, cost);
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i] >> r[i];
		cost = max(0.0, sqrt((xs - x[i]) * (xs - x[i]) + (ys - y[i]) * (ys - y[i])) - r[i]);
		graph[i].emplace_back(n, cost);
		graph[n].emplace_back(i, cost);
		cost = max(0.0, sqrt((xt - x[i]) * (xt - x[i]) + (yt - y[i]) * (yt - y[i])) - r[i]);
		graph[i].emplace_back(n + 1, cost);
		graph[n + 1].emplace_back(i, cost);
	}

	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++) {
			cost = max(0.0, sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j])) - r[i] - r[j]);
			graph[i].emplace_back(j, cost);
			graph[j].emplace_back(i, cost);
		}
	}

	vector<double> minc(n + 2, INF);
	vector<int> Prev(n + 2, NONE);

	dijkstra(n, minc, Prev);
	cout << fixed << setprecision(15) << minc[n + 1] << endl;
	return 0;
}

*/