#include <cstdio>
#include <vector>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

typedef vector<long long> vll;
typedef long long ll;

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

struct TrivialBIT{
    int N;
    vll a;
    void init(int n){
        a.resize(n+2);
        N = n;
    }
    void upd(int p, ll val){
        a[p] += val;
    }

    // sum[0,p]
    ll sum(int p){
        ll ret = 0;
        for(int i=0; i<(int)p+1; i++)
            ret += a[i];
        return ret;
    }

    // gets greatest p such that sum[0,p] <= K
    ll BIT_inv(ll K){
        ll acc = 0;
        for(int i=0; i<(int)N+1; i++){
			acc += a[i];
			if(acc > K) return i-1;
		}
		return N;
    }
};


int main(){
	srand(time(NULL));
	for(int TC=0; TC<(int)40; TC++){
		printf("\r%d/40",TC+1); fflush(stdout);
		BIT bit;
		TrivialBIT bit2;

		int n = 1000;
		bit.init(n); bit2.init(n);


		ll totalsum = 0;
		for(int i=0; i<(int)100000; i++){
			int p = rand() % n;
			ll val = (1LL*rand()*RAND_MAX + rand()) % (1LL << 40);
			bit.upd(p, val), bit2.upd(p, val);
			totalsum += val;
		}

		for(int i=0; i<(int)n; i++){
			//if(bit.sum(i) != bit2.sum(i)){
				//printf("sum(%d)=%lld != sum(%d)=%lld\n", i, bit.sum(i), i, bit2.sum(i));
				//return 0;
			//}
			assert(bit.sum(i) == bit2.sum(i));
		}

		for(int i=0; i<(int)1000000; i++){
			ll val = (1LL*rand()*RAND_MAX + rand()) % totalsum;

			assert(bit.BIT_inv(val) == bit2.BIT_inv(val));
		}
	}
}
