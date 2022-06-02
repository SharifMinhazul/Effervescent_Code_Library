const int mxn     = 1e5+5; //CHECK here for every problem
int root[mxn], leftchild[25*mxn], rightchild[25*mxn], value[25*mxn], a[mxn];
int now = 0, n;

int build(int L, int R){
	int node = ++now;
	
	if(L == R){
		return node;
	}
	int mid = (L+R)>>1;
	leftchild[node] = build(L, mid);
	rightchild[node] = build(mid+1, R);
	//initialize value[node]
	return node;
}

int update(int nownode, int L, int R, int val){
	int node = ++now;
	if(L == R){
		//value[node] = value[nownode]+1;
		//update value[node]
		return node;
	}
	int mid = (L+R)>>1;
	leftchild[node] = leftchild[nownode];
	rightchild[node] = rightchild[nownode];
	
	if(mid <= val){//change condition as required
		leftchild[node] = update(leftchild[nownode], L, mid, val);
	}
	else{
		rightchild[node] = update(rightchild[nownode], mid+1, R, val);
	}
	//value[node] = value[nownode]+1;
	//update value[node]
	return node;
}

int query(int leftnode, int rightnode, int L, int R, int k){
	if(L==R) return L;
	//int leftcnt = value[leftchild[rightnode]]-value[leftchild[leftnode]];a
	//change as required
	int mid = (L+R)>>1;
	if(leftcnt >= k){//change condition as required
		return query(leftchild[leftnode], leftchild[rightnode], L, mid, k);
	}
	else{
		return query(rightchild[leftnode], rightchild[rightnode], mid+1, R, k-leftcnt);
	}
}

void persistentsegtree(){
	root[0] = build(0, mxn);
	for(int i=1; i<=n; i++){
		root[i] = update(root[i-1], 0, mxn, a[i]);
	}
}
