//---------------------------------------LCA----------------------------------------------

int D[MAXN];
int anc[MAXN][MAXLOG]; // init -1
void dfs_anc(int u, int p = -1){
	anc[u][0] = p;
	if(p != -1) D[u] = D[p] + 1;
	else D[u]=0;

	FOR(i,1,MAXLOG) if(anc[u][i-1] != -1)
		anc[u][i] = anc[anc[u][i-1]][i-1];

	FOR(i,0,G[u].size()){
		int v=G[u][i];
		if(p != v) dfs_anc(v,u);
	}
}

//Query:
int LCA(int u,int v){
	if(D[v] < D[u]) swap(v,u);

	for(int i=MAXLOG-1; i>-1; i--)
		if(anc[v][i] != -1 && D[anc[v][i]] >= D[u])
			v = anc[v][i];

	if(v == u) return v;

	for(int i=MAXLOG-1; i>-1; i--)
		if(anc[v][i] != anc[u][i])
			v = anc[v][i], u = anc[u][i];

	return anc[v][0];
}
