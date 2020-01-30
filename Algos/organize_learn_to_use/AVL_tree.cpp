#include <algorithm>
using namespace std;

struct node{
	int key, height, sz;
	node *l, *r;
	node(int k){
		key = k;
		l = r = NULL;
		height = 1;
		sz = 1;
	}
};
typedef node* pnode;

inline int sz(pnode t){
	return t?t->sz:0;
}

inline int height(pnode t){
	return t?t->height:0;
}

inline int bfactor(pnode t){
	return height(t->r)-height(t->l);
}

inline void upd(pnode t){
	int hl = height(t->l), hr = height(t->r);
	t->height = max(hr, hl) + 1;
	t->sz = 1 + sz(t->l) + sz(t->r);
}

inline void rotateright(pnode &t){
	pnode q = t->l;
	t->l = q->r;
	q->r = t;
	upd(t);
	upd(q);
	t=q;
}

inline void rotateleft(pnode &t){
	pnode q = t->r;
	t->r = q->l;
	q->l = t;
	upd(t);
	upd(q);
	t=q;
}

void balance(pnode &t){
	upd(t);
	if(bfactor(t)==2){
		if(bfactor(t->r) < 0)
			rotateright(t->r);
		rotateleft(t);
	}
	if(bfactor(t)==-2){
		if(bfactor(t->l) > 0  )
			rotateleft(t->l);
		rotateright(t);
	}
}

void insert(pnode &t, int k){ //insert k key in a tree with t root
	if(!t) return void(t = new node(k));
	if(k < t->key)
		insert(t->l,k);
	else
		insert(t->r,k);
	balance(t);
}

pnode findmin(pnode t){ // find a node with minimal key in a t tree
	return t->l?findmin(t->l):t;
}

pnode removemin(pnode t){ // deleting a node with minimal key from a t tree
	if( t->l == NULL)
		return t->r;
	t->l = removemin(t->l);
	balance(t); return t;
}

void remove(pnode &t, int k){ // deleting k key from t tree
	if( !t ) return;
	if( k < t->key )
		remove(t->l,k);
	else if( k > t->key )
		remove(t->r,k);
	else{
		pnode l = t->l;
		pnode r = t->r;
		delete t;
		if( !r ) return void(t=l);
		pnode min = findmin(r);
		min->r = removemin(r);
		min->l = l;
		balance(min); t=min; return;
	}
	balance(t);
}

int main(){


}
