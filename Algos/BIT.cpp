#include <vector>
using namespace std;
typedef vector<long long> vll;
typedef long long ll;

// Internally it's 1-indexed but it's trivially changed to work as 0-indexed
//
// 2^(MAXLOG + 1) < MAXBITN !!
// // if BITN = 2^k + 1
// MAXLOG + 1 < k + _
// MAXLOG < k-1+_
// MAXLOG = k-1
struct BIT{
    int N, MAXLOG;
    vll a;
    void init(int n){
		ll pot = 1, k=0;
		while(pot < n) pot*=2, k++;
        a.resize(pot+2);
        N = pot; MAXLOG = k-1;
    }
    void upd(int p, ll val){
        for(++p; p <= N; p += p & -p)
            a[p] += val;
    }

    // sum[0,p]
    ll sum(int p){
        ll ret = 0;
        for(++p; p; p -= p & -p)
            ret += a[p];
        return ret;
    }

    // gets greatest p such that sum[0,p] <= K
	// Be sure there is such p!
    ll BIT_inv(ll K){
        int ret = 0;
        for(int j = MAXLOG ; j >= 0 ; j--){
            int shift = (1<<j);
            if(a[ret + shift] <= K){
                K -= a[ret + shift];
                ret += shift;
            }
        }
        return --ret;
    }

//    void range_upd(int l, int r, int v){
//        upd(l, v);
//        upd(r+1,-v);
//    }
//    ll point_query(int p){
//        return sum(p);
//    }
};

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


int BIT[MAXN][MAXN];
void UPDATE(int x , int y , int val){ // O(log^2(N))
	for(; x <= N; x += (x & -x)){
		for(int y1 = y; y1 <= N; y1 += (y1 & -y1)){
			BIT[x][y1] += val;
		}
	}
}

// Devuelve la suma de todo el rectangulo desde 1,1 hasta x,y
int SUM(int x,int y){ //O(log^2(N))
	int sum= 0;
	for(; x; x -= x & -x){
		for(int y1 = y;y1; y1 -= y1 & -y1){
			sum += BIT[x][y1];
		}
	}
	return sum;
}
