#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <climits>
#include <cctype>
#include <set>

//#include <bits/stdc++.h>

#define FOR(i,m,n) for(int i=m; i<n; i++)
#define ms(obj, val) memset(obj, val, sizeof(obj))
#define pb push_back
#define ri(x) scanf("%d",&x)
#define rii(x,y) scanf("%d %d",&x, &y)

using namespace std;

typedef long long ll;
typedef vector<int> vi;


#define dprintf debug && printf
bool debug = false;


ios_base::sync_with_stdio(false);




ll gcd(ll a, ll b){ return b ? gcd(b, a % b) : a; }
ll mcm(ll a, ll b){ return a * b / gcd(a, b); }

ll sq(ll a) { return a*a; }
ll pot(ll a, ll e){ return e ? sq(pot(a, e >> 1))*(e & 1 ? a : 1) : 1; }
ll potMod(ll a, ll e){ return e ? ((sq(potMod(a, e >> 1)) % MOD)*(e & 1 ? a : 1)) % MOD : 1; }



//##########################################################  TEORIA DE NUMEROS  ##########################################################

#define MAXSN
bool sieve[MAXSN];
void fillSieve(){
	ms(sieve,true);
	sieve[0]=sieve[1]=false;
	for(ll i=2; i*i<=MAXSN; i++){
		if(sieve[i]){
			for(ll j=i*i; j<MAXSN; j+=i){
				sieve[j]=false;
			}
		}
	}
}



#define MAXSN
bool sieve[MAXSN];
vi p;
void fillSieve(){
	ms(sieve,true);
	sieve[0]=sieve[1]=false;
	for(ll i=2; i<MAXSN; i++){
		if(sieve[i]){
			p.pb(i);
			for(ll j=i*i; j<MAXSN; j+=i){
				sieve[j]=false;
			}
		}
	}
}






//##########################################################  RECURRENCIAS  ##########################################################

#define MN 2 //matriz MNxMN
typedef vector<ll>  vll;
typedef vector<vll>  MAT;
MAT operator*(MAT &a, MAT &b) {
	MAT res(MN, vll(MN));
	FOR(i,0,MN) FOR(j,0,MN) FOR(k,0,MN)
		res[i][j] = (res[i][j] + (a[i][k] * b[k][j]) % MOD) % MOD;
		//res[i][j] = res[i][j] + a[i][k] * b[k][j];
	return res;
}

MAT pot(MAT b, ll e){
	if(e==1) return b;
	if(e==2) return b*b;
	MAT r = pot(pot(b,e/2),2);
	if(e&1) return b*r;
	return r;
}

ll fib(ll n){
	if(n==0)
		return 0;
	else if(n==2 || n==1)
		return 1;
	MAT F(MN, vll(MN,1)); F[1][1]=0;
	return pot(F,n-1)[0][0];
}












//########################################################## FFT ##########################################################

#include <complex>
typedef complex<double> cpx;
const double dos_pi = 4.0*acos(0.0);
void FFT(cpx *x, cpx *y, int dx, int N, int dir){
	if(N>1){
		FFT(x, y, 2*dx, N/2, dir);
		FFT(x+dx, y+N/2, 2*dx, N/2, dir);
		for(int i=0; i<N/2; i++){
			cpx even=y[i], odd=y[i+N/2], twiddle=exp(cpx(0,dir*dos_pi*i/N));
			y[i]=even+twiddle*odd;
			y[i+N/2]=even-twiddle*odd;
		}
	}else y[0]=x[0];
}





uint next_mask(uint mask){
	uint t = mask | (mask - 1);
	return  (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(mask) + 1));
}
// Iterar sobre todos las mascaras de tamano N con m bits prendidos
int N=4, m=2;
int mask=(1<<m)-1;
for(int mask=(1<<m)-1; !(mask & (1<<N)); mask=next_mask(mask)){
	
}

//Iterar sobre todas las submascaras de mask de forma creciente (si incluye vacio)
for (int sub = 0 ; sub = sub - mask & mask ;) {
	
}

//Iterar sobre todas las submascaras de mask de forma decreciente (no incluye vacio)
for(int sub = (mask-1) & mask ; sub; sub = (sub-1) & mask )  {
	
}
