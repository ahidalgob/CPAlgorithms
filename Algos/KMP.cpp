#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

#define pb push_back

#define FOR(i,f,t) for(int i=f; i<(int)t; i++)

typedef vector<int> vi;

vi KMP(string S, string K){ //finds all occurrences of K in S
	vi T(K.size() + 1, -1);
	for(int i = 1; i <= K.size(); i++){
		int pos = T[i - 1];
		while(pos != -1 && K[pos] != K[i - 1]) pos = T[pos];
		T[i] = pos + 1;
	}
	// T[i] = the length of the longest proper suffix of K[0..i-1] that is prefix of K
//			0  1  2  3  4  5  6  7  8  9  10
// 		    a  b  r  a  c  a  d  a  b  r  a
// 		-1  0  0  0  1  0  1  0  1  2  3  4
//		 0  1  2  3  4  5  6  7  8  9  10 11
	//printf("   ");FOR(i,0,K.size()){printf(" %c ",K[i]);}printf("\n");FOR(i,0,T.size()){printf("%2d ",T[i]);}printf("\n");

	vi matches;
	for(int sp = 0, kp = 0; sp < S.size(); sp++){
		while(kp != -1 && (kp == K.size() || K[kp] != S[sp]))
			kp = T[kp];
		kp++;
		if(kp == K.size()) matches.pb(sp + 1 - K.size());
	}
	return matches;
}

int main(){
	KMP("abracadabra", "abracadabra");
}
