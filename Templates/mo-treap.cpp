// H7d3 - Mo's Algorithm (offline range queries) [hash: h7d3]
// Implement add(idx)/remove(idx) and update curAns
struct Mo {
  int curL=0,curR=-1;ll curAns=0;vi a;
  Mo(vi&_a):a(_a){}
  void add(int i){/*TODO: add a[i]*/}
  void remove(int i){/*TODO: remove a[i]*/}
  vector<ll> query(vector<pii>& qs){
    int n=sz(a),q=sz(qs),B=max(1,(int)(n/sqrt(q)));
    vi ord(q);iota(all(ord),0);
    sort(all(ord),[&](int i,int j){
      int bi=qs[i].fi/B,bj=qs[j].fi/B;
      if(bi!=bj)return bi<bj;
      return(bi&1)?(qs[i].se>qs[j].se):(qs[i].se<qs[j].se);
    });
    vector<ll> ans(q);
    for(int i:ord){
      auto[l,r]=qs[i];
      while(curL>l)add(--curL);while(curR<r)add(++curR);
      while(curL<l)remove(curL++);while(curR>r)remove(curR--);
      ans[i]=curAns;
    }
    return ans;
  }
};

// I8e4 - Implicit Treap (randomized BST on array) [hash: i8e4]
struct Node{
  int pri,sz,val;ll sum;bool rev;Node *l,*r;
  Node(int v):pri(rand()),sz(1),val(v),sum(v),rev(0),l(0),r(0){}
};
int size(Node*t){return t?t->sz:0;}
ll sum(Node*t){return t?t->sum:0;}
void push(Node*t){if(!t||!t->rev)return;
  swap(t->l,t->r);if(t->l)t->l->rev^=1;if(t->r)t->r->rev^=1;t->rev=0;}
void pull(Node*t){if(!t)return;t->sz=1+size(t->l)+size(t->r);t->sum=t->val+sum(t->l)+sum(t->r);}
Node* merge(Node*l,Node*r){
  if(!l||!r)return l?l:r;
  if(l->pri>r->pri){push(l);l->r=merge(l->r,r);pull(l);return l;}
  else{push(r);r->l=merge(l,r->l);pull(r);return r;}
}
void split(Node*t,int k,Node*&l,Node*&r){
  if(!t){l=r=0;return;}push(t);
  if(size(t->l)>=k){split(t->l,k,l,t->l);r=t;pull(r);}
  else{split(t->r,k-size(t->l)-1,t->r,r);l=t;pull(l);}
}
