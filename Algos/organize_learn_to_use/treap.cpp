#include <iostream>
#include <algorithm>
using namespace std;

// La semilla de rand se debe inicializar con 'srand(time(NULL));'
// Sirve hacerlo al principio del programa

struct node{
	int key, prior, sz;
	node *l, *r;
	node(int k){
		key = k;
		sz = 1;
		prior = rand();
		l = r = NULL;
	}
};
typedef node* pnode;
int sz(pnode t){
	return t?t->sz:0;
}
void upd_sz(pnode t){
	if(t) t->sz = 1+sz(t->l)+sz(t->r);
}
// el elemento con clave key va a l
void split(pnode t, pnode &l, pnode &r, int key){
	if(!t) l=r=NULL;
	else if(t->key<=key) split(t->r, t->r, r, key), l=t;
	else split(t->l, l, t->l, key), r=t;    
	upd_sz(t);
}
void merge(pnode &t,pnode l,pnode r){
	if(!l || !r) t = l?l:r;
	else if(l->prior > r->prior) merge(l->r, l->r, r), t=l;
	else merge(r->l, l, r->l), t=r;
	upd_sz(t);
}
void insert(pnode &t, pnode it){
	if(!t) t=it;    
	else if(it->prior > t->prior) split(t, it->l, it->r, it->key), t=it;
	else insert(t->key <= it->key ? t->r : t->l, it);
	upd_sz(t);
}
void erase(pnode &t, int key){
	if(!t) return;
	else if(t->key==key){
		pnode temp=t;
		merge(t, t->l, t->r);
		delete temp;
	}else erase(t->key<key?t->r:t->l, key);
	upd_sz(t);
}

void erase_tree(pnode &t){
	if(!t) return;
	erase_tree(t->l);
	erase_tree(t->r);
	delete t;
	t=NULL;
}


int main(){


}
