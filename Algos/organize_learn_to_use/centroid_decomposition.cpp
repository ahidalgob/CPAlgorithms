
vector<int> G[MAXN];
int par[MAXN], sz[MAXN]; // parent in centroid decomposition
bool cent[MAXN];

int dfs_sz(int u, int p){
	sz[u] = 1;
	FOR(i,0,G[u].size()){
		int v=G[u][i];
		if(cent[v] || v == p) continue;
		sz[u] += dfs_sz(v,u);
	}
	return sz[u];
}

int dfs_cent(int u, int p, int n){
	FOR(i,0,G[u].size()){
		int v=G[u][i];
		if(cent[v] || v==p) continue;
		if(sz[v] > n/2)
			return dfs_cent(v,u,n);
	}
	return u;
}

void decompose(int root, int p=-1){
	int n = dfs_sz(root, p);
	int c = dfs_cent(root, p, n);
	par[c] = p;
	cent[c] = true;
	FOR(i,0,G[c].size()){
		int v=G[c][i];
		if(cent[v]) continue;
		decompose(v,c);
	}
}