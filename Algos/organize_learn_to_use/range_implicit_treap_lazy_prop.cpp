// La semilla de rand se debe inicializar con 'srand(time(NULL));'
// Sirve hacerlo al principio del programa

struct node{
	int prior,sz;
	ll val; //info como posicion del arreglo
	ll sum; //info como rango
	ll lazy; 
	node *l,*r;
	node(int v){
		prior=rand();
		sz=1;
		val=sum=v;
		lazy=0;
		l = r = NULL;
	}
};
typedef node* pnode;
int sz(pnode t){
	return t?t->sz:0;
}

ll sum(pnode t){
	return t?t->sum:0;
}

void push(pnode t){
	if(!t || !t->lazy)return;
	t->val+=t->lazy;
	t->sum+=t->lazy*sz(t);
	if(t->l)t->l->lazy+=t->lazy;
	if(t->r)t->r->lazy+=t->lazy;
	t->lazy=0;
}

void upd(pnode t){
	if(!t)return;
	t->sz = 1+sz(t->l)+sz(t->r);
	push(t->l); push(t->r);
	t->sum = t->val + sum(t->l) + sum(t->r); 
}

// el elemento en posicion pos va a l
void split(pnode t,pnode &l,pnode &r,int pos,int add=0){
	if(!t)return void(l=r=NULL);
	push(t);
	int curr_pos = add + sz(t->l);
	if(curr_pos<=pos) split(t->r,t->r,r,pos,curr_pos+1),l=t;
	else split(t->l,l,t->l,pos,add),r=t;
	upd(t);
}

void merge(pnode &t,pnode l,pnode r){
	push(l); push(r);
	if(!l || !r) t = l?l:r;
	else if(l->prior>r->prior) merge(l->r,l->r,r),t=l;
	else merge(r->l,l,r->l),t=r;
	upd(t);
}

ll range_query(pnode t,int l,int r){//[l,r]
	pnode L,mid,R;
	split(t,mid,R,r);
	split(mid,L,mid,l-1);
	ll ans = mid->sum;
	merge(t,L,mid);
	merge(t,t,R);
	return ans;
}

void range_update(pnode t,int l,int r,ll val){
	pnode L,mid,R;
	split(t,mid,R,r);
	split(mid,L,mid,l-1);
	mid->lazy+=val;
	merge(t,L,mid);
	merge(t,t,R);
}

void erase_tree(pnode &t){
	if(!t) return;
	erase_tree(t->l);
	erase_tree(t->r);
	delete t;
	t=NULL;
}

void inorder(pnode t, int add=0){
	if(!t) return;
	push(t);
	inorder(t->l, add);
	add += sz(t->l);
	printf("%d: %lld\n", add, t->val);
	inorder(t->r, add+1);
}

int main(){

}