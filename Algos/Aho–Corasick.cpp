struct vertex{
	int p, link, dlink, wrd;
	char pch;
	map<char, int> next, go;
};

struct AC_Automaton{
	int sz;
	vector<vertex> t;
	vector<string> dict;

	void init(){
		t.clear();
		t.pb({-1,-1,-1,-1,0});
		dict.clear();
		sz = 1;
	}

	inline void add(const string &s){
		int v = 0;
		FOR(i,0,s.length()){
			char c = s[i];
			if(!t[v].next.count(c)){
				t.pb({v,-1,-1,-1,c});
				t[v].next[c] = sz++;
			}
			v = t[v].next[c];
		}
		t[v].wrd = dict.size();
		dict.pb(s);
	}

	inline int go(int v, int c){
		if(!t[v].go.count(c))
			if(t[v].next.count(c))
				t[v].go[c] = t[v].next[c];
			else
				t[v].go[c] = v==0 ? 0 : go(link(v), c);
		return t[v].go[c];
	}

	inline int link(int v){
		if(t[v].link == -1)
			if(!v || !t[v].p)
				t[v].link = 0;
			else
				t[v].link = go(link(t[v].p), t[v].pch);
		return t[v].link;
	}

	inline int dlink(int v){
		if(t[v].dlink == -1)
			if(!v || t[v].wrd!=-1)
				t[v].dlink = v;
			else
				t[v].dlink = dlink(link(v));
		return t[v].dlink;
	}
	// returns a vector of occurrences {index_of_matched_word, left-position_in_s}
	vector<ii> matches(const string &s){
		vector<ii> ret;
		int v=0;
		FOR(i,0,s.length()){
			v=go(v,s[i]);
			int u=dlink(v);
			while(u){
				int wrd=t[u].wrd;
				ret.pb({wrd, i-dict[wrd].length()+1});
				u=dlink(link(u));
			}
		}
		return ret;
	}
};