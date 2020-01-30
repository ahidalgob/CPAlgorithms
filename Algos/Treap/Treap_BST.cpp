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
using namespace std;

void fastIO() {
	std::ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
}

#define FOR(i,f,t) for(int i=f; i<(int)t; i++)
#define FORR(i,f,t) for(int i=f; i>(int)t; i--)
#define pb push_back
#define all(obj) obj.begin(), obj.end()
#define ms(obj, val) memset(obj, val, sizeof(obj))
#define ms2(obj, val, sz) memset(obj, val, sizeof(obj[0])*sz)
#define ri(x) scanf("%d",&x)
#define rl(x) scanf("%lld",&x)
#define rii(x,y) ri(x), ri(y)
#define rll(x,y) rl(x), rl(y)

#define fst first
#define snd second
#define dprintf debug && printf
#define debug false

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;


struct tnode{
	int key;
	int prior, sz;
	tnode *l, *r;
	tnode(int k){
		key = k;
		sz = 1;
		prior = rand();
		l = r = NULL;
	}
};
typedef tnode* ptnode;

int sz(ptnode t){
	return t?t->sz:0;
}
void upd_tnode(ptnode t){
	if(t) t->sz = 1+sz(t->l)+sz(t->r);
}
// l with all elements <= k and r with all elements > r
void split(ptnode t, ptnode &l, ptnode &r, int k){
	if(!t) l=r=NULL;
	else if(t->key<=k) split(t->r, t->r, r, k), l=t;
	else split(t->l, l, t->l, k), r=t;
	upd_tnode(t);
}
void merge(ptnode &t,ptnode l,ptnode r){
	if(!l || !r) t = l?l:r;
	else if(l->prior > r->prior) merge(l->r, l->r, r), t=l;
	else merge(r->l, l, r->l), t=r;
	upd_tnode(t);
}
void insert(ptnode &t, ptnode it){
	if(!t) t=it;
	else if(it->prior > t->prior) split(t, it->l, it->r, it->key), t=it;
	else insert(t->key <= it->key ? t->r : t->l, it);
	upd_tnode(t);
}
void erase(ptnode &t, int k){
	if(!t) return;
	else if(t->key==k){
		ptnode temp=t;
		merge(t, t->l, t->r);
		delete temp;
	}else erase(t->key<k?t->r:t->l, k);
	upd_tnode(t);
}

void erase_tree(ptnode &t){
	if(!t) return;
	erase_tree(t->l);
	erase_tree(t->r);
	delete t;
	t=NULL;
}


int main(){
	srand(time(NULL));
}
