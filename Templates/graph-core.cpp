// J9f5 - SCC (Kosaraju) [hash: j9f5]
struct SCC{
  int n,c;vvi g,rg;vi comp,ord;vector<bool>vis;
  SCC(int _n):n(_n),g(_n),rg(_n),comp(_n,-1){}
  void add(int u,int v){g[u].pb(v);rg[v].pb(u);}
  void dfs1(int u){vis[u]=1;for(int v:g[u])if(!vis[v])dfs1(v);ord.pb(u);}
  void dfs2(int u,int ci){comp[u]=ci;for(int v:rg[u])if(comp[v]==-1)dfs2(v,ci);}
  void build(){
    vis.assign(n,0);rep(i,0,n)if(!vis[i])dfs1(i);
    reverse(all(ord));for(int u:ord)if(comp[u]==-1)dfs2(u,c++);
  }
};

// K0a6 - BCC / Bridges / Articulation Points [hash: k0a6]
struct BCC{
  int n,t;vvi g;vi tin,low;vector<bool>art;vector<pii>br;
  BCC(int _n):n(_n),g(_n),tin(_n,-1),low(_n),art(_n){}
  void add(int u,int v){g[u].pb(v);g[v].pb(u);}
  void dfs(int u,int p){
    tin[u]=low[u]=t++;int ch=0;
    for(int v:g[u])if(v!=p){
      if(tin[v]>=0)low[u]=min(low[u],tin[v]);
      else{dfs(v,u);low[u]=min(low[u],low[v]);
        if(low[v]>tin[u])br.pb({u,v});
        if(low[v]>=tin[u]&&p>=0)art[u]=1;ch++;}
    }
    if(p<0&&ch>1)art[u]=1;
  }
  void build(){rep(i,0,n)if(tin[i]<0)dfs(i,-1);}
};

// L1b7 - LCA (Binary Lifting) [hash: l1b7]
struct LCA{
  int n,K;vvi up;vi dep;
  LCA(vvi&g,int r):n(sz(g)){K=32-__builtin_clz(n);
    up.assign(K,vi(n,-1));dep.assign(n,0);dfs(g,r,-1);
    rep(k,1,K)rep(v,0,n)if(up[k-1][v]>=0)up[k][v]=up[k-1][up[k-1][v]];}
  void dfs(vvi&g,int u,int p){up[0][u]=p;
    for(int v:g[u])if(v!=p){dep[v]=dep[u]+1;dfs(g,v,u);}}
  int lca(int u,int v){
    if(dep[u]<dep[v])swap(u,v);
    int d=dep[u]-dep[v];for(int k=0;d;k++,d>>=1)if(d&1)u=up[k][u];
    if(u==v)return u;
    per(k,0,K)if(up[k][u]!=up[k][v])u=up[k][u],v=up[k][v];
    return up[0][u];
  }
  int dist(int u,int v){int w=lca(u,v);return dep[u]+dep[v]-2*dep[w];}
};

// M2c8 - Euler Tour (subtree queries) [hash: m2c8]
struct Euler{
  int n,t;vvi g;vi tin,tout;BIT bit;
  Euler(int _n):n(_n),g(_n),tin(_n),tout(_n),bit(2*_n){}
  void add(int u,int v){g[u].pb(v);g[v].pb(u);}
  void dfs(int u,int p){tin[u]=++t;for(int v:g[u])if(v!=p)dfs(v,u);tout[u]=t;}
  void build(int r=0){t=0;dfs(r,-1);}
  void upd(int u,ll v){bit.add(tin[u],v);}
  ll sub(int u){return bit.qry(tin[u],tout[u]);}
};
