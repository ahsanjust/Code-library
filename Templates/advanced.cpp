// M8c4 - Gaussian Elimination (Ax=b) O(n^3) [hash: m8c4]
// Uses long double for precision. For GF(2), use bitset + Gauss-Jordan.
int gauss(vvd&a,vd&ans){
  int n=sz(a),m=sz(a[0])-1;vi wh(m,-1);
  for(int c=0,r=0;c<m&&r<n;c++){int s=r;
    rep(i,r,n)if(abs(a[i][c])>abs(a[s][c]))s=i;
    if(abs(a[s][c])<1e-12)continue;swap(a[s],a[r]);ld iv=a[r][c];
    rep(j,c,m+1)a[r][j]/=iv;
    rep(i,0,n)if(i!=r){ld f=a[i][c];if(abs(f)>1e-12)rep(j,c,m+1)a[i][j]-=f*a[r][j];}
    wh[c]=r++;}
  ans.assign(m,0);rep(i,0,m)if(wh[i]>=0)ans[i]=a[wh[i]][m];
  rep(i,0,n){ld s=0;rep(j,0,m)s+=a[i][j]*ans[j];if(abs(s-a[i][m])>1e-9)return 0;}
  rep(i,0,m)if(wh[i]<0)return INF;return 1;}

// N9d5 - LIS O(n log n) [hash: n9d5]
int lis(vi&a){vi d;for(int x:a){auto it=lower_bound(all(d),x);if(it==d.end())d.pb(x);else*it=x;}return sz(d);}
// For non-decreasing: use upper_bound

// O0e6 - Divide & Conquer DP [hash: o0e6]
// dp[i][j]=min(dp[i-1][k]+C(k+1,j)), opt[i][j] monotonic
void dcDp(int i,int l,int r,int optL,int optR,vector<vl>&dp,auto&cost){
  if(l>r)return;int m=(l+r)/2,best=-1;
  rep(k,optL,min(m,optR)+1){ll v=dp[i-1][k]+cost(k+1,m);if(v<dp[i][m])dp[i][m]=v,best=k;}
  dcDp(i,l,m-1,optL,best,dp,cost);dcDp(i,m+1,r,best,optR,dp,cost);}

// P1f7 - Kitamasa (k-th term linear rec.) O(k^2 log n) [hash: p1f7]
// rec: a[n]=c[0]*a[n-k]+...+c[k-1]*a[n-1]
ll kitamasa(ll n,vl&a,vl&c){
  int k=sz(a);if(n<k)return a[n];
  auto comb=[&](vl&p,vl&q){vl r(2*k,0);
    rep(i,0,k)rep(j,0,k)r[i+j]=(r[i+j]+p[i]*q[j])%MOD;
    per(i,k,2*k-1)rep(j,0,k)r[i-1-j]=(r[i-1-j]+r[i]*c[k-1-j])%MOD;
    r.resize(k);return r;};
  vl p(k,0),q(k,0);p[0]=1;q[1]=1;
  while(n){if(n&1)p=comb(p,q);q=comb(q,q);n>>=1;}
  ll r=0;rep(i,0,k)r=(r+p[i]*a[i])%MOD;return r;}
