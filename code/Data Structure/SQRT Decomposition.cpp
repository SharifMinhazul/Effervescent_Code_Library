struct sqrtDecomposition {
  static const int sz = 320;//sz = sqrt(N);
  int numberofblocks;

  struct node {
    int L, R;
    bool islazy = false;	
    ll lazyval=0;
    //extra data needed for different problems
    void ini(int l, int r) {
      for(int i=l; i<=r; i++) {
        //...initialize as need 
      }
      L=l, R=r;
    }
    void semiupdate(int l, int r, ll val) {
      if(l>r) return;
      if(islazy){
        for(int i=L; i<=R; i++){
          //...distribute lazy to everyone
        }
        islazy = 0;
        lazyval = 0;
      }
      for(int i=l; i<=r; i++){
        //...do it manually
      }
    }
    void fullupdate(ll val){
      if(islazy){
        //...only update lazyval
      }
      else{
        for(int i=L; i<=R; i++){
          //...everyone are not equal, make them equal
        }
        islazy = 1;
        //update lazyval
      }
    }
    void update(int l, int r, ll val){
      if(l<=L && r>=R) fullupdate(val);
      else semiupdate(max(l, L), min(r, R), val);
    }
    ll semiquery(int l, int r){
      if(l>r) return 0;
      if(islazy){
        for(int i=L; i<=R; i++){
          //...distribute lazy to everyone
        }
        islazy = 0;
        lazyval = 0;
      }
      ll ret = 0;
      for(int i=l; i<=r; i++){
        //...take one by one
      }
      return ret;
    }
    ll fullquery(){
      //return stored value;
    }
    ll query(int l, int r){
      if(l<=L && r>=R) return fullquery();
      else return semiquery(max(l, L), min(r, R));
    }
  };
  vector<node> blocks;
  void init(int n){
    numberofblocks = (n+sz-1)/sz;
    int curL = 1, curR = sz;
    blocks.resize(numberofblocks+5);
    for(int i=1; i<=numberofblocks; i++){
      curR = min(n, curR);
      blocks[i].ini(curL, curR);
      curL += sz;
      curR += sz;
    }
  }
  void update(int l, int r, ll val){
    int left = (l-1)/sz+1;
    int right = (r-1)/sz+1;
    for(int i=left; i<=right; i++){
      blocks[i].update(l, r, val);
    }
  }
  ll query(int l, int r){
    int left = (l-1)/sz+1;
    int right = (r-1)/sz+1;
    ll ret = 0;
    for(int i=left; i<=right; i++){
      ret += blocks[i].query(l, r);
    }
    return ret;
  }
};
