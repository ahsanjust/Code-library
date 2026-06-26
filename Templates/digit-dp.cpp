// R3h9 - Digit DP Template [hash: r3h9]
// Count numbers <= N satisfying property P
// Modify state (pos, tight, started, ...) as needed
ll dp[20][2][2][...]; // adjust dimensions
string s;

ll dfs(int pos,bool tight,bool started,...){
  if(pos==sz(s))return started?1:0; // base case depends on problem
  ll&mem=dp[pos][tight][started][...];
  if(mem>=0)return mem;
  int lim=tight?s[pos]-'0':9;ll res=0;
  rep(d,0,lim+1){
    bool nt=tight&&(d==lim);
    bool ns=started||d!=0;
    int nd=(!started&&!d)?0:d; // example: skip leading zeros
    // add constraints here
    res+=dfs(pos+1,nt,ns,...);
  }
  return mem=res;
}
// Usage: memset(dp,-1,sizeof dp); s=to_string(N); ll ans=dfs(0,1,0,...);
// For [L,R]: solve(R)-solve(L-1)
