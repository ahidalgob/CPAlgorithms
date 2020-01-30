//------------------------------------TARJAN SCC------------------------------------
#define MAXN
vector<int> G[MAXN];
int N;

int td[MAXN], low[MAXN], SCCI[MAXN]; //  para un nodo u, u pertenece a SCC[SCCI[u]]  (SCCI[u] es el indice de la SCC a la cual pertenece u)
vector<vi> SCC;
int SCCN, dfst;
bool onStk[MAXN];
stack<int> stk;

void tarj(int u){
	low[u]=td[u]=dfst++;
	stk.push(u);
	onStk[u]=true;
	FOR(i,0,G[u].size()){
		int v=G[u][i];
		if(td[v]==-1)
			tarj(v);
		if(onStk[v])
			low[u]=min(low[u],low[v]);
	}

	if(low[u]==td[u]){
		vector<int> scc;
		while(true){
			int v=stk.top();stk.pop(); onStk[v]=false;
			SCCI[v]=SCCN;
			scc.pb(v);
			if(u==v) break;
		}
		SCC.pb(scc);
		SCCN++;
	}
}

void tarjanSCC(){
	ms(onStk,false);
	ms(td,-1);
	ms(low,0);
	ms(SCCI, -1);
	dfst=0;
	SCCN=0;
	SCC.clear();
	FOR(u,0,N)
		if(td[u]==-1)
			tarj(u);
}

//------------------------------------TARJAN BICC------------------------------------

/**
 * Tarjan's algorithm for finding biconnected componets in UNDIRECTED GRAPHS.
 *
 * Finds all bridges (isthmus, cut-edges), articulation points (cut-vertex),
 * and biconnected components in a provided undirected graph.
 *
 * @param MAXN          The maximum number of nodes in the graph.
 * @param graph         Adjecency-list description of the graph.
 * @param n             Number of nodes in the graph.

 * @return bridges      All bridges in the graph.
 * @return b_comp       All biconnected components in the graph, the
 *                      components are given as a set of non-repeated
 *                      edges. The direction of the edges follow
 *                      a DFS in the biconneced component.
 * @return a_points     All articulation points in the provided graph.
 *
 * @time: O(|E|+|V|)
 */


#define MAXN
vi G[MAXN];
int N;

vector<vii> BCC;
vii bridges;
vi aPoints;
stack<ii> stk;
int td[MAXN], low[MAXN];

void newBCC(int u, int v){
	int x = BCC.size();
	BCC.pb(vector< pair<int,int> >());
	bool stop = false;
	while(!stop){
		BCC[x].pb(stk.top());
		stop = stk.top().first == u && stk.top().second == v;
		stk.pop();
	}
}

void tarj(int u, int p){
	low[u] = td[u];
	bool isAPoint = false;
	FOR(i,0,G[u].size()){
		int v = G[u][i];
		if(v==p || td[v] > td[u]) continue;
		stk.push(mp(u,v));
		if(td[v]==-1){
			td[v] = td[u]+1;
			tarj(v,u);
			low[u] = min(low[u],low[v]);
			if(low[v] >= td[u]) //u is an articulation point
				isAPoint = true, newBCC(u,v);
			if(low[v]==td[v]) //u - v is a bridge
				bridges.pb(mp(min(u,v),max(u,v)));
		}else low[u] = min(low[u],td[v]);
	}
	//root-nodes need a diffetent analysis
	if(td[u]!=0 && isAPoint) aPoints.pb(u);
}


void findBCC(){
	BCC.clear(), bridges.clear(), aPoints.clear();
	ms(td,-1);
	stk = stack<ii>();
	for(int u=0; u<N; u++) if(td[u]==-1){
		td[u] = 0, tarj(-1,u);

		int cnt = 0;
		for(int i=0; i<E[u].size() && cnt<2 ;i++)
			if(td[E[u][i]]==1) cnt++;
		if(cnt > 1) aPoints.push_back(u);
	}
}
