// A4f3 - IUPC Template [hash: a4f3] - Common macros & typedefs
#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=(a);i<(b);++i)
#define per(i,a,b) for(int i=(b)-1;i>=(a);--i)
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
#define eb emplace_back
#define pb push_back
#define fi first
#define se second
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using vd = vector<long double>;
using vvd = vector<vd>;

const int INF = 1e9;
const ll LINF = 1e18;
const ld PI = acos(-1.0);
const ll MOD = 1000000007;

// For C++17: use std::gcd. For C++14: __gcd(a,b)
// PBDS: #include <ext/pb_ds/assoc_container.hpp>
// tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>
