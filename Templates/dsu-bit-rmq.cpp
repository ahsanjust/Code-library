// B1d7 - DSU [hash: b1d7]
struct DSU {
  vi p,sz;
  DSU(int n):p(n),sz(n,1){iota(all(p),0);}
  int find(int x){return p[x]==x?x:p[x]=find(p[x]);}
  bool unite(int a,int b){
    a=find(a),b=find(b);if(a==b)return 0;
    if(sz[a]<sz[b])swap(a,b);
    p[b]=a;sz[a]+=sz[b];return 1;
  }
};

// C2e8 - Fenwick Tree [hash: c2e8]
struct BIT {
  int n;vl t;
  BIT(int _n):n(_n),t(_n+1){}
  void add(int i,ll v){for(;i<=n;i+=i&-i)t[i]+=v;}
  ll sum(int i){ll r=0;for(;i;i-=i&-i)r+=t[i];return r;}
  ll qry(int l,int r){return sum(r)-sum(l-1);}
};

// D3f9 - Sparse Table (RMQ) [hash: d3f9]
struct Sparse {
  int n,K;vvi st;vi lg;
  Sparse(vi& a):n(sz(a)){
    lg.resize(n+1);rep(i,2,n+1)lg[i]=lg[i/2]+1;
    K=lg[n]+1;st.assign(K,vi(n));
    copy(all(a),st[0].begin());
    rep(j,1,K)rep(i,0,n-(1<<j)+1)
      st[j][i]=min(st[j-1][i],st[j-1][i+(1<<(j-1))]);
  }
  int qry(int l,int r){int j=lg[r-l+1];return min(st[j][l],st[j][r-(1<<j)+1]);}
};
