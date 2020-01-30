
//------------------------------------COMBINACIONES DE n EN m------------------------------------
ll COMB[][];
ll comb(int n, int m){
	if(COMB[n][m]>0)
		return COMB[n][m];
	if(m == 0 || n==m)
		return COMB[n][m] = 1;
	return COMB[n][m] = comb(n-1,m)+comb(n-1,m-1);
	//return COMB[n][m] = (comb(n-1,m)+comb(n-1,m-1))%MOD;
}

//------------------------------------NUMEROS DE BELL------------------------------------
//
ll BELL[];
ll bell(int n){
	if(BELL[n]!=-1)
		return BELL[n];
	ll b =0;
	for(int k=0; k<n; k++)
		b += (COMB(n-1,k) * bell(k);
		//b = (b+(COMB(n-1,k) * bell(k))%MOD)%MOD;
	return BELL[n] = b;
}
ms(BELL,-1)


//------------------------------------Permutaciones de Multiconjunto------------------------------------
//k es el vector de ocurrencias de cada elemento
//{a,a,a,b,c,c} -> k = [3,1,2]
ll mcomb(vi k){
	ll r = 1;
	ll s=0;
	for(int i=0; i<k.size(); i++){
		s+=k[i];
		r*= comb(s,k[i]);
	}
	return r;
}

