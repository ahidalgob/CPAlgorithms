
typedef vector<ll> vll;
typedef vector<vll> vvll;

struct Matrix{
	vvll M;
	int N;
	Matrix(){}
	Matrix(int n){
		N=n;
		M = vvll(N,vll(N,0));
	}
	vll & operator[](int i){return M[i];}
	Matrix operator+(Matrix &B){
		Matrix ret(N);
		FOR(i,0,N) FOR(j,0,N) ret[i][j]=(M[i][j]+B[i][j])%MOD;
		return ret;
	}
	Matrix operator*(Matrix &B){
		Matrix ret(N);
		FOR(i,0,N) FOR(j,0,N) FOR(k,0,N) ret[i][j]=(ret[i][j]+M[i][k]*B[k][j])%MOD;
		return ret;
	}
};
Matrix ID(int N){
	Matrix ret(N);
	FOR(i,0,N) ret[i][i]=1;
	return ret;
}
Matrix sq(Matrix A){
	Matrix ret = A*A;
	return ret;
}
Matrix matPot(Matrix &A, ll e){
	Matrix id = ID(A.N);
	if(!e) return id;
	return sq(matPot(A, e>>1)) * (e&1 ? A : id);
}
