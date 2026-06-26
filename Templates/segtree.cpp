// E4a0 - Iterative SegTree (point update, range sum) [hash: e4a0]
struct SegTree {
  int n;vl t;
  SegTree(int _n){n=1;while(n<_n)n<<=1;t.assign(2*n,0);}
  void upd(int p,ll v){for(t[p+=n]=v;p>>=1;)t[p]=t[2*p]+t[2*p+1];}
  ll qry(int l,int r){
    ll res=0;
    for(l+=n,r+=n+1;l<r;l>>=1,r>>=1){
      if(l&1)res+=t[l++];if(r&1)res+=t[--r];
    }
    return res;
  }
};

// F5b1 - Lazy SegTree (range add, range sum) [hash: f5b1]
struct LazySeg {
  int n;vl t,lz;
  LazySeg(int _n){n=1;while(n<_n)n<<=1;t.assign(2*n,0);lz.assign(2*n,0);}
  void push(int v,int l,int r){
    if(!lz[v])return;
    t[v]+=lz[v]*(r-l+1);
    if(v<n){lz[2*v]+=lz[v];lz[2*v+1]+=lz[v];}
    lz[v]=0;
  }
  void upd(int l,int r,ll val,int v=1,int L=0,int R=-1){
    if(R<0)R=n-1;push(v,L,R);
    if(r<L||R<l)return;
    if(l<=L&&R<=r){lz[v]+=val;push(v,L,R);return;}
    int M=(L+R)/2;
    upd(l,r,val,2*v,L,M);upd(l,r,val,2*v+1,M+1,R);
    t[v]=t[2*v]+t[2*v+1];
  }
  ll qry(int l,int r,int v=1,int L=0,int R=-1){
    if(R<0)R=n-1;push(v,L,R);
    if(r<L||R<l)return 0;
    if(l<=L&&R<=r)return t[v];
    int M=(L+R)/2;
    return qry(l,r,2*v,L,M)+qry(l,r,2*v+1,M+1,R);
  }
};

// G6c2 - Li Chao Tree (min, lines ax+b) [hash: g6c2]
struct Line{ll a,b;Line(ll _a=0,ll _b=LINF):a(_a),b(_b){}
  ll eval(ll x){return a*x+b;}};
struct LiChao{
  struct Node{Line line;Node *l,*r;};
  Node*rt;ll LO,HI;
  LiChao(ll lo,ll hi):rt(new Node()),LO(lo),HI(hi){}
  void add(Node*v,ll l,ll r,Line nl){
    ll m=(l+r)/2;
    bool left=nl.eval(l)<v->line.eval(l);
    bool mid=nl.eval(m)<v->line.eval(m);
    if(mid)swap(v->line,nl);
    if(l==r)return;
    if(left!=mid){if(!v->l)v->l=new Node();add(v->l,l,m,nl);}
    else{if(!v->r)v->r=new Node();add(v->r,m+1,r,nl);}
  }
  void add(ll a,ll b){add(rt,LO,HI,Line(a,b));}
  ll qry(Node*v,ll l,ll r,ll x){
    if(!v)return LINF;ll res=v->line.eval(x);
    if(l==r)return res;ll m=(l+r)/2;
    if(x<=m)return min(res,qry(v->l,l,m,x));
    return min(res,qry(v->r,m+1,r,x));
  }
  ll qry(ll x){return qry(rt,LO,HI,x);}
};
