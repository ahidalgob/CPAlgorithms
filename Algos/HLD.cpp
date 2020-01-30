#include <vector>
using namespace std;

typedef vector<int> vi;
const int MAXN = 1e5+5; // TODO change
// taken from adamant's codeforces blog: https://codeforces.com/blog/entry/53170

vi G[MAXN];

int sz[MAXN];
int in[MAXN], out[MAXN], t;		// v's subtree is:			[in[v], out[v])
int nxt[MAXN];					// path from v to it's <<heavy head>>
								// on the path up is:		[in[nxt[v]], in[v]]

void dfs_sz(int v = 0) {
    sz[v] = 1;
    for(auto &u: G[v]) {
        dfs_sz(u);
        sz[v] += sz[u];
        if(sz[u] > sz[G[v][0]]) {
            swap(u, G[v][0]);
        }
    }
}

void dfs_hld(int v = 0) {
    in[v] = t++;
    for(auto u: G[v]) {
        nxt[u] = (u == G[v][0] ? nxt[v] : u);
        dfs_hld(u);
    }
    out[v] = t;
}
