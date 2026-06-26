// H3x9 - Miller-Rabin + Pollard-Rho [hash: h3x9]
ll modMul(ll a,ll b,ll m){return(__int128)a*b%m;}
ll modPow(ll a,ll e,ll m){ll r=1;while(e){if(e&1)r=modMul(r,a,m);a=modMul(a,a,m);e>>=1;}return r;}
bool isPrime(ll n){
  if(n<2)return 0;if(n%2==0)return n==2;
  ll d=n-1,s=0;while(d%2==0)d/=2,s++;
  for(ll a:{2,3,5,7,11,13,17}){if(a%n==0)continue;
    ll x=modPow(a,d,n);if(x==1||x==n-1)continue;bool ok=0;
    rep(r,0,s-1){x=modMul(x,x,n);if(x==n-1){ok=1;break;}}
    if(!ok)return 0;}
  return 1;}
ll pollardRho(ll n){
  if(n%2==0)return 2;if(n%3==0)return 3;
  mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
  while(1){ll c=uniform_int_distribution<ll>(1,n-1)(rng);
    auto f=[&](ll x){return(modMul(x,x,n)+c)%n;};
    ll x=2,y=2,d=1;while(d==1){x=f(x);y=f(f(y));d=__gcd(abs(x-y),n);}
    if(d!=n)return d;}}
void factor(ll n,vl&f){if(n==1)return;if(isPrime(n)){f.pb(n);return;}
  ll d=pollardRho(n);factor(d,f);factor(n/d,f);}
