#include <vector>
#include <cstdio>
#include <map>
#include <stack>
using namespace std;

#define FOR(i,f,t) for(int i=f; i<(int)t; i++)
#define pb push_back
#define fst first
#define snd second
typedef vector<int> vi;
typedef pair<int, int> ii;

#define ADD 0
#define REMOVE 1
#define CHECK 2
struct DSU_query{
	int t, other_end, v, u, id;
};
// first add al the changes and queries with add, remove and check
// then call init and solve.
struct DSU{
	map<pair<int, int>, int> adds;
	vector<DSU_query> q;
	vi ans;
	void add(int v, int u){
		if(v>u) swap(v,u);
		adds[{v,u}] = q.size();
		q.pb({ADD, -1, v, u});
	}
	void remove(int v, int u){
		if(v>u) swap(v,u);
		int a = adds[{v,u}];
		adds.erase({v,u});
		q[a].other_end = q.size();
		q.pb({REMOVE, a, v, u});
	}
	void check(){
		q.pb({CHECK, -1, -1, -1, int(ans.size())});
		ans.pb(0);
	}

	int n;
	vi rep, rnk, dst;
	stack<pair<int*, int>> stk;
	int bipartite=true;
	int init(int _n){
		while(adds.size()) remove(adds.begin()->fst.fst, adds.begin()->fst.snd);
		n = _n;
		rep.resize(n);
		rnk.resize(n);
		dst.resize(n);
		FOR(i,0,n) rep[i]=i;
	}
	void assign(int *a, int x){
		stk.push({a,*a});
		*a = x;
	}
	void roll_back(int s){
		while(stk.size() > s){
			*(stk.top().fst) = stk.top().snd;
			stk.pop();
		}
	}
	int find(int v){
		if(rep[v]==v) return v;
		return find(rep[v]);
	}
	int parity(int v){
		if(rep[v]==v) return dst[v];
		return dst[v]^parity(rep[v]);
	}
	void connect(int v, int u){
		int parv = parity(v), paru = parity(u);
		v = find(v); u = find(u);
		if(v==u){
			if(parv == paru) assign(&bipartite, 0);
		}else{
			if(rnk[v] < rnk[u]) swap(v,u),swap(parv, paru);
			assign(&rep[u], v);
			assign(&rnk[v], rnk[v] + (rnk[v]==rnk[u]));
			assign(&dst[u], parv^paru^1);
		}
	}
	void solve(){solve(0, q.size());}
	void solve(int l, int r){
		if(l+1 == r){
			if(q[l].t==CHECK) ans[q[l].id]=bipartite;
			return;
		}
		int mid = (l+r)/2;
		int snap = stk.size();
		FOR(i,l,mid)
			if(q[i].t == ADD && q[i].other_end >= r) connect(q[i].v, q[i].u);
		solve(mid,r);
		roll_back(snap);

		FOR(i,mid,r)
			if(q[i].t == REMOVE && q[i].other_end < l) connect(q[i].v, q[i].u);
		solve(l,mid);
		roll_back(snap);
	}
};

int main(){}