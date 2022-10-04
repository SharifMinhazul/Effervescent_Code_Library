struct Treap {
  struct Node {
    int val, priority, cnt;  // value, priority, subtree size
    Node* l, * r;             // left child,right child pointer
    Node() {} //rng from template
    Node(int key) : val(key), priority(rng()), l(nullptr), r(nullptr) {}
  };
  typedef Node* node;
  node root;
  Treap() : root(0) {}
  int cnt(node t) { return t ? t->cnt : 0; }  // return subtree size
  void updateCnt(node t) {
    if (t) t->cnt = 1 + cnt(t->l) + cnt(t->r);  // update subtree size
  }
  void push(node cur) {
    ;  // Lazy Propagation
  }

  void combine(node& cur, node l, node r) {
    if (!l) {
      cur = r;
      return;
    }
    if (!r) {
      cur = l;
      return;
    }
    // Merge Operations like in segment tree
  }

  void reset(node& cur) {
    if (!cur) return;  // To reset other fields of cur except value and cnt
  }

  void operation(node& cur) {
    if (!cur) return;
    reset(cur);
    combine(cur, cur->l, cur);
    combine(cur, cur, cur->r);
  }
  // Split(T,key): split the tree in two tree. Left pointer contains all value
  // less than or equal to key.Right pointer contains the rest.
  void split(node t, node& l, node& r, int key) {
    if (!t)
      return void(l = r = nullptr);
    push(t);
    if (t->val <= key) {
      split(t->r, t->r, r, key), l = t;

    }
    else {
      split(t->l, l, t->l, key), r = t;
    }
    updateCnt(t);
    operation(t);
  }
  void splitPos(node t, node& l, node& r, int k, int add = 0) {
    if (!t) return void(l = r = 0);
    push(t);
    int idx = add + cnt(t->l);
    if (idx <= k)
      splitPos(t->r, t->r, r, k, idx + 1), l = t;
    else
      splitPos(t->l, l, t->l, k, add), r = t;
    updateCnt(t);
    operation(t);
  }
  // Merge(T1,T2): merges 2 tree into one.The tree with root of higher
  // priority becomes the new root.
  void merge(node& t, node l, node r) {
    push(l);
    push(r);
    if (!l || !r)
      t = l ? l : r;
    else if (l->priority > r->priority)
      merge(l->r, l->r, r), t = l;
    else
      merge(r->l, l, r->l), t = r;
    updateCnt(t);
    operation(t);
  }

  node merge_treap(node l, node r) {
    if (!l) return r;
    if (!r) return l;
    if (l->priority < r->priority) swap(l, r);
    node L, R;
    split(r, L, R, l->val);
    l->r = merge_treap(l->r, R);
    l->l = merge_treap(L, l->l);
    updateCnt(l);
    operation(l);
    return l;
  }
  // insert creates a set.all unique value.
  void insert(int val) {
    if (!root) {
      root = new Node(val);
      return;
    }
    node l, r, mid, mid2, rr;
    mid = new Node(val);
    split(root, l, r, val);
    merge(l, l, mid);  // these 3 lines will create multiset.
    merge(root, l, r);
    /*split(root, l, r, val - 1);  // l contains all small values.
      merge(l, l, mid);            // l contains new val too.
      split(r, mid2, rr, val);     // rr contains all greater values.
      merge(root, l, rr);*/
  }
  // removes all similar values.
  void erase(int val) {
    node l, r, mid;
    /* Removes all similar element*/
    split(root, l, r, val - 1);
    split(r, mid, r, val);
    merge(root, l, r);
    /*Removes single instance*/
    /*split(root, l, r, val - 1);
      split(r, mid, r, val);
      merge(mid,mid->l,mid->r);
      merge(l, l, mid);
      merge(root, l, r);*/
  }
  void clear(node cur) {
    if (!cur) return;
    clear(cur->l), clear(cur->r);
    delete cur;
  }

  void clear() { clear(root); }
  void inorder(node t) {
    if (!t) return;
    inorder(t->l);
    cout << t->val << ' ';
    inorder(t->r);
  }
  void inorder() {
    inorder(root);
    puts("");
  }
  //1 indexed - xth element after sorting.
  int find_by_order(int x) {
    if (!x) return -1;
    x--;
    node l, r, mid;
    splitPos(root, l, r, x - 1);
    splitPos(r, mid, r, 0);
    int ans = -1;
    if (cnt(mid) == 1) ans = mid->val;
    merge(r, mid, r);
    merge(root, l, r);
  }
  // 1 indexed. index of val in sorted array. -1 if not found.
  int order_of_key(int val) {
    node l, r, mid;
    split(root, l, r, val - 1);
    split(r, mid, r, val);
    int ans = -1;
    if (cnt(mid) == 1) ans = 1 + cnt(l);
    merge(r, mid, r);
    merge(root, l, r);
    return ans;
  }
};

