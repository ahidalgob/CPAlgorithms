// [l,r) semi-closed intervals!

const int MAXN = 1<<18, MAXLOG = 18;
int stbl[MAXLOG][MAXN], lg[1 << 20];

ll n, k;
int rmq(int l, int r){
	int p = lg[r - l];
    return min(stbl[p][l],stbl[p][r - (1 << p)]);
}
void make_stbl(){
	FOR(i,2,n+1)
        lg[i] = lg[i >> 1] + 1;
	for (int p = 1; (1 << p)<=n; p++)
		FOR(i,0,n+1-(1<<p))
			stbl[p][i] = min(stbl[p-1][i],stbl[p-1][i + (1 << (p-1))]);
}