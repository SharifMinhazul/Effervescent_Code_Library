const int mxc = 26;
/*
  + link     - longest suffix belonging to another endpos-equivalent class.
  + len      - largest string length ending in current state.
  + firstPos - first occurance of substring ending at current state.
  + adj      - suffix link tree.
  + sz       - number of states.
  + occ      - number of times state occured in string.
  + dist     - number of distinct substring.
  + cnt & SA - for count sorting the nodes.
*/
struct SuffixAutomata{
  struct state{
    int link, len, firstPos;
    int next[mxc];
    bool is_clone;
    state(){}
    state(int l){
      len = l, link = -1;
      is_clone = false;
      for(int i=0;i<mxc;i++)next[i] = -1;
    }
  };
  vector<state>t;
  int sz, last;
  vector<ll>cnt,dist, occ,SA;
  vector<vector<int>> adj;
  SuffixAutomata(){
    t.pb(state(0));
    occ.pb(0);
    last = sz = 0;
  }
  int getID(char c){ return c - 'a';}
  void extend(char c){
    int idx = ++sz, p = last, id = getID(c);
    t.pb(state(t[last].len + 1));
    t[idx].firstPos = t[idx].len - 1;
    occ.pb(1);
    while(p!= -1 and t[p].next[id] == - 1){
      t[p].next[id] = idx;
      p = t[p].link;
    }
    if(p==-1) t[idx].link = 0;
    else{
      int q = t[p].next[id];
      if(t[p].len+1 == t[q].len) t[idx].link = q;
      else{
        int clone = ++sz;
        state x = t[q];
        x.len = t[p].len+1;
        t.pb(x);
        t[clone].firstPos = t[q].firstPos;
        t[clone].is_clone = true;
        occ.pb(0);
        while(p!=-1 and t[p].next[id]==q){
          t[p].next[id] = clone;
          p = t[p].link;
        }
        t[idx].link = t[q].link = clone;
      }
    }
    last = idx;
  }
  void build(string &s){
    for(char c:s) extend(c);
    cnt = dist = SA = vector<ll>(sz+1);
    adj.resize(sz+1);
    for(int i=0;i<=sz;i++)cnt[t[i].len]++;
    for(int i=1;i<=sz;i++)cnt[i]+=cnt[i-1];
    for(int i=0;i<=sz;i++) SA[--cnt[t[i].len]] = i;
    
    for(int i=sz;i>0;i--){
      int idx = SA[i];
      occ[t[idx].link]+=occ[idx];
      adj[t[idx].link].pb(idx);
      dist[idx] = 1;
      for(int j=0;j<mxc;j++){
        if(t[idx].next[j]+1){
          dist[idx]+=dist[t[idx].next[j]];
        }
      }
    }
    for(int i=0;i<mxc;i++){
      if(t[0].next[i]+1) dist[0]+=dist[t[0].next[i]];
    }
  }
  pair<int,int> LCS( string& s){
    int mxlen = 0, bestpos = -1, pos = 0,len = 0;
    int u = 0;
    for(char c:s){
      int v = getID(c);
      while( u and t[u].next[v]!=-1){
        u = t[u].link;
        len = t[u].len;
      }
      if(t[u].next[v]+1){
        len++;
        u = t[u].next[v];
      }
      if(len>mxlen){
        mxlen = len;
        bestpos = pos;
      }
      pos++;
    }
    return {bestpos - mxlen + 1, mxlen};
  }
  state &operator[](int index) { return t[index];}
};
