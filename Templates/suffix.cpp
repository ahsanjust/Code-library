// Z5p1 - Suffix Array O(n log n) [hash: z5p1]
vi suffixArray(string&s){
  int n=sz(s);vi sa(n),rk(n),tmp(n);
  iota(all(sa),0);sort(all(sa),[&](int i,int j){return s[i]<s[j];});
  rk[sa[0]]=0;rep(i,1,n)rk[sa[i]]=rk[sa[i-1]]+(s[sa[i]]!=s[sa[i-1]]);
  for(int k=1;k<n;k<<=1){
    sort(all(sa),[&](int i,int j){
      if(rk[i]!=rk[j])return rk[i]<rk[j];
      return(i+k<n?rk[i+k]:-1)<(j+k<n?rk[j+k]:-1);});
    tmp[sa[0]]=0;
    rep(i,1,n){int pv=sa[i-1],cu=sa[i];
      int pvk=pv+k<n?rk[pv+k]:-1,cuk=cu+k<n?rk[cu+k]:-1;
      tmp[cu]=tmp[pv]+(rk[pv]!=rk[cu]||pvk!=cuk);}
    rk.swap(tmp);}
  return sa;}
// LCP (Kasai) O(n)
vi lcpArray(string&s,vi&sa){int n=sz(s);vi rk(n),lcp(n-1);
  rep(i,0,n)rk[sa[i]]=i;
  for(int i=0,k=0;i<n;i++,k=max(k-1,0)){
    if(rk[i]==n-1){k=0;continue;}int j=sa[rk[i]+1];
    while(i+k<n&&j+k<n&&s[i+k]==s[j+k])k++;lcp[rk[i]]=k;}
  return lcp;}

// A6q2 - Suffix Automaton [hash: a6q2]
struct SAM{
  struct Node{int len,link,nxt[26];};
  vector<Node>t;int last;
  SAM(){t.pb({0,-1,{}});last=0;}
  void ext(char c){
    int cur=sz(t);t.pb({t[last].len+1,0,{}});int p=last;
    while(p>=0&&!t[p].nxt[c-'a']){t[p].nxt[c-'a']=cur;p=t[p].link;}
    if(p<0)t[cur].link=0;
    else{int q=t[p].nxt[c-'a'];
      if(t[p].len+1==t[q].len)t[cur].link=q;
      else{int cl=sz(t);t.pb({t[p].len+1,t[q].link,{}});
        copy(all(t[q].nxt),t[cl].nxt);
        while(p>=0&&t[p].nxt[c-'a']==q){t[p].nxt[c-'a']=cl;p=t[p].link;}
        t[q].link=t[cur].link=cl;}}
    last=cur;}
  ll distSub(){ll r=0;rep(i,1,sz(t))r+=t[i].len-t[t[i].link].len;return r;}
};

// B7r3 - Palindromic Tree (Eertree) [hash: b7r3]
struct Eertree{
  struct Node{int nxt[26],len,suff,cnt;};
  vector<Node>t;string s;int last;
  Eertree(){t.pb({{},-1,0,0});t.pb({{},0,0,0});t[0].suff=1;last=0;}
  void add(char ch){s+=ch;int c=ch-'a',cur=last;
    while(true){int cl=t[cur].len;if(sz(s)-cl-2>=0&&s[sz(s)-cl-2]==ch)break;cur=t[cur].suff;}
    if(t[cur].nxt[c]){last=t[cur].nxt[c];t[last].cnt++;return;}
    int nw=sz(t);t.pb({{},t[cur].len+2,0,1});t[cur].nxt[c]=nw;last=nw;
    if(t[nw].len==1){t[nw].suff=0;return;}cur=t[cur].suff;
    while(true){int cl=t[cur].len;if(sz(s)-cl-2>=0&&s[sz(s)-cl-2]==ch)break;cur=t[cur].suff;}
    t[nw].suff=t[cur].nxt[c];}
  void cntProp(){per(i,2,sz(t))t[t[i].suff].cnt+=t[i].cnt;}
};
