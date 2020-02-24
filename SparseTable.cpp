//marico el que lo lea
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <stdlib.h>
#include <assert.h>
using namespace std;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <class T>
using vv = vector<vector<T>>;


template<class T>
struct SparseTable{
	int N, LG;
	vv<T> t;
	const T& (*merge)(const T&, const T&);
	SparseTable(vector<T> a, const T& (*f)(const T&, const T&)){
		merge =  f;
		N = a.size();
		LG = 32 - __builtin_clz(N);

		t.resize(LG, vector<T>(N));
		for(int i=0; i<N; i++) t[0][i] = a[i];
		for(int e=1; e<LG; e++){
			int sz = 1<<e;
			for(int l=0; l+sz-1<N; l++){
				t[e][l] = merge(t[e-1][l], t[e-1][l+sz/2]);
			}

		}
	}
	// semi-open [l, r)
	T query(int l, int r){
		assert(l >= 0 && r <= N);
		int sz=r-l;
		assert(sz > 0);
		int b = 31 - __builtin_clz(sz);
		sz = 1<<b;
		return merge(t[b][l], t[b][r-sz]);
	}
};

template<class T>
struct SparseTable2D{
	int R, C, LGR, LGC;
	vv<vv<T>> t;
	const T& (*merge)(const T&, const T&);
	SparseTable2D(vv<T> a, const T& (*f)(const T&, const T&)){
		merge =  f;
		R = a.size();
		C = a[0].size();
		LGR = 32 - __builtin_clz(R);
		LGC = 32 - __builtin_clz(C);

		t.resize(LGR, vector<vv<T>>(LGC, vv<T>(R, vector<T>(C))));
		for(int r=0; r<R; r++) for(int c=0; c<C; c++)
			t[0][0][r][c] = a[r][c];

		for(int lr=1; lr<LGR; lr++){
			int szr = 1<<lr;
			for(int r=0; r+szr-1<R; r++) for(int c=0; c<C; c++){
				t[lr][0][r][c] = merge(t[lr-1][0][r][c], t[lr-1][0][r+szr/2][c]);
			}
		}
		for(int lc=1; lc<LGC; lc++){
			int szc = 1<<lc;
			for(int r=0; r<R; r++) for(int c=0; c+szc-1<C; c++){
				t[0][lc][r][c] = merge(t[0][lc-1][r][c], t[0][lc-1][r][c+szc/2]);
			}
		}

		for(int lr=1; lr<LGR; lr++) for(int lc=1; lc<LGC; lc++){
			int szr = 1<<lr, szc = 1<<lc;
			for(int r=0; r+szr-1<R; r++) for(int c=0; c+szc-1<C; c++){
				t[lr][lc][r][c] =
					merge(t[lr-1][lc][r][c], t[lr-1][lc][r+szr/2][c]);
			}
		}
	}
	// semi-open [r1, r2) [c1, c2)
	T query(int r1, int c1, int r2, int c2){
		assert(r1 >= 0 && r2 <= R);
		assert(c1 >= 0 && c2 <= C);
		int szr=r2-r1,
			szc=c2-c1;
		assert(szr > 0 && szc > 0);
		int lr = 31 - __builtin_clz(szr),
			lc = 31 - __builtin_clz(szc);
		szr = 1<<lr;
		szc = 1<<lc;
		return merge( merge(t[lr][lc][r1][c1], t[lr][lc][r2-szr][c1])
					, merge(t[lr][lc][r1][c2-szc], t[lr][lc][r2-szr][c2-szc]) );
	}
};

const int& mymax(const int& a, const int& b){
	return a>b?a:b;
}

int main(){
	vector<int> a = {5,-1,3,-5};
	SparseTable<int> mint(a, min);
	SparseTable<int> maxt(a, max);
	//printf("%d\n", mint.query(0, 4));

	vv<int> ab = { {5, -1, 3, 2}
				 , {1, -2, 2, -3}
				 , {0, 2, 10, -5}};
	SparseTable2D<int> mint2d(ab, min);
	SparseTable2D<int> maxt2d(ab, max);
	printf("%d\n", mint2d.query(0, 3, 0, 4));
	printf("%d\n", mint2d.query(0, 2, 0, 4));
	printf("%d\n", mint2d.query(0, 3, 0, 3));
	printf("%d\n", mint2d.query(0, 3, 2, 3));

}
