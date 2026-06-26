// U0k6 - KMP [hash: u0k6]
vi kmp(string&s){int n=sz(s);vi pi(n);
  rep(i,1,n){int j=pi[i-1];while(j>0&&s[i]!=s[j])j=pi[j-1];if(s[i]==s[j])j++;pi[i]=j;}
  return pi;}
vi kmpSearch(string&t,string&p){string s=p+'#'+t;vi pi=kmp(s),r;rep(i,0,sz(t))if(pi[sz(p)+1+i]==sz(p))r.pb(i-sz(p)+1);return r;}

// V1l7 - Z-Algorithm [hash: v1l7]
vi zAlgo(string&s){int n=sz(s);vi z(n);
  for(int i=1,l=0,r=0;i<n;i++){if(i<=r)z[i]=min(r-i+1,z[i-l]);
    while(i+z[i]<n&&s[z[i]]==s[i+z[i]])z[i]++;if(i+z[i]-1>r)l=i,r=i+z[i]-1;}
  return z;}

// W2m8 - Manacher [hash: w2m8]
pair<vi,vi> manacher(string&s){int n=sz(s);vi d1(n),d2(n);
  for(int i=0,l=0,r=-1;i<n;i++){int k=i>r?1:min(d1[l+r-i],r-i+1);
    while(i-k>=0&&i+k<n&&s[i-k]==s[i+k])k++;d1[i]=k--;
    if(i+k>r)l=i-k,r=i+k;}
  for(int i=0,l=0,r=-1;i<n;i++){int k=i>r?0:min(d2[l+r-i+1],r-i+1);
    while(i-k-1>=0&&i+k<n&&s[i-k-1]==s[i+k])k++;d2[i]=k--;
    if(i+k>r)l=i-k-1,r=i+k;}
  return{d1,d2};}

// X3n9 - Double Rolling Hash [hash: x3n9]
struct Hash{ll mod,base;vl pow,h;
  Hash(string&s,ll _mod,ll _base=911382323):mod(_mod),base(_base){
    int n=sz(s);pow.resize(n+1,1);h.resize(n+1,0);
    rep(i,0,n){pow[i+1]=pow[i]*base%mod;h[i+1]=(h[i]*base+s[i])%mod;}}
  ll get(int l,int r){return(h[r+1]-h[l]*pow[r-l+1]%mod+mod)%mod;}};
struct DHash{Hash h1,h2;
  DHash(string&s):h1(s,1000000007),h2(s,1000000009){}
  pll get(int l,int r){return{h1.get(l,r),h2.get(l,r);}}};

// Y4o0 - Aho-Corasick [hash: y4o0]
struct Aho{
  struct Node{int nxt[26],fail,out;};
  vector<Node>t;Aho(){t.pb({});}
  void ins(string&s){int v=0;for(char c:s){int&nv=t[v].nxt[c-'a'];
    if(!nv){nv=sz(t);t.pb({});}v=nv;}t[v].out++;}
  void build(){queue<int>q;
    rep(c,0,26)if(t[0].nxt[c])q.push(t[0].nxt[c]);
    while(!q.empty()){int v=q.front();q.pop();
      rep(c,0,26){int u=t[v].nxt[c];
        if(u){t[u].fail=t[t[v].fail].nxt[c];t[u].out+=t[t[u].fail].out;q.push(u);}
        else t[v].nxt[c]=t[t[v].fail].nxt[c];}}}
  ll match(string&s){int v=0;ll r=0;for(char c:s){v=t[v].nxt[c-'a'];r+=t[v].out;}return r;}
};
