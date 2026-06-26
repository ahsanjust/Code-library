// T9j5 - Geometry Primitives [hash: t9j5]
using T = long double;
const T EPS = 1e-9;
int sgn(T x){return (x>EPS)-(x<-EPS);}
struct PT{T x,y;
  PT(T _x=0,T _y=0):x(_x),y(_y){}
  PT operator+(PT p)const{return{x+p.x,y+p.y};}
  PT operator-(PT p)const{return{x-p.x,y-p.y};}
  PT operator*(T d)const{return{x*d,y*d};}
  PT operator/(T d)const{return{x/d,y/d};}
  bool operator==(PT p)const{return !sgn(x-p.x)&&!sgn(y-p.y);}
  bool operator<(PT p)const{return sgn(x-p.x)?x<p.x:y<p.y;}
};
T dot(PT a,PT b){return a.x*b.x+a.y*b.y;}
T cross(PT a,PT b){return a.x*b.y-a.y*b.x;}
T cross2(PT a,PT b,PT c){return cross(b-a,c-a);}
T norm2(PT a){return dot(a,a);}
T norm(PT a){return sqrt(norm2(a));}
PT perp(PT a){return{-a.y,a.x};}
PT rotate(PT a,T ang){return{a.x*cos(ang)-a.y*sin(ang),a.x*sin(ang)+a.y*cos(ang)};}
// Line: cross(v,p)=c. Line(a,b): v=b-a, c=cross(v,a)
struct Line{PT v;T c;Line(PT a,PT b):v(b-a),c(cross(v,a)){}
  T side(PT p){return cross(v,p)-c;}
  T dist(PT p){return abs(side(p))/norm(v);}
  PT proj(PT p){return p-perp(v)*side(p)/norm2(v);}};
PT lineInter(PT a,PT b,PT c,PT d){return a+(b-a)*cross(c-a,d-c)/cross(b-a,d-c);}
bool onSeg(PT a,PT b,PT p){return !sgn(cross2(a,b,p))&&sgn(dot(p-a,p-b))<=0;}
T distToSeg(PT a,PT b,PT p){
  if(a==b)return norm(p-a);
  T t=dot(p-a,b-a)/norm2(b-a);
  if(t<0)return norm(p-a);if(t>1)return norm(p-b);
  return abs(cross2(a,b,p))/norm(b-a);
}
using Polygon = vector<PT>;
T area(Polygon&p){T r=0;rep(i,0,sz(p))r+=cross(p[i],p[(i+1)%sz(p)]);return abs(r)/2;}
int pointInPolygon(Polygon&p,PT q){
  int n=sz(p),wn=0;
  rep(i,0,n){
    if(onSeg(p[i],p[(i+1)%n],q))return 0;
    int k=sgn(cross2(p[i],p[(i+1)%n],q)),d1=sgn(p[i].y-q.y),d2=sgn(p[(i+1)%n].y-q.y);
    if(k>0&&d1<=0&&d2>0)wn++;if(k<0&&d2<=0&&d1>0)wn--;}
  return wn?-1:1;}
int pointInConvex(Polygon&p,PT q){
  int n=sz(p);
  if(sgn(cross2(p[0],p[1],q))<0)return 1;
  if(sgn(cross2(p[0],p[n-1],q))>0)return 1;
  int l=1,r=n-1;while(r-l>1){int m=(l+r)/2;if(sgn(cross2(p[0],p[m],q))>=0)l=m;else r=m;}
  int c=sgn(cross2(p[l],p[r],q));if(c<0)return 1;if(!c)return 0;return -1;}
Polygon convexHull(Polygon p){
  sort(all(p));p.erase(unique(all(p)),p.end());if(sz(p)<=1)return p;
  Polygon h;rep(_,0,2){int s=sz(h);for(auto&pt:p){
    while(sz(h)>=s+2&&sgn(cross2(h[sz(h)-2],h.back(),pt))<=0)h.pop_back();h.pb(pt);}
    h.pop_back();reverse(all(p));}return h;}
// Circle
struct Circle{PT c;T r;Circle(PT _c,T _r):c(_c),r(_r){}
  Circle(PT a,PT b,PT c){b=(a+b)*0.5;c=(a+c)*0.5;
    this->c=lineInter(b,b+perp(a-b),c,c+perp(a-c));r=norm(a-this->c);}};
vector<PT> circleLineInter(PT c,T r,PT a,PT b){
  PT p=c+perp(b-a)*dot(a-c,b-a)/norm2(b-a);T d2=norm2(p-c),h=sqrt(max((T)0,r*r-d2));
  if(!sgn(h))return{p};PT d=(b-a)/norm(b-a)*h;return{p-d,p+d};}
vector<PT> circleCircleInter(PT a,T r,PT b,T R){
  T d=norm(b-a);if(d>r+R+EPS||d<abs(r-R)-EPS)return{};
  T x=(d*d-R*R+r*r)/(2*d);T h=sqrt(max((T)0,r*r-x*x));PT v=(b-a)/d;
  PT p=a+v*x;if(!sgn(h))return{p};return{p+perp(v)*h,p-perp(v)*h};}
// Min Enclosing Circle O(n) expected
Circle minEnclosing(vector<PT>p){
  shuffle(all(p),mt19937(1337));Circle c(p[0],0);
  rep(i,1,sz(p))if(sgn(norm(p[i]-c.c)-c.r)>0){c={p[i],0};
    rep(j,0,i)if(sgn(norm(p[j]-c.c)-c.r)>0){c={(p[i]+p[j])/2,norm(p[i]-p[j])/2};
      rep(k,0,j)if(sgn(norm(p[k]-c.c)-c.r)>0)c=Circle(p[i],p[j],p[k]);}}
  return c;}
// Closest Pair O(n log n)
T closestPair(vector<PT>&p){
  sort(all(p),[](PT a,PT b){return a.x<b.x;});
  vector<PT>st(sz(p));
  function<T(int,int)>dc=[&](int l,int r)->T{
    if(r-l<=3){T b=LINF;rep(i,l,r)rep(j,i+1,r)b=min(b,norm2(p[i]-p[j]));return b;}
    int m=(l+r)/2;T midX=p[m].x,d=min(dc(l,m),dc(m,r));int k=0;
    rep(i,l,r)if(abs(p[i].x-midX)<d)st[k++]=p[i];
    sort(st.begin(),st.begin()+k,[](PT a,PT b){return a.y<b.y;});
    rep(i,0,k)rep(j,i+1,k){if(st[j].y-st[i].y>=d)break;d=min(d,norm2(st[i]-st[j]));}
    return d;};
  return sqrt(dc(0,sz(p)));}
