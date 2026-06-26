// N3d9 - Heavy-Light Decomposition [hash: n3d9]
struct HLD{
  int n,cur;vvi g;vi par,dep,heavy,head,pos,sz;BIT bit;
  HLD(int _n):n(_n),g(_n),par(_n,-1),dep(_n),heavy(_n,-1),
    head(_n),pos(_n),sz(_n),bit(_n){}
  void add(int u,int v){g[u].pb(v);g[v].pb(u);}
  int dfs(int u){
    int mx=0;sz[u]=1;
    for(int v:g[u])if(v!=par[u]){
      par[v]=u;dep[v]=dep[u]+1;int sub=dfs(v);sz[u]+=sub;
      if(sub>mx)mx=sub,heavy[u]=v;
    }return sz[u];
  }
  void dec(int u,int h){
    head[u]=h;pos[u]=cur++;
    if(heavy[u]>=0)dec(heavy[u],h);
    for(int v:g[u])if(v!=par[u]&&v!=heavy[u])dec(v,v);
  }
  void build(int r=0){dfs(r);cur=0;dec(r,r);}
  void upd(int u,ll v){bit.add(pos[u],v);}
  ll path(int u,int v){
    ll res=0;
    while(head[u]!=head[v]){
      if(dep[head[u]]<dep[head[v]])swap(u,v);
      res+=bit.qry(pos[head[u]],pos[u]);u=par[head[u]];
    }
    if(dep[u]>dep[v])swap(u,v);
    return res+bit.qry(pos[u],pos[v]);
  }
};

// O4e0 - 2-SAT (using SCC) [hash: o4e0]
struct TwoSAT{
  int n;SCC scc;
  TwoSAT(int _n):n(_n),scc(2*_n){}
  void addImp(int u,bool vu,int v,bool vv){scc.add(2*u+vu,2*v+vv);}
  void addOr(int u,bool vu,int v,bool vv){
    addImp(u,!vu,v,vv);addImp(v,!vv,u,vu);}
  void addXor(int u,bool vu,int v,bool vv){
    addOr(u,vu,v,vv);addOr(u,!vu,v,!vv);}
  void force(int u,bool v){addImp(u,!v,u,v);}
  bool solve(vector<bool>&ans){
    scc.build();ans.assign(n,0);
    rep(i,0,n){if(scc.comp[2*i]==scc.comp[2*i+1])return 0;
      ans[i]=scc.comp[2*i]>scc.comp[2*i+1];}
    return 1;
  }
};
