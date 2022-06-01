struct TwoSat {
  vector<bool>vis;
  vector<vector<int>>adj, radj;
  vector<int>dfs_t, ord, par;
  int n, intime;//For n node there will be 2*n node in SAT.
  void init(int N) {
    n = N;
    intime = 0;
    vis.assign(N * 2 + 1, false);
    adj.assign(N * 2 + 1, vector<int>());
    radj.assign(N * 2 + 1, vector<int>());
    dfs_t.resize(N * 2 + 1);
    ord.resize(N * 2 + 1);
    par.resize(N * 2 + 1);
  }
  inline int neg(int x) {
    return x <= n ? x + n : x - n;
  }
  inline void add_implication(int a, int b) {
    if (a < 0) a = n - a;
    if (b < 0) b = n - b;
    adj[a].push_back(b);
    radj[b].push_back(a);
  }
  inline void add_or(int a, int b) {
    add_implication(-a, b);
    add_implication(-b, a);
  }
  inline void add_xor(int a, int b) {
    add_or(a, b);
    add_or(-a, -b);
  }
  inline void add_and(int a, int b) {
    add_or(a, b);
    add_or(a, -b);
    add_or(-a, b);
  }
  inline void force_true(int x) {
    if (x < 0) x = n - x;
    add_implication(neg(x), x);
  }
  inline void add_xnor(int a, int b) {
    add_or(a, -b);
    add_or(-a, b);
  }
  inline void add_nand(int a, int b) {
    add_or(-a, -b);
  }
  inline void add_nor(int a, int b) {
    add_and(-a, -b);
  }
  inline void force_false(int x) {
    if (x < 0) x = n - x;
    add_implication(x, neg(x));
  }
  inline void topsort(int u) {
    vis[u] = 1;
    for (int v : radj[u]) if (!vis[v]) topsort(v);
    dfs_t[u] = ++intime;
  }
  inline void dfs(int u, int p) {
    par[u] = p, vis[u] = 1;
    for (int v : adj[u]) if (!vis[v]) dfs(v, p);
  }
  void build() {
    int i, x;
    for (i = n * 2, intime = 0;i >= 1;i--) {
      if (!vis[i]) topsort(i);
      ord[dfs_t[i]] = i;
    }
    vis.assign(n * 2 + 1, 0);
    for (i = n * 2;i > 0;i--) {
      x = ord[i];
      if (!vis[x]) dfs(x, x);
    }
  }
  bool satisfy(vector<int>& ret)//ret contains the value that are true if the graph is satisfiable.
  {
    build();
    vis.assign(n * 2 + 1, 0);
    for (int i = 1; i <= n * 2; i++) {
      int x = ord[i];
      if (par[x] == par[neg(x)]) return 0;
      if (!vis[par[x]]) {
        vis[par[x]] = 1;
        vis[par[neg(x)]] = 0;
      }
    }
    for (int i = 1;i <= n;i++) if (vis[par[i]]) ret.push_back(i);
    return 1;
  }
};
