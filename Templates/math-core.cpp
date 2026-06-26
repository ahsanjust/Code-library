// C8s4 - Modular Arithmetic [hash: c8s4]
ll modpow(ll a,ll e,ll m){ll r=1;a%=m;while(e){if(e&1)r=r*a%m;a=a*a%m;e>>=1;}return r;}
ll modinv(ll a,ll m){return modpow(a,m-2,m);} // m prime
struct Mint{
  ll x;Mint(ll _x=0):x((_x%MOD+MOD)%MOD){}
  Mint operator+(Mint o)const{return{x+o.x};}
  Mint operator-(Mint o)const{return{x-o.x};}
  Mint operator*(Mint o)const{return{x*o.x};}
  Mint operator/(Mint o)const{return*this*modinv(o.x,MOD);}
};

// D9t5 - Extended Euclid, CRT, Diophantine [hash: d9t5]
ll extGcd(ll a,ll b,ll&x,ll&y){if(!b){x=1;y=0;return a;}
  ll g=extGcd(b,a%b,y,x);y-=a/b*x;return g;}
ll modInv(ll a,ll m){ll x,y;extGcd(a,m,x,y);return(x%m+m)%m;}
pll crt(ll a1,ll m1,ll a2,ll m2){
  ll p,q,g=extGcd(m1,m2,p,q);
  if((a2-a1)%g)return{-1,-1};
  ll mod=m1/g*m2;ll x=a1+m1*((a2-a1)/g*p%(m2/g));
  return{(x%mod+mod)%mod,mod};}

// E0u6 - Linear Sieve (primes, phi, mu) [hash: e0u6]
const int SZ=10000000;
vi pr;int lp[SZ+1],phi[SZ+1],mu[SZ+1];
void sieve(){phi[1]=mu[1]=1;
  rep(i,2,SZ+1){
    if(!lp[i]){lp[i]=i;pr.pb(i);phi[i]=i-1;mu[i]=-1;}
    for(int p:pr){if(p>lp[i]||1LL*i*p>SZ)break;lp[i*p]=p;
      if(p==lp[i]){phi[i*p]=phi[i]*p;mu[i*p]=0;break;}
      phi[i*p]=phi[i]*phi[p];mu[i*p]=-mu[i];}}}

// F1v7 - Combinatorics [hash: f1v7]
vl fact,invFact;
void init(int n){fact.assign(n+1,1);invFact.assign(n+1,1);
  rep(i,1,n+1)fact[i]=fact[i-1]*i%MOD;invFact[n]=modinv(fact[n],MOD);
  per(i,0,n)invFact[i]=invFact[i+1]*(i+1)%MOD;}
ll nCr(int n,int r){if(r<0||r>n)return 0;return fact[n]*invFact[r]%MOD*invFact[n-r]%MOD;}
ll nPr(int n,int r){if(r<0||r>n)return 0;return fact[n]*invFact[n-r]%MOD;}

// G2w8 - Matrix [hash: g2w8]
using Mat = vector<vl>;
Mat matMul(Mat&a,Mat&b){int n=sz(a),m=sz(a[0]),p=sz(b[0]);Mat c(n,vl(p,0));
  rep(i,0,n)rep(k,0,m)if(a[i][k])rep(j,0,p)c[i][j]=(c[i][j]+a[i][k]*b[k][j])%MOD;return c;}
Mat matPow(Mat a,ll e){int n=sz(a);Mat r(n,vl(n,0));rep(i,0,n)r[i][i]=1;
  while(e){if(e&1)r=matMul(r,a);a=matMul(a,a);e>>=1;}return r;}
ll det(Mat a){int n=sz(a);ll r=1;
  rep(i,0,n){int p=-1;rep(j,i,n)if(a[j][i]){p=j;break;}if(p<0)return 0;
    if(p!=i)swap(a[i],a[p]),r=-r;r=r*a[i][i]%MOD;ll inv=modinv((a[i][i]%MOD+MOD)%MOD,MOD);
    rep(j,i+1,n){ll f=a[j][i]*inv%MOD;rep(k,i,n)a[j][k]=(a[j][k]-f*a[i][k])%MOD;}}
  return(r%MOD+MOD)%MOD;}
