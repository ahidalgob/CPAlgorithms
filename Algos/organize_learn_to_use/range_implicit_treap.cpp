// La semilla de rand se debe inicializar con 'srand(time(NULL));'
// Sirve hacerlo al principio del programa

struct node{
	int prior, sz;
	int val; //info como posicion del arreglo
	int maxi; //info como rango
	node *l, *r;
	node(int v){
		val = maxi = v;
		sz = 1;
		prior = rand();
		l = r = NULL;
	}
};

typedef node* pnode;
int sz(pnode t){
	return t?t->sz:0;
}

int maxi(pnode t){
	return t?t->maxi:-1e9;
}

void upd(pnode t){
	if(!t) return;
	t->sz = 1+sz(t->l)+sz(t->r);
	t->maxi = max(maxi(t->l), max(maxi(t->r), t->val));
}
// el elemento en posicion pos va a l
void split(pnode t,pnode &l,pnode &r,int pos,int add=0){
	if(!t)return void(l=r=NULL);
	int curr_pos = add + sz(t->l);
	if(curr_pos<=pos)  split(t->r,t->r,r,pos,curr_pos+1),l=t;
	else split(t->l,l,t->l,pos,add),r=t;
	upd(t);
}

void merge(pnode &t,pnode l,pnode r) {
	if(!l || !r) t = l?l:r;
	else if(l->prior>r->prior)merge(l->r,l->r,r),t=l;
	else    merge(r->l,l,r->l),t=r;
	upd(t);
}

void insert(pnode &t, pnode it, int pos, int add=0){
	if(!t) return void(t=it);
	int curr_pos = add+sz(t->l);
	if(it->prior > t->prior)
		split(t, it->l, it->r, pos-1, add), t=it;
	else if(curr_pos < pos)
		insert(t->r, it, pos, curr_pos+1);
	else
		insert(t->l, it, pos, add);
	upd(t);
}

void update(pnode &t, int v, int pos, int add=0){
	if(!t) return;
	int curr_pos = add+sz(t->l);
	if(curr_pos < pos)
		update(t->r, v, pos, curr_pos+1);
	else if(curr_pos > pos)
		update(t->l, v, pos, add);
	else
		t->val = t->maxi = v;
	upd(t);
}

void erase(pnode &t, int pos, int add=0){
	if(!t) return;
	int curr_pos = add+sz(t->l);
	if(curr_pos == pos){
		pnode temp=t; merge(t, t->l, t->r);
		delete temp;
	}else if(curr_pos < pos) erase(t->r, pos, curr_pos+1);
	else erase(t->l, pos, add);
	upd(t);
}

//Es mas sencillo cortar el rango [x,y], responder y volver a unir el arbol
//pero a veces es mas rapido recorriendo el arbol
int query(pnode t, int x, int y, int l, int r){
	int ans = -1e9;
	if(!t) return ans;
	if(x<=l && r<=y)
		return t->maxi;
	int pos = l+sz(t->l);

	if(y <= pos){
		ans = query(t->l, x, y, l, pos-1);
	}else if(pos <= x){
		ans = query(t->r, x, y, pos+1, r);
	}else{
		ans = max(query(t->l, x, pos-1, l, pos-1),
				query(t->r, pos+1, y, pos+1, r));
	}
	if(x<=pos && pos<=y) ans = max(ans, t->val);
	return ans;
}


void inorder(pnode t, int add=0){
	if(!t) return;
	inorder(t->l, add);
	add += sz(t->l);
	printf("%d: %d\n", add, t->val);
	inorder(t->r, add+1);
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
