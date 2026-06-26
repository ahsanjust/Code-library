// I4y0 - FFT O(n log n) [hash: i4y0]
using cd=complex<double>;
void fft(vector<cd>&a,bool inv){
  int n=sz(a);
  for(int i=1,j=0;i<n;i++){int bit=n>>1;for(;j&bit;bit>>=1)j^=bit;j^=bit;if(i<j)swap(a[i],a[j]);}
  for(int len=2;len<=n;len<<=1){
    double ang=2*PI/len*(inv?-1:1);cd wlen(cos(ang),sin(ang));
    for(int i=0;i<n;i+=len){cd w(1);rep(j,0,len/2){cd u=a[i+j],v=a[i+j+len/2]*w;
      a[i+j]=u+v;a[i+j+len/2]=u-v;w*=wlen;}}}
  if(inv)for(cd&x:a)x/=n;}
vector<ll> conv(vi&a,vi&b){
  vector<cd> fa(all(a)),fb(all(b));int n=1;while(n<sz(a)+sz(b)-1)n<<=1;
  fa.resize(n);fb.resize(n);fft(fa,0);fft(fb,0);rep(i,0,n)fa[i]*=fb[i];fft(fa,1);
  vector<ll>r(sz(a)+sz(b)-1);rep(i,0,sz(r))r[i]=round(fa[i].real());return r;}

// J5z1 - NTT (mod=998244353, root=3) [hash: j5z1]
const ll NTT_MOD=998244353,NTT_ROOT=3;
void ntt(vl&a,bool inv){
  int n=sz(a);
  for(int i=1,j=0;i<n;i++){int bit=n>>1;for(;j&bit;bit>>=1)j^=bit;j^=bit;if(i<j)swap(a[i],a[j]);}
  for(int len=2;len<=n;len<<=1){
    ll wlen=modpow(NTT_ROOT,(NTT_MOD-1)/len,NTT_MOD);if(inv)wlen=modinv(wlen,NTT_MOD);
    for(int i=0;i<n;i+=len){ll w=1;rep(j,0,len/2){ll u=a[i+j],v=a[i+j+len/2]*w%NTT_MOD;
      a[i+j]=(u+v)%NTT_MOD;a[i+j+len/2]=(u-v+NTT_MOD)%NTT_MOD;w=w*wlen%NTT_MOD;}}}
  if(inv){ll ni=modinv(n,NTT_MOD);for(ll&x:a)x=x*ni%NTT_MOD;}}
vector<ll> nttConv(vi&a,vi&b){
  vl fa(all(a)),fb(all(b));int n=1;while(n<sz(a)+sz(b)-1)n<<=1;
  fa.resize(n);fb.resize(n);ntt(fa,0);ntt(fb,0);rep(i,0,n)fa[i]=fa[i]*fb[i]%NTT_MOD;ntt(fa,1);
  vector<ll>r(sz(a)+sz(b)-1);rep(i,0,sz(r))r[i]=fa[i];return r;}

// K6a2 - FWHT (XOR convolution) [hash: k6a2]
void fwht(vl&a,bool inv){
  int n=sz(a);
  for(int len=1;len<n;len<<=1)rep(i,0,n)if(i&len){ll u=a[i^len],v=a[i];
    a[i^len]=(u+v)%MOD;a[i]=(u-v+MOD)%MOD;}
  if(inv){ll ni=modinv(n,MOD);for(ll&x:a)x=x*ni%MOD;}}

// L7b3 - SOS DP (sum over subsets) [hash: l7b3]
vector<ll> sosDp(vector<ll>&a){
  int n=sz(a),b=32-__builtin_clz(n);vector<ll>dp=a;
  rep(bit,0,b)rep(mask,0,n)if(mask>>bit&1)dp[mask]+=dp[mask^(1<<bit)];
  return dp;}
