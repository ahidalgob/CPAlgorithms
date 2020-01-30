#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
using namespace std;
#define FOR(i,f,t) for(int i=f;i<(int)t;i++)
#define pb push_back

struct state{
	int len, link;
	map<char, int> mp;
	bool terminal;
};
struct Suffix_Automaton{
	state & operator[](int i){ return G[i]; }
	vector<state> G;
	int N;
	void build(string S){
		int last = 0;
		G.clear();
		G.pb({0, -1});
		for(char c : S){
			int v = G.size(), p=last; 
			G.pb({G[last].len+1});
			for(;p>-1 && !G[p].mp.count(c); p=G[p].link)
				G[p].mp[c]=v;
			if(p == -1){
				G[v].link = 0;
			}else{
				int q=G[p].mp[c];
				if(G[p].len+1 == G[q].len){
					G[v].link = q;
				}else{
					int qq = G.size();
					G.pb({G[p].len+1, G[q].link, G[q].mp});
					G[v].link = G[q].link = qq;
					for(;p>-1 && G[p].mp[c] == q; p=G[p].link)
						G[p].mp[c] = qq;
				}
			}
			last = v;
		}
		N = G.size();
		while(last>0){
			G[last].terminal = true;
			last = G[last].link;
		}
	}
};

Suffix_Automaton sa;

int main(){
	string S; cin>>S;
	sa.build(S);
	//##################################
	FOR(i,0,sa.N){
		printf("%d:\n",i);
		for(auto it=sa.G[i].mp.begin(); it!=sa.G[i].mp.end(); it++)
			printf("  %c -> %d\n",it->first,it->second);
	}
	printf("\n");
	FOR(i,0,sa.N){
		printf("%d   %d\n",i,sa.G[i].link);
	}
	printf("##\n\n");
	//##################################
}
