// Queries de max, se agregan las lineas en orden ascendente de pendinte(m)

const int MAXHSZ = 1500;
ll hb[MAXHSZ], hm[MAXHSZ], hsz;
void add_line(ll m, ll b){
	while(true){
		if(hsz < 2){
			hm[hsz]=m;
			hb[hsz++]=b;
			break;
		}else{
			if( (hb[hsz-1]-b)*(hm[hsz-1]-hm[hsz-2]) <= (hb[hsz-2]-hb[hsz-1])*(m-hm[hsz-1]) ){
				hullsz--;
			}else{
				hm[hsz]=m;
				hb[hsz++]=b;
				break;
			}
		}
	}
}

ll query(int b, ll x){
	int lo = 0, hi = hsz;
	while(lo < hi-1){
		int mi = (lo+hi)/2;
		if((hb[mi-1]-hb[mi]) <= x*(hm[mi] - hm[mi-1])) lo=mi;
		else hi=mi;
	}
	return hm[lo]*x + hb[lo];
}
