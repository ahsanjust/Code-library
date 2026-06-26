// P5f1 - Dinic Max Flow [hash: p5f1]
struct Dinic{
  struct Edge{int v,rev;ll cap;};
  int n;vector<vector<Edge>> g;vi lvl,it;
  Dinic(int _n):n(_n),g(_n),lvl(_n),it(_n){}
  void add(int u,int v,ll cap){
    g[u].pb({v,sz(g[v]),cap});g[v].pb({u,sz(g[u])-1,0});}
  bool bfs(int s,int t){
    fill(all(lvl),-1);lvl[s]=0;queue<int>q;q.push(s);
    while(!q.empty()){int u=q.front();q.pop();
      for(auto&e:g[u])if(e.cap>0&&lvl[e.v]<0)lvl[e.v]=lvl[u]+1,q.push(e.v);}
    return lvl[t]>=0;}
  ll dfs(int u,int t,ll f){
    if(u==t||!f)return f;
    for(int&i=it[u];i<sz(g[u]);i++){Edge&e=g[u][i];
      if(e.cap>0&&lvl[e.v]==lvl[u]+1){
        ll p=dfs(e.v,t,min(f,e.cap));
        if(p>0){e.cap-=p;g[e.v][e.rev].cap+=p;return p;}}
    }return 0;}
  ll maxFlow(int s,int t){
    ll fl=0;
    while(bfs(s,t)){fill(all(it),0);while(ll f=dfs(s,t,LINF))fl+=f;}
    return fl;}
};

// Q6g2 - Min Cost Max Flow (SPFA-based) [hash: q6g2]
struct MCMF{
  struct Edge{int v,rev;ll cap,cost;};
  int n;vector<vector<Edge>> g;vl dist;vi pv,pe;
  MCMF(int _n):n(_n),g(_n){}
  void add(int u,int v,ll cap,ll cost){
    g[u].pb({v,sz(g[v]),cap,cost});g[v].pb({u,sz(g[u])-1,0,-cost});}
  bool spfa(int s,int t){
    dist.assign(n,LINF);dist[s]=0;pv.assign(n,-1);pe.assign(n,-1);
    vector<bool>inq(n,0);queue<int>q({s});inq[s]=1;
    while(!q.empty()){int u=q.front();q.pop();inq[u]=0;
      rep(i,0,sz(g[u])){auto&e=g[u][i];
        if(e.cap&&dist[e.v]>dist[u]+e.cost){
          dist[e.v]=dist[u]+e.cost;pv[e.v]=u;pe[e.v]=i;
          if(!inq[e.v])q.push(e.v),inq[e.v]=1;}}}
    return dist[t]!=LINF;}
  pll flow(int s,int t){
    ll fl=0,cost=0;
    while(spfa(s,t)){
      ll f=LINF;for(int v=t;v!=s;v=pv[v])f=min(f,g[pv[v]][pe[v]].cap);
      fl+=f;cost+=f*dist[t];
      for(int v=t;v!=s;v=pv[v]){auto&e=g[pv[v]][pe[v]];
        e.cap-=f;g[v][e.rev].cap+=f;}}
    return {fl,cost};}
};

// R7h3 - Hopcroft-Karp Bipartite Matching [hash: r7h3]
struct HK{
  int n,m;vi L,R,dist;vvi g;
  HK(int _n,int _m):n(_n),m(_m),g(_n){}
  void add(int u,int v){g[u].pb(v);}
  bool bfs(){
    queue<int>q;dist.assign(n,-1);
    rep(u,0,n)if(L[u]<0){dist[u]=0;q.push(u);}
    bool ok=0;
    while(!q.empty()){int u=q.front();q.pop();
      for(int v:g[u]){int nu=R[v];
        if(nu>=0&&dist[nu]<0){dist[nu]=dist[u]+1;q.push(nu);}
        else if(nu<0)ok=1;}}
    return ok;}
  bool dfs(int u){
    for(int v:g[u]){int nu=R[v];
      if(nu<0||(dist[nu]==dist[u]+1&&dfs(nu))){L[u]=v;R[v]=u;return 1;}}
    dist[u]=-1;return 0;}
  int match(){
    L.assign(n,-1);R.assign(m,-1);int r=0;
    while(bfs())rep(u,0,n)if(L[u]<0&&dfs(u))r++;
    return r;}
};

// S8i4 - Hungarian (Assignment, O(n^3)) [hash: s8i4]
ll hungarian(vector<vl>&a){
  int n=sz(a),m=sz(a[0]);vl u(n+1),v(m+1),p(m+1),way(m+1);
  rep(i,1,n+1){p[0]=i;int j0=0;vl minv(m+1,LINF);vi used(m+1,0);
    do{used[j0]=1;int i0=p[j0];ll delta=LINF;int j1=0;
      rep(j,1,m+1)if(!used[j]){
        ll cur=a[i0-1][j-1]-u[i0]-v[j];
        if(cur<minv[j])minv[j]=cur,way[j]=j0;
        if(minv[j]<delta)delta=minv[j],j1=j;}
      rep(j,0,m+1)if(used[j])u[p[j]]+=delta,v[j]-=delta;else minv[j]-=delta;
      j0=j1;}while(p[j0]);
    do{int j1=way[j0];p[j0]=p[j1];j0=j1;}while(j0);}
  return -v[0];}
