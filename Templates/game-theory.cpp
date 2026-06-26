// Q2g8 - Game Theory / Grundy [hash: q2g8]
// Nim: xor of pile sizes != 0 => first player wins
// Grundy: mex of reachable states; G = xor of sub-game Grundy numbers

// Compute Grundy for impartial combinatorial game
// dp[x] = mex{ dp[child] for all moves from state x }
int mex(vi&v){sort(all(v));v.erase(unique(all(v)),v.end());
  rep(i,0,sz(v))if(v[i]!=i)return i;return sz(v);}
// Example: Grundy for subtraction game (remove 1..k stones)
vi grundy(int n,int k){
  vi g(n+1,0);
  rep(i,1,n+1){vi s;
    rep(j,1,k+1)if(i>=j)s.pb(g[i-j]);
    g[i]=mex(s);}
  return g;}
// Winning condition: xor of all sub-game Grundy numbers != 0

// Sprague-Grundy for matrix game
int sg(int r,int c,vector<vi>&memo){
  if(r==0||c==0)return 0;
  if(memo[r][c]>=0)return memo[r][c];
  vi s;s.pb(sg(r-1,c,memo));s.pb(sg(r,c-1,memo));s.pb(sg(r-1,c-1,memo));
  return memo[r][c]=mex(s);}
