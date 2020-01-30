#include <vector>
#include <cstring>
#include <queue>
using namespace std;

#define FOR(i,f,t) for(int i=f; i<(int)t; i++)
#define FORR(i,f,t) for(int i=f; i>(int)t; i--)
#define pb push_back
#define ms(obj, val) memset(obj, val, sizeof(obj))
#define ms2(obj, val, sz) memset(obj, val, sizeof(obj[0])*sz)
typedef vector<int> vi;
typedef long long ll;

const int MAXN = 1e4;
const ll INF = 0x3f3f3f3f3f3f3f3f;

struct edge {
	int a, b;
	ll cap, cost;
};

int N, s, t;
int from[MAXN];
ll d[MAXN];
bool in_q[MAXN];
vector<edge> e;
vi G[MAXN];

void add_edge(int a, int b, ll cap, ll cost) {
	edge e1 = { a, b, cap, cost};
	edge e2 = { b, a, 0, -cost};
	G[a].pb((int)e.size());
	e.pb(e1);
	G[b].pb((int) e.size());
	e.pb(e2);
}

void augment(ll &flow, ll &cost, ll flow_limit=INF){
	cost = flow = 0;
	ms2(in_q,false,N);
	ms2(from,-1,N);
	ms2(d,-1,N);
	in_q[s] = true;
	queue<int> q;
	q.push(s);
	d[s] = 0;
	while(!q.empty()){
		int v=q.front(); q.pop(); in_q[v] = false;
		FOR(i,0,G[v].size()){
			int id=G[v][i];
			if(e[id].cap == 0)continue;
			int u=e[id].b;
			if(d[v]+e[id].cost < d[u]){
				d[u] = d[v] + e[id].cost;
				from[u] = id;
				if(!in_q[u])
					q.push(u), in_q[u]=true;
			}
		}
	}
	if(from[t]==-1) return;
	flow = flow_limit;
	int cur=t, prev;
	while(from[cur] != -1){
		flow = min(flow, e[from[cur]].cap);
		cur = e[from[cur]].a;
	}
	cur=t;
	while(from[cur] != -1){
		cost += e[from[cur]].cost * flow;
		e[from[cur]].cap -= flow;
		e[from[cur]^1].cap += flow;
		cur = e[from[cur]].a;
	}
}

pair<ll, ll> min_cost_flow(ll flow_limit){
	ll flow=0, cost=0, f, c;
	while(flow < flow_limit){
		augment(f, c);
		if(!f) break;
		flow += f; cost += c;
	}
	return {flow, cost};
}



int main(){

}