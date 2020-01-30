
typedef long long ll;

ll MOD = 1e9+7;

inline ll Msum(ll x){return x;}
template<typename... Rest>
inline ll Msum(ll x, Rest... rest){ return (x + Msum(rest...)) % MOD; }

inline ll Mprod(ll x){return x;}
template<typename... Rest>
inline ll Mprod(ll x, Rest... rest){ return x * Mprod(rest...) % MOD; }

inline ll Mnorm(ll x){ return (x%MOD + MOD) %MOD; }
