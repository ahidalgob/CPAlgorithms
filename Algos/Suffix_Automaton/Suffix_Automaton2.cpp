#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
using namespace std;
#define FOR(i,f,t) for(int i=f;i<(int)t;i++)
#define pb push_back

struct state{
	int len, link;
	map<int, int> mp;
	bool terminal;
};
struct Suffix_Automaton{
	state & operator[](int i){ return G[i]; }
	vector<state> G;
	int N;
	void build(vector<int> S){
		int last = 0;
		G.clear();
		G.pb({0, -1});
		for(int c : S){
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
int N;
string S;
vector<int> v;

int main(){
    cin >> N;
    FOR(i,0,N){
        cin >> S;
        FOR(j,0,S.length()) v.push_back(int(S[j]));
        v.push_back(1000+i);
    }
	sa.build(v);
	//##################################
	FOR(i,0,sa.N){
		printf("%d:\n",i);
		for(auto it=sa[i].mp.begin(); it!=sa[i].mp.end(); it++)
            if(it->first >= 900)
			    printf("  %d -> %d\n",it->first - 1000,it->second);
            else
			    printf("  %c -> %d\n",char(it->first),it->second);
	}
	printf("\n");
	FOR(i,0,sa.N){
		printf("%d   %d\n",i,sa[i].link);
	}
	printf("##\n\n");
	//##################################
}
